#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include <common.h>
#include <storage/Storage.h>

/**
 * A beállítható adatátviteli sebességek felsorolása.
 */
enum BaudRate {
  BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400,
  BAUD_57600, BAUD_115200
};

/**
 * @breif Inicializálja a soros kommunikációs portot és beállíja az adatátviteli
 * sebességet a megadott értéknek megfelelõen, majd engedélyezi a megszakítást
 * az adatbájtok érkezésére.
 *
 * @param baudrate A beállítani kívánt adatátviteli sebesség.
 */
void Serial_initialize(enum BaudRate baudrate);

/**
 * @brief Kezeli a soros portra érkezett adatbájttal járó megszakítást és törli
 * a megszakítás jelzõbitjét.
 *
 * Annak érdekében, hogy a megszakítás le legyen kezelve annak bekövetkezésekor,
 * ennek a függvénynek megszakításokat kiszolgáló rutinban kell lennie.
 */
void Serial_handleInterrupt();

/**
 * @brief Visszaadja a fogadott adatra mutató általános pointert.
 *
 * A fogadott adat típusától függõen a pointert típus-konvertálni kell a
 * fogadott adatnak megfelelõ pointerré.
 *
 * @return A fogadott adatra mutató általános pointer.
 */
void* Serial_getReceivedData();

/**
 * @brief Kiküldi az átadott naplóbejegyzést a soros porton keresztül.
 *
 * @param entry A kiküldésre szánt naplóbejegyzésre mutató pointer.
 */
void Serial_sendLogEntry(LogEntry* entry);

/**
 * @brief Kiküld egy nyugtázó karaktersorozatot a soros porton keresztül.
 */
void Serial_sendAcknowledgement();

/**
 * @brief Az új dátum és idõ fogadása esemény eseménykezelõjének deklarációja.
 * (Az eseménykezelõ törzsét definiálni kell.)
 */
extern void Serial_receivedTimeSettingEvent();

/**
 * @brief Az új riasztási küszöbérték fogadása esemény eseménykezelõjének
 * deklarációja. (Az eseménykezelõ törzsét definiálni kell.)
 */
extern void Serial_receivedThresholdSettingEvent();

/**
 * @brief A naplóbejegyzések elküldésére vonatkozó felszólítás
 * eseménykezelõjének deklarációja. (Az eseménykezelõ törzsét definiálni kell.)
 */
extern void Serial_receivedLogRequestEvent();

#endif /* INC_SERIAL_H_ */