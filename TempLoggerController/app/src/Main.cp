#line 1 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
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
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/storage/storage.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
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
#line 9 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
sbit LCD_RS at LATB4_bit; sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN at LATB5_bit; sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4 at LATB0_bit; sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5 at LATB1_bit; sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6 at LATB2_bit; sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7 at LATB3_bit; sbit LCD_D7_Direction at TRISB3_bit;
#line 22 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
void interrupt() {

 if(TMR0IF_bit && TMR0IE_bit)
 Timer_handleInterrupt();
#line 28 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
 else if(RC1IF_bit && RC1IE_bit)
 Serial_handleInterrupt();
}
#line 35 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
void main() {

 Application_initialize();
 Application_run();
}
