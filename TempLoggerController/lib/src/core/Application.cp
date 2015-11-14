#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
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
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef void (*EventHandler)(void);
#line 28 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef struct event_queue_t {
#line 32 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t end;
#line 37 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t next;
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
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_initialize();
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* format, ...);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_clearLine(uint8_t line);
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 13 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
void Sensor_initialize(const float _vref);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
float Sensor_getTemperature();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_initialize();
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_setThreshold(float _threshold);
#line 23 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_clearThreshold();
#line 37 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
 _Bool  Alarm_checkConditions(float _temperature);
#line 42 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_playAlarmSound();
#line 10 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
EventQueue eventQueue = { 0, 0, { 0 }};
#line 16 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_initialize() {
#line 19 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
 ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
 SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;


 ADCON0 = ADCON1 = ADCON2 = 0x00;
 C1ON_bit = C2ON_bit =  0 ;


 Display_initialize();
 Alarm_initialize();
 Timer_initialize();
 Sensor_initialize(3.3f);

 Alarm_setThreshold(40.0);
}
#line 40 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_dispatchEvent(EventHandler handler) {
#line 43 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 eventQueue.eventHandlers[eventQueue.end] = handler;
 eventQueue.end = (eventQueue.end + 1) %  20 ;
#line 49 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.end == eventQueue.next)
 eventQueue.next = (eventQueue.next + 1) %  20 ;
}
#line 57 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_handleEvents() {

 if(eventQueue.next == eventQueue.end) return;
#line 64 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.eventHandlers[eventQueue.next]) {
 eventQueue.eventHandlers[eventQueue.next]();
 eventQueue.eventHandlers[eventQueue.next] = 0;
 }


 eventQueue.next = (eventQueue.next + 1) %  20 ;
}
#line 77 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_run() {
#line 80 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 IPEN_bit =  0 ;
 PEIE_bit = GIE_bit =  1 ;


 while( 1 ) Application_handleEvents();
}
#line 90 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedSecondEvent() {

 float actual_temp = Sensor_getTemperature();
#line 97 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 char* date_str = Timer_timeToString(Timer_getSystemTime());
 char* time_str = strstr(date_str, " ");
 *time_str++ = '\0';
#line 103 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 Display_writeLine(1, "%a   [T]", date_str);
 Display_writeLine(2, "%a %2f%cC", time_str, actual_temp, 223);
#line 108 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(Alarm_checkConditions(actual_temp)) {
 Display_writeLine(1, "     ALARM!");
 Display_clearLine(2);
 Alarm_playAlarmSound();
 }
}
#line 118 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedMinuteEvent() {

}
