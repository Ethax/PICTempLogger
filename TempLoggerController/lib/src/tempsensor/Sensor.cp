#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/tempsensor/Sensor.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
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
#line 13 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
void Sensor_initialize(const float _vref);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/tempsensor/sensor.h"
float Sensor_getTemperature();
#line 6 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/tempsensor/Sensor.c"
float VREF = 0;

void Sensor_initialize(const float _vref) {

 ANSELE = 0x02;
 TRISE1_bit = 1;
#line 15 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/tempsensor/Sensor.c"
 ADC_Init();
 VREF = _vref;
}
#line 23 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/tempsensor/Sensor.c"
float Sensor_getTemperature() {
#line 26 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/tempsensor/Sensor.c"
 unsigned int temp_res = ADC_Get_Sample(6);


 return ((float)temp_res * VREF) / 10.240;
}
