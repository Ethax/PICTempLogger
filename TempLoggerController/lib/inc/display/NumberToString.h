#ifndef INC_NUMBERTOSTRING_H_
#define INC_NUMBERTOSTRING_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief �talak�tja a megadott eg�sz sz�mot karakterl�ncc� a megadott
 * sz�mrendszerben kifejezve.
 *
 * @param value Az �talak�tani k�v�nt eg�sz sz�m.
 * @param base Az �talak�t�s eredm�ny�nek sz�mrendszere. (Legkevesebb 2 �s
 * let�bb 16 lehet.)
 * @return A megadott eg�sz sz�m karakterl�nccal reprezent�lt alakja.
 */
char* intToString(int32_t value, uint8_t base);

/**
 * @brief �talak�tja a megadott lebeg�pontos sz�mot karakterl�ncc� a megadott
 * pontoss�gnak megfelel�en.
 *
 * @param value Az �talak�tani k�v�nt lebeg�pontos sz�m.
 * @param precision Az �talak�t�s pontoss�ga.
 * @return A megadott lebeg�pontos sz�m karakterl�nccal reprezent�lt alakja.
 */
char* floatToString(float value, uint8_t precision);

#endif /* INC_NUMBERTOSTRING_H_ */