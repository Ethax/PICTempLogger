#include <core/Application.h>
#include <timer/Timer.h>
#include <display/Display.h>
#include <tempsensor/Sensor.h>
#include <alarm/Alarm.h>

/*
 * Az esem�nykezel�k v�rakoz�si sor�nak deklar�l�sa �s inicializ�l�sa.
 */
EventQueue eventQueue = { 0, 0, { 0 }};

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
  
  Alarm_setThreshold(40.0);
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
  if(eventQueue.end == eventQueue.next)
    eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
}

/*
 * V�grehajtja a soron k�vetkez� esem�nykezel�t az esem�nykezel�k v�rakoz�si
 * sor�b�l, amennyiben a sor nem �res.
 */
void Application_handleEvents() {
  /* Azonnali visszat�r�s a f�ggv�nyb�l, ha a v�rakoz�si sor �res. */
  if(eventQueue.next == eventQueue.end) return;

  /* A soron k�vetkez� esem�nykezel� v�grehajt�sa, ha a r� mutat�
  f�ggv�nypointer �rt�ke nem nulla, �s a v�grehajt�st k�vet�en az
  esem�nykezel�re mutat� f�ggv�nypointer elt�vol�t�sa a v�rakoz�si sorb�l. */
  if(eventQueue.eventHandlers[eventQueue.next]) {
    eventQueue.eventHandlers[eventQueue.next]();
    eventQueue.eventHandlers[eventQueue.next] = 0;
  }

  /* A v�rakoz�si sorban lev� k�vetkez� esem�nykezel� kijel�l�se. */
  eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
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
  if(Alarm_checkConditions(actual_temp)) {
    Display_writeLine(1, "     ALARM!");
    Display_clearLine(2);
    Alarm_playAlarmSound();
  }
}

/*
 * Kezeli a percenk�nt bek�vetkez� periodikus esem�nyt.
 */
void Timer_elapsedMinuteEvent() {

}