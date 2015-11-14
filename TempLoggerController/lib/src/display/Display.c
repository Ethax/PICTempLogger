#include <display/Display.h>
#include <display/NumberToString.h>

/*
 * Inicializ�lja az LCD kijelz�t, t�rli a DDRAM tartalm�t �s kikapcsolja a
 * villog� kurzort.
 */
void Display_initialize() {
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
}

/*
 * Be�ll�tja az LCD kurzor�t a megadott sor elej�re �s fel�l�rja annak
 * tartalm�t.
 */
void Display_writeLine_O(uint8_t line, char* text) {
  /* Az LCD sor�nak hossza �s az �tadott sz�veg hossza k�z�tti k�l�nbs�g
  kisz�m�t�sa. */
  int fill_length = 16 - strlen(text);
  
  /* Az LCD kurzor�nak pozicion�l�sa a megadott sorba a hamis sorsz�mokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A megadott sz�veg ki�rat�sa a be�ll�tott poz�ci�ra �s az LCD sor�nak v�g�ig
  fennmarad� helyek felt�lt�se sz�k�z karakterekkel. */
  Lcd_Out_CP(text);
  while(fill_length-- > 0)
    Lcd_Chr_CP(' ');
}

void Display_writeLine(uint8_t line, char* format, ...) {
  char actual_char;
  va_list va;

  /* Az LCD kurzor�nak pozicion�l�sa a megadott sorba a hamis sorsz�mokat is
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