#include "bloques.h"

static int descriptor=0;
static sem_t *mutex;
static unsigned int inside_sc = 0;


//This function is used to open the file requested
int bmount(const char *camino){
descriptor=open(camino,O_RDWR|O_CREAT,0666);
if(descriptor==-1){
 	printf("Error in open function, line 7, file bloques.c\n");
 	return -1;
}
mutex = initSem();
  	return descriptor;
}
//This function is used to close the file requested
int bumount(int descriptor){
descriptor=close(descriptor);
if(descriptor==-1){
	printf("Error in close function, line 16, file bloques.c\n");
	return -1;
}
	deleteSem();
  return descriptor;
}
//This function writes a block in the file requested
int bwrite(unsigned int nbloque, const void *buf){
int bytesWritten = 0;
if(lseek(descriptor,nbloque*BLOCKSIZE,SEEK_SET)==-1){
	printf("Error in lseek function, line 26, file bloques.c\n");
	return -1;
}
bytesWritten=write(descriptor,buf,BLOCKSIZE);
if(bytesWritten==-1){
	printf("Error in write function, line 30, file bloques.c\n");
	return -1;
}
	return bytesWritten;
}
//This function reads a block from the file requested
int bread(unsigned int nbloque, void *buf){
int bytesRead = 0;
if(lseek(descriptor,nbloque*BLOCKSIZE,SEEK_SET)==-1){
	printf("Error in lseek function, line 40, file bloques.c\n");
	return -1;
}
bytesRead = read(descriptor,buf,BLOCKSIZE);
if(bytesRead ==-1){
	printf("Error in read function, line 44, file bloques.c\n");
	return -1;
}
	return bytesRead;
}

void mi_waitSem(){
	if (!inside_sc) {
		waitSem(mutex);
	}
	inside_sc++;
}

void mi_signalSem() {
	inside_sc--;
	if (!inside_sc) {
    	signalSem(mutex);
}
