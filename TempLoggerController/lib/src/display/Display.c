#include <display/Display.h>

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
void Display_writeLine(uint8_t line, char* text) {
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