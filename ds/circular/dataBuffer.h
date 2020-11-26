#pragma once

#ifndef DATA_BUFFER_HEADER
#define DATA_BUFFER_HEADER

/****** Includes *****/

#include <stdio.h>
#include <stdint.h>

/****** Define *****/

#define XML_NODE 6

#define DATA_BUFFER_ITEM_NB 10

#define DATA_BUFFER_DEBUG

#define DATA_BUFFER_SUCESS 0
#define DATA_BUFFER_EMPTY 1
#define DATA_BUFFER_NOT_EMPTY 0
#define DATA_BUFFER_FULL 1
#define DATA_BUFFER_FAIL 1
#define DATA_BUFFER_ERROR 2

typedef struct _DataBuffer_Data_Element {

    void* 		adr;
    uint8_t     nb;
    uint8_t     type;

} DataBuffer_Data_Element;

typedef struct _DataBuffer_Element {

    DataBuffer_Data_Element data;
    uint8_t                 node;
    uint8_t                 id;

} DataBuffer_Element;

typedef struct _DataBuffer {

    DataBuffer_Element  item[DATA_BUFFER_ITEM_NB];
	uint8_t             lenght; //Taille du buffer circulaire
	uint8_t             head; //Fin du buffer circulaire
    uint8_t             tail; //Debut du Buffer circulaire
    uint8_t             full;

} DataBuffer;

/*volatile DataBuffer *debug0_data_buffer; //init the buffer

#define dataBuffer debug0_data_buffer*/

void init(DataBuffer *buffer, uint8_t len);   // Initialisation du buffer circulaire
void free(DataBuffer *buffer);   // Suppress all data in the buffer and reinit it
uint8_t put(DataBuffer *buffer, DataBuffer_Element newData); //Add data to the buffer
DataBuffer_Element get(DataBuffer *buffer); //Read head value
uint8_t capacity(DataBuffer *buffer); //Give remaning space
uint8_t size(DataBuffer *buffer); //Give number of element in it
uint8_t empty(DataBuffer *buffer); // check if buffer empty
uint8_t full(DataBuffer *buffer); // check if buffer full

#endif /*DATA_BUFFER_HEADER*/
