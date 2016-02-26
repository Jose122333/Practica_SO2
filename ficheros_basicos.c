		#include "ficheros_basicos.h"
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
		    //Memory space reserved for inode array
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
		//Function in charge of writing a value to a certain bit in the BM
		int escribir_bit(unsigned int nbloque, unsigned int bit){
                int posbyte;
                int posbit;
                int posBlock
                unsigned char bufferMB[BLOCKSIZE];    
                unsigned char mascara = 128;     
                struct superbloque sb;
				//Read from the sb to obtain the location of the BM 
			    if(bread(posSB,&sb)==-1){
			        printf("Error in escribir_bit, while reading SB. file fichero_basico.c");
			        return -1;
			    }
                posbyte = nbloque/8;
                posbit = posbyte%8;
                //Calculte the block position where the bit will be replaced
                posBlock = (posbyte/BLOCKSIZE)+sb.posPrimerBloqueMB;
                //Memory space reserved for inode array
		        memset(bufferMB,0, BLOCKSIZE);
		        //Read the 
                if(bread(posBlock,bufferMB)==-1){
			        printf("Error in escribir_bit, while reading block in BM. file fichero_basico.c");
			        return -1;
                }
                //We assign the value of the mask
                mascara >>= posbit;
                //Now, we calculate the precise byte of the block
                posbyte = posbyte % BLOCKSIZE;
                //Regarding the value of the bit to write, we do the respective calculation
                if (bit == 1){
                  bufferMB[posbyte] |= mascara;
                }else if (bit == 0)
                {
                	bufferMB[posbyte] &= ~mascara; 
                }
                //Finally, we write the new value of the block
                if(bwrite(posBlock,bufferMB)){
		        printf("Error in escribir_bit, while writing block in BM. file fichero_basico.c");
			        return -1;
                }
                return 0;               
		}
		unsigned char leer_bit(unsigned int nbloque){
                int posbyte;
                int posbit;
                int posBlock
                unsigned char bufferMB[BLOCKSIZE];    
                unsigned char mascara = 128;     
                struct superbloque sb;
				//Read from the sb to obtain the location of the BM 
			    if(bread(posSB,&sb)==-1){
			        printf("Error in leer_bit, while reading SB. file fichero_basico.c");
			        return -1;
			    }
                posbyte = nbloque/8;
                posbit = posbyte%8;
                //Calculte the block position where the bit will be replaced
                posBlock = (posbyte/BLOCKSIZE)+sb.posPrimerBloqueMB;
                //Memory space reserved for inode array
		        memset(bufferMB,0, BLOCKSIZE);
		        //Read the 
                if(bread(posBlock,bufferMB)==-1){
			        printf("Error in leer_bit, while reading block in BM. file fichero_basico.c");
			        return -1;
                }
                //Now, we calculate the precise byte of the block
                posbyte = posbyte % BLOCKSIZE;
                //We allocate to the desired bit
                mascara >>= posbit; 
                //Get the value of the bit
                mascara &= bufferMB[posbyte];
                //Re-allocate, to get the real value
                mascara >>= (7 - posbit);
                //If there was a 0 in the bit, the result will be 00000000
                //If there was a 1 in the bit, the result will be 00000001
                return mascara;
		}

