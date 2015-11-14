#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include <common.h>

void Sensor_initialize(const float _vref);

float Sensor_getTemperature();

#endif /* INC_SENSOR_H_ */