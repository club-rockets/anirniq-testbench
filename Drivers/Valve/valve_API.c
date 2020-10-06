#include "valve_API.h"

void v_API_init(void){

    valve_initial();

}

void v_init(API_VALVE_STRUCT* t_struct, uint8_t id, uint8_t pin){

    t_struct->id = id;
    t_struct->pin = pin;

}
void v_start(API_VALVE_STRUCT* t_struct){

    valve_close(t_struct->pin);
    t_struct->data = valve_getstatus(t_struct->pin);

}

void v_get(API_VALVE_STRUCT* t_struct){

    t_struct->data = valve_getstatus(t_struct->pin);

}
void v_lock(API_VALVE_STRUCT* t_struct){

    t_struct->data = valve_getstatus(t_struct->pin);

    if(!(t_struct->data)){

        t_struct->lock = 1;
    }

}
void v_unlock(API_VALVE_STRUCT* t_struct){

    t_struct->data = valve_getstatus(t_struct->pin);

    if(!(t_struct->data)){

        t_struct->lock = 0;
    }

}