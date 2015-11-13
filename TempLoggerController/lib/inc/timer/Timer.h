#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <common.h>

/**
 * @typedef PICTime
 * @brief A mikrovez�rl� �ltal sz�molt d�tum �s id� adatszerkezete.
 *
 * Ez az adatszerkezet biztos�tja azt, hogy a mikrovez�rl� �ltal sz�molt d�tum
 * �s id� b�rmelyik id�egys�ge azonnal hozz�f�rhet� legyen �tsz�m�t�sok n�lk�l.
 * A megfelel� m�k�d�s�hez a Timer modul megszak�t�skezel�j�nek �sszehangoltan
 * kell m�dos�tania az adatszerkezet minden elem�t.
 */
typedef struct pic_time_t {
  /**
   * Az eltelt perc ut�ni m�sodpercek sz�ma.
   */
  uint8_t second;
  
  /**
   * Az eltelt �ra ut�ni percek sz�ma.
   */
  uint8_t minute;
  
  /**
   * �jf�l �ta eltelt �r�k sz�ma.
   */
  uint8_t hour;
  
  /**
   * Az adott h�nap napja.
   */
  uint8_t day;
  
  /**
   * Az adott �v h�napja.
   */
  uint8_t month;
  
  /**
   * 1900 �ta eltelt �vek sz�ma.
   */
  uint8_t year;
} PICTime;

/**
 * @breif Be�ll�tja a Timer0 id�z�t�t egym�sodperces t�lcsordul�s-peri�dusra
 * 8MHz-es �rajel mellett, �s enged�lyezi a Timer0 megszak�t�st az id�z�t�
 * t�lcsordul�s�ra.
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

/**
 * @brief Visszaadja az aktu�lis d�tumot �s id�t.
 *
 * @return A rendszerid� adatszerkezet�re mutat� pointer.
 */
PICTime* getSystemTime();

/**
 * @brief Be�ll�tja az �j d�tumot �s id�t.
 *
 * @param time_ptr A be�ll�tani k�v�nt d�tum �s id� adatszerkezet�re mutat�
 * pointer.
 */
void setSystemTime(PICTime* time_ptr);

/**
 * @brief �talak�tja az �tadott d�tum �s id� adatszerkezetet megjelen�thet�
 * karakterl�ncc� a k�vetkez� s�ma szerint: ����-HH-NN ��:PP:MM
 *
 * @param Az �talak�tani k�v�nt adatszerkezet.
 * @return A karakterl�ncc� �talak�tott adatszerkezet.
 */
char* timeToString(PICTime* time_ptr);

/**
 * @brief A m�sodpercenk�nt bek�vetkez� periodikus esem�ny esem�nykezel�j�nek
 * deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Timer_elapsedSecondEvent();

/**
 * @brief A percenk�nt bek�vetkez� periodikus esem�ny esem�nykezel�j�nek
 * deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Timer_elapsedMinuteEvent();

#endif /* INC_TIMER_H_ */