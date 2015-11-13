#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <common.h>

/**
 * @brief Inicializálja az LCD kijelzõt, törli a DDRAM tartalmát és kikapcsolja
 * a villogó kurzort.
 */
void Display_initialize();

/**
 * @brief Beállítja az LCD kurzorát a megadott sor elejére és felülírja annak
 * tartalmát.
 */
void Display_writeLine(uint8_t line, char* text);

#endif /* INC_DISPLAY_H_ */