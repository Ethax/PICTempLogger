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
  Lcd_Out(1, 5, "Ready...");
}

/*
 * Beállítja az LCD kurzorát a megadott sor elejére és felülírja annak tartalmát
 * a formátummal és azt követõ argumentumok értékeivel.
 */
void Display_writeLine(uint8_t line, char* format, ...) {
  int fill_length = 16;
  char actual_char;
  char* string_ptr;
  va_list va;

  /* Az LCD kurzorának pozicionálása a megadott sorba a hamis sorszámokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A formátum minden egyes karakterének megvizsgálása. */
  va_start(va, format);
  while((actual_char = *(format++))) {
    /* Az argumentumok karakterláncokká alakítása és kiíratása az LCD-re a
    megadott formázási paraméterek szerint, ha az aktuális karakter valamilyen
    formázást vezet be. */
    if(actual_char == '%') {
      actual_char = *(format++);
      switch(actual_char) {
      case 'a': /* alphanumeric */
        string_ptr = va_arg(va, char*);
        Lcd_Out_CP(string_ptr);
        break;
      case 'c': /* char */
        fill_length--;
        Lcd_Chr_CP(va_arg(va, char));
        break;
      case 's': /* (signed) short int */
        string_ptr = intToString(va_arg(va, short), 10);
        Lcd_Out_CP(string_ptr);
        break;
      case 'i': /* (signed) int */
        string_ptr = intToString(va_arg(va, int), 10);
        Lcd_Out_CP(string_ptr);
        break;
      case 'l': /* (signed) long int */
        string_ptr = intToString(va_arg(va, long), 10);
        Lcd_Out_CP(string_ptr);
        break;
      case 'u': /* unsigned */
        actual_char = *(format++);
        switch(actual_char) {
        case 's': /* unsigned short int */
          string_ptr = intToString(va_arg(va, unsigned short), 10);
          Lcd_Out_CP(string_ptr);
          break;
        case 'i': /* unsigned int */
          string_ptr = intToString(va_arg(va, unsigned int), 10);
          Lcd_Out_CP(string_ptr);
          break;
        case 'l': /* unsigned long int */
          string_ptr = intToString(va_arg(va, unsigned long), 10);
          Lcd_Out_CP(string_ptr);
          break;
        }
        break;
      default:
        if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
          string_ptr = floatToString(va_arg(va, float), actual_char - '0');
          Lcd_Out_CP(string_ptr);
          format++;
        }
        else {
          fill_length--;
          Lcd_Chr_CP(actual_char);
        }
      }
      
      /* A kijelzõ kiválasztott sorának végéig fennmaradó karaktereket tároló
      változó frissítése az átalakításból származó karakterlánc hosszának
      kivonásával az aktuális értékébõl. */
      if(string_ptr) {
        fill_length -= strlen(string_ptr);
        string_ptr = 0;
      }
    }
    /* Az aktuális karakter kiírása a kijelzõre, ha nem vezet be semmilyen
    formázást sem. */
    else {
      fill_length--;
      Lcd_Chr_CP(actual_char);
    }
  }
  
  /* A kijelzõ kiválasztott sorának végéig fennmaradó helyek feltöltése
  szóközökkel a korábban kiíratott szöveg törlésének érdekében. */
  while(fill_length-- > 0)
    Lcd_Chr_CP(' ');
}

/*
 * Törli az LCD megadott sorát.
 */
void Display_clearLine(uint8_t line) {
  uint8_t current_char;
  
  /* Az LCD kurzorának pozicionálása a megadott sorba a hamis sorszámokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A kijelzõ kiválasztott sorának feltöltése szóközökkel a korábban kiíratott
  szöveg törlésének érdekében. */
  for(current_char = 0; current_char < 16; current_char++)
    Lcd_Chr_CP(' ');
}