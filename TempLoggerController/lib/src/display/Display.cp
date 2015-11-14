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
#line 10 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdbool.h"
typedef unsigned char _Bool;
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/include/stdarg.h"





typedef void * va_list[1];
#line 10 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_initialize();
#line 16 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* format, ...);
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
}
#line 18 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_writeLine_O(uint8_t line, char* text) {
#line 21 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 int fill_length = 16 - strlen(text);
#line 25 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(line < 2)
 Lcd_Cmd(_LCD_FIRST_ROW);
 else
 Lcd_Cmd(_LCD_SECOND_ROW);
#line 32 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 Lcd_Out_CP(text);
 while(fill_length-- > 0)
 Lcd_Chr_CP(' ');
}

void Display_writeLine(uint8_t line, char* format, ...) {
 char actual_char;
 va_list va;
#line 43 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(line < 2)
 Lcd_Cmd(_LCD_FIRST_ROW);
 else
 Lcd_Cmd(_LCD_SECOND_ROW);

  *va = (char *)&format + sizeof format ;
 while((actual_char = *(format++))) {
 if(actual_char == '%') {
 actual_char = *(format++);
 switch(actual_char) {
 case 'a':
 Lcd_Out_CP( (*(*(char* **)va)++) );
 break;

 case 'c':
 Lcd_Chr_CP( (*(*(char **)va)++) );
 break;

 case 's':
 Lcd_Out_CP(intToString( (*(*(short **)va)++) , 10));
 break;

 case 'i':
 Lcd_Out_CP(intToString( (*(*(int **)va)++) , 10));
 break;

 case 'l':
 Lcd_Out_CP(intToString( (*(*(long **)va)++) , 10));
 break;

 case 'u':
 actual_char = *(format++);
 switch(actual_char) {
 case 's':
 Lcd_Out_CP(intToString( (*(*(unsigned short **)va)++) , 10));
 break;

 case 'i':
 Lcd_Out_CP(intToString( (*(*(unsigned int **)va)++) , 10));
 break;

 case 'l':
 Lcd_Out_CP(intToString( (*(*(unsigned long **)va)++) , 10));
 break;
 }
 break;

 default:
 if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
 Lcd_Out_CP(floatToString( (*(*(float **)va)++) , actual_char - '0'));
 format++;
 }
 else {
 Lcd_Chr_CP(actual_char);
 }
 }
 }
 else {
 Lcd_Chr_CP(actual_char);
 }
 }
}
