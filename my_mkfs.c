#include "bloques.h"
#include <string.h>
#include "ficheros_basicos.h"

int main(int argc, char **argv){
int descriptor = bmount(argv[1]);
int numBlocks = atoi(argv[2]);
int numInodos = numBlocks/4;
struct superbloque sb;
unsigned char bufferAux[BLOCKSIZE];

memset(bufferAux,0, BLOCKSIZE);

int i;
for(i=0;i<numBlocks;i++){
	bwrite(i,bufferAux);
}

initSB(numBlocks, numInodos);
initMB();
initAI(numInodos);

reservar_inodo('d','7');

bumount();
return 0;

}
