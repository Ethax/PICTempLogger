#ifndef INC_EXTERNAL_EEPROM_H_
#define INC_EXTERNAL_EEPROM_H_

#include <common.h>

/**
 * @brief Az I2C buszra kapcsolt 24Cxx EEPROM chip azonosítója.
 */
#define EEPROM_FIXED_ID 0xA0

/**
 * Az I2C busz kommunikációs üzemmódjainak felsorolása.
 */
enum CommunicationType { I2C_WRITE, I2C_READ };

/**
 * @brief Letárolja az EEPROM chip fizikai címét és inicializálja az I2C
 * kommunikációt 100kHz-es órajellel.
 *
 * Az EEPROM chippel való kommunikáció megkezdéséhez a kommunikáció fajtáját
 * (írás vagy olvasás) meghatározó utasításnak tartalmaznia kell a chip
 * azonosítóját, a fizikai címét és kommunikáció típusát jelölõ bitet a
 * következõ formában: IIIIAAAC.
 *
 * @param i2c_address Az EEPROM chip fizikai címe.
 */
void ExternalEEPROM_initialize(uint8_t i2c_address);

/**
 * @brief Beleír egy egybájtos adatot a külsõ EEPROM megcímzett
 * memóriacellájába.
 *
 * @param address Az írni kívánt memóriacella címe.
 * @param _data A megcímzett memóriacellába írni kívánt adat.
 */
void ExternalEEPROM_write(uint8_t address, uint8_t _data);

/**
 * @brief Kiolvas egy egybájtos adatot a külsõ EEPROM megcímzett
 * memóriacellájából.
 *
 * @param address Az olvasni kívánt memóriacella címe.
 * @return A megcímzett memóriacella tartalma.
 */
uint8_t ExternalEEPROM_read(uint8_t address);

/**
 * @brief Beleírja az mutatott memóriaterületet a külsõ EEPROM megcímzett
 * "sorába" és kiszámítja a beleírt adat ellenõrzõ összegét.
 *
 * Az írás csak akkor hajtható végre, ha a címzett terület az EEPROM valamelyik
 * "sorának" a kezdetére mutat (a cím alsó négy bitje nulla) és a beleírni
 * kívánt memóriaterület mérete nem nagyobb, mint 16 bájt. Ebben az írási
 * üzemmódban a címnek csak az alsó négy bitje növekszik az EEPROM belsejében.
 *
 * @param address Az írni kívánt "sor" kezdõcíme.
 * @param _data Az EEPROM-ba beleírni kívánt memóriaterületre mutató pointer.
 * @param length Az EEPROM-ba beleírni kívánt memóriaterület hossza.
 * @return A mutatott memóriaterületet ellenõrzõ összege.
 */
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length);

/**
 * @brief Kiolvassa a megadott hosszúságú bájtsorozatot a külsõ EEPROM
 * megcímzett memóriacellájától kezdõdõen és beleírja a mutatott
 * megmóriaterületbe.
 *
 * Bájtsorozatok kiolvasásakor az olvasás bármelyik címen kezdõdhet és a
 * hosszára vonatkozóan sincs semmilyen korlátozás.
 *
 * @param address Az olvasni kívánt bájtsorozat kezdõcíme.
 * @param _data A kiolvasás eredményének tárolására szánt memóriaterületre
 * mutató pointer.
 * @param length Az EEPROM-ból kiolvasni kívánt memóriaterület hossza.
 * @return A mutatott memóriaterületet ellenõrzõ összege.
 */
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length);

#endif /* INC_EXTERNAL_EEPROM_H_ */