#include "sd_API.h"
#include "fatfs_sd.h"

#include <stdio.h>
#include <string.h>


#define SD_USER_IO
#ifdef SD_USER_IO

extern uint8_t retUSER; /* Return value for USER */
extern char USERPath[4]; /* USER logical drive path */
extern FATFS USERFatFs; /* File system object for USER logical drive */
extern FIL USERFile; /* File object for USER */

#define retSD retUSER
#define SDPath USERPath
#define SDFatFS USERFatFs
#define SDFile USERFile

#else
extern uint8_t retSD;    /* Return value for SD */
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
extern FIL SDFile;       /* File object for SD */
#endif

uint32_t createDir(char* path);
static char directory[10+1] = "";

void sd_init(void){

	SD_disk_initialize(0);

	//this string contains the path to the currently used file
	char filePath[16+1] = {0};

	uint32_t fileCounter = 0;

	wait(100);

	f_mount(&SDFatFS,SDPath,1);

	//create a new directory to avoid overwriting old data
	uint32_t dirCounter = createDir(filePath);

	snprintf(filePath,16,"Acquisition_%03lu/%03lu.txt",dirCounter,++fileCounter);
	snprintf(directory,10,"Acquisition_%03lu/",dirCounter);
	//open the new file
	f_open(&SDFile,filePath,FA_CREATE_ALWAYS|FA_WRITE);

	f_write(&SDFile,"COUCOU",6,NULL);

	f_sync(&SDFile);
}


uint32_t createDir(char* path){
	//check for a unused directory name
	uint32_t dirCounter = 0;
	FRESULT fatStatus = FR_OK;
		do{
			dirCounter += 1;
			//check if 00x directory already exist
			snprintf(path,16,"%03lu",dirCounter);
			fatStatus = f_stat(path,0);
		}while( fatStatus == FR_OK && dirCounter <= 999);

	//create a new directory
		fatStatus = f_mkdir(path);

	return dirCounter;
}

FIL* sd_getFile(){
	return &SDFile;
}

char* sd_getDirectory(){
	return directory;
}

UINT sd_write(void* data, size_t size){

	UINT byte_written;

	f_write(&SDFile,data,size,&byte_written);
	f_sync(&SDFile);

	return byte_written;
}
