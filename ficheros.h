#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* Uses the system functions open(), read() and write()*/
#include <stdlib.h>
#include <stdio.h>

//Struct to show the meta information of the inodes
struct STAT{ 
unsigned char tipo; //Type (libre, directorio o fichero)
unsigned char permisos; //Permissions (lectura y/o escritura y/o ejecución)
time_t atime; //Latest access time: atime
time_t mtime; //Lates data modified time: mtime
time_t ctime; //Latest inode modified time: ctime
unsigned int nlinks; //Number of links to directories
unsigned int tamEnBytesLog; //Size in logical bytes
unsigned int numBloquesOcupados; //Number of ocupied blocks in the data field
};

//Functions that belong to the 5th stage
int mi_write_f(unsigned int ninodo, const void *buf_original, unsigned int offset, unsigned int nbytes);
int mi_read_f(unsigned int ninodo, void *buf_original, unsigned int offset, unsigned int nbytes);
int setBottomLimit(int offset);
int setTopLimit(int offset, int nbytes);
//Functions that belong to the 6th stage
int mi_chmod_f(unsigned int ninodo, unsigned char permisos);
int mi_truncar_f(unsigned int ninodo, unsigned int nbytes);
int mi_stat_f(unsigned int ninodo, struct STAT *p_stat);

