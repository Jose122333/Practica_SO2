#include "bloques.h"
#include <string.h>
#include "ficheros_basicos.h"

int main(int argc, char **argv){
int numBlocks = atoi(argv[2]);
int descriptor = bmount(argv[1]);
int numInodos = atoi(argv[3]);
initSB(numBlocks, numInodos);
initMB();
initAI();
}
