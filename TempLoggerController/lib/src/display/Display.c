#include <display/Display.h>

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
void Display_writeLine(uint8_t line, char* text) {
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