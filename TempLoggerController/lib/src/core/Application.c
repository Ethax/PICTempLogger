#include <core/Application.h>
#include <timer/Timer.h>
#include <display/Display.h>

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
  Timer_initialize();
  Display_initialize();
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
  static int event_num = 0;
  char output[50];
  sprinti(output, "Second event: %d", event_num);
  Display_writeLine(1, output);
}

/*
 * Kezeli a percenk�nt bek�vetkez� periodikus esem�nyt.
 */
void Timer_elapsedMinuteEvent() {
  static int event_num = 0;
  char output[50];
  sprinti(output, "Minute event: %d", event_num);
  Display_writeLine(2, output);
}