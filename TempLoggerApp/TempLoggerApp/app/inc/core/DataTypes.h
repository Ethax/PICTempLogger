#ifndef INC_DATATYPES_H_
#define INC_DATATYPES_H_

#include <app/inc/common.h>

/**
* @struct PICTime
* @brief A mikrovez�rl� �ltal sz�molt d�tum �s id� adatszerkezete.
*
* Ez az adatszerkezet biztos�tja azt, hogy a mikrovez�rl� �ltal sz�molt d�tum
* �s id� b�rmelyik id�egys�ge azonnal hozz�f�rhet� legyen �tsz�m�t�sok n�lk�l.
* A megfelel� m�k�d�s�hez a Timer modul megszak�t�skezel�j�nek �sszehangoltan
* kell m�dos�tania az adatszerkezet minden elem�t.
*/
struct PICTime {
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
* @brief A napl�bejegyz�sek adatszerkezete.
*
* Ez az adatszerkezet a m�rt h�m�rs�klet id�b�lyegezett napl�z�s�t teszi
* �ttekinthet�bb� az�ltal, hogy egyetlen adatszerkezetbe t�m�r�ti a
* napl�zott mennyis�get �s a m�r�s id�pontj�t.
*/
struct LogEntry {
	/**
	* A bejegyz�s l�trehoz�s�nak id�pontj�t t�rol� adatszerkezet.
	*/
	PICTime timeStamp;

	/**
	* A bejegyzett adatot t�rol� v�ltoz�.
	*/
	float value;

	friend std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
		return os << "[" << entry.timeStamp.print() << "] ";// << entry.value << "\xC2\xB0""C";
	}
};

#endif /* INC_DATATYPES_H_ */