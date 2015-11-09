#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>
#include <core/Application.h>

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
  /* A TIMER0 t�lcsordul�s�ra bek�vetkezett megszak�t�s kezel�se. */
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  /* Az UART fogad� puffer�be �rkezett adat hat�s�ra bek�vetkezett megszak�t�s
  kezel�se. */
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program fut�s�nak kezd�pontja.
 */
void main() {
  /* Az alkalmaz�s inicializ�l�sa �s futtat�sa. */
  Application_initialize();
  Application_run();
}