#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <common.h>

/**
 * @breif Be�ll�tja a Timer0 id�z�t�t egym�sodperces t�lcsordul�s-peri�dusra, �s
 * enged�lyezi a Timer0 megszak�t�st az id�z�t� t�lcsordul�s�ra.
 */
void Timer_initialize();

/**
 * @brief Kezeli az id�z�t� t�lcsordul�sakor bek�vetkezett megszak�t�st �s t�rli
 * a megszak�t�s jelz�bitj�t.
 *
 * Annak �rdek�ben, hogy a megszak�t�s le legyen kezelve annak bek�vetkez�sekor,
 * ennek a f�ggv�nynek megszak�t�sokat kiszolg�l� rutinban kell lennie.
 */
void Timer_handleInterrupt();

/*
  struct Time
  getTime, setTime, timeToString
*/

extern void Timer_elapsedSecondEvent();
extern void Timer_elapsedMinuteEvent();

#endif /* INC_TIMER_H_ */