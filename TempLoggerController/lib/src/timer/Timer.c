#include <timer/Timer.h>

/*
 * Beállítja a Timer0 idõzítõt egymásodperces túlcsordulás-periódusra, és
 * engedélyezi a Timer0 megszakítást az idõzítõ túlcsordulására.
 */
void Timer_initialize() {
  /* Elõosztó beállítása 1:32-re, elõtöltés beállítása 3036-ra. (A várható
  túlcsordulás-periódus: 1s.) */
  T0CON = 0x84;
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * Kezeli az idõzítõ túlcsordulásakor bekövetkezett megszakítást és törli  a
 * megszakítás jelzõbitjét.
 */
void Timer_handleInterrupt() {
  // TODO: idõ növelése, eseménykezelõre mutató pointer elhelyezése a várakozás sorban
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IF_bit = false;
}