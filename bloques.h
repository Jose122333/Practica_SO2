#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* Uses the system functions open(), read() and write()*/
#include <stdlib.h>
#include <stdio.h>
#include "semaforo_mutex_posix.h"
#define BLOCKSIZE 1024 //bytes

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int bmount(const char *camino);
int bumount();
int bwrite(unsigned int nbloque, const void *buf);
int bread(unsigned int nbloque, void *buf);
