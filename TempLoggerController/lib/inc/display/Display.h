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
 * tartalmát a formátummal és azt követõ argumentumok értékeivel.
 *
 * @param line A kiíratás sorának a száma. (Értéke 1 vagy 2 lehet.)
 * @param format Az argumentumlista formázását is magába foglaló szöveg, ami
 * kiíratásra kerül a kijelzõre.
 * @param ... A kiíratni kívánt argumentumok listája. (A hosszának és a benne
 * levõ elemek sorrendjének igazodni kell a formázáshoz.)
 */
void Display_writeLine(uint8_t line, char* format, ...);

/**
 * @brief Törli az LCD megadott sorát.
 *
 * @param line A törölni kívánt sor.
 */
void Display_clearLine(uint8_t line);

#endif /* INC_DISPLAY_H_ */