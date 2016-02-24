/#include "ficheros_basicos.h"
#include "bloques.h"


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
sb.posPrimerBloqueMB = posSB + 1; //Tamaño SB = 1
sb.posUltimoBloqueMB = sb.posPrimerBloqueMB + tamMB(nbloques) - 1;
sb.posPrimerBloqueAI = sb.posUltimoBloqueMB + 1;
sb.posUltimoBloqueAI = sb.posPrimerBloqueMB + tamAI(nbloques) - 1; 
sb.posPrimerBloqueDatos = sb.posUltimoBloqueAI + 1;
sb.posUltimoBloqueDatos = nbloques - 1;
sb.posInodoRaiz = 0;
sb.posPrimerInodoLibre = 0;
sb.cantBloquesLibres = nbloques;
sb.cantInodosLibres = ninodos;
sb.totBloques = nbloques;
sb.totInodos = ninodos;
int i;
for (i=0;i<PadLenght;i++){
    sb.padding[i] = '0'; 
}
//Write the structure in a block
if(bwrite(posSB,&sb)==-1){
    printf("Error en fichero_basico.c en initSB");
    return -1;
}else{
    return 0;
}
}

//This function initalizes the bit map of the file system
int initMB(){
    unsigned char buf[BLOCKSIZE];
    struct superbloque sb;
    if(bread(posSB,&sb)==-1){
        printf("Error in initMB, while reading SB. file fichero_basico.c");
        return -1;
    }
//Memory space reserved for bit maps
    memset(buf,0, BLOCKSIZE);
    int i;
//Write all the blocks requiered
    for(i=sb.posPrimerBloqueMB; i<sb.posUltimoBloqueMB; i++){
        if(bwrite(i,buf)==-1){
            printf("Error in initMB, while writing block number %d. file fichero_basico.c", i);
            return -1;
        }
    }
    return 0;
}
int initAI() {
    int i,j;
    int x =1;
    struct inodo ai[BLOCKSIZE/TAM_INODO];
    struct superbloque sb;
    if(bread(posSB,&sb)==-1){
        printf("Error in initAI, while reading SB. file fichero_basico.c");
        return -1;
    }
    //Memory space reserved for bit maps
    memset(ai,0, BLOCKSIZE);
    //Set all inodes to free in a linked list for each block of AI
    for (i =sb.posPrimerBloqueAI; i <= sb.posUltimoBloqueAI; i++){
        for(j=0; j< BLOCKSIZE/TAM_INODO; j++){
            ai[j].tipo= 'l'; //type free inode
            if(x< sb.totInodos){
                ai[j].punterosDirectos[0]= x;
                x++;
            } else {
                ai[j].punterosDirectos[0]= UINT_MAX;
                j = BLOCKSIZE/TAM_INODO; //Condition to exit for
            }
        }
        
        if(bwrite(i,ai)==-1){
            printf("Error in initMB, while writing block number %d. file fichero_basico.c", i);
            return -1;
        }

    }
    return 0;
}
void leer_sf(){
    printf("El primer bloque del MB es: \n");
}

