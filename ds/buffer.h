#ifndef BUFFER_HEADER
#define BUFFER_HEADER

#include <stdio.h>
#include <stdint.h>

#define XML_NODE 				6
#define DATA_BUFFER_ITEM_NB 	10
#define DATA_BUFFER_SUCESS 		0
#define DATA_BUFFER_EMPTY 		1
#define DATA_BUFFER_NOT_EMPTY 	0
#define DATA_BUFFER_FULL 		1
#define DATA_BUFFER_FAIL 		1
#define DATA_BUFFER_ERROR 		2

typedef struct _DataBuffer_Element {

    uint32_t*  adr;
    uint8_t    node;
    uint8_t    id;

} DataBuffer_Element;

typedef struct _DataBuffer {

    DataBuffer_Element  item[DATA_BUFFER_ITEM_NB];
    uint8_t				ptr;

} DataBuffer;

void init(DataBuffer *buffer);   // Initialisation du buffer circulaire
void free(DataBuffer *buffer);   // Suppress all data in the buffer and reinit it
uint8_t put(DataBuffer *buffer, DataBuffer_Element item); //Add data to the buffer
DataBuffer_Element get(DataBuffer *buffer, uint8_t ptr); //Read head value
uint8_t remain(DataBuffer *buffer); //Give remaning space
uint8_t size(DataBuffer *buffer); //Give number of element in it
uint8_t empty(DataBuffer *buffer); // check if buffer empty
uint8_t full(DataBuffer *buffer); // check if buffer full

#endif /*BUFFER_HEADER*/
