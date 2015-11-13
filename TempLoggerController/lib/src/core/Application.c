#include <core/Application.h>
#include <timer/Timer.h>
#include <display/Display.h>

/*
 * Az eseménykezelõk várakozási sorának deklarálása és inicializálása.
 */
EventQueue eventQueue = { 0, 0, { 0 }};

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
  Timer_initialize();
  Display_initialize();
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
  if(eventQueue.end == eventQueue.next)
    eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
}

/*
 * Végrehajtja a soron következõ eseménykezelõt az eseménykezelõk várakozási
 * sorából, amennyiben a sor nem üres.
 */
void Application_handleEvents() {
  /* Azonnali visszatérés a függvénybõl, ha a várakozási sor üres. */
  if(eventQueue.next == eventQueue.end) return;

  /* A soron következõ eseménykezelõ végrehajtása, ha a rá mutató
  függvénypointer értéke nem nulla, és a végrehajtást követõen az
  eseménykezelõre mutató függvénypointer eltávolítása a várakozási sorból. */
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

/*
 * Kezeli a másodpercenként bekövetkezõ periodikus eseményt.
 */
void Timer_elapsedSecondEvent() {
  static int event_num = 0;
  char output[50];
  sprinti(output, "Second event: %d", event_num);
  Display_writeLine(1, output);
}

/*
 * Kezeli a percenként bekövetkezõ periodikus eseményt.
 */
void Timer_elapsedMinuteEvent() {
  static int event_num = 0;
  char output[50];
  sprinti(output, "Minute event: %d", event_num);
  Display_writeLine(2, output);
}