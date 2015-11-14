#include <display/Display.h>
#include <display/NumberToString.h>

/*
 * Inicializálja az LCD kijelzõt, törli a DDRAM tartalmát és kikapcsolja a
 * villogó kurzort.
 */
void Display_initialize() {
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
}

/*
 * Beállítja az LCD kurzorát a megadott sor elejére és felülírja annak
 * tartalmát.
 */
void Display_writeLine_O(uint8_t line, char* text) {
  /* Az LCD sorának hossza és az átadott szöveg hossza közötti különbség
  kiszámítása. */
  int fill_length = 16 - strlen(text);
  
  /* Az LCD kurzorának pozicionálása a megadott sorba a hamis sorszámokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A megadott szöveg kiíratása a beállított pozícióra és az LCD sorának végéig
  fennmaradó helyek feltöltése szóköz karakterekkel. */
  Lcd_Out_CP(text);
  while(fill_length-- > 0)
    Lcd_Chr_CP(' ');
}

void Display_writeLine(uint8_t line, char* format, ...) {
  char actual_char;
  va_list va;

  /* Az LCD kurzorának pozicionálása a megadott sorba a hamis sorszámokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  va_start(va, format);
  while((actual_char = *(format++))) {
    if(actual_char == '%') {
      actual_char = *(format++);
      switch(actual_char) {
      case 'a':
        Lcd_Out_CP(va_arg(va, char*));
        break;

      case 'c':
        Lcd_Chr_CP(va_arg(va, char));
        break;
        
      case 's':
        Lcd_Out_CP(intToString(va_arg(va, short), 10));
        break;
      
      case 'i':
        Lcd_Out_CP(intToString(va_arg(va, int), 10));
        break;
        
      case 'l':
        Lcd_Out_CP(intToString(va_arg(va, long), 10));
        break;
        
      case 'u':
        actual_char = *(format++);
        switch(actual_char) {
        case 's':
          Lcd_Out_CP(intToString(va_arg(va, unsigned short), 10));
          break;

        case 'i':
          Lcd_Out_CP(intToString(va_arg(va, unsigned int), 10));
          break;

        case 'l':
          Lcd_Out_CP(intToString(va_arg(va, unsigned long), 10));
          break;
        }
        break;
        
      default:
        if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
          Lcd_Out_CP(floatToString(va_arg(va, float), actual_char - '0'));
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