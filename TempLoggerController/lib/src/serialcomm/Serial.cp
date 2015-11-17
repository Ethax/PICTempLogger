#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
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
#line 10 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"
typedef unsigned char _Bool;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdarg.h"





typedef void * va_list[1];
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
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
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
enum BaudRate {
 BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400,
 BAUD_57600, BAUD_115200
};
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_initialize(enum BaudRate baudrate);
#line 31 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_handleInterrupt();
#line 41 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void* Serial_getReceivedData();
#line 48 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_sendLogEntry(LogEntry* entry);
#line 53 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_sendAcknowledgement();
#line 59 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedTimeSettingEvent();
#line 65 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedThresholdSettingEvent();
#line 71 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
extern void Serial_receivedLogRequestEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef void (*EventHandler)(void);
#line 28 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef struct event_queue_t {
#line 32 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t end;
#line 37 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t begin;
#line 42 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 EventHandler eventHandlers[ 20 ];
} EventQueue;
#line 49 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_initialize();
#line 57 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_dispatchEvent(EventHandler handler);
#line 63 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_handleEvents();
#line 69 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_run();
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
uint8_t receiveBuffer[20] = { 0 };
#line 13 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
uint8_t transmitBuffer[20] = { 0 };
#line 18 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
uint8_t receiveCounter = 0;
#line 25 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void Serial_initialize(enum BaudRate baudrate) {
#line 28 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 switch(baudrate) {
 case BAUD_1200:
 UART1_Init(1200); break;
 case BAUD_2400:
 UART1_Init(2400); break;
 case BAUD_4800:
 UART1_Init(4800); break;
 case BAUD_9600:
 UART1_Init(9600); break;
 case BAUD_19200:
 UART1_Init(19200); break;
 case BAUD_38400:
 UART1_Init(38400); break;
 case BAUD_57600:
 UART1_Init(57600); break;
 case BAUD_115200:
 UART1_Init(115200); break;
 }


 RC1IF_bit =  0 ;
 RC1IE_bit =  1 ;
}
#line 56 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void Serial_handleInterrupt() {

 uint8_t next_byte = UART1_Read();
#line 63 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 if(next_byte == '\n') {
 switch(receiveBuffer[0]) {
 case 'T':
 Application_dispatchEvent(Serial_receivedTimeSettingEvent);
 break;
 case 'R':
 Application_dispatchEvent(Serial_receivedThresholdSettingEvent);
 break;
 case 'L':
 Application_dispatchEvent(Serial_receivedLogRequestEvent);
 break;
 }
 receiveCounter = 0;
 }
#line 80 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 else {
 receiveBuffer[receiveCounter++] = next_byte;
 }


 RC1IF_bit =  0 ;
}
#line 91 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void* Serial_getReceivedData() {
 return (void*)&receiveBuffer[1];
}
#line 98 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void Serial_sendLogEntry(LogEntry* entry) {
 uint8_t i;
#line 103 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 memcpy(transmitBuffer, entry, sizeof(LogEntry));
 for(i = 0; i < sizeof(LogEntry); i++)
 UART1_Write(transmitBuffer[i]);
#line 109 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 UART1_Write('\n');
}
#line 115 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void Serial_sendAcknowledgement() {

 UART1_Write('A'); UART1_Write('C'); UART1_Write('K');
#line 121 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
 UART1_Write('\n');
}
