#include <storage/ExternalEEPROM.h>

/*
 * Az I2C buszra kapcsolt 24Cxx EEPROM chip fizikai címe, ami a chip
 * beforrasztásakor lett meghatározva.
 */
uint8_t hardwareAddress;

/*
 * Kiszámolja az ellenõzõ összeget és az eredményt eltárolja a pointerként
 * átadott paraméterben. A CRC polinomja: P(x) = x^8 + x^5 + x^4 + x^0
 */
void calculateChecksum(unsigned char* checksum_ptr, unsigned char value) {
  uint8_t i;
  for(i = 8; i; i--) {
    if((*checksum_ptr ^ value) & 0x80)
      *checksum_ptr = (*checksum_ptr << 1) ^ 0x31;
    else
      *checksum_ptr <<= 1;
    value <<= 1;
  }
}

/*
 * Letárolja az EEPROM chip fizikai címét és inicializálja az I2C kommunikációt
 * 100kHz-es órajellel.
 */
void ExternalEEPROM_initialize(uint8_t i2c_address) {
  hardwareAddress = (i2c_address & 0b00000111) << 1;
  I2C1_Init(100000);
}

/*
 * Beleír egy egybájtos adatot a külsõ EEPROM megcímzett memóriacellájába.
 */
void ExternalEEPROM_write(uint8_t address, uint8_t _data) {
  /* A Start jelzés kiküldése az I2C buszon és az EEPROM írásra címzése a
  kommunikáció megkezdéséhez. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  
  /* A megadott adat beleírása a megadott címû memóriacellába és a kommunikáció
  befejezése a Stop jelzés kiküldésével. */
  I2C1_Wr(address);
  I2C1_Wr(_data);
  I2C1_Stop();
}

/*
 * Kiolvas egy egybájtos adatot a külsõ EEPROM megcímzett memóriacellájából.
 */
uint8_t ExternalEEPROM_read(uint8_t address) {
  uint8_t _data;
  
  /* A Start jelzés kiküldése az I2C buszon és az EEPROM írásra címzése a
  kommunikáció megkezdéséhez, majd a olvasni kívánt memóriacella megcímzése. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  I2C1_Wr(address);
  
  /* Repeated Start jelzés kiküldése az I2C buszon és az EEPROM olvasásra
  címzése. */
  I2C1_Repeated_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);

  /* A megcímzett memóriacella kiolvasása (nyugtázás nélkül) és az olvasási
  ciklus befejezõdésének kivárása. */
  _data = I2C1_Rd(false);
  while(!I2C1_Is_Idle());
  
  /* A kommunikáció befejezése a Stop jelzés kiküldésével és a kiolvasott
  adatbájt visszaadása. */
  I2C1_Stop();
  return _data;
}

/*
 * Beleírja az mutatott memóriaterületet a külsõ EEPROM megcímzett "sorába" és
 * kiszámítja a beleírt adat ellenõrzõ összegét.
 */
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length) {
  uint8_t checksum = 0, i, current_byte;
  
  /* Az írási mûvelet megszakítása, ha a cím alsó négy bitje nem nulla vagy az
  EEPROM-ba írni kívánt memóriaterület mérete nagyobb, mint 16 bájt. */
  if(length > 16 || (address & 0x0F)) return 0;
  
  /* A Start jelzés kiküldése az I2C buszon és az EEPROM írásra címzése a
  kommunikáció megkezdéséhez. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  
  /* A mutatott memóriaterület beleírása a megadott címû "sorba" és az
  ellenõrzõ összeg kiszámítása. */
  I2C1_Wr(address);
  for(i = 0; i < length; i++) {
    current_byte = *((uint8_t*)_data + i);
    I2C1_Wr(current_byte);
    calculateChecksum(&checksum, current_byte);
    Delay_us(80);
  }

  /* A kommunikáció befejezése a Stop jelzés kiküldésével és a kiszámított
  ellenõrzõ összeg visszaadása. */
  I2C1_Stop();
  return checksum;
}

/*
 * Kiolvassa a megadott hosszúságú bájtsorozatot a külsõ EEPROM megcímzett
 * memóriacellájától kezdõdõen és beleírja a mutatott megmóriaterületbe.
 */
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length) {
  uint8_t checksum = 0, i, current_byte;
  
  /* A Start jelzés kiküldése az I2C buszon és az EEPROM írásra címzése a
  kommunikáció megkezdéséhez, majd a olvasni kívánt sorozat elsõ
  memóriacellájának megcímzése. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  I2C1_Wr(address);
  
  /* Repeated Start jelzés kiküldése az I2C buszon és az EEPROM olvasásra
  címzése. */
  I2C1_Repeated_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);

  /* A megadott hosszúságú sorozat kiolvasása (nyugtázással) az utolsó bájt
  kivételével, az eredmény beleírása a mutatott memóriaterületbe és az
  ellenõrzõ összeg kiszámítása. */
  for(i = 0; i < length - 1; i++) {
    current_byte = I2C1_Rd(true);
    calculateChecksum(&checksum, current_byte);
    *((uint8_t*)_data + i) = current_byte;
    Delay_us(80);
  }
  
  /* A megadott hosszúságú sorozat utolsó bájtjának kiolvasása (nyugtázás
  nélkül) és az olvasási ciklus befejezõdésének kivárása. */
  current_byte = I2C1_Rd(false);
  calculateChecksum(&checksum, current_byte);
  *((uint8_t*)_data + i) = current_byte;
  while(!I2C1_Is_Idle());
  
  /* A kommunikáció befejezése a Stop jelzés kiküldésével és a kiszámított
  ellenõrzõ összeg visszaadása. */
  I2C1_Stop();
  return checksum;
}