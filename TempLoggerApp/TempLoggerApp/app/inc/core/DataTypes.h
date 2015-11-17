#ifndef INC_DATATYPES_H_
#define INC_DATATYPES_H_

#include <app/inc/common.h>

/**
* @struct PICTime
* @brief A mikrovezérlõ által számolt dátum és idõ adatszerkezete.
*
* Ez az adatszerkezet biztosítja azt, hogy a mikrovezérlõ által számolt dátum
* és idõ bármelyik idõegysége azonnal hozzáférhetõ legyen átszámítások nélkül.
* A megfelelõ mûködéséhez a Timer modul megszakításkezelõjének összehangoltan
* kell módosítania az adatszerkezet minden elemét.
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

	PICTime() {
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm* now_tm = std::localtime(&now);

		second = (uint8_t)now_tm->tm_sec;
		minute = (uint8_t)now_tm->tm_min;
		hour = (uint8_t)now_tm->tm_hour;

		day = (uint8_t)now_tm->tm_mday;
		month = (uint8_t)now_tm->tm_mon + 1;
		year = (uint8_t)now_tm->tm_year;
	}

	unsigned char* serialize() {
		static unsigned char serialized[10];
		std::memcpy(serialized, this, sizeof(PICTime));
		return serialized;
	}

	std::string print() const {
		std::tm timeinfo;
		char buffer[80];

		timeinfo.tm_sec = second;
		timeinfo.tm_min = minute;
		timeinfo.tm_hour = hour;

		timeinfo.tm_mday = day;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_year = year;

		std::strftime(buffer, 20, "%F %T", &timeinfo);

		return std::string(buffer);
	}
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
	* A bejegyzett adatot tároló változó.
	*/
	float value;

	friend std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
		return os << "[" << entry.timeStamp.print() << "] ";// << entry.value << "\xC2\xB0""C";
	}
};

#endif /* INC_DATATYPES_H_ */