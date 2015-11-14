#include <tempsensor/Sensor.h>

/*
 * A referenciafesz�lts�g �rt�ke, amivel az A/D �talak�t� sz�mol.
 */
float VREF = 0;

void Sensor_initialize(const float _vref) {
  /* A mikrovez�rl� RE1 kivezet�s�nek be�ll�t�sa anal�g bemenett�. */
  ANSELE = 0x02;
  TRISE1_bit = 1;

  /* Az A/D modul inicializ�l�sa �s a megadott referenciafesz�lts�g �rt�k�nek
  elt�rol�sa. */
  ADC_Init();
  VREF = _vref;
}

/*
 * Megm�ri a h�m�rs�kletet a mikrovez�rl�re kapcsolt h�m�rs�klet �rz�kel�
 * seg�ts�g�vel �s visszaadja annak �r�k�t.
 */
float Sensor_getTemperature() {
  /* A 6-os sz�m� anal�g csatorna mintav�telez�se �s az A/D �talak�t�s 10-bites
  eredm�ny�nek lek�rdez�se. */
  unsigned int temp_res = ADC_Get_Sample(6);
  
  /* A h�m�rs�klet �talak�t�sa Celsuis fokokra �s az eredm�ny visszaad�sa. */
  return ((float)temp_res * VREF) / 10.240;
}