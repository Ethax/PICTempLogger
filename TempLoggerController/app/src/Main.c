#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>

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
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program futásának kezdõpontja.
 */
void main() {
     // Application_initialize();
     // Application_run();
     return;
}