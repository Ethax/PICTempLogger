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



 typedef char _Bool;
#line 6 "c:/projects/pictemplogger/temploggercontroller/lib/inc/serialcomm/serial.h"
void Serial_initialize();

void Serial_handleInterrupt();
#line 3 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/serialcomm/Serial.c"
void Serial_initialize() {

}

void Serial_handleInterrupt() {

 RC1IF_bit =  0 ;
}
