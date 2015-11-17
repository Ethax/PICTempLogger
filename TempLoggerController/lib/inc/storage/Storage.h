#ifndef INC_STORAGE_H_
#define INC_STORAGE_H_

#include <common.h>
#include <timer/Timer.h>

/**
 * @brief A napl�ba bejegyezhet� sorok maxim�lis sz�ma. (Legfeljebb 15 lehet.)
 */
#define LOG_SIZE 15

/**
 * @typedef StorableData
 * @brief A k�ls� EEPROM-ban elt�rolhat� be�ll�t�sok adatszerkezete.
 *
 * Annak k�sz�nhet�en, hogy a 24Cxx t�pus� EEPROM chip k�pes az I2C kommunik�ci�
 * egyszeri ki�p�t�s�vel a mem�ria valamely "sor�nak" folyamatos �r�s�ra
 * (legfeljebb 16 b�jtig), ez az adatszerkezet lehet�s�get biztos�t a legf�bb
 * be�ll�t�sok egyetlen 8-bites pointerrel t�rt�n� bej�r�s�ra �s folyamatos
 * bele�r�s�ba az EEPROM-ba.
 */
typedef struct storable_data_t {
  /**
   * A rendszerid� m�solat�t t�rol� adatszerkezet.
   */
  PICTime systemTime;
  
  /**
   * A riaszt�s k�sz�b�rt�k�nek m�solat�t t�rol� v�ltoz�.
   */
  float threshold;
  
  /**
   * Az els� napl�bejegyz�s "sor�nak" c�me a k�ls� EEPROM-ban.
   */
  uint8_t logBegin;
  
  /**
   * Az utols� napl�bejegyz�s "sor�nak" c�me a k�ls� EEPROM-ban.
   */
  uint8_t logEnd;
} StorableData;

/**
 * @typedef LogEntry
 * @brief A napl�bejegyz�sek adatszerkezete.
 *
 * Ez az adatszerkezet a m�rt h�m�rs�klet id�b�lyegezett napl�z�s�t teszi
 * �ttekinthet�bb� az�ltal, hogy egyetlen adatszerkezetbe t�m�r�ti a
 * napl�zott mennyis�get �s a m�r�s id�pontj�t.
 */
typedef struct log_t {
  /**
   * A bejegyz�s l�trehoz�s�nak id�pontj�t t�rol� adatszerkezet.
   */
  PICTime timeStamp;
  
  /**
   * A bejegyzett adatot t�rol� v�ltoz�.
   */
  float value;
} LogEntry;

/**
 * @brief Inicializ�lja az I2C kommunik�ci�t a k�ls� EEPROM chippel �s bet�lti a
 * legut�bb let�rolt be�ll�t�sokat.
 *
 * Ha a be�ll�t�sokon v�gzett CRC sikeres volt, akkor v�grehajtja az �j
 * be�ll�t�sok bet�lt�s�nek esem�nykezel�j�t.
 */
void Storage_initialize();

/**
 * @brief Alaphelyzetbe �ll�tja a napl�bejegyz�sek sz�ml�l�it.
 *
 * FIGYELEM: Ennek hat�s�ra az �sszes be�rt napl�bejegyz�s elveszik.
 */
void Storage_resetLogCounter();

/**
 * @brief Bet�lti a be�ll�t�sokat a k�ls� EEPROM-b�l �s visszaadja a bet�lt�tt
 * be�ll�t�sokra mutat� pointert.
 *
 * @return A CRC-t�l f�gg�en a bet�lt�tt be�ll�t�sokra mutat� ponter vagy NULL.
 */
StorableData* Storage_getStoredSettings();

/**
 * @brief Lementi az aktu�lis be�ll�t�sokat a k�ls� EEPROM-ba �s azok ellen�rz�
 * �sszeg�t.
 *
 * @param _systemTime Az aktu�lis rendszerid� adatszerkezet�re mutat� pointer.
 * @param _threshold A riaszt�s aktu�lis k�sz�b�rt�ke.
 */
void Storage_storeSettings(PICTime* _systemTime, float _threshold);

/**
 * @brief �j napl�bejegyz�st �r a k�ls� EEPROM-ba.
 *
 * @param timeStamp Az aktu�lis rendszerid� adatszerkezet�re mutat� pointer.
 * @param value A m�rt h�m�rs�klet Celsuis fokokban.
 */
void Storage_writeLog(PICTime* timeStamp, float value);

/**
 * @brief Beolvassa a legkor�bbi napl�bejegyz�st a k�ls� EEPROM-b�l �s
 * visszaadja a beolvasott adatszerkezetre mutat� pointert.
 *
 * A beolvas�st k�vet�en automatikusan n�veli a legkor�bbi bejegyz�sre mutat�
 * sz�ml�l�t, �gy a k�vetkez� megh�v�sakor m�r a soron k�vetkez� bejegyz�st adja
 * vissza.
 *
 * @return Az utols� napl�bejegyz�s beolvas�s�ig a beolvasott adatszerkezetre
 * mutat� pointer, azt k�vet�en NULL.
 */
LogEntry* Storage_readEarliestLog();

/**
 * @brief A kor�bban let�rolt be�ll�t�sok beolvas�s�t k�vet�en v�grehajt�sra
 * ker�l� esem�nykezel� deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni
 * kell.)
 */
extern void Storage_settingsLoadedEvent();

/**
 * @brief Az els� ind�t�skor, vagy az EEPROM chip cser�j�t k�vet�en
 * v�grehajt�sra ker�l� esem�nykezel� deklar�ci�ja. (Az esem�nykezel� t�rzs�t
 * defini�lni kell.)
 */
extern void Storage_firstBootEvent();

#endif /* INC_STORAGE_H_ */