#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>

/**
 * A k�ls� eszk�z�k huzaloz�sainak be�ll�t�sa.
 */
// TODO: LCD, h�m�r�, stb. huzaloz�sainak be�ll�t�s.

/**
 * @brief A magas priorit�s� megszak�t�sokat kiszolg�l� rutin.
 *
 * Amennyiben a priorit�skezel�s nincs enged�lyezve, minden megszak�t�s ide fut
 * be.
 */
void interrupt() {
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program fut�s�nak kezd�pontja.
 */
void main() {
     // Application_initialize();
     // Application_run();
     return;
}