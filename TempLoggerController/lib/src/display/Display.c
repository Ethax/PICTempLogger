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
  Lcd_Out(1, 5, "Ready...");
}

/*
 * Be�ll�tja az LCD kurzor�t a megadott sor elej�re �s fel�l�rja annak tartalm�t
 * a form�tummal �s azt k�vet� argumentumok �rt�keivel.
 */
void Display_writeLine(uint8_t line, char* format, ...) {
  int fill_length = 16;
  char actual_char;
  char* string_ptr;
  va_list va;

  /* Az LCD kurzor�nak pozicion�l�sa a megadott sorba a hamis sorsz�mokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A form�tum minden egyes karakter�nek megvizsg�l�sa. */
  va_start(va, format);
  while((actual_char = *(format++))) {
    /* Az argumentumok karakterl�ncokk� alak�t�sa �s ki�rat�sa az LCD-re a
    megadott form�z�si param�terek szerint, ha az aktu�lis karakter valamilyen
    form�z�st vezet be. */
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
      
      /* A kijelz� kiv�lasztott sor�nak v�g�ig fennmarad� karaktereket t�rol�
      v�ltoz� friss�t�se az �talak�t�sb�l sz�rmaz� karakterl�nc hossz�nak
      kivon�s�val az aktu�lis �rt�k�b�l. */
      if(string_ptr) {
        fill_length -= strlen(string_ptr);
        string_ptr = 0;
      }
    }
    /* Az aktu�lis karakter ki�r�sa a kijelz�re, ha nem vezet be semmilyen
    form�z�st sem. */
    else {
      fill_length--;
      Lcd_Chr_CP(actual_char);
    }
  }
  
  /* A kijelz� kiv�lasztott sor�nak v�g�ig fennmarad� helyek felt�lt�se
  sz�k�z�kkel a kor�bban ki�ratott sz�veg t�rl�s�nek �rdek�ben. */
  while(fill_length-- > 0)
    Lcd_Chr_CP(' ');
}

/*
 * T�rli az LCD megadott sor�t.
 */
void Display_clearLine(uint8_t line) {
  uint8_t current_char;
  
  /* Az LCD kurzor�nak pozicion�l�sa a megadott sorba a hamis sorsz�mokat is
  kezelve. */
  if(line < 2)
    Lcd_Cmd(_LCD_FIRST_ROW);
  else
    Lcd_Cmd(_LCD_SECOND_ROW);
  
  /* A kijelz� kiv�lasztott sor�nak felt�lt�se sz�k�z�kkel a kor�bban ki�ratott
  sz�veg t�rl�s�nek �rdek�ben. */
  for(current_char = 0; current_char < 16; current_char++)
    Lcd_Chr_CP(' ');
}