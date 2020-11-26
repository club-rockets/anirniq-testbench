#include "dataBuffer.h"

//La fonction initialise un buffer circulaire vide
void init(DataBuffer *buffer, uint8_t len){

    uint8_t i;

    buffer->lenght = DATA_BUFFER_ITEM_NB; //Buffer not full

    for (i = 0; i < DATA_BUFFER_ITEM_NB; i++)
    {
        buffer->item->data.adr = NULL; //init the adr
        buffer->item->data.nb = 0; //init the adr
        buffer->item->data.type = 0; //init the adr
        buffer->item->id = 0; //init the adr
        buffer->item->node = 0; //init the adr
    }

    buffer->tail = 0;
    buffer->head = 0;

    buffer->full = 0; //Buffer not full
}

void free(DataBuffer *buffer){

    uint8_t i;

    for (i = 0; i < DATA_BUFFER_ITEM_NB; i++)
    {
        buffer->item->data.adr = NULL; //init the adr
        buffer->item->data.nb = 0; //init the adr
        buffer->item->data.type = 0; //init the adr
        buffer->item->id = 0; //init the adr
        buffer->item->node = 0; //init the adr
    }

    buffer->tail = 0;
    buffer->head = 0;

    buffer->full = 0; //Buffer not full
}

// check if buffer empty
uint8_t empty(DataBuffer *buffer){


    if(buffer->head == buffer->tail){

        return 1;

    }else{

        return 0;

    }
}

// check if buffer full
uint8_t full(DataBuffer *buffer){

    return buffer->full;

}

//Give remaning space
uint8_t capacity(DataBuffer *buffer){

    if(full(buffer)){

        return 0;

    }else if(buffer->head > buffer->tail){

        return (buffer->lenght-((buffer->head-buffer->tail)+1));

    }else{

        return ((buffer->tail-buffer->head)-1);

    }
}

//Give number of element in it
uint8_t size(DataBuffer *buffer){

    if(empty(buffer)){

        return 0;

    }else if(buffer->head > buffer->tail){

        return ((buffer->head-buffer->tail)+1);

    }else{

        return (buffer->lenght-(buffer->tail-buffer->head)-1);

    }
}

 //Read tail value
DataBuffer_Element get(DataBuffer *buffer){

    DataBuffer_Element value;

    //if not empty
    if(!empty(buffer)){

        value = buffer->item[buffer->tail];

        buffer->item[buffer->tail].data.adr = NULL;
        buffer->item[buffer->tail].data.nb = 0;
        buffer->item[buffer->tail].data.type = 0;
        buffer->item[buffer->tail].id = 0;
        buffer->item[buffer->tail].node = 0;

        buffer->tail = (buffer->tail+1)%(buffer->lenght);
    }

    return value;
}

 //Put tail value
uint8_t put(DataBuffer *buffer, DataBuffer_Element newData){

    //if not empty
    if(!full(buffer)){

        buffer->item[buffer->head].data.adr = newData.data.adr;
        buffer->item[buffer->head].data.nb = newData.data.nb;
        buffer->item[buffer->head].data.type = newData.data.type;
        buffer->item[buffer->head].id = newData.id;
        buffer->item[buffer->head].node = newData.node;

        buffer->head = (buffer->head+1)%(buffer->lenght);

        return 1;
    }

    return 0;
}
