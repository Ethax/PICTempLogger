#include <core/Application.h>
#include <timer/Timer.h>

/*
 * Az eseménykezelõk várakozási sorának deklarálása és inicializálása.
 */
struct EventQueue eventQueue = { 0, 0, { 0 }};

/*
 * Inicializálja a mikrovezérlõ I/O portjait, a perifériáit és az alkalmazást
 * a hozzá kapcsolódó összes modullal együtt.
 */
void Application_initialize() {
  /* Minden I/O port kimenetre konfigurálása és a hozzájuk tartozó tárolók
  törlése. */
  TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
  LATA = LATB = LATC = LATD = LATE = 0x00;
  
  /* Az A/D átalakítók és a komparátorok kikapcsolása. */
  ADCON0 = ADCON1 = ADCON2 = 0x00;
  C1ON_bit = C2ON_bit = false;
  
  /* Az alkalmazás moduljainak inicializálása. */
}

/*
 * Elhelyezi az átadott eseménykezelõre mutató függvénypointert az
 * eseménykezelõk várakozási sorában.
 */
void Application_dispatchEvent(EventHandler handler) {
  eventQueue.eventHandlers[eventQueue.end] = handler;
  eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
}

/*
 * Végrehajtja a soron következõ eseménykezelõt az eseménykezelõk várakozási
 * sorából, amennyiben a sor nem üres.
 */
void Application_handleEvents() {
  /* Azonnali visszatérés a függvénybõl, ha a várakozási sor üres. */
  if(eventQueue.next == eventQueue.end) return;

  /* A soron következõ eseménykezelõ végrehajtása, ha a rá mutató
  függvénypointer értéke nem nulla, majd az eseménykezelõre mutató
  függvénypointer törlése. */
  if(eventQueue.eventHandlers[eventQueue.next]) {
    eventQueue.eventHandlers[eventQueue.next]();
    eventQueue.eventHandlers[eventQueue.next] = 0;
  }

  /* A várakozási sorban levõ következõ eseménykezelõ kijelölése. */
  eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
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

void Timer_elapsedSecondEvent() {

}

void Timer_elapsedMinuteEvent() {

}