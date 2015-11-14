#include <timer/Timer.h>
#include <core/Application.h>

/*
 * A rendszeridõ deklarálása és inicializálása (1970. január 1. éjfél).
 */
volatile PICTime systemTime = { 0, 0, 0, 1, 1, 70 };

/*
 * A hónapok hosszait tároló tömb deklarálása és feltöltése.
 */
uint8_t monthsLength[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*
 * Beállítja a Timer0 idõzítõt egymásodperces túlcsordulás-periódusra 8MHz-es
 * órajel mellett, és engedélyezi a Timer0 megszakítást az idõzítõ
 * túlcsordulására.
 */
void Timer_initialize() {
  /* Elõosztó beállítása 1:32-re, elõtöltés beállítása 3036-ra. (A várható
  túlcsordulás-periódus: 1s.) */
  T0CON = 0x84;
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * Kezeli az idõzítõ túlcsordulásakor bekövetkezett megszakítást és törli a
 * megszakítás jelzõbitjét.
 */
void Timer_handleInterrupt() {
  /* Az idõ számlálása a szökõévek figyelembevételével és a megfelelõ
  eseménykezelõkre mutató pointerek elhelyezése a várakozási sorban, a követett
  események bekövetkezésekor. */
  if(++systemTime.second > 59) {
    systemTime.second = 0;
    if(++systemTime.minute > 59) {
      systemTime.minute = 0;
      if(++systemTime.hour > 23) {
        systemTime.hour = 0;
        if(++systemTime.day > monthsLength[systemTime.month - 1]) {
          systemTime.day = 1;
          if(++systemTime.month > 12) {
            systemTime.month = 1;
            systemTime.year++;
            if(!(systemTime.year && 0b00000011))
              monthsLength[1] = 29;
            else
              monthsLength[1] = 28;
          }
        }
      }
    }
    Application_dispatchEvent(Timer_elapsedMinuteEvent);
  }
  Application_dispatchEvent(Timer_elapsedSecondEvent);
  
  /* Az idõzítõ elõtöltésének visszaállítása és a lekezelt megszakítás
  jelzöbitjének törlése. */
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IF_bit = false;
}

/*
 * Visszaadja az aktuális dátumot és idõt.
 */
PICTime* Timer_getSystemTime() {
  return &systemTime;
}

/*
 * Beállítja az új dátumot és idõt.
 */
void Timer_setSystemTime(PICTime* time_ptr) {
  /* A Timer0 túlcsordulására bekövetkezõ megszakítás tiltása és az átadott idõ
  átmásolása a rendszeridõ adatszerkezetébe. */
  TMR0IE_bit = false;
  memcpy(&systemTime, time_ptr, sizeof(PICTime));
  
  /* A Timer0 túlcsordulására bekövetkezõ megszakítás alaphelyzetbe állítása és
  újraengedélyezése. */
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * Átalakítja az átadott dátum és idõ adatszerkezetet megjeleníthetõ
 * karakterlánccá a következõ séma szerint: ÉÉÉÉ-HH-NN ÓÓ:PP:MM
 */
char* Timer_timeToString(PICTime* time_ptr) {
  static char time_str[20];
  uint8_t i = 0;
  
  /* Az évek átalakítása karakterlánccá. */
  time_str[i++] = ((1900 + time_ptr->year) / 1000) + '0';
  time_str[i++] = (((1900 + time_ptr->year) % 1000) / 100) + '0';
  time_str[i++] = (((1900 + time_ptr->year) % 100) / 10) + '0';
  time_str[i++] = ((1900 + time_ptr->year) % 10) + '0';
  time_str[i++] = '-';
  
  /* A hónapok átalakítása karakterlánccá. */
  time_str[i++] = ((time_ptr->month) / 10) + '0';
  time_str[i++] = ((time_ptr->month) % 10) + '0';
  time_str[i++] = '-';
  
  /* A napok átalakítása karakterlánccá. */
  time_str[i++] = (time_ptr->day / 10) + '0';
  time_str[i++] = (time_ptr->day % 10) + '0';
  time_str[i++] = ' ';
  
  /* Az órák átalakítása karakterlánccá. */
  time_str[i++] = (time_ptr->hour / 10) + '0';
  time_str[i++] = (time_ptr->hour % 10) + '0';
  time_str[i++] = ':';
  
  /* A percek átalakítása karakterlánccá. */
  time_str[i++] = (time_ptr->minute / 10) + '0';
  time_str[i++] = (time_ptr->minute % 10) + '0';
  time_str[i++] = ':';
  
  /* A másodpercek átalakítása karakterlánccá. */
  time_str[i++] = (time_ptr->second / 10) + '0';
  time_str[i++] = (time_ptr->second % 10) + '0';
  time_str[i++] = '\0';
  
  /* Az átalakítás eredményére mutató pointer visszaadása. */
  return time_str;
}