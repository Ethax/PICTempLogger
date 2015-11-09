#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <common.h>

/**
 * @breif Beállítja a Timer0 idõzítõt egymásodperces túlcsordulás-periódusra, és
 * engedélyezi a Timer0 megszakítást az idõzítõ túlcsordulására.
 */
void Timer_initialize();

/**
 * @brief Kezeli az idõzítõ túlcsordulásakor bekövetkezett megszakítást és törli
 * a megszakítás jelzõbitjét.
 *
 * Annak érdekében, hogy a megszakítás le legyen kezelve annak bekövetkezésekor,
 * ennek a függvénynek megszakításokat kiszolgáló rutinban kell lennie.
 */
void Timer_handleInterrupt();

/*
  struct Time
  getTime, setTime, timeToString
*/

extern void Timer_elapsedSecondEvent();
extern void Timer_elapsedMinuteEvent();

#endif /* INC_TIMER_H_ */