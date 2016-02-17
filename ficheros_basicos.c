#include "ficheros_basicos.h"
#include "bloques.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

struct inodo ex;
struct superbloque sb;
printf("El tamaño del fichero es: %lu", sizeof(sb));
printf("El tamaño del fichero es: %lu", sizeof(ex));
printf ("sizeof time_t is: %d\n", sizeof(time_t));
return 0;
}
//Returns the value(in blocks) of the bit map
int tamMB(unsigned int nbloques){
    int auxMB = nbloques/8;
    //We have to check if the value is a integer
    if(auxMB % BLOCKSIZE != 0){
       auxMB = auxMB/BLOCKSIZE;
    }else{
       auxMB = (auxMB/BLOCKSIZE)+1;
    }
    return auxMB;
}
//Returns the value(in blocks) of inode array
int tamAI(unsigned int ninodos){
    int auxAI = ninodos*TAM_INODO;
    //We have to check if the value is a integer
    if(auxAI % BLOCKSIZE !=0){
    auxAI = auxAI/BLOCKSIZE;
    }else{
    auxAI = (auxAI/BLOCKSIZE)+1;
    }
    return auxAI;
}
//This function initializes the superblock structure
int initSB(unsigned int nbloques, unsigned int ninodos){
int PadLenght = BLOCKSIZE - 12*sizeof(unsigned int);
struct superbloque sb;
//We initilize every node of the superblock structure
sb.posPrimerBloqueMB = posSB + sizeof(sb);
sb.posUltimoBloqueMB = sb.posPrimerBloqueMB + tamMB(nbloques) - 1;
sb.posPrimerBloqueAI = sb.posUltimoBloqueMB + 1;
sb.posUltimoBloqueAI = sb.posPrimerBloqueMB + tamAI(nbloques) - 1; 
sb.posPrimerBloqueDatos = sb.posUltimoBloqueAI + 1;
sb.posUltimoBloqueDatos = nbloques - 1;
sb.posInodoRaiz = 0;
sb.posPrimerInodoLibre = 0;
sb.cantBloquesLibres = nbloques;
sb.cantInodosLibres = ninodos;
sb.totBlouqes = nbloques;
sb.totInodos = ninodos;
int i;
for (i=0;i<PadLenght;i++;){
sb.padding[i] = '0'; 
}
}



