#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <stdio.h>
#include <stdint.h>
#include "sensor.h"

typedef struct _ACTUATOR_STRUCT{ // Structure of one sensor

  SENSOR_STRUCT	sensor;
  uint8_t 		lock;

} ACTUATOR_STRUCT;

#endif
