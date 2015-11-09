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
#line 17 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
typedef void (*EventHandler)(void);
#line 27 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
struct EventQueue {
#line 31 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t end;
#line 36 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 uint8_t next;
#line 41 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
 EventHandler eventHandlers[ 10 ];
};
#line 48 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_initialize();
#line 56 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_dispatchEvent(EventHandler handler);
#line 62 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_handleEvents();
#line 68 "c:/projects/pictemplogger/temploggercontroller/lib/inc/core/application.h"
void Application_run();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_initialize();
#line 19 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_handleInterrupt();

extern void Timer_elapsedSecondEvent();
extern void Timer_elapsedMinuteEvent();
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
struct EventQueue eventQueue = { 0, 0, { 0 }};
#line 13 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_initialize() {
#line 16 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
 LATA = LATB = LATC = LATD = LATE = 0x00;


 ADCON0 = ADCON1 = ADCON2 = 0x00;
 C1ON_bit = C2ON_bit =  0 ;


}
#line 30 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_dispatchEvent(EventHandler handler) {
 eventQueue.eventHandlers[eventQueue.end] = handler;
 eventQueue.end = (eventQueue.end + 1) %  10 ;
}
#line 39 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_handleEvents() {

 if(eventQueue.next == eventQueue.end) return;
#line 46 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 if(eventQueue.eventHandlers[eventQueue.next]) {
 eventQueue.eventHandlers[eventQueue.next]();
 eventQueue.eventHandlers[eventQueue.next] = 0;
 }


 eventQueue.next = (eventQueue.next + 1) %  10 ;
}
#line 59 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
void Application_run() {
#line 62 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/core/Application.c"
 IPEN_bit =  0 ;
 PEIE_bit = GIE_bit =  1 ;


 while( 1 ) Application_handleEvents();
}

void Timer_elapsedSecondEvent() {

}

void Timer_elapsedMinuteEvent() {

}
