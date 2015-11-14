#include <timer/Timer.h>
#include <core/Application.h>

/*
 * A rendszerid� deklar�l�sa �s inicializ�l�sa (1970. janu�r 1. �jf�l).
 */
volatile PICTime systemTime = { 0, 0, 0, 1, 1, 70 };

/*
 * A h�napok hosszait t�rol� t�mb deklar�l�sa �s felt�lt�se.
 */
uint8_t monthsLength[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*
 * Be�ll�tja a Timer0 id�z�t�t egym�sodperces t�lcsordul�s-peri�dusra 8MHz-es
 * �rajel mellett, �s enged�lyezi a Timer0 megszak�t�st az id�z�t�
 * t�lcsordul�s�ra.
 */
void Timer_initialize() {
  /* El�oszt� be�ll�t�sa 1:32-re, el�t�lt�s be�ll�t�sa 3036-ra. (A v�rhat�
  t�lcsordul�s-peri�dus: 1s.) */
  T0CON = 0x84;
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * Kezeli az id�z�t� t�lcsordul�sakor bek�vetkezett megszak�t�st �s t�rli a
 * megszak�t�s jelz�bitj�t.
 */
void Timer_handleInterrupt() {
  /* Az id� sz�ml�l�sa a sz�k��vek figyelembev�tel�vel �s a megfelel�
  esem�nykezel�kre mutat� pointerek elhelyez�se a v�rakoz�si sorban, a k�vetett
  esem�nyek bek�vetkez�sekor. */
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
  
  /* Az id�z�t� el�t�lt�s�nek vissza�ll�t�sa �s a lekezelt megszak�t�s
  jelz�bitj�nek t�rl�se. */
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IF_bit = false;
}

/*
 * Visszaadja az aktu�lis d�tumot �s id�t.
 */
PICTime* Timer_getSystemTime() {
  return &systemTime;
}

/*
 * Be�ll�tja az �j d�tumot �s id�t.
 */
void Timer_setSystemTime(PICTime* time_ptr) {
  /* A Timer0 t�lcsordul�s�ra bek�vetkez� megszak�t�s tilt�sa �s az �tadott id�
  �tm�sol�sa a rendszerid� adatszerkezet�be. */
  TMR0IE_bit = false;
  memcpy(&systemTime, time_ptr, sizeof(PICTime));
  
  /* A Timer0 t�lcsordul�s�ra bek�vetkez� megszak�t�s alaphelyzetbe �ll�t�sa �s
  �jraenged�lyez�se. */
  TMR0H = 0x0B;
  TMR0L = 0xDC;
  TMR0IE_bit = true;
}

/*
 * �talak�tja az �tadott d�tum �s id� adatszerkezetet megjelen�thet�
 * karakterl�ncc� a k�vetkez� s�ma szerint: ����-HH-NN ��:PP:MM
 */
char* Timer_timeToString(PICTime* time_ptr) {
  static char time_str[20];
  uint8_t i = 0;
  
  /* Az �vek �talak�t�sa karakterl�ncc�. */
  time_str[i++] = ((1900 + time_ptr->year) / 1000) + '0';
  time_str[i++] = (((1900 + time_ptr->year) % 1000) / 100) + '0';
  time_str[i++] = (((1900 + time_ptr->year) % 100) / 10) + '0';
  time_str[i++] = ((1900 + time_ptr->year) % 10) + '0';
  time_str[i++] = '-';
  
  /* A h�napok �talak�t�sa karakterl�ncc�. */
  time_str[i++] = ((time_ptr->month) / 10) + '0';
  time_str[i++] = ((time_ptr->month) % 10) + '0';
  time_str[i++] = '-';
  
  /* A napok �talak�t�sa karakterl�ncc�. */
  time_str[i++] = (time_ptr->day / 10) + '0';
  time_str[i++] = (time_ptr->day % 10) + '0';
  time_str[i++] = ' ';
  
  /* Az �r�k �talak�t�sa karakterl�ncc�. */
  time_str[i++] = (time_ptr->hour / 10) + '0';
  time_str[i++] = (time_ptr->hour % 10) + '0';
  time_str[i++] = ':';
  
  /* A percek �talak�t�sa karakterl�ncc�. */
  time_str[i++] = (time_ptr->minute / 10) + '0';
  time_str[i++] = (time_ptr->minute % 10) + '0';
  time_str[i++] = ':';
  
  /* A m�sodpercek �talak�t�sa karakterl�ncc�. */
  time_str[i++] = (time_ptr->second / 10) + '0';
  time_str[i++] = (time_ptr->second % 10) + '0';
  time_str[i++] = '\0';
  
  /* Az �talak�t�s eredm�ny�re mutat� pointer visszaad�sa. */
  return time_str;
}