#ifndef VALVE_API_H
#define VALVE_API_H

#include <String.h>
#include <Valve_driver.h>
#include "uart1.h"
#include "uart2.h"

#define NB_VALVE 2

typedef struct _API_VALVE_STRUCT{ //Structure d'une valve

    uint8_t id;
    uint8_t lock;
    uint8_t pin;
    uint32_t data;

} API_VALVE_STRUCT;

void v_API_init(void);
void v_init(API_VALVE_STRUCT* t_struct, uint8_t id, uint8_t pin);
void v_start(API_VALVE_STRUCT* t_struct);
void v_get(API_VALVE_STRUCT* t_struct);
void v_lock(API_VALVE_STRUCT* t_struct);
void v_unlock(API_VALVE_STRUCT* t_struct);

#endif