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
#line 16 "c:/projects/pictemplogger/temploggercontroller/lib/inc/display/display.h"
void Display_writeLine(uint8_t line, char* text);
#line 7 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_initialize() {
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
}
#line 17 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
void Display_writeLine(uint8_t line, char* text) {
#line 20 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 int fill_length = 16 - strlen(text);
#line 24 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 if(line < 2)
 Lcd_Cmd(_LCD_FIRST_ROW);
 else
 Lcd_Cmd(_LCD_SECOND_ROW);
#line 31 "C:/Projects/PICTempLogger/TempLoggerController/lib/src/display/Display.c"
 Lcd_Out_CP(text);
 while(fill_length-- > 0)
 Lcd_Chr_CP(' ');
}
