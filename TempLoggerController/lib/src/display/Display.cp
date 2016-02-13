#line 1 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
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
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_initialize();
#line 22 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* format, ...);
#line 29 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_clearLine(uint8_t line);
#line 1 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdint.h"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"
#line 16 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
char* intToString(int32_t value, uint8_t base);
#line 26 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/numbertostring.h"
char* floatToString(float value, uint8_t precision);
#line 8 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_initialize() {
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 5, "Ready...");
}
#line 19 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_writeLine(uint8_t line, char* format, ...) {
 int fill_length = 16;
 char actual_char;
 char* string_ptr;
 va_list va;
#line 27 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(line < 2)
 Lcd_Cmd(_LCD_FIRST_ROW);
 else
 Lcd_Cmd(_LCD_SECOND_ROW);


  *va = (char *)&format + sizeof format ;
 while((actual_char = *(format++))) {
#line 38 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(actual_char == '%') {
 actual_char = *(format++);
 switch(actual_char) {
 case 'a':
 string_ptr =  (*(*(char* **)va)++) ;
 Lcd_Out_CP(string_ptr);
 break;
 case 'c':
 fill_length--;
 Lcd_Chr_CP( (*(*(char **)va)++) );
 break;
 case 's':
 string_ptr = intToString( (*(*(short **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 case 'i':
 string_ptr = intToString( (*(*(int **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 case 'l':
 string_ptr = intToString( (*(*(long **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 case 'u':
 actual_char = *(format++);
 switch(actual_char) {
 case 's':
 string_ptr = intToString( (*(*(unsigned short **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 case 'i':
 string_ptr = intToString( (*(*(unsigned int **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 case 'l':
 string_ptr = intToString( (*(*(unsigned long **)va)++) , 10);
 Lcd_Out_CP(string_ptr);
 break;
 }
 break;
 default:
 if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
 string_ptr = floatToString( (*(*(float **)va)++) , actual_char - '0');
 Lcd_Out_CP(string_ptr);
 format++;
 }
 else {
 fill_length--;
 Lcd_Chr_CP(actual_char);
 }
 }
#line 93 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(string_ptr) {
 fill_length -= strlen(string_ptr);
 string_ptr = 0;
 }
 }
#line 100 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 else {
 fill_length--;
 Lcd_Chr_CP(actual_char);
 }
 }
#line 108 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 while(fill_length-- > 0)
 Lcd_Chr_CP(' ');
}
#line 115 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_clearLine(uint8_t line) {
 uint8_t current_char;
#line 120 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(line < 2)
 Lcd_Cmd(_LCD_FIRST_ROW);
 else
 Lcd_Cmd(_LCD_SECOND_ROW);
#line 127 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 for(current_char = 0; current_char < 16; current_char++)
 Lcd_Chr_CP(' ');
}
