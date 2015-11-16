#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>
#include <core/Application.h>

/**
 * A k�ls� eszk�z�k huzaloz�sainak be�ll�t�sa.
 */
sbit LCD_RS at LATB4_bit; sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN at LATB5_bit; sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4 at LATB0_bit; sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5 at LATB1_bit; sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6 at LATB2_bit; sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7 at LATB3_bit; sbit LCD_D7_Direction at TRISB3_bit;

/**
 * @brief A magas priorit�s� megszak�t�sokat kiszolg�l� rutin.
 *
 * Amennyiben a priorit�skezel�s nincs enged�lyezve, minden megszak�t�s ide fut
 * be.
 */
void interrupt() {
  /* A Timer0 t�lcsordul�s�ra bek�vetkezett megszak�t�s kezel�se. */
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  /* Az UART fogad� puffer�be �rkezett adat hat�s�ra bek�vetkezett megszak�t�s
  kezel�se. */
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program fut�s�nak kezd�pontja.
 */
void main() {
  /* Az alkalmaz�s inicializ�l�sa �s futtat�sa. */
  Application_initialize();
  Application_run();
}