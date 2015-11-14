#ifndef INC_NUMBERTOSTRING_H_
#define INC_NUMBERTOSTRING_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Átalakítja a megadott egész számot karakterlánccá a megadott
 * számrendszerben kifejezve.
 *
 * @param value Az átalakítani kívánt egész szám.
 * @param base Az átalakítás eredményének számrendszere. (Legkevesebb 2 és
 * letöbb 16 lehet.)
 * @return A megadott egész szám karakterlánccal reprezentált alakja.
 */
char* intToString(int32_t value, uint8_t base);

/**
 * @brief Átalakítja a megadott lebegõpontos számot karakterlánccá a megadott
 * pontosságnak megfelelõen.
 *
 * @param value Az átalakítani kívánt lebegõpontos szám.
 * @param precision Az átalakítás pontossága.
 * @return A megadott lebegõpontos szám karakterlánccal reprezentált alakja.
 */
char* floatToString(float value, uint8_t precision);

#endif /* INC_NUMBERTOSTRING_H_ */