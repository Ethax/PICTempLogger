#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include <common.h>

/**
 * @brief Inicializálja a riasztó modult az RC2-es kivezetésre és lead egy egy
 * másodpercig tartó 880Hz-es hangjelzést az inicializáció végeztével.
 */
void Alarm_initialize();

/**
 * @brief Beállítja a riasztás küszöbértékét, és egyúttal engedélyezi a
 * riasztást.
 *
 * @param _threshold A riasztás küszöbértéke Celsuis fokokban.
 */
void Alarm_setThreshold(float _threshold);

/**
 * @brief Törli a riasztás küszöbértékét, és egyúttal letiltja a riasztást.
 */
void Alarm_clearThreshold();

/**
 * @brief Ellenõrzi a riasztás feltételeit és IGAZ értékkel tér vissza, ha a
 * feltételek alapján meg kell kezdeni a riasztást.
 *
 * A riasztáshoz három feltétel kell, hogy teljesüljön: a riasztásnak
 * engedélyezettnek kell lennie, a mért hõmérsékletnek meg kell haladnia a
 * beállított küszöböt és a korábbi riasztás óta a hõmérsékletnek legalább
 * egyszer a küszöb alá kellett esnie.
 *
 * @param _temperature A mért hõmérséklet Celsuis fokokban.
 * @return Ha a riasztás feltételei teljesültek, akkor IGAZ, egyébként HAMIS.
 */
bool Alarm_checkConditions(float _temperature);

/**
 * @brief Lejátssza a riasztó hangjelzést.
 */
void Alarm_playAlarmSound();

#endif /* INC_ALARM_H_ */