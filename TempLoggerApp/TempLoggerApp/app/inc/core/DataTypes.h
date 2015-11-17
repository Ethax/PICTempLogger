#ifndef INC_DATATYPES_H_
#define INC_DATATYPES_H_

#include <app/inc/common.h>

/**
 * @class FloatUtils
 * @brief A Microchip AN575 és az IEEE 754 típusú 32-bites
 * lebegõpontos számok közötti konverziós megvalósító segédosztály
 */
class FloatUtils {
public:
	/**
	 * @brief Átalakítja az IEEE 754 típusú 32-bites lebegõpontos számot
	 * a Microchip AN575 típusú lebegõpontos szám bájtjait tároló tömbbé.
	 *
	 * @param _IEEE754 Az IEEE 754 típusú 32-bites lebegõpontos szám.
	 * @return A Microchip AN575 típusú lebegõpontos szám bájtjait
	 * tároló tömbre mutató pointer.
	 */
	static unsigned char* convertIEEE754ToMicrochip(float _IEEE754);

	/**
	 * @brief Átalakítja a Microchip AN575 típusú 32-bites lebegõpontos
	 * szám bájtjait tároló tömböt IEEE 754 típusú lebegõpontos számmá.
	 *
	 * @param _Microchip A Microchip AN575 típusú lebegõpontos szám
	 * bájtjait tároló tömbre mutató pointer.
	 * @return Az IEEE 754 típusú 32-bites lebegõpontos szám.
	 */
	static float convertMicrochipToIEEE754(const unsigned char* _Microchip);
};

/**
 * @struct PICTime
 * @brief A mikrovezérlõ által számolt dátum és idõ adatszerkezete.
 *
 * Ez az adatszerkezet biztosítja azt, hogy a mikrovezérlõ által számolt
 * dátum és idõ fogadható és értelmezhetõ legyen a PC-n.
 */
struct PICTime {
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

	/**
	 * @brief A struktúra alapértelmezett konstruktora, amelyik
	 * feltölti a létrehozott objektumot az aktuális dátummal és idõvel.
	 */
	PICTime();

	/**
	 * @brief Átalakítja a példányosított objektumot bájtok láncává.
	 *
	 * @return Az objektum méretével és tartalmával megegyezõ méretû
	 * bájt-tömb.
	 */
	unsigned char* serialize();

	/**
	 * @brief Megjeleníthetõ sztringgé alakítja az objektum adattagjainak
	 * értékeit a következõ formátumnak megfelelõen: ÉÉÉÉ-HH-NN ÓÓ:PP:MM.
	 *
	 * @return A sztringgé alakított objektum.
	 */
	std::string print() const;
};

/**
 * @struct LogEntry
 * @brief A naplóbejegyzések adatszerkezete.
 *
 * Ez az adatszerkezet a mért hõmérséklet idõbélyegezett naplózását teszi
 * áttekinthetõbbé azáltal, hogy egyetlen adatszerkezetbe tömöríti a
 * naplózott mennyiséget és a mérés idõpontját.
 */
struct LogEntry {
	/**
	 * A bejegyzés létrehozásának idõpontját tároló adatszerkezet.
	 */
	PICTime timeStamp;

	/**
	 * A bejegyzett adatot tároló tömb.
	 */
	unsigned char value[4];

	/**
	 * @brief Ráírja az objektum adattagjainak sztringekké alakított
	 * formáját az átadott kimenõ adatfolyamra.
	 *
	 * @param os A kimenõ adatfolyamra mutató referencia.
	 * @param entry Egy LogEntry típusú objektumra mutató konstans
	 * referencia.
	 * @return Az átalakíott értékekkel terhelt adatfolyamra mutató
	 * referencia.
	 */
	friend std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
		return os << "[" << entry.timeStamp.print() << "] " << FloatUtils::convertMicrochipToIEEE754(entry.value) << "\xC2\xB0""C";
	}
};

#endif /* INC_DATATYPES_H_ */