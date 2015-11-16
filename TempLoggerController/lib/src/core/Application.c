#include <core/Application.h>
#include <timer/Timer.h>
#include <display/Display.h>
#include <tempsensor/Sensor.h>
#include <alarm/Alarm.h>
#include <storage/Storage.h>
#include <serialcomm/Serial.h>

/*
 * Az esem�nykezel�k v�rakoz�si sor�nak deklar�l�sa �s inicializ�l�sa.
 */
volatile EventQueue eventQueue = { 0, 0, { 0 }};

/*
 * Inicializ�lja a mikrovez�rl� I/O portjait, a perif�ri�it �s az alkalmaz�st
 * a hozz� kapcsol�d� �sszes modullal egy�tt.
 */
void Application_initialize() {
  /* Minden I/O port standard jelv�ltoz�si sebess�g� digit�lis kimenetre
  konfigur�l�sa, �s a hozz�juk tartoz� t�rol�k t�rl�se. */
  TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
  ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
  SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
  
  /* Az A/D �talak�t�k �s a kompar�torok kikapcsol�sa. */
  ADCON0 = ADCON1 = ADCON2 = 0x00;
  C1ON_bit = C2ON_bit = false;

  /* Az alkalmaz�s moduljainak inicializ�l�sa. */
  Display_initialize();
  Alarm_initialize();
  Timer_initialize();
  Sensor_initialize(3.3f);
  Storage_initialize();
  Serial_initialize(BAUD_9600);
}

/*
 * Elhelyezi az �tadott esem�nykezel�re mutat� f�ggv�nypointert az
 * esem�nykezel�k v�rakoz�si sor�ban.
 */
void Application_dispatchEvent(EventHandler handler) {
  /* Az �tadott esem�nykezel�re mutat� f�ggv�nypointer hozz�ad�sa a v�rakoz�si
  sorhoz �s a sor utols� elem�re mutat� sz�ml�l� n�vel�se. */
  eventQueue.eventHandlers[eventQueue.end] = handler;
  eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
  
  /* A v�rakoz�si sorban lev� k�vetkez� esem�nykezel� kijel�l�se, amennyiben a
  v�rakoz�si sorban t�lcsordul�s keletkezett. (A legr�gebbi esem�ny el fog
  veszni.) */
  if(eventQueue.end == eventQueue.begin)
    eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
}

/*
 * V�grehajtja a soron k�vetkez� esem�nykezel�t az esem�nykezel�k v�rakoz�si
 * sor�b�l, amennyiben a sor nem �res.
 */
void Application_handleEvents() {
  /* Azonnali visszat�r�s a f�ggv�nyb�l, ha a v�rakoz�si sor �res. */
  if(eventQueue.begin == eventQueue.end) return;

  /* A soron k�vetkez� esem�nykezel� v�grehajt�sa, ha a r� mutat�
  f�ggv�nypointer �rt�ke nem nulla, �s a v�grehajt�st k�vet�en az
  esem�nykezel�re mutat� f�ggv�nypointer elt�vol�t�sa a v�rakoz�si sorb�l. */
  if(eventQueue.eventHandlers[eventQueue.begin]) {
    eventQueue.eventHandlers[eventQueue.begin]();
    eventQueue.eventHandlers[eventQueue.begin] = 0;
  }

  /* A v�rakoz�si sorban lev� k�vetkez� esem�nykezel� kijel�l�se. */
  eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
}

/*
 * Enged�lyezi a glob�lis megszak�t�sokat �s v�gtelen ciklusban v�grehajtja a
 * be�kez� esem�nykezel�ket.
 */
void Application_run() {
  /* A megszak�t�sok priorit�skezel�s�nek tilt�sa, majd a periferi�lis �s
  glob�lis megszak�t�sok enged�lyez�se. */
  IPEN_bit = false;
  PEIE_bit = GIE_bit = true;
  
  /* A be�rkezett esem�nykezel�k folyamatos v�grehajt�sa. */
  while(true) Application_handleEvents();
}

/*
 * Kezeli a be�ll�t�sok bet�lt�s�vel j�r� esem�nyt.
 */
void Storage_settingsLoadedEvent() {
  /* A bet�lt�tt be�ll�t�sok lek�rdez�se �s alkalmaz�sa. */
  StorableData* settings_ptr = Storage_getStoredSettings();
  Timer_setSystemTime(&settings_ptr->systemTime);
  Alarm_setThreshold(settings_ptr->threshold);
}

/*
 * Kezeli a m�sodpercenk�nt bek�vetkez� periodikus esem�nyt.
 */
void Timer_elapsedSecondEvent() {
  /* A pillanatnyi h�m�rs�klet lek�rdez�se a h�m�r�t�l. */
  float actual_temp = Sensor_getTemperature();
  
  /* Az aktu�lis d�tum �s id� lek�rdez�se az id�z�t�t�l karakterl�nc form�j�ban,
  majd a fogadott karakterl�nc sz�tv�laszt�sa d�tum �s az id� k�z�tti sz�k�z
  men�n. */
  char* date_str = Timer_timeToString(Timer_getSystemTime());
  char* time_str = strstr(date_str, " ");
  *time_str++ = '\0';
  
  /* A kor�bban lek�rdezett pillanatnyi h�m�rs�klet, d�tum �s id� megjelen�t�se
  kijelz�n. */
  Display_writeLine(1, "%a   [T]", date_str);
  Display_writeLine(2, "%a %2f%cC", time_str, actual_temp, 223);

  /* A riaszt�s bekapcsol�sa, amennyiben a pillanatnyi h�m�rs�klettel egy�tt a
  riaszt�s felt�telei teljes�ltek.*/
  Alarm_checkConditions(actual_temp);
}

/*
 * Kezeli a percenk�nt bek�vetkez� periodikus esem�nyt.
 */
void Timer_elapsedMinuteEvent() {
  /* �j napl�bejegyz�s �s az aktu�lis be�ll�t�sok bele�r�sa az EEPROM-ba. */
  Storage_writeLog(Timer_getSystemTime(), Sensor_getTemperature());
  Delay_ms(5);
  Storage_storeSettings(Timer_getSystemTime(), Alarm_getThreshold());
}

/*
 * Kezeli a riaszt�s felt�teleinek teljes�l�s�vel j�r� esem�nyt.
 */
void Alarm_thresholdExceededEvent() {
  /* A riaszt� �zenet ki�r�sa a kijelz�re �s a riaszt� hangjelz�s lej�tsz�sa. */
  Display_writeLine(1, "     ALARM!");
  Display_clearLine(2);
  Alarm_playAlarmSound();
}

/*
 * Kezeli az �j d�tum �s id� fogad�s�val j�r� esem�nyt.
 */
void Serial_receivedTimeSettingEvent() {
  /* Az �j d�tum �s id� be�ll�t�sa, �s a fogadott k�relem nyugt�z�sa. */
  Timer_setSystemTime((PICTime*)Serial_getReceivedData());
  Serial_sendAcknowledgement();
}

/*
 * Kezeli az �j riaszt�si k�sz�b�rt�k fogad�s�val j�r� esem�nyt.
 */
void Serial_receivedThresholdSettingEvent() {
  /* A riaszt�s �j k�sz�b�rt�knek be�ll�t�sa �s a fogadott k�relem
  nyugt�z�sa. */
  Alarm_setThreshold(*(float*)Serial_getReceivedData());
  Serial_sendAcknowledgement();
}

/*
 * Kezeli a napl�bejegyz�sek elk�ld�s�re vonatkoz� felsz�l�t�ssal j�r� esem�nyt.
 */
void Serial_receivedLogRequestEvent() {
  /* Minden egyes napl�bejegyz�s elk�ld�se a soros porton kereszt�l. */
  LogEntry* entry;
  while((entry = Storage_readEarliestLog()))
    Serial_sendLogEntry(entry);
  
  /* A fogadott k�relem nyugt�z�sa. */
  Serial_sendAcknowledgement();
}