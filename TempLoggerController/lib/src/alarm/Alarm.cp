#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
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
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_initialize();
#line 18 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_setThreshold(float _threshold);
#line 25 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
float Alarm_getThreshold();
#line 30 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_clearThreshold();
#line 43 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_checkConditions(float _temperature);
#line 48 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_playAlarmSound();
#line 53 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
void Alarm_beep();
#line 59 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/alarm.h"
extern void Alarm_thresholdExceededEvent();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/melody.h"
#line 130 "c:/projects/pictemplogger/temploggercontroller/lib/inc/alarm/melody.h"
void playTheImperialMarch() {
 Sound_Play( 880.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 880.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 880.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 880.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  2 * 60000 / 160 ); Delay_ms(1 +  2 * 60000 / 160 );

 Sound_Play( 1318.51 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1318.51 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1318.51 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1396.91 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 830.61 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  2 * 60000 / 160 ); Delay_ms(1 +  2 * 60000 / 160 );

 Sound_Play( 1760.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 880.00 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1760.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1661.22 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1567.98 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 1479.98 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1318.51 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1396.91 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 932.33 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 1244.51 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1174.66 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1108.73 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 987.77 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 698.46 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 830.61 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 1046.50 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 880.00 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1318.51 ,  2 * 60000 / 160 ); Delay_ms(1 +  2 * 60000 / 160 );

 Sound_Play( 1760.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 880.00 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1760.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1661.22 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1567.98 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 1479.98 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1318.51 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1396.91 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 932.33 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 1244.51 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 1174.66 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1108.73 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 987.77 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 698.46 ,  60000 / 160  / 2 ); Delay_ms(1 +  60000 / 160  / 2 );
 Sound_Play( 830.61 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );

 Sound_Play( 880.00 ,  60000 / 160 ); Delay_ms(1 +  60000 / 160 );
 Sound_Play( 698.46 ,  60000 / 160  / 2  +  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 2  +  60000 / 160  / 4 );
 Sound_Play( 1046.50 ,  60000 / 160  / 4 ); Delay_ms(1 +  60000 / 160  / 4 );
 Sound_Play( 880.00 ,  2 * 60000 / 160 ); Delay_ms(1 +  2 * 60000 / 160 );
}
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
#line 8 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
float threshold = 90.0f;
#line 14 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
 _Bool  isAlerted =  0 ;
#line 19 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
 _Bool  isThresholdSet =  0 ;
#line 26 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_initialize() {
 Sound_Init(&PORTC, 2);
 Alarm_beep();
}
#line 34 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_setThreshold(float _threshold) {
 threshold = _threshold;
 isThresholdSet =  1 ;
}
#line 42 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
float Alarm_getThreshold() {
 return threshold;
}
#line 49 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_clearThreshold() {
 threshold = 0.0f;
 isThresholdSet =  0 ;
}
#line 58 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_checkConditions(float _temperature) {
#line 61 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
 if(!isThresholdSet) return;
#line 66 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
 if(_temperature > threshold && !isAlerted) {
 isAlerted =  1 ;
 Alarm_thresholdExceededEvent();
 }
 else if(_temperature <= threshold && isAlerted) {
 isAlerted =  0 ;
 }
}
#line 78 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_playAlarmSound() {
 playTheImperialMarch();
}
#line 85 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/alarm/Alarm.c"
void Alarm_beep() {
 Sound_Play(880, 1000);
}
