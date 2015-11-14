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
 * tartalm�t a form�tummal �s azt k�vet� argumentumok �rt�keivel.
 *
 * @param line A ki�rat�s sor�nak a sz�ma. (�rt�ke 1 vagy 2 lehet.)
 * @param format Az argumentumlista form�z�s�t is mag�ba foglal� sz�veg, ami
 * ki�rat�sra ker�l a kijelz�re.
 * @param ... A ki�ratni k�v�nt argumentumok list�ja. (A hossz�nak �s a benne
 * lev� elemek sorrendj�nek igazodni kell a form�z�shoz.)
 */
void Display_writeLine(uint8_t line, char* format, ...);

/**
 * @brief T�rli az LCD megadott sor�t.
 *
 * @param line A t�r�lni k�v�nt sor.
 */
void Display_clearLine(uint8_t line);

#endif /* INC_DISPLAY_H_ */