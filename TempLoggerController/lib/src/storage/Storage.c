#include <storage/Storage.h>
#include <storage/ExternalEEPROM.h>

/*
 * A k�ls� EEPROM-ban elt�rolhat� be�ll�t�sok deklar�l�sa �s inicializ�l�sa.
 */
StorableData systemSettings = { { 0, 0, 0, 1, 1, 70 }, 90.0f, 0x10, 0x10 };

/*
 * Az els� �s az utols� napl�bejegyz�sekre mutat� sz�ml�l�k deklar�l�sa.
 */
uint8_t logBegin = 0x10, logEnd = 0x10;

/*
 * A bet�lt�tt be�ll�t�sok aktualit�s�t jel�l� jelz�bit deklar�l�sa �s
 * inicializ�l�sa.
 */
bool isLoadedAlready = false;

/*
 * Inicializ�lja az I2C kommunik�ci�t a k�ls� EEPROM chippel �s bet�lti a
 * legut�bb let�rolt be�ll�t�sokat.
 */
void Storage_initialize() {
  ExternalEEPROM_initialize(0x01);
  if(Storage_getStoredSettings())
    Storage_settingsLoadedEvent();
  else
    Storage_firstBootEvent();
}

/*
 * Alaphelyzetbe �ll�tja a napl�bejegyz�sek sz�ml�l�it.
 */
void Storage_resetLogCounter() {
  logBegin = logEnd = 0x10;
}

/*
 * Bet�lti a be�ll�t�sokat a k�ls� EEPROM-b�l �s visszaadja a bet�lt�tt
 * be�ll�t�sokra mutat� pointert.
 */
StorableData* Storage_getStoredSettings() {
  uint8_t checksum;
  
  /* A be�ll�t�sok bet�lt�se a k�ls� EEPROM-b�l �s �rv�nyes�t�se, amennyiben
  azok m�g nem lettek bet�ltve. */
  if(!isLoadedAlready) {
    checksum = ExternalEEPROM_readSequence(0x00, &systemSettings, sizeof(StorableData));
    Delay_ms(5);
    if(checksum == ExternalEEPROM_read(sizeof(StorableData)))
      isLoadedAlready = true;
    else
      return 0;
  }
  
  /* A napl�bejegyz�sekre mutat� sz�ml�l�k �rt�keinek m�dos�t�sa a bet�lt�tt
  be�ll�t�sok alapj�n �s a be�ll�t�sokra mutat� pointer visszaad�sa. */
  logBegin = systemSettings.logBegin;
  logEnd = systemSettings.logEnd;
  return &systemSettings;
}

/*
 * Lementi az aktu�lis be�ll�t�sokat a k�ls� EEPROM-ba �s azok ellen�rz�
 * �sszeg�t.
 */
void Storage_storeSettings(PICTime* _systemTime, float _threshold) {
  uint8_t checksum;
  
  /* A be�ll�t�sokat t�rol� adatszerkezet felt�lt�se az �j �rt�kekkel. */
  memcpy(&systemSettings.systemTime, _systemTime, sizeof(PICTime));
  systemSettings.threshold = _threshold;
  systemSettings.logBegin = logBegin;
  systemSettings.logEnd = logEnd;
  
  /* A be�ll�t�sok �s az �rv�nyes�t�shez sz�ks�ges ellen�rz� �sszeg ment�se a
  k�ls� EEPROM-ba. */
  isLoadedAlready = false;
  checksum = ExternalEEPROM_writeRow(0x00, &systemSettings, sizeof(StorableData));
  Delay_ms(5);
  ExternalEEPROM_write(sizeof(StorableData), checksum);
}

/*
 * �j napl�bejegyz�st �r a k�ls� EEPROM-ba.
 */
void Storage_writeLog(PICTime* timeStamp, float value) {
  static LogEntry new_log;
  
  /* Az �j napl�bejegyz�s �ssze�ll�t�sa �s bele�r�sa az EEPROM k�vetkez�
  "sor�ba". */
  memcpy(&new_log.timeStamp, timeStamp, sizeof(PICTime));
  new_log.value = value;
  ExternalEEPROM_writeRow(logEnd, &new_log, sizeof(LogEntry));
  
  /* A napl� k�vetkez� sor�ra mutat� sz�ml�l� n�vel�se �s a legr�gebbi bejegyz�s
  t�rl�se, amennyiben t�lcsordul�s keletkezett. */
  logEnd = ((logEnd & 0xF0) % (LOG_SIZE << 4)) + 0x10;
  if(logBegin == logEnd)
    logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;
}

/*
 * Beolvassa a legkor�bbi napl�bejegyz�st a k�ls� EEPROM-b�l �s visszaadja a
 * beolvasott adatszerkezetre mutat� pointert.
 */
LogEntry* Storage_readEarliestLog() {
  static LogEntry read_log;
  
  /* Azonnali visszat�r�s a f�ggv�nyb�l, ha a napl�ban nincs �j bejegyz�s. */
  if(logBegin == logEnd) return 0;

  /* A legkor�bbi napl�bejegyz�s beolvas�sa �s a soron k�vetkez� bejegyz�s
  kijel�l�se. */
  ExternalEEPROM_readSequence(logBegin, &read_log, sizeof(LogEntry));
  logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;

  /* A kiolvasott bejegyz�s visszaad�sa. */
  return &read_log;
}