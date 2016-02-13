#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/built_in.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"



 typedef char _Bool;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdarg.h"





typedef void * va_list[1];
#line 14 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
enum CommunicationType { I2C_WRITE, I2C_READ };
#line 27 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
void ExternalEEPROM_initialize(uint8_t i2c_address);
#line 36 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
void ExternalEEPROM_write(uint8_t address, uint8_t _data);
#line 45 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
uint8_t ExternalEEPROM_read(uint8_t address);
#line 61 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length);
#line 77 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length);
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
uint8_t hardwareAddress;
#line 13 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
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
#line 28 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
void ExternalEEPROM_initialize(uint8_t i2c_address) {
 hardwareAddress = (i2c_address & 0b00000111) << 1;
 I2C1_Init(100000);
}
#line 36 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
void ExternalEEPROM_write(uint8_t address, uint8_t _data) {
#line 39 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_WRITE);
#line 44 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Wr(address);
 I2C1_Wr(_data);
 I2C1_Stop();
}
#line 52 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
uint8_t ExternalEEPROM_read(uint8_t address) {
 uint8_t _data;
#line 57 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_WRITE);
 I2C1_Wr(address);
#line 63 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Repeated_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_READ);
#line 68 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 _data = I2C1_Rd( 0 );
 while(!I2C1_Is_Idle());
#line 73 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Stop();
 return _data;
}
#line 81 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length) {
 uint8_t checksum = 0, i, current_byte;
#line 86 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 if(length > 16 || (address & 0x0F)) return 0;
#line 90 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_WRITE);
#line 95 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Wr(address);
 for(i = 0; i < length; i++) {
 current_byte = *((uint8_t*)_data + i);
 I2C1_Wr(current_byte);
 calculateChecksum(&checksum, current_byte);
 Delay_us(80);
 }
#line 105 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Stop();
 return checksum;
}
#line 113 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length) {
 uint8_t checksum = 0, i, current_byte;
#line 119 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_WRITE);
 I2C1_Wr(address);
#line 125 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Repeated_Start();
 I2C1_Wr( 0xA0  | hardwareAddress | I2C_READ);
#line 131 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 for(i = 0; i < length - 1; i++) {
 current_byte = I2C1_Rd( 1 );
 calculateChecksum(&checksum, current_byte);
 *((uint8_t*)_data + i) = current_byte;
 Delay_us(80);
 }
#line 140 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 current_byte = I2C1_Rd( 0 );
 calculateChecksum(&checksum, current_byte);
 *((uint8_t*)_data + i) = current_byte;
 while(!I2C1_Is_Idle());
#line 147 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/ExternalEEPROM.c"
 I2C1_Stop();
 return checksum;
}
