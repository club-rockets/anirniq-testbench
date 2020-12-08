#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <stdio.h>
#include <stdint.h>

typedef struct _ACTUATOR_STRUCT{ // Structure of one sensor

  uint8_t		id;
  uint8_t 		lock;
  uint32_t      *data_raw;
  uint32_t		data;

} ACTUATOR_STRUCT;

#endif
