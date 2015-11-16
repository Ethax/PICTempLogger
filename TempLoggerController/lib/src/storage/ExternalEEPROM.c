#include <storage/ExternalEEPROM.h>

/*
 * Az I2C buszra kapcsolt 24Cxx EEPROM chip fizikai c�me, ami a chip
 * beforraszt�sakor lett meghat�rozva.
 */
uint8_t hardwareAddress;

/*
 * Kisz�molja az ellen�z� �sszeget �s az eredm�nyt elt�rolja a pointerk�nt
 * �tadott param�terben. A CRC polinomja: P(x) = x^8 + x^5 + x^4 + x^0
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
 * Let�rolja az EEPROM chip fizikai c�m�t �s inicializ�lja az I2C kommunik�ci�t
 * 100kHz-es �rajellel.
 */
void ExternalEEPROM_initialize(uint8_t i2c_address) {
  hardwareAddress = (i2c_address & 0b00000111) << 1;
  I2C1_Init(100000);
}

/*
 * Bele�r egy egyb�jtos adatot a k�ls� EEPROM megc�mzett mem�riacell�j�ba.
 */
void ExternalEEPROM_write(uint8_t address, uint8_t _data) {
  /* A Start jelz�s kik�ld�se az I2C buszon �s az EEPROM �r�sra c�mz�se a
  kommunik�ci� megkezd�s�hez. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  
  /* A megadott adat bele�r�sa a megadott c�m� mem�riacell�ba �s a kommunik�ci�
  befejez�se a Stop jelz�s kik�ld�s�vel. */
  I2C1_Wr(address);
  I2C1_Wr(_data);
  I2C1_Stop();
}

/*
 * Kiolvas egy egyb�jtos adatot a k�ls� EEPROM megc�mzett mem�riacell�j�b�l.
 */
uint8_t ExternalEEPROM_read(uint8_t address) {
  uint8_t _data;
  
  /* A Start jelz�s kik�ld�se az I2C buszon �s az EEPROM �r�sra c�mz�se a
  kommunik�ci� megkezd�s�hez, majd a olvasni k�v�nt mem�riacella megc�mz�se. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  I2C1_Wr(address);
  
  /* Repeated Start jelz�s kik�ld�se az I2C buszon �s az EEPROM olvas�sra
  c�mz�se. */
  I2C1_Repeated_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);

  /* A megc�mzett mem�riacella kiolvas�sa (nyugt�z�s n�lk�l) �s az olvas�si
  ciklus befejez�d�s�nek kiv�r�sa. */
  _data = I2C1_Rd(false);
  while(!I2C1_Is_Idle());
  
  /* A kommunik�ci� befejez�se a Stop jelz�s kik�ld�s�vel �s a kiolvasott
  adatb�jt visszaad�sa. */
  I2C1_Stop();
  return _data;
}

/*
 * Bele�rja az mutatott mem�riater�letet a k�ls� EEPROM megc�mzett "sor�ba" �s
 * kisz�m�tja a bele�rt adat ellen�rz� �sszeg�t.
 */
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length) {
  uint8_t checksum = 0, i, current_byte;
  
  /* Az �r�si m�velet megszak�t�sa, ha a c�m als� n�gy bitje nem nulla vagy az
  EEPROM-ba �rni k�v�nt mem�riater�let m�rete nagyobb, mint 16 b�jt. */
  if(length > 16 || (address & 0x0F)) return 0;
  
  /* A Start jelz�s kik�ld�se az I2C buszon �s az EEPROM �r�sra c�mz�se a
  kommunik�ci� megkezd�s�hez. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  
  /* A mutatott mem�riater�let bele�r�sa a megadott c�m� "sorba" �s az
  ellen�rz� �sszeg kisz�m�t�sa. */
  I2C1_Wr(address);
  for(i = 0; i < length; i++) {
    current_byte = *((uint8_t*)_data + i);
    I2C1_Wr(current_byte);
    calculateChecksum(&checksum, current_byte);
    Delay_us(80);
  }

  /* A kommunik�ci� befejez�se a Stop jelz�s kik�ld�s�vel �s a kisz�m�tott
  ellen�rz� �sszeg visszaad�sa. */
  I2C1_Stop();
  return checksum;
}

/*
 * Kiolvassa a megadott hossz�s�g� b�jtsorozatot a k�ls� EEPROM megc�mzett
 * mem�riacell�j�t�l kezd�d�en �s bele�rja a mutatott megm�riater�letbe.
 */
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length) {
  uint8_t checksum = 0, i, current_byte;
  
  /* A Start jelz�s kik�ld�se az I2C buszon �s az EEPROM �r�sra c�mz�se a
  kommunik�ci� megkezd�s�hez, majd a olvasni k�v�nt sorozat els�
  mem�riacell�j�nak megc�mz�se. */
  I2C1_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
  I2C1_Wr(address);
  
  /* Repeated Start jelz�s kik�ld�se az I2C buszon �s az EEPROM olvas�sra
  c�mz�se. */
  I2C1_Repeated_Start();
  I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);

  /* A megadott hossz�s�g� sorozat kiolvas�sa (nyugt�z�ssal) az utols� b�jt
  kiv�tel�vel, az eredm�ny bele�r�sa a mutatott mem�riater�letbe �s az
  ellen�rz� �sszeg kisz�m�t�sa. */
  for(i = 0; i < length - 1; i++) {
    current_byte = I2C1_Rd(true);
    calculateChecksum(&checksum, current_byte);
    *((uint8_t*)_data + i) = current_byte;
    Delay_us(80);
  }
  
  /* A megadott hossz�s�g� sorozat utols� b�jtj�nak kiolvas�sa (nyugt�z�s
  n�lk�l) �s az olvas�si ciklus befejez�d�s�nek kiv�r�sa. */
  current_byte = I2C1_Rd(false);
  calculateChecksum(&checksum, current_byte);
  *((uint8_t*)_data + i) = current_byte;
  while(!I2C1_Is_Idle());
  
  /* A kommunik�ci� befejez�se a Stop jelz�s kik�ld�s�vel �s a kisz�m�tott
  ellen�rz� �sszeg visszaad�sa. */
  I2C1_Stop();
  return checksum;
}