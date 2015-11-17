#include <app/inc/core/DataTypes.h>

/*
 * Átalakítja az IEEE 754 típusú 32-bites lebegõpontos számot a
 * Microchip AN575 típusú lebegõpontos szám bájtjait tároló tömbbé.
 */
unsigned char* FloatUtils::convertIEEE754ToMicrochip(float _IEEE754) {
	static unsigned char Microchip[4];
	memcpy(Microchip, &_IEEE754, 4);

	/* Az IEEE-754 elõjelének lekérdezése (az 31. biten helyezkedik
	el) és a legnagyobb helyértékû bájt eltolása egy bittel balra. */
	unsigned char sign_bit = Microchip[3] & 0x80;
	Microchip[3] *= 2;

	/* A 24. bit logikai egyesre állítása, amennyiben a 23. bit
	értéke logikai egyes. */
	if(Microchip[2] & 0x80) {
		Microchip[3] |= 0x01;
		Microchip[2] &= 0x7F;
	};

	/* A 23. bitlogikai egyesre állítása, a mennyiben az IEEE-754
	elõjelbitjének értéke logikai egyes volt, majd az átalakított
	értékre mutató pointer visszaadása. */
	if(sign_bit)
		Microchip[2] |= 0x80;
	return Microchip;
}

/*
 * Átalakítja a Microchip AN575 típusú 32-bites lebegõpontos szám
 * bájtjait tároló tömböt IEEE 754 típusú lebegõpontos számmá.
 */
float FloatUtils::convertMicrochipToIEEE754(const unsigned char* _Microchip) {
	static float IEEE754;
	static unsigned char Microchip[4];
	memcpy(Microchip, _Microchip, 4);

	/* A Microchip elõjelének lekérdezése (az 23. biten helyezkedik
	el) és a 23. bit logikai nullára állítása. */
	unsigned char sign_bit = Microchip[2] & 0x80;
	Microchip[2] &= 0x7F;

	/* A 23. bit logikai egyesre állítása, amennyiben a 24. bit
	értéke logikai egyes, majd a legnagyobb helyértékû bájt eltolása
	egy bittel jobbra. */
	if(Microchip[3] & 0x01)
		Microchip[2] |= 0x80;
	Microchip[3] /= 2;

	/* A 31. bitlogikai egyesre állítása, a mennyiben a Microchip
	elõjelbitjének értéke logikai egyes volt, majd az átalakított
	érték visszaadása. */
	if(sign_bit)
		Microchip[3] |= 0x80;
	memcpy(&IEEE754, Microchip, 4);
	return IEEE754;
}

/*
 * A struktúra alapértelmezett konstruktora, amelyik feltölti a
 * létrehozott objektumot az aktuális dátummal és idõvel.
 */
PICTime::PICTime() {
	/* A rendszer aktuális idõpillanatának lekérdezése és
	átalakítása a helyi idõnek megfelelõ adatszerkezetté. */
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* now_tm = std::localtime(&now);

	/* Az objektum adattagjainak feltöltése az aktuális helyi idõ
	értékeivel. */
	second = (uint8_t)now_tm->tm_sec;
	minute = (uint8_t)now_tm->tm_min;
	hour = (uint8_t)now_tm->tm_hour;
	day = (uint8_t)now_tm->tm_mday;
	month = (uint8_t)now_tm->tm_mon + 1;
	year = (uint8_t)now_tm->tm_year;
}

/*
 * Átalakítja a példányosított objektumot bájtok láncává.
 */
unsigned char* PICTime::serialize() {
	static unsigned char serialized[10];
	std::memcpy(serialized, this, sizeof(PICTime));
	return serialized;
}

/*
 * Megjeleníthetõ sztringgé alakítja az objektum adattagjainak értékeit
 * a következõ formátumnak megfelelõen: ÉÉÉÉ-HH-NN ÓÓ:PP:MM.
 */
std::string PICTime::print() const {
	std::tm timeinfo;
	char buffer[80];

	/* A objektum adattagjai által tárol értékek átmásolása a
	szabványos dátum-és-idõ adatszerkezetbe. */
	timeinfo.tm_sec = second;
	timeinfo.tm_min = minute;
	timeinfo.tm_hour = hour;
	timeinfo.tm_mday = day;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_year = year;

	/* A szabványos dátum-és-idõ adatszerkezet átalakítása karakterlánccá
	a megadott formátumnak megfelelõen, majd a karaterlánccal
	példányosított sztring visszaadása. */
	std::strftime(buffer, 20, "%F %T", &timeinfo);
	return std::string(buffer);
}