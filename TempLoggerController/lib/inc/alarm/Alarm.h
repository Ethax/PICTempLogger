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
 * @brief T�rli a riaszt�s k�sz�b�rt�k�t, �s egy�ttal letiltja a riaszt�st.
 */
void Alarm_clearThreshold();

/**
 * @brief Ellen�rzi a riaszt�s felt�teleit �s IGAZ �rt�kkel t�r vissza, ha a
 * felt�telek alapj�n meg kell kezdeni a riaszt�st.
 *
 * A riaszt�shoz h�rom felt�tel kell, hogy teljes�lj�n: a riaszt�snak
 * enged�lyezettnek kell lennie, a m�rt h�m�rs�kletnek meg kell haladnia a
 * be�ll�tott k�sz�b�t �s a kor�bbi riaszt�s �ta a h�m�rs�kletnek legal�bb
 * egyszer a k�sz�b al� kellett esnie.
 *
 * @param _temperature A m�rt h�m�rs�klet Celsuis fokokban.
 * @return Ha a riaszt�s felt�telei teljes�ltek, akkor IGAZ, egy�bk�nt HAMIS.
 */
bool Alarm_checkConditions(float _temperature);

/**
 * @brief Lej�tssza a riaszt� hangjelz�st.
 */
void Alarm_playAlarmSound();

#endif /* INC_ALARM_H_ */