#include <tempsensor/Sensor.h>

/*
 * A referenciafeszültség értéke, amivel az A/D átalakító számol.
 */
float VREF = 0;

void Sensor_initialize(const float _vref) {
  /* A mikrovezérlõ RE1 kivezetésének beállítása analóg bemenetté. */
  ANSELE = 0x02;
  TRISE1_bit = 1;

  /* Az A/D modul inicializálása és a megadott referenciafeszültség értékének
  eltárolása. */
  ADC_Init();
  VREF = _vref;
}

/*
 * Megméri a hõmérsékletet a mikrovezérlõre kapcsolt hõmérséklet érzékelõ
 * segítségével és visszaadja annak érékét.
 */
float Sensor_getTemperature() {
  /* A 6-os számú analóg csatorna mintavételezése és az A/D átalakítás 10-bites
  eredményének lekérdezése. */
  unsigned int temp_res = ADC_Get_Sample(6);
  
  /* A hõmérséklet átalakítása Celsuis fokokra és az eredmény visszaadása. */
  return ((float)temp_res * VREF) / 10.240;
}