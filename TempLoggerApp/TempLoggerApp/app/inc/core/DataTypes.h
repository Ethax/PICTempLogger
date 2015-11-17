#ifndef INC_DATATYPES_H_
#define INC_DATATYPES_H_

#include <app/inc/common.h>

/**
 * @class FloatUtils
 * @brief A Microchip AN575 �s az IEEE 754 t�pus� 32-bites
 * lebeg�pontos sz�mok k�z�tti konverzi�s megval�s�t� seg�doszt�ly
 */
class FloatUtils {
public:
	/**
	 * @brief �talak�tja az IEEE 754 t�pus� 32-bites lebeg�pontos sz�mot
	 * a Microchip AN575 t�pus� lebeg�pontos sz�m b�jtjait t�rol� t�mbb�.
	 *
	 * @param _IEEE754 Az IEEE 754 t�pus� 32-bites lebeg�pontos sz�m.
	 * @return A Microchip AN575 t�pus� lebeg�pontos sz�m b�jtjait
	 * t�rol� t�mbre mutat� pointer.
	 */
	static unsigned char* convertIEEE754ToMicrochip(float _IEEE754);

	/**
	 * @brief �talak�tja a Microchip AN575 t�pus� 32-bites lebeg�pontos
	 * sz�m b�jtjait t�rol� t�mb�t IEEE 754 t�pus� lebeg�pontos sz�mm�.
	 *
	 * @param _Microchip A Microchip AN575 t�pus� lebeg�pontos sz�m
	 * b�jtjait t�rol� t�mbre mutat� pointer.
	 * @return Az IEEE 754 t�pus� 32-bites lebeg�pontos sz�m.
	 */
	static float convertMicrochipToIEEE754(const unsigned char* _Microchip);
};

/**
 * @struct PICTime
 * @brief A mikrovez�rl� �ltal sz�molt d�tum �s id� adatszerkezete.
 *
 * Ez az adatszerkezet biztos�tja azt, hogy a mikrovez�rl� �ltal sz�molt
 * d�tum �s id� fogadhat� �s �rtelmezhet� legyen a PC-n.
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

	/**
	 * @brief A strukt�ra alap�rtelmezett konstruktora, amelyik
	 * felt�lti a l�trehozott objektumot az aktu�lis d�tummal �s id�vel.
	 */
	PICTime();

	/**
	 * @brief �talak�tja a p�ld�nyos�tott objektumot b�jtok l�nc�v�.
	 *
	 * @return Az objektum m�ret�vel �s tartalm�val megegyez� m�ret�
	 * b�jt-t�mb.
	 */
	unsigned char* serialize();

	/**
	 * @brief Megjelen�thet� sztringg� alak�tja az objektum adattagjainak
	 * �rt�keit a k�vetkez� form�tumnak megfelel�en: ����-HH-NN ��:PP:MM.
	 *
	 * @return A sztringg� alak�tott objektum.
	 */
	std::string print() const;
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
	 * A bejegyzett adatot t�rol� t�mb.
	 */
	unsigned char value[4];

	/**
	 * @brief R��rja az objektum adattagjainak sztringekk� alak�tott
	 * form�j�t az �tadott kimen� adatfolyamra.
	 *
	 * @param os A kimen� adatfolyamra mutat� referencia.
	 * @param entry Egy LogEntry t�pus� objektumra mutat� konstans
	 * referencia.
	 * @return Az �talak�ott �rt�kekkel terhelt adatfolyamra mutat�
	 * referencia.
	 */
	friend std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
		return os << "[" << entry.timeStamp.print() << "] " << FloatUtils::convertMicrochipToIEEE754(entry.value) << "\xC2\xB0""C";
	}
};

#endif /* INC_DATATYPES_H_ */