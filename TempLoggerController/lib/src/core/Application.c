#include <core/Application.h>
#include <timer/Timer.h>
#include <display/Display.h>
#include <tempsensor/Sensor.h>
#include <alarm/Alarm.h>
#include <storage/Storage.h>
#include <serialcomm/Serial.h>

/*
 * Az eseménykezelõk várakozási sorának deklarálása és inicializálása.
 */
volatile EventQueue eventQueue = { 0, 0, { 0 }};

/*
 * Inicializálja a mikrovezérlõ I/O portjait, a perifériáit és az alkalmazást
 * a hozzá kapcsolódó összes modullal együtt.
 */
void Application_initialize() {
  /* Minden I/O port standard jelváltozási sebességû digitális kimenetre
  konfigurálása, és a hozzájuk tartozó tárolók törlése. */
  TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
  ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
  SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
  
  /* Az A/D átalakítók és a komparátorok kikapcsolása. */
  ADCON0 = ADCON1 = ADCON2 = 0x00;
  C1ON_bit = C2ON_bit = false;

  /* Az alkalmazás moduljainak inicializálása. */
  Display_initialize();
  Alarm_initialize();
  Timer_initialize();
  Sensor_initialize(3.3f);
  Storage_initialize();
  Serial_initialize(BAUD_9600);
}

/*
 * Elhelyezi az átadott eseménykezelõre mutató függvénypointert az
 * eseménykezelõk várakozási sorában.
 */
void Application_dispatchEvent(EventHandler handler) {
  /* Az átadott eseménykezelõre mutató függvénypointer hozzáadása a várakozási
  sorhoz és a sor utolsó elemére mutató számláló növelése. */
  eventQueue.eventHandlers[eventQueue.end] = handler;
  eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
  
  /* A várakozási sorban levõ következõ eseménykezelõ kijelölése, amennyiben a
  várakozási sorban túlcsordulás keletkezett. (A legrégebbi esemény el fog
  veszni.) */
  if(eventQueue.end == eventQueue.begin)
    eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
}

/*
 * Végrehajtja a soron következõ eseménykezelõt az eseménykezelõk várakozási
 * sorából, amennyiben a sor nem üres.
 */
void Application_handleEvents() {
  /* Azonnali visszatérés a függvénybõl, ha a várakozási sor üres. */
  if(eventQueue.begin == eventQueue.end) return;

  /* A soron következõ eseménykezelõ végrehajtása, ha a rá mutató
  függvénypointer értéke nem nulla, és a végrehajtást követõen az
  eseménykezelõre mutató függvénypointer eltávolítása a várakozási sorból. */
  if(eventQueue.eventHandlers[eventQueue.begin]) {
    eventQueue.eventHandlers[eventQueue.begin]();
    eventQueue.eventHandlers[eventQueue.begin] = 0;
  }

  /* A várakozási sorban levõ következõ eseménykezelõ kijelölése. */
  eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
}

/*
 * Engedélyezi a globális megszakításokat és végtelen ciklusban végrehajtja a
 * beékezõ eseménykezelõket.
 */
void Application_run() {
  /* A megszakítások prioritáskezelésének tiltása, majd a periferiális és
  globális megszakítások engedélyezése. */
  IPEN_bit = false;
  PEIE_bit = GIE_bit = true;
  
  /* A beérkezett eseménykezelõk folyamatos végrehajtása. */
  while(true) Application_handleEvents();
}

/*
 * Kezeli a beállítások betöltésével járó eseményt.
 */
void Storage_settingsLoadedEvent() {
  /* A betöltött beállítások lekérdezése és alkalmazása. */
  StorableData* settings_ptr = Storage_getStoredSettings();
  Timer_setSystemTime(&settings_ptr->systemTime);
  Alarm_setThreshold(settings_ptr->threshold);
}

/*
 * Kezeli a másodpercenként bekövetkezõ periodikus eseményt.
 */
void Timer_elapsedSecondEvent() {
  /* A pillanatnyi hõmérséklet lekérdezése a hõmérõtõl. */
  float actual_temp = Sensor_getTemperature();
  
  /* Az aktuális dátum és idõ lekérdezése az idõzítõtõl karakterlánc formájában,
  majd a fogadott karakterlánc szétválasztása dátum és az idõ közötti szóköz
  menén. */
  char* date_str = Timer_timeToString(Timer_getSystemTime());
  char* time_str = strstr(date_str, " ");
  *time_str++ = '\0';
  
  /* A korábban lekérdezett pillanatnyi hõmérséklet, dátum és idõ megjelenítése
  kijelzõn. */
  Display_writeLine(1, "%a   [T]", date_str);
  Display_writeLine(2, "%a %2f%cC", time_str, actual_temp, 223);

  /* A riasztás bekapcsolása, amennyiben a pillanatnyi hõmérséklettel együtt a
  riasztás feltételei teljesültek.*/
  Alarm_checkConditions(actual_temp);
}

/*
 * Kezeli a percenként bekövetkezõ periodikus eseményt.
 */
void Timer_elapsedMinuteEvent() {
  /* Új naplóbejegyzés és az aktuális beállítások beleírása az EEPROM-ba. */
  Storage_writeLog(Timer_getSystemTime(), Sensor_getTemperature());
  Delay_ms(5);
  Storage_storeSettings(Timer_getSystemTime(), Alarm_getThreshold());
}

/*
 * Kezeli a riasztás feltételeinek teljesülésével járó eseményt.
 */
void Alarm_thresholdExceededEvent() {
  /* A riasztó üzenet kiírása a kijelzõre és a riasztó hangjelzés lejátszása. */
  Display_writeLine(1, "     ALARM!");
  Display_clearLine(2);
  Alarm_playAlarmSound();
}

/*
 * Kezeli az új dátum és idõ fogadásával járó eseményt.
 */
void Serial_receivedTimeSettingEvent() {
  /* Az új dátum és idõ beállítása, és a fogadott kérelem nyugtázása. */
  Timer_setSystemTime((PICTime*)Serial_getReceivedData());
  Serial_sendAcknowledgement();
}

/*
 * Kezeli az új riasztási küszöbérték fogadásával járó eseményt.
 */
void Serial_receivedThresholdSettingEvent() {
  /* A riasztás új küszöbértéknek beállítása és a fogadott kérelem
  nyugtázása. */
  Alarm_setThreshold(*(float*)Serial_getReceivedData());
  Serial_sendAcknowledgement();
}

/*
 * Kezeli a naplóbejegyzések elküldésére vonatkozó felszólítással járó eseményt.
 */
void Serial_receivedLogRequestEvent() {
  /* Minden egyes naplóbejegyzés elküldése a soros porton keresztül. */
  LogEntry* entry;
  while((entry = Storage_readEarliestLog()))
    Serial_sendLogEntry(entry);
  
  /* A fogadott kérelem nyugtázása. */
  Serial_sendAcknowledgement();
}