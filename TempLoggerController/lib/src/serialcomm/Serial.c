#include <serialcomm/Serial.h>
#include <core/Application.h>

uint8_t receiveBuffer[20] = { 0 };

uint8_t transmitBuffer[20] = { 0 };

uint8_t receiveCounter = 0;

/*
 * Inicializálja a soros kommunikációs portot és beállíja az adatátviteli
 * sebességet a megadott értéknek megfelelõen, majd engedélyezi a megszakítást
 * az adatbájtok érkezésére.
 */
void Serial_initialize(enum BaudRate baudrate) {
  /* A soros kommunikációs port inicializálása és a megadott adatátviteli
  sebesség beállítása. */
  switch(baudrate) {
  case BAUD_1200:
    UART1_Init(1200); break;
  case BAUD_2400:
    UART1_Init(2400); break;
  case BAUD_4800:
    UART1_Init(4800); break;
  case BAUD_9600:
    UART1_Init(9600); break;
  case BAUD_19200:
    UART1_Init(19200); break;
  case BAUD_38400:
    UART1_Init(38400); break;
  case BAUD_57600:
    UART1_Init(57600); break;
  case BAUD_115200:
    UART1_Init(115200); break;
  }

  /* A soros portra érkezett adatbájtokkal járó megszakítások engedélyezése. */
  RC1IF_bit = false;
  RC1IE_bit = true;
}

/*
 * Kezeli a soros portra érkezett adatbájttal járó megszakítást és törli a
 * megszakítás jelzõbitjét.
 */
void Serial_handleInterrupt() {
  /* A fogadott bájt kiolvasása a soros port pufferébõl. */
  uint8_t next_byte = UART1_Read();

  /* A fogadott üzenet elsõ bájtja alapján a megfelelõ eseménykezelõre mutató
  pointer elhelyezése a várakozási sorban, amennyiben az üzenetet lezáró
  karakter megérkezett.*/
  if(next_byte == '\n') {
    switch(receiveBuffer[0]) {
    case 'T': /* Time Setting */
      Application_dispatchEvent(Serial_receivedTimeSettingEvent);
      break;
    case 'R': /* Threshold Setting */
      Application_dispatchEvent(Serial_receivedThresholdSettingEvent);
      break;
    case 'L': /* Log Request */
      Application_dispatchEvent(Serial_receivedLogRequestEvent);
      break;
    }
    receiveCounter = 0;
  }
  /* Az üzenet fogadott bájtjának letárolása az üzenetek fogadására fenntartott
  pufferbe, amennyiben a fogadott bájt különbözik az üzenetet lezáró
  karaktertõl. */
  else {
    receiveBuffer[receiveCounter++] = next_byte;
  }
  
  /* A lekezelt megszakítás jelzöbitjének törlése. */
  RC1IF_bit = false;
}

/*
 * Lekérdezi a fogadott adatra mutató általános pointert.
 */
void* Serial_getReceivedData() {
  return (void*)&receiveBuffer[1];
}

/*
 * Kiküldi az átadott naplóbejegyzést a soros porton keresztül.
 */
void Serial_sendLogEntry(LogEntry* entry) {
  uint8_t i;

  /* Az kiküldésre szánt naplóbejegyzés átmásolása a kimenõ pufferbe és a puffer
  minden egyes bájtjának kilüdése a soros porton keresztül. */
  memcpy(transmitBuffer, entry, sizeof(LogEntry));
  for(i = 0; i < sizeof(LogEntry); i++)
    UART1_Write(transmitBuffer[i]);
  
  /* A lezáró karakter küldése a soros porton keresztül az adatátvitel
  befejezésének érdekében. */
  UART1_Write('\n');
}

/*
 * Kiküld egy nyugtázó karaktersorozatot a soros porton keresztül.
 */
void Serial_sendAcknowledgement() {
  /* A nyugtázó "ACK" karaktersorozat kiküldése a soros porton keresztül. */
  UART1_Write('A'); UART1_Write('C'); UART1_Write('K');
  
  /* A lezáró karakter küldése a soros porton keresztül az adatátvitel
  befejezésének érdekében. */
  UART1_Write('\n');
}