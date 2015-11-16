#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
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
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
volatile PICTime systemTime = { 0, 0, 0, 1, 1, 70 };
#line 12 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
uint8_t monthsLength[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#line 19 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
void Timer_initialize() {
#line 22 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
 T0CON = 0x84;
 TMR0H = 0x0B;
 TMR0L = 0xDC;
 TMR0IE_bit =  1 ;
}
#line 32 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
void Timer_handleInterrupt() {
#line 36 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
 if(++systemTime.second > 59) {
 systemTime.second = 0;
 if(++systemTime.minute > 59) {
 systemTime.minute = 0;
 if(++systemTime.hour > 23) {
 systemTime.hour = 0;
 if(++systemTime.day > monthsLength[systemTime.month - 1]) {
 systemTime.day = 1;
 if(++systemTime.month > 12) {
 systemTime.month = 1;
 systemTime.year++;
 if(!(systemTime.year && 0b00000011))
 monthsLength[1] = 29;
 else
 monthsLength[1] = 28;
 }
 }
 }
 }
 Application_dispatchEvent(Timer_elapsedMinuteEvent);
 }
 Application_dispatchEvent(Timer_elapsedSecondEvent);
#line 61 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
 TMR0H = 0x0B;
 TMR0L = 0xDC;
 TMR0IF_bit =  0 ;
}
#line 69 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
PICTime* Timer_getSystemTime() {
 return &systemTime;
}
#line 76 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
void Timer_setSystemTime(PICTime* time_ptr) {
#line 79 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
 TMR0IE_bit =  0 ;
 memcpy(&systemTime, time_ptr, sizeof(PICTime));
#line 84 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
 TMR0H = 0x0B;
 TMR0L = 0xDC;
 TMR0IE_bit =  1 ;
}
#line 93 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/timer/Timer.c"
char* Timer_timeToString(PICTime* time_ptr) {
 static char time_str[20];
 uint8_t i = 0;


 time_str[i++] = ((1900 + time_ptr->year) / 1000) + '0';
 time_str[i++] = (((1900 + time_ptr->year) % 1000) / 100) + '0';
 time_str[i++] = (((1900 + time_ptr->year) % 100) / 10) + '0';
 time_str[i++] = ((1900 + time_ptr->year) % 10) + '0';
 time_str[i++] = '-';


 time_str[i++] = ((time_ptr->month) / 10) + '0';
 time_str[i++] = ((time_ptr->month) % 10) + '0';
 time_str[i++] = '-';


 time_str[i++] = (time_ptr->day / 10) + '0';
 time_str[i++] = (time_ptr->day % 10) + '0';
 time_str[i++] = ' ';


 time_str[i++] = (time_ptr->hour / 10) + '0';
 time_str[i++] = (time_ptr->hour % 10) + '0';
 time_str[i++] = ':';


 time_str[i++] = (time_ptr->minute / 10) + '0';
 time_str[i++] = (time_ptr->minute % 10) + '0';
 time_str[i++] = ':';


 time_str[i++] = (time_ptr->second / 10) + '0';
 time_str[i++] = (time_ptr->second % 10) + '0';
 time_str[i++] = '\0';


 return time_str;
}
