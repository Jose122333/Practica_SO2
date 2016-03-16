#include "ficheros_basicos.h"
#include "bloques.h"

int mi_write_f(unsigned int ninodo, const void *buf_original, unsigned int offset, unsigned int nbytes){
	struct inodo inode;
	unsigned char buf_aux[BLOCKSIZE];
	int primerBloque;
	int ultimoBloque;
	int bf;
	int total;
	int desp1 = setBottomLimit(offset);
	int desp2 = setTopLimit(offset,nbytes);
	//First we have to read the inode, to check if we can use the function
	inode = leer_inodo(ninodo);
	if((inode.permisos & 2) == 2){
	   //We calculate the first and the last logical block to be written to
       primerBloque = offset/BLOCKSIZE;
       ultimoBloque = (offset+nbytes-1)/BLOCKSIZE;
       //If the first and last block to be written into are the same
       if(primerBloque == ultimoBloque){
            bf = traducir_bloque_inodo(ninodo,primerBloque,1);
            if(bread(bf,buf_aux)==-1){
				printf("Error in mi_write_f while reading(first=last) the block, file ficheros.c");
	    		return -1;                	
            }
            memcpy (buf_aux + desp1, buf_original, nbytes);
            if(bwrite(bf,buf_aux)==-1){
				printf("Error in mi_write_f while writing(first=last) the block, file ficheros.c");
	    		return -1;                 	
            }
       //If the first and last block to be written into are NOT the same     
       }else{       	
       int i;
       //loop that checks all the blocks to be written into
       for (i=primerBloque;i<=ultimoBloque;i++){
       	    //Translate the logical value of the block
       	    bf = traducir_bloque_inodo(ninodo,i,1);
       	    if(bf==-1){
				printf("Error in mi_write_f translating the block into phisical value, file ficheros.c");
	    		return -1;    			
    		}
    		//If the block to be written into is the first
    		if(i==primerBloque){
              if(bread(bf,buf_aux)==-1){
				printf("Error in mi_write_f while reading(first) the block, file ficheros.c");
	    		return -1;                	
              }
              memcpy (buf_aux + desp1, buf_original, BLOCKSIZE - desp1);
              if(bwrite(bf,buf_aux)==-1){
				printf("Error in mi_write_f while writing(first) the block, file ficheros.c");
	    		return -1;                 	
              }
            //If the block to be written into is the last
    		}else if (i==ultimoBloque){
              	if(bread(bf,buf_aux)==-1){
					printf("Error in mi_write_f while reading(last) the block, file ficheros.c");
	    			return -1;                	
                }
                memcpy (buf_aux, buf_original + (nbytes - desp2 - 1), desp2 + 1);
                if(bwrite(bf,buf_aux)==-1){
					printf("Error in mi_write_f while writing(last) the block, file ficheros.c");
	    			return -1;                 	
                }                    			
            //If the block to be written is in between
    		}else{
        	     	if(bwrite (bf, buf_original + (BLOCKSIZE - desp1) + (i - primerBloque - 1) * BLOCKSIZE) == -1){
 						printf("Error in mi_write_f while writing(in between) the block, file ficheros.c");
	    				return -1;           
               	    }
    			}
       		}
  		}
	}else{
		printf("Error in mi_write_f, file does not have the correct permissions, file ficheros.c");
	    return -1;
	}
	inode = leer_inodo(ninodo);
    if(inode.tamEnBytesLog<offset+nbytes){
       		inode.tamEnBytesLog = offset+nbytes;	
    }
    inode.mtime = time(NULL);
    inode.ctime = time(NULL);
    if(escribir_inodo(inode,ninodo)==-1){
			printf("Error in mi_write_f while writing updated inode, file ficheros.c");
	    	return -1;
    }
    return nbytes;
}
int mi_read_f(unsigned int ninodo, void *buf_original, unsigned int offset, unsigned int nbytes){
	struct inodo inode;
	unsigned char buf_aux[BLOCKSIZE];
	int primerBloque;
	int ultimoBloque;
	int bf;
	int total;
	int desp1 = setBottomLimit(offset);
	int desp2 = setTopLimit(offset,nbytes);
    //First we have to read the inode, to check if we can use the function
	inode = leer_inodo(ninodo);
	if((inode.permisos & 4) == 4){
		if (offset + nbytes >= inode.tamEnBytesLog){
			nbytes = inode.tamEnBytesLog - offset; 
		}
		if (offset >= inode.tamEnBytesLog){
			return 0;
		}
		//We calculate the first and the last logical block to be written to
       primerBloque = offset/BLOCKSIZE;
       ultimoBloque = (offset+nbytes-1)/BLOCKSIZE;
       //If the first and last block to be written into are the same
       if(primerBloque == ultimoBloque){
       		bf = traducir_bloque_inodo(ninodo,primerBloque,1);
            if(bread(bf,buf_aux)==-1){
				printf("Error in mi_write_f while reading(first=last) the block, file ficheros.c");
	    		return -1;                	
            }
            memcpy(buf_original, buf_aux + desp1, nbytes);
       }else{
       int i;
       //loop that checks all the blocks to be written into
       	for (i=primerBloque;i<=ultimoBloque;i++){
       	    //Translate the logical value of the block
       	    bf = traducir_bloque_inodo(ninodo,i,1);
       	    if(bf==-1){
				printf("Error in mi_write_f translating the block into phisical value, file ficheros.c");
	    		return -1;    			
    		}
    		//If the block to be written into is the first
    		if(i==primerBloque){
              if(bread(bf,buf_aux)==-1){
				printf("Error in mi_write_f while reading(first) the block, file ficheros.c");
	    		return -1;                	
              }
              memcpy (buf_original, buf_aux + desp1, BLOCKSIZE - desp1);
            //If the block to be written into is the last
    		}else if (i==ultimoBloque){
              	if(bread(bf,buf_aux)==-1){
					printf("Error in mi_write_f while reading(last) the block, file ficheros.c");
	    			return -1;                	
                }
                memcpy (buf_original + (nbytes - desp2 - 1),buf_aux, desp2 + 1);                 			
            //If the block to be written is in between
    		}else{
        	    if(memcpy((buf_original + (BLOCKSIZE - desp1) + (i - primerBloque - 1) * BLOCKSIZE),buf_aux,BLOCKSIZE)){
 						printf("Error in mi_write_f while writing(in between) the block, file ficheros.c");
	    				return -1;           
               	}
    		}
       	}       		
       }
       	inode = leer_inodo(ninodo);
    	inode.atime = time(NULL);
    	if(escribir_inodo(inode,ninodo)==-1){
			printf("Error in mi_write_f while writing updated inode, file ficheros.c");
	    	return -1;
    	}
    	return nbytes;
		}

}
int setBottomLimit(int offset){
  return (offset%BLOCKSIZE);
}
int setTopLimit(int offset, int nbytes){
	return ((offset+nbytes-1)/BLOCKSIZE);
}