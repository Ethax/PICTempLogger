#include <core/Application.h>
#include <timer/Timer.h>

/*
 * Az esem�nykezel�k v�rakoz�si sor�nak deklar�l�sa �s inicializ�l�sa.
 */
struct EventQueue eventQueue = { 0, 0, { 0 }};

/*
 * Inicializ�lja a mikrovez�rl� I/O portjait, a perif�ri�it �s az alkalmaz�st
 * a hozz� kapcsol�d� �sszes modullal egy�tt.
 */
void Application_initialize() {
  /* Minden I/O port kimenetre konfigur�l�sa �s a hozz�juk tartoz� t�rol�k
  t�rl�se. */
  TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
  LATA = LATB = LATC = LATD = LATE = 0x00;
  
  /* Az A/D �talak�t�k �s a kompar�torok kikapcsol�sa. */
  ADCON0 = ADCON1 = ADCON2 = 0x00;
  C1ON_bit = C2ON_bit = false;
  
  /* Az alkalmaz�s moduljainak inicializ�l�sa. */
}

/*
 * Elhelyezi az �tadott esem�nykezel�re mutat� f�ggv�nypointert az
 * esem�nykezel�k v�rakoz�si sor�ban.
 */
void Application_dispatchEvent(EventHandler handler) {
  eventQueue.eventHandlers[eventQueue.end] = handler;
  eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
}

/*
 * V�grehajtja a soron k�vetkez� esem�nykezel�t az esem�nykezel�k v�rakoz�si
 * sor�b�l, amennyiben a sor nem �res.
 */
void Application_handleEvents() {
  /* Azonnali visszat�r�s a f�ggv�nyb�l, ha a v�rakoz�si sor �res. */
  if(eventQueue.next == eventQueue.end) return;

  /* A soron k�vetkez� esem�nykezel� v�grehajt�sa, ha a r� mutat�
  f�ggv�nypointer �rt�ke nem nulla, majd az esem�nykezel�re mutat�
  f�ggv�nypointer t�rl�se. */
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

void Timer_elapsedSecondEvent() {

}

void Timer_elapsedMinuteEvent() {

}