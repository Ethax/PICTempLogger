#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#include <common.h>

/**
 * @brief Az esem�nykezel�k v�rakoz�si sor�nak m�rete.
 */
#define EVENT_QUEUE_SIZE 20

/**
 * @typedef EventHandler
 * @brief Az esem�nykezel�kre mutat� f�ggv�nypointer t�pusdefin�ci�ja.
 *
 * Az esem�nykezel�knek nincs visszat�r� �rt�ke �s nem fogadnak semmilyen
 * param�tert sem.
 */
typedef void (*EventHandler)(void);

/**
 * @typedef EventQueue
 * @brief Az esem�nykezel�k v�rakoz�si sora.
 *
 * Egy esem�ny l�trej�ttekor az esem�nyhez tartoz� esem�nykezel�re mutat�
 * f�ggv�nypointer ebbe a sorba ker�l bele, a v�grehajt�s�r�l pedig maga az
 * alkalmaz�s magj�ban fut� v�gtelen ciklus gondoskodik.
 */
typedef struct event_queue_t {
  /**
   * A v�rakoz�si sor utols� elem�nek sorsz�ma.
   */
  uint8_t end;
  
  /**
   * A v�rakoz�si sor k�vetkez� elem�nyek sorsz�ma.
   */
  uint8_t next;
  
  /**
   * Az esem�nykezel�kre mutat� f�ggv�nypointereket t�rol� t�mb.
   */
  EventHandler eventHandlers[EVENT_QUEUE_SIZE];
} EventQueue;

/**
 * @brief Inicializ�lja a mikrovez�rl� I/O portjait, a perif�ri�it �s az
 * alkalmaz�st a hozz� kapcsol�d� �sszes modullal egy�tt.
 */
void Application_initialize();

/**
 * @brief Elhelyezi az �tadott esem�nykezel�re mutat� f�ggv�nypointert az
 * esem�nykezel�k v�rakoz�si sor�ban.
 *
 * @param handler Az esem�nykezel�re mutat� f�ggv�nypointer.
 */
void Application_dispatchEvent(EventHandler handler);

/**
 * @brief V�grehajtja a soron k�vetkez� esem�nykezel�t az esem�nykezel�k
 * v�rakoz�si sor�b�l, amennyiben a sor nem �res.
 */
void Application_handleEvents();

/**
 * @brief Enged�lyezi a glob�lis megszak�t�sokat �s v�gtelen ciklusban
 * v�grehajtja a be�kez� esem�nykezel�ket.
 */
void Application_run();

#endif /* INC_APPLICATION_H_ */