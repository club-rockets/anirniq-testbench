#ifndef SD_DRIVER_H
#define SD_DRIVER_H

#include "stdint.h"
#include "fatfs_driver.h"

#define SD_QUEUE_SIZE 30
#define SD_QUEUE_BLOCK_SIZE sizeof(struct sd_log)


void sd_init(void);

FIL* sd_getFile();

char* sd_getDirectory();

#endif //SD_DRIVER_H
