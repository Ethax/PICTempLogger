#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include <common.h>
#include <storage/Storage.h>

/**
 * A be�ll�that� adat�tviteli sebess�gek felsorol�sa.
 */
enum BaudRate {
  BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400,
  BAUD_57600, BAUD_115200
};

/**
 * @breif Inicializ�lja a soros kommunik�ci�s portot �s be�ll�ja az adat�tviteli
 * sebess�get a megadott �rt�knek megfelel�en, majd enged�lyezi a megszak�t�st
 * az adatb�jtok �rkez�s�re.
 *
 * @param baudrate A be�ll�tani k�v�nt adat�tviteli sebess�g.
 */
void Serial_initialize(enum BaudRate baudrate);

/**
 * @brief Kezeli a soros portra �rkezett adatb�jttal j�r� megszak�t�st �s t�rli
 * a megszak�t�s jelz�bitj�t.
 *
 * Annak �rdek�ben, hogy a megszak�t�s le legyen kezelve annak bek�vetkez�sekor,
 * ennek a f�ggv�nynek megszak�t�sokat kiszolg�l� rutinban kell lennie.
 */
void Serial_handleInterrupt();

/**
 * @brief Visszaadja a fogadott adatra mutat� �ltal�nos pointert.
 *
 * A fogadott adat t�pus�t�l f�gg�en a pointert t�pus-konvert�lni kell a
 * fogadott adatnak megfelel� pointerr�.
 *
 * @return A fogadott adatra mutat� �ltal�nos pointer.
 */
void* Serial_getReceivedData();

/**
 * @brief Kik�ldi az �tadott napl�bejegyz�st a soros porton kereszt�l.
 *
 * @param entry A kik�ld�sre sz�nt napl�bejegyz�sre mutat� pointer.
 */
void Serial_sendLogEntry(LogEntry* entry);

/**
 * @brief Kik�ld egy nyugt�z� karaktersorozatot a soros porton kereszt�l.
 */
void Serial_sendAcknowledgement();

/**
 * @brief Az �j d�tum �s id� fogad�sa esem�ny esem�nykezel�j�nek deklar�ci�ja.
 * (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Serial_receivedTimeSettingEvent();

/**
 * @brief Az �j riaszt�si k�sz�b�rt�k fogad�sa esem�ny esem�nykezel�j�nek
 * deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Serial_receivedThresholdSettingEvent();

/**
 * @brief A napl�bejegyz�sek elk�ld�s�re vonatkoz� felsz�l�t�s
 * esem�nykezel�j�nek deklar�ci�ja. (Az esem�nykezel� t�rzs�t defini�lni kell.)
 */
extern void Serial_receivedLogRequestEvent();

#endif /* INC_SERIAL_H_ */