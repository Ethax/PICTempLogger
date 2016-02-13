#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
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
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 15 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
typedef struct pic_time_t {
#line 19 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t second;
#line 24 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t minute;
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t hour;
#line 34 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t day;
#line 39 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t month;
#line 44 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
 uint8_t year;
} PICTime;
#line 52 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_initialize();
#line 61 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_handleInterrupt();
#line 68 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
PICTime* Timer_getSystemTime();
#line 76 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_setSystemTime(PICTime* time_ptr);
#line 85 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
char* Timer_timeToString(PICTime* time_ptr);
#line 91 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedSecondEvent();
#line 97 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedMinuteEvent();
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
typedef struct storable_data_t {
#line 26 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 PICTime systemTime;
#line 31 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 float threshold;
#line 36 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 uint8_t logBegin;
#line 41 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 uint8_t logEnd;
} StorableData;
#line 52 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
typedef struct log_t {
#line 56 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 PICTime timeStamp;
#line 61 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
 float value;
} LogEntry;
#line 71 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_initialize();
#line 78 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_resetLogCounter();
#line 86 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
StorableData* Storage_getStoredSettings();
#line 95 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_storeSettings(PICTime* _systemTime, float _threshold);
#line 103 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
void Storage_writeLog(PICTime* timeStamp, float value);
#line 116 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
LogEntry* Storage_readEarliestLog();
#line 123 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
extern void Storage_settingsLoadedEvent();
#line 130 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
extern void Storage_firstBootEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/externaleeprom.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
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
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
StorableData systemSettings = { { 0, 0, 0, 1, 1, 70 }, 90.0f, 0x10, 0x10 };
#line 12 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
uint8_t logBegin = 0x10, logEnd = 0x10;
#line 18 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 _Bool  isLoadedAlready =  0 ;
#line 24 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
void Storage_initialize() {
 ExternalEEPROM_initialize(0x01);
 if(Storage_getStoredSettings())
 Storage_settingsLoadedEvent();
 else
 Storage_firstBootEvent();
}
#line 35 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
void Storage_resetLogCounter() {
 logBegin = logEnd = 0x10;
}
#line 43 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
StorableData* Storage_getStoredSettings() {
 uint8_t checksum;
#line 48 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 if(!isLoadedAlready) {
 checksum = ExternalEEPROM_readSequence(0x00, &systemSettings, sizeof(StorableData));
 Delay_ms(5);
 if(checksum == ExternalEEPROM_read(sizeof(StorableData)))
 isLoadedAlready =  1 ;
 else
 return 0;
 }
#line 59 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 logBegin = systemSettings.logBegin;
 logEnd = systemSettings.logEnd;
 return &systemSettings;
}
#line 68 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
void Storage_storeSettings(PICTime* _systemTime, float _threshold) {
 uint8_t checksum;


 memcpy(&systemSettings.systemTime, _systemTime, sizeof(PICTime));
 systemSettings.threshold = _threshold;
 systemSettings.logBegin = logBegin;
 systemSettings.logEnd = logEnd;
#line 79 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 isLoadedAlready =  0 ;
 checksum = ExternalEEPROM_writeRow(0x00, &systemSettings, sizeof(StorableData));
 Delay_ms(5);
 ExternalEEPROM_write(sizeof(StorableData), checksum);
}
#line 88 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
void Storage_writeLog(PICTime* timeStamp, float value) {
 static LogEntry new_log;
#line 93 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 memcpy(&new_log.timeStamp, timeStamp, sizeof(PICTime));
 new_log.value = value;
 ExternalEEPROM_writeRow(logEnd, &new_log, sizeof(LogEntry));
#line 99 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 logEnd = ((logEnd & 0xF0) % ( 15  << 4)) + 0x10;
 if(logBegin == logEnd)
 logBegin = ((logBegin & 0xF0) % ( 15  << 4)) + 0x10;
}
#line 108 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
LogEntry* Storage_readEarliestLog() {
 static LogEntry read_log;


 if(logBegin == logEnd) return 0;
#line 116 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/storage/Storage.c"
 ExternalEEPROM_readSequence(logBegin, &read_log, sizeof(LogEntry));
 logBegin = ((logBegin & 0xF0) % ( 15  << 4)) + 0x10;


 return &read_log;
}
