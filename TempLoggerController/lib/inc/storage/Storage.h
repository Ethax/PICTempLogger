#ifndef INC_STORAGE_H_
#define INC_STORAGE_H_

#include <common.h>
#include <timer/Timer.h>

/**
 * @brief A naplóba bejegyezhetõ sorok maximális száma. (Legfeljebb 15 lehet.)
 */
#define LOG_SIZE 15

/**
 * @typedef StorableData
 * @brief A külsõ EEPROM-ban eltárolható beállítások adatszerkezete.
 *
 * Annak köszönhetõen, hogy a 24Cxx típusú EEPROM chip képes az I2C kommunikáció
 * egyszeri kiépítésével a memória valamely "sorának" folyamatos írására
 * (legfeljebb 16 bájtig), ez az adatszerkezet lehetõséget biztosít a legfõbb
 * beállítások egyetlen 8-bites pointerrel történõ bejárására és folyamatos
 * beleírásába az EEPROM-ba.
 */
typedef struct storable_data_t {
  /**
   * A rendszeridõ másolatát tároló adatszerkezet.
   */
  PICTime systemTime;
  
  /**
   * A riasztás küszöbértékének másolatát tároló változó.
   */
  float threshold;
  
  /**
   * Az elsõ naplóbejegyzés "sorának" címe a külsõ EEPROM-ban.
   */
  uint8_t logBegin;
  
  /**
   * Az utolsó naplóbejegyzés "sorának" címe a külsõ EEPROM-ban.
   */
  uint8_t logEnd;
} StorableData;

/**
 * @typedef LogEntry
 * @brief A naplóbejegyzések adatszerkezete.
 *
 * Ez az adatszerkezet a mért hõmérséklet idõbélyegezett naplózását teszi
 * áttekinthetõbbé azáltal, hogy egyetlen adatszerkezetbe tömöríti a
 * naplózott mennyiséget és a mérés idõpontját.
 */
typedef struct log_t {
  /**
   * A bejegyzés létrehozásának idõpontját tároló adatszerkezet.
   */
  PICTime timeStamp;
  
  /**
   * A bejegyzett adatot tároló változó.
   */
  float value;
} LogEntry;

/**
 * @brief Inicializálja az I2C kommunikációt a külsõ EEPROM chippel és betölti a
 * legutóbb letárolt beállításokat.
 *
 * Ha a beállításokon végzett CRC sikeres volt, akkor végrehajtja az új
 * beállítások betöltésének eseménykezelõjét.
 */
void Storage_initialize();

/**
 * @brief Alaphelyzetbe állítja a naplóbejegyzések számlálóit.
 *
 * FIGYELEM: Ennek hatására az összes beírt naplóbejegyzés elveszik.
 */
void Storage_resetLogCounter();

/**
 * @brief Betölti a beállításokat a külsõ EEPROM-ból és visszaadja a betöltött
 * beállításokra mutató pointert.
 *
 * @return A CRC-tõl függõen a betöltött beállításokra mutató ponter vagy NULL.
 */
StorableData* Storage_getStoredSettings();

/**
 * @brief Lementi az aktuális beállításokat a külsõ EEPROM-ba és azok ellenõrzõ
 * összegét.
 *
 * @param _systemTime Az aktuális rendszeridõ adatszerkezetére mutató pointer.
 * @param _threshold A riasztás aktuális küszöbértéke.
 */
void Storage_storeSettings(PICTime* _systemTime, float _threshold);

/**
 * @brief Új naplóbejegyzést ír a külsõ EEPROM-ba.
 *
 * @param timeStamp Az aktuális rendszeridõ adatszerkezetére mutató pointer.
 * @param value A mért hõmérséklet Celsuis fokokban.
 */
void Storage_writeLog(PICTime* timeStamp, float value);

/**
 * @brief Beolvassa a legkorábbi naplóbejegyzést a külsõ EEPROM-ból és
 * visszaadja a beolvasott adatszerkezetre mutató pointert.
 *
 * A beolvasást követõen automatikusan növeli a legkorábbi bejegyzésre mutató
 * számlálót, így a következõ meghívásakor már a soron következõ bejegyzést adja
 * vissza.
 *
 * @return Az utolsó naplóbejegyzés beolvasásáig a beolvasott adatszerkezetre
 * mutató pointer, azt követõen NULL.
 */
LogEntry* Storage_readEarliestLog();

/**
 * @brief A korábban letárolt beállítások beolvasását követõen végrehajtásra
 * kerülõ eseménykezelõ deklarációja. (Az eseménykezelõ törzsét definiálni
 * kell.)
 */
extern void Storage_settingsLoadedEvent();

/**
 * @brief Az elsõ indításkor, vagy az EEPROM chip cseréjét követõen
 * végrehajtásra kerülõ eseménykezelõ deklarációja. (Az eseménykezelõ törzsét
 * definiálni kell.)
 */
extern void Storage_firstBootEvent();

#endif /* INC_STORAGE_H_ */