#include "bloques.h"
#include <string.h>

int main(int argc, char **argv){
int numBlocks = atoi(argv[2]);
int descriptor = bmount(argv[1]);
unsigned char buf[BLOCKSIZE];
memset(buf,0,sizeof(numBlocks*BLOCKSIZE));
int i;
for(i=0; i<numBlocks; i++){
bwrite(i,buf);
}
bumount(descriptor);
}
