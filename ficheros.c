#include "ficheros_basicos.h"
#include "bloques.h"

int mi_write_f(unsigned int ninodo, const void *buf_original, unsigned int offset, unsigned int nbytes){
	struct inodo inode;
	unsigned char buf_aux[BLOCKSIZE];
	int primerBloque;
	int ultimoBloque;
	int bf;
	int total;
	//First we have to read the inode, to check if we can use the function
	inode = leer_inodo(ninodo);
	if((inode.permisos & 2) == 2){
	   //We calculate the first and the last block to be written to
       primerBloque = offset/BLOCKSIZE;
       ultimoBloque = (offset+nbytes-1)/BLOCKSIZE;
       int i;
       //loop that checks all the blocks to be written into
       for (i=primerBloque;i<ultimoBloque;i++){
       	    //Translate the logical value of the block
       	    bf = traducir_bloque_inodo(ninodo,i,1);
       	    if(bf==-1){
				printf("Error in mi_write_f translating the block into phisical value, file ficheros.c");
	    		return -1;    			
    		}
       	    //calculate the limits of where are we going to write
       		int start = setBottomLimit(offset);
       		int end = setTopLimit(offset,nbytes);
       		//Check if the limits contain a complete block
       		if(start || end < BLOCKSIZE){
       			if(bread(bf,buf_aux)==-1){
    				printf("Error in mi_write_f while reading phisical block, file ficheros.c");
	    			return -1;   
    			}
       		}            
    		total +=nbytes;
    		memcpy(buf_aux+offset,buf_original+total,nbytes);
    		if(bwrite(bf,buf_aux)){
    			printf("Error in mi_write_f while writing phisical block, file ficheros.c");
	    		return -1;   
    		}
          
       }
       inode = leer_inodo(ninodo);
       //FALTA ACTUALIZAR EL VALOR DEL INODO, SI HEMOS ESCRITO MÁS DE LO QUE TENEMOS EN EL FICHERO
       inode.mtime = time(NULL);
       inode.ctime = time(NULL);
       if(escribir_inodo(inode,ninodo)==-1){
		printf("Error in mi_write_f while writing updated inode, file ficheros.c");
	    return -1;
       }
       return nbytes;
	}else{
		printf("Error in mi_write_f, file does not have the correct permissions, file ficheros.c");
	    return -1;
	}
}
int setBottomLimit(int offset){
  return (offset%BLOCKSIZE);
}
int setTopLimit(int offset, int nbytes){
	return ((offset+nbytes-1)/BLOCKSIZE);
}