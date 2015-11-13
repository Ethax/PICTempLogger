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



 typedef char _Bool;
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
PICTime* getSystemTime();
#line 76 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void setSystemTime(PICTime* time_ptr);
#line 85 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
char* timeToString(PICTime* time_ptr);
#line 91 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedSecondEvent();
#line 97 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
extern void Timer_elapsedMinuteEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_initialize();
#line 16 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* text);
#line 8 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
EventQueue eventQueue = { 0, 0, { 0 }};
#line 14 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_initialize() {
#line 17 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
 ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
 SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;


 ADCON0 = ADCON1 = ADCON2 = 0x00;
 C1ON_bit = C2ON_bit =  0 ;


 Timer_initialize();
 Display_initialize();
}
#line 34 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_dispatchEvent(EventHandler handler) {
#line 37 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 eventQueue.eventHandlers[eventQueue.end] = handler;
 eventQueue.end = (eventQueue.end + 1) %  20 ;
#line 43 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.end == eventQueue.next)
 eventQueue.next = (eventQueue.next + 1) %  20 ;
}
#line 51 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_handleEvents() {

 if(eventQueue.next == eventQueue.end) return;
#line 58 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.eventHandlers[eventQueue.next]) {
 eventQueue.eventHandlers[eventQueue.next]();
 eventQueue.eventHandlers[eventQueue.next] = 0;
 }


 eventQueue.next = (eventQueue.next + 1) %  20 ;
}
#line 71 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_run() {
#line 74 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 IPEN_bit =  0 ;
 PEIE_bit = GIE_bit =  1 ;


 while( 1 ) Application_handleEvents();
}
#line 84 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedSecondEvent() {
 static int event_num = 0;
 char output[50];
 sprinti(output, "Second event: %d", event_num);
 Display_writeLine(1, output);
}
#line 94 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Timer_elapsedMinuteEvent() {
 static int event_num = 0;
 char output[50];
 sprinti(output, "Minute event: %d", event_num);
 Display_writeLine(2, output);
}
