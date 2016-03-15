#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /* Uses the system functions open(), read() and write()*/
#include <stdlib.h>
#include <stdio.h>

//Functions that belong to the 5th stage
int mi_write_f(unsigned int ninodo, const void *buf_original, unsigned int offset, unsigned int nbytes);
int mi_read_f(unsigned int ninodo, void *buf_original, unsigned int offset, unsigned int nbytes);
int setBottomLimit(int offset);
int setTopLimit(int offset, int nbytes);
