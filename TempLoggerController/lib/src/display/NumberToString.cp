#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
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
#line 16 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
char* intToString(int32_t value, uint8_t base);
#line 26 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
char* floatToString(float value, uint8_t precision);
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
char* intToString(int32_t value, uint8_t base) {
 static const char DIGIT_MAP[] = "0123456789ABCDEF";
 static char result[17];
 uint8_t max_length = 14;


  _Bool  isNegative = value < 0 ?  1  :  0 ;
 if(isNegative) value = -value;
#line 19 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 if(base < 2 || base > 16 || !value) return "0";


 result[max_length + isNegative + 1] = '\0';
 for(; value && max_length ; --max_length, value /= base)
 result[max_length + isNegative] = DIGIT_MAP[value % base];
#line 28 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 if(isNegative) result[max_length + 1] = '-';
 return &result[max_length + 1];
}
#line 36 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
char* floatToString(float value, uint8_t precision) {
 static char result[15];
 char* result_ptr;
 int32_t mantissa, int_part = 0, frac_part = 0;
 int8_t exponent;
 uint8_t length, max_length;
 char* str_ptr;
#line 46 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 union { int32_t raw_value; float float_value; } _value;
 _value.float_value = value;
 exponent = (uint8_t)(_value.raw_value >> 24) - 127;
 mantissa = (_value.raw_value & 0xFFFFFF) | 0x800000;
#line 53 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 if(exponent >= 31 || exponent < -23 || !_value.raw_value) return "0.0";


 if(exponent >= 23) {
 int_part = mantissa << (exponent - 23);
 }
 else if(exponent >= 0) {
 int_part = mantissa >> (23 - exponent);
 frac_part = (mantissa << (exponent + 1)) & 0xFFFFFF;
 }
 else {
 frac_part = (mantissa & 0xFFFFFF) >> -(exponent + 1);
 }
#line 69 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 result_ptr = result;
 if(_value.raw_value & 0x800000) *result_ptr++ = '-';


 if(int_part == 0) {
 *result_ptr++ = '0';
 }
 else {
 str_ptr = intToString(int_part, 10);
 while(*str_ptr)
 *result_ptr++ = *str_ptr++;
 }


 *result_ptr++ = '.';
 if(frac_part == 0) {
 *result_ptr++ = '0';
 }
 else {
 max_length = precision ? precision : (sizeof(result) - (result_ptr - result) - 1);
 if(max_length > 7) max_length = 7;
#line 93 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 for(length = 0; length < max_length; length++) {
 frac_part = (frac_part << 3) + (frac_part << 1);
 *result_ptr++ = (frac_part >> 24) + '0';
 frac_part &= 0xFFFFFF;
 }
#line 101 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 for(--result_ptr; result_ptr[0] == '0' && result_ptr[-1] != '.'; --result_ptr);
 ++result_ptr;
 }
#line 107 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/NumberToString.c"
 *result_ptr = '\0';
 return result;
}
