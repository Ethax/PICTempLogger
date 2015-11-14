#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include <common.h>

/**
 * @brief Inicializ�lja a mikrovez�rl� A/D �talak�t�j�t �s be�ll�tja az RE1
 * kivezet�st (6-os sz�m� A/D csatorna) anal�g bemenett�.
 *
 * @param _vref Az A/D �talak�t� referenciafesz�lts�ge (alap�rtelmezetten a
 * mikrovez�rl� t�pl�l�sa) Voltokban megadva.
 */
void Sensor_initialize(const float _vref);

/**
 * @brief Megm�ri a h�m�rs�kletet a mikrovez�rl�re kapcsolt h�m�rs�klet �rz�kel�
 * seg�ts�g�vel �s visszaadja annak �r�k�t.
 *
 * A PIC18F45K22 A/D �talak�t�ja 10-bites, azaz a referenciafesz�lts�get 1024
 * r�szre osztja, �gy az A/D �talak�t�t�l sz�rmaz� minta alapj�n a m�rt
 * fesz�lts�g val�di �rt�ke a k�vetkez�k�ppen sz�m�that�:
 * V[mV] = AD[sample] * Vref[mV] / 1024[steps]
 * Az LM35 kimenete k�zel line�ris m�don Celsuis fokonk�nt 10mV jelet ad ki,
 * vagyis a h�m�rs�klet ezek alapj�n:
 * T[�C] = V[mV] / 10.
 *
 * @return A m�rt h�m�rs�klet Celsuis fokokban.
 */
float Sensor_getTemperature();

#endif /* INC_SENSOR_H_ */