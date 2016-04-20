#include "ficheros_basicos.h"
#include "bloques.h"
#include "ficheros.h"

int mi_write_f(unsigned int ninodo, const void *buf_original, unsigned int offset, unsigned int nbytes){
	struct inodo inode;
	unsigned char buf_aux[BLOCKSIZE];
	int primerBloque;
	int ultimoBloque;
	int bf;
	int total;
	int i;
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
				printf("Error in mi_write_f while reading(first=last) the block, line 24, file ficheros.c\n");
	    		return -1;                	
            }
            memcpy (buf_aux + desp1, buf_original, nbytes);
            if(bwrite(bf,buf_aux)==-1){
				printf("Error in mi_write_f while writing(first=last) the block, line 29, file ficheros.c\n");
	    		return -1;                 	
            }
       //If the first and last block to be written into are NOT the same     
       }else{       	
       //loop that checks all the blocks to be written into
       for (i=primerBloque;i<=ultimoBloque;i++){
       		memset(buf_aux,0, sizeof(buf_aux));
       	    //Translate the logical value of the block
       	    bf = traducir_bloque_inodo(ninodo,i,1);
       	    if(bf==-1){
				printf("Error in mi_write_f translating the block into phisical value, line 38, file ficheros.c\n");
	    		return -1;    			
    		}
    		//If the block to be written into is the first
    		if(i==primerBloque){
              if(bread(bf,buf_aux)==-1){
				printf("Error in mi_write_f while reading(first) the block, line 45, file ficheros.c\n");
	    		return -1;                	
              }
              memcpy (buf_aux + desp1, buf_original, BLOCKSIZE - desp1);
              if(bwrite(bf,buf_aux)==-1){
				printf("Error in mi_write_f while writing(first) the block, line 50, file ficheros.c\n");
	    		return -1;                 	
              }
            //If the block to be written into is the last
    		}else if (i==ultimoBloque){
              	if(bread(bf,buf_aux)==-1){
					printf("Error in mi_write_f while reading(last) the block, line 56, file ficheros.c\n");
	    			return -1;                	
                }
                memcpy (buf_aux,buf_original+(BLOCKSIZE-desp1)+(ultimoBloque-primerBloque-1)*BLOCKSIZE,desp2+1);
                if(bwrite(bf,buf_aux)==-1){
					printf("Error in mi_write_f while writing(last) the block, line 61, file ficheros.c\n");
	    			return -1;                 	
                }                    			
            //If the block to be written is in between
    		}else{
        	     	if(bwrite (bf, buf_original + (BLOCKSIZE - desp1) + (i - primerBloque - 1) * BLOCKSIZE) == -1){
 						printf("Error in mi_write_f while writing(in between) the block, line 67, file ficheros.c\n");
	    				return -1;           
               	    }
    			}
       		}
  		}
	}else{
		printf("Error in mi_read_f, file does not have the correct permissions, line 17, file ficheros.c\n");
	    return -1;
	}
	inode = leer_inodo(ninodo);
    if(inode.tamEnBytesLog<offset+nbytes){
       	inode.tamEnBytesLog = offset+nbytes;	
    }
    inode.mtime = time(NULL);
    inode.ctime = time(NULL);
    if(escribir_inodo(inode,ninodo)==-1){
		printf("Error in mi_read_f while writing updated inode, line 84, file ficheros.c\n");
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
	char string[128];


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
				printf("Error in mi_read_f while reading(first=last) the block, line 117, file ficheros.c\n");
	    		return -1;                	
            }
            memcpy(buf_original, buf_aux + desp1, nbytes);
       }else{
       int i;
       //loop that checks all the blocks to be written into
       	for (i=primerBloque;i<=ultimoBloque;i++){
       		       		memset(buf_aux,0, sizeof(buf_aux));

       	    //Translate the logical value of the block
       	    bf = traducir_bloque_inodo(ninodo,i,1);
       	    if(bf==-1){
				printf("Error in mi_read_f translating the block into phisical value, line 127, file ficheros.c\n");
	    		return -1;    			
    		}
    		//If the block to be written into is the first
    		if(i==primerBloque){
              	if(bread(bf,buf_aux)==-1){
					printf("Error in mi_read_f while reading(first) the block, line 134, file ficheros.c\n");
	    			return -1;                	
            	}
            memcpy (buf_original, buf_aux + desp1, BLOCKSIZE - desp1);
            //If the block to be written into is the last
    		}else if (i==ultimoBloque){
              	if(bread(bf,buf_aux)==-1){
					printf("Error in mi_read_f while reading(last) the block, line 141, file ficheros.c\n");
	    			return -1;                	
                }
                memcpy (buf_original+(BLOCKSIZE-desp1)+(ultimoBloque-primerBloque-1)*BLOCKSIZE,buf_aux,desp2+1);                 			
            //If the block to be written is in between
    		}else{
				if(bread(bf,buf_aux)==-1){
 						     printf("Error in mi_read_f while reading(in between) the block, file ficheros.c");
	    				   return -1;           
               	}
                memcpy((buf_original + (BLOCKSIZE - desp1) + (i - primerBloque - 1) * BLOCKSIZE),buf_aux,BLOCKSIZE);
    		}
       	}       		
       }
      	inode = leer_inodo(ninodo);
    	inode.atime = time(NULL);
    	if(escribir_inodo(inode,ninodo)==-1){
			printf("Error in mi_read_f while writing updated inode, line 157, file ficheros.c\n");
	    	return -1;
    	}
    	return nbytes;
		}else{
			printf("Error in mi_read_f, file does not have the correct permissions, line 104, file ficheros.c\n");
	    	return -1;
		}

}
int mi_chmod_f(unsigned int ninodo, unsigned char permisos){
	struct inodo in;
	//first we read the inode
	in = leer_inodo(ninodo);
	//We update the information required
	in.permisos = permisos;
	in.ctime = time(NULL);
	//Now we write the updated inode
	if(escribir_inodo(in,ninodo)==-1){
 		printf("Error in mi_chmod_f while writing updated inode, line 176, file ficheros.c\n");
	    return -1; 
	}
	return 0;
}
int mi_truncar_f(unsigned int ninodo, unsigned int nbytes){
	struct inodo in;
	int nblogico;
	//first we read the inode
	in = leer_inodo(ninodo);
	//Now we have to check if the inode has the correct permissions
	if((in.permisos & 2) == 2){
		//Now we check if the number of bytes is correct
		if(in.tamEnBytesLog >= nbytes){
			nblogico = (nbytes/BLOCKSIZE) + 1;
			//if() EMPLEAR LA FUNCION DE LIBERAR BLOQUES INODDO(HAY QUE REVISARLO)
			//We update the required files of the inode
			in.mtime = time(NULL);
			in.ctime = time(NULL);
			in.tamEnBytesLog = nbytes;
			//Finally we write the update inode
			if(escribir_inodo(in,ninodo)==-1){
 				printf("Error in mi_truncar_f while writing updated inode, line 198, file ficheros.c\n");
	    		return -1; 
			}
			return 0;
		}else{
			printf("Error in mi_truncar_f, the number of bytes is superior of the file's size, line 190, file ficheros.c\n");
			return -1;
		}
	}else{
		printf("Error in mi_truncar_f, inode does not have the correct permissions, line 188, file ficheros.c\n");
		return -1;
	}	
}
int mi_stat_f(unsigned int ninodo, struct STAT *p_stat){
	struct inodo in;
	struct STAT ret;
	//first we read the inode
	in = leer_inodo(ninodo);
	//Now we wrtie all the meta-info of the inode to the stat struct passed
	ret.tipo = in.tipo;
	ret.permisos = in.permisos;
	ret.atime = in.atime;
	ret.mtime = in.mtime;
	ret.ctime = in.ctime;
	ret.nlinks = in.nlinks;
	ret.tamEnBytesLog = in.tamEnBytesLog;
	ret.numBloquesOcupados = in.numBloquesOcupados;
	*p_stat = ret;
	return 0;
}
//Indicates where we begin to write in the first block
int setBottomLimit(int offset){
  return (offset%BLOCKSIZE);
}
//Indicates where to end the writing in the last block 
int setTopLimit(int offset, int nbytes){
	return ((offset+nbytes-1)%BLOCKSIZE);
}