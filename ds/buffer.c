#include "buffer.h"

// Initialisation du buffer circulaire
void init(DataBuffer *buffer){

	size_t i;

	for(i = 0; i<DATA_BUFFER_ITEM_NB;i++){

		buffer->item[i].adr = null; //Init all the data from the buffer to null (no pointer)

	}

	buffer->ptr = 0;

}

// Suppress all data in the buffer and reinit it
void free(DataBuffer *buffer){

	size_t i;

	for(i = 0; i<DATA_BUFFER_ITEM_NB;i++){

		buffer->item[i].adr = null; //Init all the data from the buffer to null (no pointer)

	}

	buffer->ptr = 0;

}

//Add data to the bufferd
uint8_t push(DataBuffer *buffer, SENSOR_STRUCT data){

	//Give remaning space
	if(full(buffer) != DATA_BUFFER_FULL){

		DataBuffer_Element item;

		item.node = XML_NODE;
		item.id = data->id;
		item.adr = data->data_raw;

		buffer->item[ptr].adr = item.adr; //add new item to buffer
		buffer->ptr++; //increase the pointer

		return DATA_BUFFER_SUCESS;

	}

	return DATA_BUFFER_FAIL;
}

//Read head value
DataBuffer_Element get(DataBuffer *buffer, uint8_t ptr){

	DataBuffer_Element val;

	val.adr = buffer->item[ptr].adr;
	val.id = buffer->item[ptr].id;
	val.node = buffer->item[ptr].node;

	return val;
}

//Give remaning space
uint8_t remain(DataBuffer *buffer){

	return (DATA_BUFFER_ITEM_NB-(buffer->ptr));

}

//Give number of element in it
uint8_t size(DataBuffer *buffer){

	return buffer->ptr;

}

// check if buffer empty
uint8_t empty(DataBuffer *buffer){

	if(buffer->ptr == 0){

		return DATA_BUFFER_EMPTY;

	}else{

		return DATA_BUFFER_NOT_EMPTY;

	}

}

// check if buffer full
uint8_t full(DataBuffer *buffer){

	if(buffer->ptr < DATA_BUFFER_ITEM_NB-1){

		return 0;

	}else{

		return DATA_BUFFER_FULL;

	}

}
