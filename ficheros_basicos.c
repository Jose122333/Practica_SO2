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
			//Function in charge of writing a specific value of a certain bit in the BM
			int escribir_bit(unsigned int nbloque, unsigned int bit){
	                int posbyte;
	                int posbit;
	                int posBlock;
	                unsigned char bufferMB[BLOCKSIZE];    
	                unsigned char mascara = 128;     
	                struct superbloque sb;
					//Read from the sb to obtain the location of the BM 
				    if(bread(posSB,&sb)==-1){
				        printf("Error in escribir_bit, while reading SB. file fichero_basico.c");
				        return -1;
				    }
	                posbyte = nbloque/8;
	                posbit = nbloque%8;
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
			//Function in charge of reading the value value of a certain bit in the BM
			unsigned char leer_bit(unsigned int nbloque){
	                int posbyte;
	                int posbit;
	                int posBlock;
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
			//Reserves a free block, writing a 1 in the correspondent bit in the BM
			int reservar_bloque(){
				    struct superbloque sb;
				    unsigned char bufferLec[BLOCKSIZE];
				    unsigned char bufferAux[BLOCKSIZE];
				    int bloqueMB;
				    int numbloque;
				    int posbyte;
				    int posbit; 
				    unsigned char mascara = 128; 			    
					//Read from the sb to obtain the location of the BM 
				    if(bread(posSB,&sb)==-1){
				        printf("Error in reservar_bloque, while reading SB. file fichero_basico.c");
				        return -1;
				    }
	                if (sb.cantBloquesLibres>0)
	                {
	                    //We reserve, extra space for the auxiliar array
	                    memset (bufferAux, 255, BLOCKSIZE);
	                    bloqueMB = sb.posPrimerBloqueMB;
	                    if(bread(bloqueMB,bufferLec)==-1){
				        printf("Error in reservar_bloque, while reading block in BM. file fichero_basico.c");
				        return -1;
	                    }
	                    while(memcmp(bufferAux,bufferLec,BLOCKSIZE)==0){
                           if(bloqueMB<sb.posUltimoBloqueMB){
                              bloqueMB++;
	                          if(bread(bloqueMB,bufferLec)==-1){
				              printf("Error in reservar_bloque, while reading block in BM(loop). file fichero_basico.c");
				              return -1;
	                          }                              
                           }else{
                           	  printf("Error in reservar_bloque, there are no free blocks in BM");
                           	  return -1;
                           }
	                    }
	                    //We locate the position of the first free byte
	                    posbyte = 0;
	                    while(bufferLec[posbyte]==255){
							posbyte++;
	                    }
	                    //We locate the position of the first free bit
	                    posbit = 0;
                        if (posbyte < 255) {
                           while (posbyte & mascara) {
                             posbit++;
                             posbyte <<= 1;
                            }
                        }
                        //We find the real block number in the system
                        numbloque = ((bloqueMB - sb.posPrimerBloqueMB) * BLOCKSIZE + posbyte) * 8 + posbit;
                        if(escribir_bit(numbloque,1)){
                           //We update the super block, with the new info	
                           sb.cantBloquesLibres = sb.cantBloquesLibres-1;
                           if(bread(posSB,&sb)==-1){
				           printf("Error in reservar_bloque, while writing SB. file fichero_basico.c");
				           return -1;
				           }
				           //If everithing goes well, return the correct block
				           return numbloque;
                        }else{
                        	printf("Error in reservar_bloque, while writing a bit. file fichero_basico.c");
				            return -1;
                        }
	                }else{
	                	printf("Error in reservar_bloque, There are no free blocks available");
	                	return -1;
	                }
			}
			//Frees a certain block, by writing a 0 in the correspondent bit in the BM
			int liberar_bloque(unsigned int nbloque){
				struct superbloque sb;
				//Read the sb
				if(bread(posSB,&sb)==-1){
				        printf("Error in liberar_bloque, while reading SB. file fichero_basico.c");
				        return -1;
				}
				//Free the block in question with 				
				if(escribir_bit(nbloque,0)==-1){
				        printf("Error in liberar_bloque, while writng bit. file fichero_basico.c");
				        return -1;                
				}
                //We update the super block, with the new info escribir_bit	
                sb.cantBloquesLibres = sb.cantBloquesLibres+1;
				if(bwrite(posSB,&sb)==-1){
				        printf("Error in liberar_bloque, while updating SB. file fichero_basico.c");
				        return -1;
				}	                
                return nbloque;
			}
			//Writes a new inode structure and adds it to the IA
			int escribir_inodo(struct inodo inodo, unsigned int ninodo){
				//Read the Sb
				struct superbloque sb;
				int nbloque;
				struct inodo ai[BLOCKSIZE/TAM_INODO];
				if(bread(posSB,&sb)==-1){
				        printf("Error in liberar_bloque, while reading SB. file fichero_basico.c");
				        return -1;
				}
               //We calculate the block where the inode is located
				nbloque = ((BLOCKSIZE/TAM_INODO)*tamAI(sb.totInodos))/ninodo;
				//We read the correspondent block
				if(bread(nbloque,ai)==-1){
				        printf("Error in liberar_bloque, while reading inode in IA. file fichero_basico.c");
				        return -1;
				}
				//We assign the inode the new value of the inode to the previous
				ai[(ninodo%(BLOCKSIZE/TAM_INODO))] = inodo;
				//Finally we write the new value of the block
				if(bwrite(nbloque,ai)==-1){
				        printf("Error in liberar_bloque, while writing inode in IA. file fichero_basico.c");
				        return -1;
				}
				return nbloque;								
			}
			//Reads a ninode from the IA
			struct inodo leer_inodo(unsigned int ninodo){
				struct superbloque sb;
				int nbloque;
				struct inodo ai[BLOCKSIZE/TAM_INODO];
				//Read the Sb
				if(bread(posSB,&sb)==-1){
				    printf("Error in liberar_bloque, while reading SB. file fichero_basico.c");
                    //Revisar como se tiene que controlar la exception
				}
                //We calculate the block where the inode is located
				nbloque = ((BLOCKSIZE/TAM_INODO)*tamAI(sb.totInodos))/ninodo;
				//We read the correspondent block
				if(bread(nbloque,ai)==-1){
				    printf("Error in liberar_bloque, while reading inode in IA. file fichero_basico.c");	        
                    //Revisar como se tiene que controlar la exception
				}
				return ai[(ninodo%(BLOCKSIZE/TAM_INODO))];
			}
			//Reserves a Inode from the IA
			int reservar_inodo(unsigned char tipo, unsigned char permisos){
				struct superbloque sb;
				struct inodo inodoAux;
				struct inodo inodo;
				int ninodo;
				//Read the sb
				if(bread(posSB,&sb)==-1){
				        printf("Error in reservar_inodo, while reading SB. file fichero_basico.c");
				        return -1;
				}
				if(sb.cantInodosLibres>0){
					 //Initialize the inode, with all the requiered variables
                     inodo.tipo = tipo;
                     inodo.permisos = permisos;
                     inodo.atime = (time_t)NULL;
                     inodo.mtime = (time_t)NULL;
                     inodo.ctime = (time_t)NULL;
                     inodo.nlinks = 1; 
                     inodo.tamEnBytesLog = 0; 
                     inodo.numBloquesOcupados = 0;
                     int i;
                     for (i = 0; i<12;i++){
                     	inodo.punterosDirectos[i] = 0;
                     }
                     int j;
                     for (j = 0; i<3;i++){
                     	inodo.punterosDirectos[i] = 0;
                     }
                     inodoAux=inodo;
                     inodoAux = leer_inodo(sb.posPrimerInodoLibre);
                     ninodo = sb.posPrimerInodoLibre;
                     escribir_inodo(inodo, ninodo);
                     sb.posPrimerInodoLibre = inodoAux.punterosDirectos[0];
                     sb.cantInodosLibres=sb.cantInodosLibres-1;
				     if(bwrite(posSB,&sb)==-1){
				        printf("Error in reservar_inodo, while reading SB. file fichero_basico.c");
				        return -1;
				      } 
				      return ninodo;                    
				}else{
					printf("Error in reservar_inodo, there are no free inodes");
					return -1;
				}				
			}
			int obtener_rangoBL(struct inodo inodo, int nblogico, int *ptr){
				//We calculate how many pointer are allowed
				int numPunteros = BLOCKSIZE/sizeof(unsigned int);
				//For each level of pointers, a limit variables is created 
				int punterosDirectos = 12;
				int punterosIndirectos1 = 12 + numPunteros;
				int punterosIndirectos2 = numPunteros*numPunteros + punterosIndirectos1;
				int punterosIndirectos3 = numPunteros*numPunteros*numPunteros + punterosIndirectos2;
				int rangoBL;
				//Now we check in which level is located our pointer
				if (nblogico<punterosDirectos){
				    //The logical block is located in the direct pointers	
				    *ptr = inodo.punterosDirectos[nblogico];	
				    rangoBL = 0;	
				}else if (nblogico<punterosIndirectos1){
				    //The logical block is located in the 1st level of indirect pointers						
				    *ptr = inodo.punterosIndirectos[0];
				    rangoBL = 1;	
				}else if (nblogico<punterosIndirectos2){
					//The logical block is located in the 2nd level of indirect pointers		
					*ptr = inodo.punterosIndirectos[1];
					rangoBL = 2;					 
				}else if (nblogico<punterosIndirectos3){
					//The logical block is located in the 3rd level of indirect pointers
					*ptr = inodo.punterosIndirectos[2];
					rangoBL = 3;
				}else{
					printf("Error in obtener_rangoBL, the logic block introduced is incorrect. file fichero_basico.c");
					rangoBL = -1;
				}							
            return rangoBL;
			}
			int obtener_indice (int nblogico, int nivel_punteros){
				//We calculate how many pointer are allowed
				int numPunteros = BLOCKSIZE/sizeof(unsigned int);
				//For each level of pointers, a limit variables is created 
				int punterosDirectos = 12;
				int punterosIndirectos0 = 12 + numPunteros;
				int punterosIndirectos1 = numPunteros*numPunteros + punterosIndirectos1;
				int punterosIndirectos2 = numPunteros*numPunteros*numPunteros + punterosIndirectos2;
				int index;
				if (nblogico<punterosDirectos){
					// We are currently located in the direct pointers list
					index = nblogico;
				}else{
					if(nblogico<punterosIndirectos0){
						// Returns the index of the 1st level of indirect pointers
						index = nblogico-punterosDirectos;
					}else{
						if (nblogico<punterosIndirectos1){
							if (nivel_punteros == 2){
								// Returns the index of the 2nd level of indirect pointers
								index = (nblogico - punterosIndirectos0) / numPunteros;
							}else if (nivel_punteros == 1){
								// Returns the index of the 1st level of indirect pointers
								index = (nblogico - punterosIndirectos0) % numPunteros;
							}else{
							printf("Error in obtener_indice, the logic block introduced is incorrect. file fichero_basico.c");
					        index = -1;
							}
						}else{
							if (nblogico<punterosIndirectos2){
								if (nivel_punteros == 3){
									// Returns the index of the 3rd level of indirect pointers
									index = (nblogico - punterosIndirectos1)/(numPunteros*numPunteros);									
								}else if (nivel_punteros == 2){
									// Returns the index of the 2nd level of indirect pointers
									index = ((nblogico - punterosIndirectos1)%(numPunteros*numPunteros))/numPunteros;	
								}else if (nivel_punteros == 1){
									// Returns the index of the 1st level of indirect pointers
                                    index = ((nblogico - punterosIndirectos1)%(numPunteros*numPunteros))%numPunteros;
								}else{
							        printf("Error in obtener_indice, the logic block introduced is incorrect. file fichero_basico.c");
					                index = -1;									
								}
							}else{
							    printf("Error in obtener_indice, the logic block introduced is incorrect. file fichero_basico.c");
					            index = -1;									
					        }
						}
					}
				}
                return index;
			} 

