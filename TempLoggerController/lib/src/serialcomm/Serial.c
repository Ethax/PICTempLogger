#include <serialcomm/Serial.h>

void Serial_initialize() {
  // TODO: implementálni...
}

void Serial_handleInterrupt() {
  // TODO: hasonlóan a Timer-hez, eseményt generálni, stb.
  RC1IF_bit = false;
}