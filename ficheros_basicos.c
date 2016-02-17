#include "ficheros_basicos.h"
#include "bloques.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

struct inodo ex;
printf("El tamaño del fichero es: %lu", sizeof(ex));
printf ("sizeof time_t is: %d\n", sizeof(time_t));
return 0;
}

int tamMB(unsigned int nbloques){
    int auxMB = nbloques/8;
    if(auxMB % BLOCKSIZE != 0){
       auxMB++;

    }
    return auxMB;
}

int tamAI(unsigned int ninodos){
    int auxAI = ninodos*TAM_INODO;
    if(auxAI % BLOCKSIZE){
    auxAI++;
    }
    return auxAI;
}

int initSB(unsigned int nbloques, unsigned int ninodos){

}


