#ifndef INC_EXTERNAL_EEPROM_H_
#define INC_EXTERNAL_EEPROM_H_

#include <common.h>

/**
 * @brief Az I2C buszra kapcsolt 24Cxx EEPROM chip azonos�t�ja.
 */
#define EEPROM_FIXED_ID 0xA0

/**
 * Az I2C busz kommunik�ci�s �zemm�djainak felsorol�sa.
 */
enum CommunicationType { I2C_WRITE, I2C_READ };

/**
 * @brief Let�rolja az EEPROM chip fizikai c�m�t �s inicializ�lja az I2C
 * kommunik�ci�t 100kHz-es �rajellel.
 *
 * Az EEPROM chippel val� kommunik�ci� megkezd�s�hez a kommunik�ci� fajt�j�t
 * (�r�s vagy olvas�s) meghat�roz� utas�t�snak tartalmaznia kell a chip
 * azonos�t�j�t, a fizikai c�m�t �s kommunik�ci� t�pus�t jel�l� bitet a
 * k�vetkez� form�ban: IIIIAAAC.
 *
 * @param i2c_address Az EEPROM chip fizikai c�me.
 */
void ExternalEEPROM_initialize(uint8_t i2c_address);

/**
 * @brief Bele�r egy egyb�jtos adatot a k�ls� EEPROM megc�mzett
 * mem�riacell�j�ba.
 *
 * @param address Az �rni k�v�nt mem�riacella c�me.
 * @param _data A megc�mzett mem�riacell�ba �rni k�v�nt adat.
 */
void ExternalEEPROM_write(uint8_t address, uint8_t _data);

/**
 * @brief Kiolvas egy egyb�jtos adatot a k�ls� EEPROM megc�mzett
 * mem�riacell�j�b�l.
 *
 * @param address Az olvasni k�v�nt mem�riacella c�me.
 * @return A megc�mzett mem�riacella tartalma.
 */
uint8_t ExternalEEPROM_read(uint8_t address);

/**
 * @brief Bele�rja az mutatott mem�riater�letet a k�ls� EEPROM megc�mzett
 * "sor�ba" �s kisz�m�tja a bele�rt adat ellen�rz� �sszeg�t.
 *
 * Az �r�s csak akkor hajthat� v�gre, ha a c�mzett ter�let az EEPROM valamelyik
 * "sor�nak" a kezdet�re mutat (a c�m als� n�gy bitje nulla) �s a bele�rni
 * k�v�nt mem�riater�let m�rete nem nagyobb, mint 16 b�jt. Ebben az �r�si
 * �zemm�dban a c�mnek csak az als� n�gy bitje n�vekszik az EEPROM belsej�ben.
 *
 * @param address Az �rni k�v�nt "sor" kezd�c�me.
 * @param _data Az EEPROM-ba bele�rni k�v�nt mem�riater�letre mutat� pointer.
 * @param length Az EEPROM-ba bele�rni k�v�nt mem�riater�let hossza.
 * @return A mutatott mem�riater�letet ellen�rz� �sszege.
 */
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length);

/**
 * @brief Kiolvassa a megadott hossz�s�g� b�jtsorozatot a k�ls� EEPROM
 * megc�mzett mem�riacell�j�t�l kezd�d�en �s bele�rja a mutatott
 * megm�riater�letbe.
 *
 * B�jtsorozatok kiolvas�sakor az olvas�s b�rmelyik c�men kezd�dhet �s a
 * hossz�ra vonatkoz�an sincs semmilyen korl�toz�s.
 *
 * @param address Az olvasni k�v�nt b�jtsorozat kezd�c�me.
 * @param _data A kiolvas�s eredm�ny�nek t�rol�s�ra sz�nt mem�riater�letre
 * mutat� pointer.
 * @param length Az EEPROM-b�l kiolvasni k�v�nt mem�riater�let hossza.
 * @return A mutatott mem�riater�letet ellen�rz� �sszege.
 */
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length);

#endif /* INC_EXTERNAL_EEPROM_H_ */