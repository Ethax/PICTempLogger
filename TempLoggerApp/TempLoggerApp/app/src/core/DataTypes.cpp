#include <app/inc/core/DataTypes.h>

/*
 * �talak�tja az IEEE 754 t�pus� 32-bites lebeg�pontos sz�mot a
 * Microchip AN575 t�pus� lebeg�pontos sz�m b�jtjait t�rol� t�mbb�.
 */
unsigned char* FloatUtils::convertIEEE754ToMicrochip(float _IEEE754) {
	static unsigned char Microchip[4];
	memcpy(Microchip, &_IEEE754, 4);

	/* Az IEEE-754 el�jel�nek lek�rdez�se (az 31. biten helyezkedik
	el) �s a legnagyobb hely�rt�k� b�jt eltol�sa egy bittel balra. */
	unsigned char sign_bit = Microchip[3] & 0x80;
	Microchip[3] *= 2;

	/* A 24. bit logikai egyesre �ll�t�sa, amennyiben a 23. bit
	�rt�ke logikai egyes. */
	if(Microchip[2] & 0x80) {
		Microchip[3] |= 0x01;
		Microchip[2] &= 0x7F;
	};

	/* A 23. bitlogikai egyesre �ll�t�sa, a mennyiben az IEEE-754
	el�jelbitj�nek �rt�ke logikai egyes volt, majd az �talak�tott
	�rt�kre mutat� pointer visszaad�sa. */
	if(sign_bit)
		Microchip[2] |= 0x80;
	return Microchip;
}

/*
 * �talak�tja a Microchip AN575 t�pus� 32-bites lebeg�pontos sz�m
 * b�jtjait t�rol� t�mb�t IEEE 754 t�pus� lebeg�pontos sz�mm�.
 */
float FloatUtils::convertMicrochipToIEEE754(const unsigned char* _Microchip) {
	static float IEEE754;
	static unsigned char Microchip[4];
	memcpy(Microchip, _Microchip, 4);

	/* A Microchip el�jel�nek lek�rdez�se (az 23. biten helyezkedik
	el) �s a 23. bit logikai null�ra �ll�t�sa. */
	unsigned char sign_bit = Microchip[2] & 0x80;
	Microchip[2] &= 0x7F;

	/* A 23. bit logikai egyesre �ll�t�sa, amennyiben a 24. bit
	�rt�ke logikai egyes, majd a legnagyobb hely�rt�k� b�jt eltol�sa
	egy bittel jobbra. */
	if(Microchip[3] & 0x01)
		Microchip[2] |= 0x80;
	Microchip[3] /= 2;

	/* A 31. bitlogikai egyesre �ll�t�sa, a mennyiben a Microchip
	el�jelbitj�nek �rt�ke logikai egyes volt, majd az �talak�tott
	�rt�k visszaad�sa. */
	if(sign_bit)
		Microchip[3] |= 0x80;
	memcpy(&IEEE754, Microchip, 4);
	return IEEE754;
}

/*
 * A strukt�ra alap�rtelmezett konstruktora, amelyik felt�lti a
 * l�trehozott objektumot az aktu�lis d�tummal �s id�vel.
 */
PICTime::PICTime() {
	/* A rendszer aktu�lis id�pillanat�nak lek�rdez�se �s
	�talak�t�sa a helyi id�nek megfelel� adatszerkezett�. */
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* now_tm = std::localtime(&now);

	/* Az objektum adattagjainak felt�lt�se az aktu�lis helyi id�
	�rt�keivel. */
	second = (uint8_t)now_tm->tm_sec;
	minute = (uint8_t)now_tm->tm_min;
	hour = (uint8_t)now_tm->tm_hour;
	day = (uint8_t)now_tm->tm_mday;
	month = (uint8_t)now_tm->tm_mon + 1;
	year = (uint8_t)now_tm->tm_year;
}

/*
 * �talak�tja a p�ld�nyos�tott objektumot b�jtok l�nc�v�.
 */
unsigned char* PICTime::serialize() {
	static unsigned char serialized[10];
	std::memcpy(serialized, this, sizeof(PICTime));
	return serialized;
}

/*
 * Megjelen�thet� sztringg� alak�tja az objektum adattagjainak �rt�keit
 * a k�vetkez� form�tumnak megfelel�en: ����-HH-NN ��:PP:MM.
 */
std::string PICTime::print() const {
	std::tm timeinfo;
	char buffer[80];

	/* A objektum adattagjai �ltal t�rol �rt�kek �tm�sol�sa a
	szabv�nyos d�tum-�s-id� adatszerkezetbe. */
	timeinfo.tm_sec = second;
	timeinfo.tm_min = minute;
	timeinfo.tm_hour = hour;
	timeinfo.tm_mday = day;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_year = year;

	/* A szabv�nyos d�tum-�s-id� adatszerkezet �talak�t�sa karakterl�ncc�
	a megadott form�tumnak megfelel�en, majd a karaterl�nccal
	p�ld�nyos�tott sztring visszaad�sa. */
	std::strftime(buffer, 20, "%F %T", &timeinfo);
	return std::string(buffer);
}