#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdio.h>
#include <stdint.h>

typedef struct _SENSOR_STRUCT{ // Structure of one sensor

  uint8_t		id;
  uint32_t      *data_raw;
  uint32_t		data;

} SENSOR_STRUCT;

#endif
