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



 typedef char _Bool;
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_initialize();
#line 19 "c:/projects/pictemplogger/temploggercontroller/lib/inc/timer/timer.h"
void Timer_handleInterrupt();
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/common.h"
#line 6 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_initialize();

void Serial_handleInterrupt();
#line 16 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
void interrupt() {
 if(TMR0IF_bit && TMR0IE_bit)
 Timer_handleInterrupt();
 else if(RC1IF_bit && RC1IE_bit)
 Serial_handleInterrupt();
}
#line 26 "C:/Projects/PICTempLogger/TempLoggerController/app/src/Main.c"
void main() {


 return;
}
