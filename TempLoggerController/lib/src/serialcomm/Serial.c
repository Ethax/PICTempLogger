#include <serialcomm/Serial.h>
#include <core/Application.h>

uint8_t receiveBuffer[20] = { 0 };

uint8_t transmitBuffer[20] = { 0 };

uint8_t receiveCounter = 0;

/*
 * Inicializ�lja a soros kommunik�ci�s portot �s be�ll�ja az adat�tviteli
 * sebess�get a megadott �rt�knek megfelel�en, majd enged�lyezi a megszak�t�st
 * az adatb�jtok �rkez�s�re.
 */
void Serial_initialize(enum BaudRate baudrate) {
  /* A soros kommunik�ci�s port inicializ�l�sa �s a megadott adat�tviteli
  sebess�g be�ll�t�sa. */
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

  /* A soros portra �rkezett adatb�jtokkal j�r� megszak�t�sok enged�lyez�se. */
  RC1IF_bit = false;
  RC1IE_bit = true;
}

/*
 * Kezeli a soros portra �rkezett adatb�jttal j�r� megszak�t�st �s t�rli a
 * megszak�t�s jelz�bitj�t.
 */
void Serial_handleInterrupt() {
  /* A fogadott b�jt kiolvas�sa a soros port puffer�b�l. */
  uint8_t next_byte = UART1_Read();

  /* A fogadott �zenet els� b�jtja alapj�n a megfelel� esem�nykezel�re mutat�
  pointer elhelyez�se a v�rakoz�si sorban, amennyiben az �zenetet lez�r�
  karakter meg�rkezett.*/
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
  /* Az �zenet fogadott b�jtj�nak let�rol�sa az �zenetek fogad�s�ra fenntartott
  pufferbe, amennyiben a fogadott b�jt k�l�nb�zik az �zenetet lez�r�
  karaktert�l. */
  else {
    receiveBuffer[receiveCounter++] = next_byte;
  }
  
  /* A lekezelt megszak�t�s jelz�bitj�nek t�rl�se. */
  RC1IF_bit = false;
}

/*
 * Lek�rdezi a fogadott adatra mutat� �ltal�nos pointert.
 */
void* Serial_getReceivedData() {
  return (void*)&receiveBuffer[1];
}

/*
 * Kik�ldi az �tadott napl�bejegyz�st a soros porton kereszt�l.
 */
void Serial_sendLogEntry(LogEntry* entry) {
  uint8_t i;

  /* Az kik�ld�sre sz�nt napl�bejegyz�s �tm�sol�sa a kimen� pufferbe �s a puffer
  minden egyes b�jtj�nak kil�d�se a soros porton kereszt�l. */
  memcpy(transmitBuffer, entry, sizeof(LogEntry));
  for(i = 0; i < sizeof(LogEntry); i++)
    UART1_Write(transmitBuffer[i]);
  
  /* A lez�r� karakter k�ld�se a soros porton kereszt�l az adat�tvitel
  befejez�s�nek �rdek�ben. */
  UART1_Write('\n');
}

/*
 * Kik�ld egy nyugt�z� karaktersorozatot a soros porton kereszt�l.
 */
void Serial_sendAcknowledgement() {
  /* A nyugt�z� "ACK" karaktersorozat kik�ld�se a soros porton kereszt�l. */
  UART1_Write('A'); UART1_Write('C'); UART1_Write('K');
  
  /* A lez�r� karakter k�ld�se a soros porton kereszt�l az adat�tvitel
  befejez�s�nek �rdek�ben. */
  UART1_Write('\n');
}