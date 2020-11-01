#ifndef SD_API_H
#define SD_API_H

#include "stdint.h"
#include "fatfs_sd.h"

#define SD_QUEUE_SIZE 30
#define SD_QUEUE_BLOCK_SIZE sizeof(struct sd_log)


void sd_init(void);

FIL* sd_getFile();

char* sd_getDirectory();

UINT sd_write(void* data, size_t size);

#endif //SD_API_H
