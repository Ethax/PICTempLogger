#include <tempsensor/Sensor.h>

float VREF = 0;

void Sensor_initialize(const float _vref) {
  ANSELE = 0x02;                     // Configure RE1 pin as analog
  TRISE1_bit = 1;                    // Configure RE1 pin as input

  ADC_Init();
  VREF = _vref;
}

float Sensor_getTemperature() {
  unsigned int temp_res = ADC_Get_Sample(6);     // Get 10-bit results of AD conversion
  return ((float)temp_res * VREF) / 10.240;  // Calculate temperature in Celsuis
                                      //  change Vref constant according
                                      //  to the power supply voltage
}

