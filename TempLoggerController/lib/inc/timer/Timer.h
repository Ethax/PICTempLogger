#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <common.h>

/**
 * @typedef PICTime
 * @brief A mikrovezérlõ által számolt dátum és idõ adatszerkezete.
 *
 * Ez az adatszerkezet biztosítja azt, hogy a mikrovezérlõ által számolt dátum
 * és idõ bármelyik idõegysége azonnal hozzáférhetõ legyen átszámítások nélkül.
 * A megfelelõ mûködéséhez a Timer modul megszakításkezelõjének összehangoltan
 * kell módosítania az adatszerkezet minden elemét.
 */
typedef struct pic_time_t {
  /**
   * Az eltelt perc utáni másodpercek száma.
   */
  uint8_t second;
  
  /**
   * Az eltelt óra utáni percek száma.
   */
  uint8_t minute;
  
  /**
   * Éjfél óta eltelt órák száma.
   */
  uint8_t hour;
  
  /**
   * Az adott hónap napja.
   */
  uint8_t day;
  
  /**
   * Az adott év hónapja.
   */
  uint8_t month;
  
  /**
   * 1900 óta eltelt évek száma.
   */
  uint8_t year;
} PICTime;

/**
 * @breif Beállítja a Timer0 idõzítõt egymásodperces túlcsordulás-periódusra
 * 8MHz-es órajel mellett, és engedélyezi a Timer0 megszakítást az idõzítõ
 * túlcsordulására.
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

/**
 * @brief Visszaadja az aktuális dátumot és idõt.
 *
 * @return A rendszeridõ adatszerkezetére mutató pointer.
 */
PICTime* getSystemTime();

/**
 * @brief Beállítja az új dátumot és idõt.
 *
 * @param time_ptr A beállítani kívánt dátum és idõ adatszerkezetére mutató
 * pointer.
 */
void setSystemTime(PICTime* time_ptr);

/**
 * @brief Átalakítja az átadott dátum és idõ adatszerkezetet megjeleníthetõ
 * karakterlánccá a következõ séma szerint: ÉÉÉÉ-HH-NN ÓÓ:PP:MM
 *
 * @param Az átalakítani kívánt adatszerkezet.
 * @return A karakterlánccá átalakított adatszerkezet.
 */
char* timeToString(PICTime* time_ptr);

/**
 * @brief A másodpercenként bekövetkezõ periodikus esemény eseménykezelõjének
 * deklarációja. (Az eseménykezelõ törzsét definiálni kell.)
 */
extern void Timer_elapsedSecondEvent();

/**
 * @brief A percenként bekövetkezõ periodikus esemény eseménykezelõjének
 * deklarációja. (Az eseménykezelõ törzsét definiálni kell.)
 */
extern void Timer_elapsedMinuteEvent();

#endif /* INC_TIMER_H_ */