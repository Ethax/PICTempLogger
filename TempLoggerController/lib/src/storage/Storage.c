#include <storage/Storage.h>
#include <storage/ExternalEEPROM.h>

/*
 * A külsõ EEPROM-ban eltárolható beállítások deklarálása és inicializálása.
 */
StorableData systemSettings = { { 0, 0, 0, 1, 1, 70 }, 90.0f, 0x10, 0x10 };

/*
 * Az elsõ és az utolsó naplóbejegyzésekre mutató számlálók deklarálása.
 */
uint8_t logBegin = 0x10, logEnd = 0x10;

/*
 * A betöltött beállítások aktualitását jelölõ jelzõbit deklarálása és
 * inicializálása.
 */
bool isLoadedAlready = false;

/*
 * Inicializálja az I2C kommunikációt a külsõ EEPROM chippel és betölti a
 * legutóbb letárolt beállításokat.
 */
void Storage_initialize() {
  ExternalEEPROM_initialize(0x01);
  if(Storage_getStoredSettings())
    Storage_settingsLoadedEvent();
  else
    Storage_firstBootEvent();
}

/*
 * Alaphelyzetbe állítja a naplóbejegyzések számlálóit.
 */
void Storage_resetLogCounter() {
  logBegin = logEnd = 0x10;
}

/*
 * Betölti a beállításokat a külsõ EEPROM-ból és visszaadja a betöltött
 * beállításokra mutató pointert.
 */
StorableData* Storage_getStoredSettings() {
  uint8_t checksum;
  
  /* A beállítások betöltése a külsõ EEPROM-ból és érvényesítése, amennyiben
  azok még nem lettek betöltve. */
  if(!isLoadedAlready) {
    checksum = ExternalEEPROM_readSequence(0x00, &systemSettings, sizeof(StorableData));
    Delay_ms(5);
    if(checksum == ExternalEEPROM_read(sizeof(StorableData)))
      isLoadedAlready = true;
    else
      return 0;
  }
  
  /* A naplóbejegyzésekre mutató számlálók értékeinek módosítása a betöltött
  beállítások alapján és a beállításokra mutató pointer visszaadása. */
  logBegin = systemSettings.logBegin;
  logEnd = systemSettings.logEnd;
  return &systemSettings;
}

/*
 * Lementi az aktuális beállításokat a külsõ EEPROM-ba és azok ellenõrzõ
 * összegét.
 */
void Storage_storeSettings(PICTime* _systemTime, float _threshold) {
  uint8_t checksum;
  
  /* A beállításokat tároló adatszerkezet feltöltése az új értékekkel. */
  memcpy(&systemSettings.systemTime, _systemTime, sizeof(PICTime));
  systemSettings.threshold = _threshold;
  systemSettings.logBegin = logBegin;
  systemSettings.logEnd = logEnd;
  
  /* A beállítások és az érvényesítéshez szükséges ellenõrzõ összeg mentése a
  külsõ EEPROM-ba. */
  isLoadedAlready = false;
  checksum = ExternalEEPROM_writeRow(0x00, &systemSettings, sizeof(StorableData));
  Delay_ms(5);
  ExternalEEPROM_write(sizeof(StorableData), checksum);
}

/*
 * Új naplóbejegyzést ír a külsõ EEPROM-ba.
 */
void Storage_writeLog(PICTime* timeStamp, float value) {
  static LogEntry new_log;
  
  /* Az új naplóbejegyzés összeállítása és beleírása az EEPROM következõ
  "sorába". */
  memcpy(&new_log.timeStamp, timeStamp, sizeof(PICTime));
  new_log.value = value;
  ExternalEEPROM_writeRow(logEnd, &new_log, sizeof(LogEntry));
  
  /* A napló következõ sorára mutató számláló növelése és a legrégebbi bejegyzés
  törlése, amennyiben túlcsordulás keletkezett. */
  logEnd = ((logEnd & 0xF0) % (LOG_SIZE << 4)) + 0x10;
  if(logBegin == logEnd)
    logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;
}

/*
 * Beolvassa a legkorábbi naplóbejegyzést a külsõ EEPROM-ból és visszaadja a
 * beolvasott adatszerkezetre mutató pointert.
 */
LogEntry* Storage_readEarliestLog() {
  static LogEntry read_log;
  
  /* Azonnali visszatérés a függvénybõl, ha a naplóban nincs új bejegyzés. */
  if(logBegin == logEnd) return 0;

  /* A legkorábbi naplóbejegyzés beolvasása és a soron következõ bejegyzés
  kijelölése. */
  ExternalEEPROM_readSequence(logBegin, &read_log, sizeof(LogEntry));
  logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;

  /* A kiolvasott bejegyzés visszaadása. */
  return &read_log;
}