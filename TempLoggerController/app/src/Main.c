#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>
#include <core/Application.h>

/**
 * A külsõ eszközök huzalozásainak beállítása.
 */
// TODO: LCD, hõmérõ, stb. huzalozásainak beállítás.

/**
 * @brief A magas prioritású megszakításokat kiszolgáló rutin.
 *
 * Amennyiben a prioritáskezelés nincs engedélyezve, minden megszakítás ide fut
 * be.
 */
void interrupt() {
  /* A TIMER0 túlcsordulására bekövetkezett megszakítás kezelése. */
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  /* Az UART fogadó pufferébe érkezett adat hatására bekövetkezett megszakítás
  kezelése. */
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program futásának kezdõpontja.
 */
void main() {
  /* Az alkalmazás inicializálása és futtatása. */
  Application_initialize();
  Application_run();
}