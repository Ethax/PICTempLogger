#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include <common.h>

/**
 * @brief Inicializ�lja a riaszt� modult az RC2-es kivezet�sre �s lead egy egy
 * m�sodpercig tart� 880Hz-es hangjelz�st az inicializ�ci� v�gezt�vel.
 */
void Alarm_initialize();

/**
 * @brief Be�ll�tja a riaszt�s k�sz�b�rt�k�t, �s egy�ttal enged�lyezi a
 * riaszt�st.
 *
 * @param _threshold A riaszt�s k�sz�b�rt�ke Celsuis fokokban.
 */
void Alarm_setThreshold(float _threshold);

/**
 * @brief Visszaadja a riaszt�s k�sz�b�rt�k�t.
 *
 * @return A riaszt�s k�sz�b�rt�ke Celsuis fokokban.
 */
float Alarm_getThreshold();

/**
 * @brief T�rli a riaszt�s k�sz�b�rt�k�t, �s egy�ttal letiltja a riaszt�st.
 */
void Alarm_clearThreshold();

/**
 * @brief Ellen�rzi a riaszt�s felt�teleit �s v�grehajtja a riaszt�s
 * esem�nykezel�j�t, ha a felt�telek alapj�n meg kell kezdeni a riaszt�st.
 *
 * A riaszt�shoz h�rom felt�tel kell, hogy teljes�lj�n: a riaszt�snak
 * enged�lyezettnek kell lennie, a m�rt h�m�rs�kletnek meg kell haladnia a
 * be�ll�tott k�sz�b�t �s a kor�bbi riaszt�s �ta a h�m�rs�kletnek legal�bb
 * egyszer a k�sz�b al� kellett esnie.
 *
 * @param _temperature A m�rt h�m�rs�klet Celsuis fokokban.
 */
void Alarm_checkConditions(float _temperature);

/**
 * @brief Lej�tssza a riaszt� hangjelz�st.
 */
void Alarm_playAlarmSound();

/**
 * @brief Lead egy egy m�sodpercig tart� 880Hz-es hangjelz�st.
 */
void Alarm_beep();

/**
 * @brief A riaszt�s felt�teleinek teljes�l�sekor v�grehajt�sra ker�l�
 * esem�nykezel� deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Alarm_thresholdExceededEvent();

#endif /* INC_ALARM_H_ */