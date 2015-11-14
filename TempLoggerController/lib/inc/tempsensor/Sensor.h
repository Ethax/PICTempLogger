#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include <common.h>

/**
 * @brief Inicializálja a mikrovezérlõ A/D átalakítóját és beállítja az RE1
 * kivezetést (6-os számú A/D csatorna) analóg bemenetté.
 *
 * @param _vref Az A/D átalakító referenciafeszültsége (alapértelmezetten a
 * mikrovezérlõ táplálása) Voltokban megadva.
 */
void Sensor_initialize(const float _vref);

/**
 * @brief Megméri a hõmérsékletet a mikrovezérlõre kapcsolt hõmérséklet érzékelõ
 * segítségével és visszaadja annak érékét.
 *
 * A PIC18F45K22 A/D átalakítója 10-bites, azaz a referenciafeszültséget 1024
 * részre osztja, így az A/D átalakítótól származó minta alapján a mért
 * feszültség valódi értéke a következõképpen számítható:
 * V[mV] = AD[sample] * Vref[mV] / 1024[steps]
 * Az LM35 kimenete közel lineáris módon Celsuis fokonként 10mV jelet ad ki,
 * vagyis a hõmérséklet ezek alapján:
 * T[°C] = V[mV] / 10.
 *
 * @return A mért hõmérséklet Celsuis fokokban.
 */
float Sensor_getTemperature();

#endif /* INC_SENSOR_H_ */