#include <timer/Timer.h>

/*
 * Be�ll�tja a Timer0 id�z�t�t egym�sodperces t�lcsordul�s-peri�dusra, �s
 * enged�lyezi a Timer0 megszak�t�st az id�z�t� t�lcsordul�s�ra.
 */
void Timer_initialize() {
  /* El�oszt� be�ll�t�sa 1:32-re, el�t�lt�s be�ll�t�sa 3036-ra. (A v�rhat�
  t�lcsordul�s-peri�dus: 1s.) */
  T0CON = 0x84;
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * Kezeli az id�z�t� t�lcsordul�sakor bek�vetkezett megszak�t�st �s t�rli  a
 * megszak�t�s jelz�bitj�t.
 */
void Timer_handleInterrupt() {
  // TODO: id� n�vel�se, esem�nykezel�re mutat� pointer elhelyez�se a v�rakoz�s sorban
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IF_bit = false;
}