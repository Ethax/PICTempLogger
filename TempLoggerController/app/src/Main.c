#include <common.h>
#include <timer/Timer.h>
#include <serialcomm/Serial.h>
#include <core/Application.h>

/**
 * A külsõ eszközök huzalozásainak beállítása.
 */
sbit LCD_RS at LATB4_bit; sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN at LATB5_bit; sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4 at LATB0_bit; sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5 at LATB1_bit; sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6 at LATB2_bit; sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7 at LATB3_bit; sbit LCD_D7_Direction at TRISB3_bit;

/**
 * @brief A magas prioritású megszakításokat kiszolgáló rutin.
 *
 * Amennyiben a prioritáskezelés nincs engedélyezve, minden megszakítás ide fut
 * be.
 */
void interrupt() {
  /* A Timer0 túlcsordulására bekövetkezett megszakítás kezelése. */
  if(TMR0IF_bit && TMR0IE_bit)
    Timer_handleInterrupt();
  /* Az UART fogadó pufferébe érkezett adat hatására bekövetkezett megszakítás
  kezelése. */
  else if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program futásának kezdõpontja.
 */
void main() {
  /* Az alkalmazás inicializálása és futtatása. */
  Application_initialize();
  Application_run();
}