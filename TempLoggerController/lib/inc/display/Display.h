#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <common.h>

/**
 * @brief Inicializ�lja az LCD kijelz�t, t�rli a DDRAM tartalm�t �s kikapcsolja
 * a villog� kurzort.
 */
void Display_initialize();

/**
 * @brief Be�ll�tja az LCD kurzor�t a megadott sor elej�re �s fel�l�rja annak
 * tartalm�t.
 */
void Display_writeLine(uint8_t line, char* text);

#endif /* INC_DISPLAY_H_ */