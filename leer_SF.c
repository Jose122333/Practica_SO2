#include "bloques.h"
#include <string.h>
#include "ficheros_basicos.h"

int main(int argc, char **argv){
int numBlocks = atoi(argv[2]);
int descriptor = bmount(argv[1]);
int numInodos = atoi(argv[3]);
struct superbloque sb;
if (descriptor==-1)
{
	printf("Error in bmount function, file leer_SF.c");
}
//First we intialize all the different fields
initSB(numBlocks,numInodos);
initMB();
initAI();
//We show how many blocks are required for the BM and the IA
printf("The number of blocks requiered for the bit map is: %d",tamMB(numBlocks));
printf("\n");
printf("The number of blocks requiered for the inode array is: %d",tamAI(numInodos));
printf("\n");
//We read the value of the superblock and we show each element
if (bread(posSB,&sb)==-1)
{
	printf("Error in bread function, file leer_SF.c");
}
printf("The value of the position of the first block of the BM is: %d",sb.posPrimerBloqueMB);
printf("\n");
printf("The value of the position of the last block of the BM is: %d",sb.posUltimoBloqueMB);
printf("\n");
printf("The value of the position of the first block of the IA is: %d",sb.posPrimerBloqueAI);
printf("\n");
printf("The value of the position of the last block of the IA is: %d",sb.posUltimoBloqueAI);
printf("\n");
printf("The value of the position of the first block of data is: %d",sb.posPrimerBloqueDatos);
printf("\n");
printf("The value of the position of the last block of data is: %d",sb.posUltimoBloqueDatos);
printf("\n");
printf("The value of the position of the root inode is: %d",sb.posInodoRaiz);
printf("\n");
printf("The value of the position of the first free block is: %d",sb.posPrimerInodoLibre);
printf("\n");
printf("The number of free block is: %d",sb.cantBloquesLibres);
printf("\n");
printf("The number of free inodes is: %d",sb.cantInodosLibres);
printf("\n");
printf("The total number of blocks is: %d",sb.totBloques);
printf("\n");
printf("The total number of inodes is: %d",sb.totInodos);
printf("\n");
//We close the file
if(bumount(descriptor)==-1){
	printf("Error in umount function, file leer_SF.c");
}
return 0;
}
