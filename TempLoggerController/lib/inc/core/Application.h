#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#include <common.h>

/**
 * @brief Az eseménykezelõk várakozási sorának mérete.
 */
#define EVENT_QUEUE_SIZE 20

/**
 * @typedef EventHandler
 * @brief Az eseménykezelõkre mutató függvénypointer típusdefiníciója.
 *
 * Az eseménykezelõknek nincs visszatérõ értéke és nem fogadnak semmilyen
 * paramétert sem.
 */
typedef void (*EventHandler)(void);

/**
 * @typedef EventQueue
 * @brief Az eseménykezelõk várakozási sora.
 *
 * Egy esemény létrejöttekor az eseményhez tartozó eseménykezelõre mutató
 * függvénypointer ebbe a sorba kerül bele, a végrehajtásáról pedig maga az
 * alkalmazás magjában futó végtelen ciklus gondoskodik.
 */
typedef struct event_queue_t {
  /**
   * A várakozási sor utolsó elemének sorszáma.
   */
  uint8_t end;
  
  /**
   * A várakozási sor következõ elemények sorszáma.
   */
  uint8_t next;
  
  /**
   * Az eseménykezelõkre mutató függvénypointereket tároló tömb.
   */
  EventHandler eventHandlers[EVENT_QUEUE_SIZE];
} EventQueue;

/**
 * @brief Inicializálja a mikrovezérlõ I/O portjait, a perifériáit és az
 * alkalmazást a hozzá kapcsolódó összes modullal együtt.
 */
void Application_initialize();

/**
 * @brief Elhelyezi az átadott eseménykezelõre mutató függvénypointert az
 * eseménykezelõk várakozási sorában.
 *
 * @param handler Az eseménykezelõre mutató függvénypointer.
 */
void Application_dispatchEvent(EventHandler handler);

/**
 * @brief Végrehajtja a soron következõ eseménykezelõt az eseménykezelõk
 * várakozási sorából, amennyiben a sor nem üres.
 */
void Application_handleEvents();

/**
 * @brief Engedélyezi a globális megszakításokat és végtelen ciklusban
 * végrehajtja a beékezõ eseménykezelõket.
 */
void Application_run();

#endif /* INC_APPLICATION_H_ */