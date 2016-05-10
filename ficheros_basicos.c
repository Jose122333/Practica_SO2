			#include "ficheros_basicos.h"
			#include "bloques.h"


			//Returns the value(in blocks) of the bit map
			int tamMB(unsigned int nbloques){
				int MB= (nbloques/8)/BLOCKSIZE;
				if(nbloques%(BLOCKSIZE)!=0){
					MB++;
				}
				return MB;
			}
			//Returns the value(in blocks) of inode array
			int tamAI(unsigned int ninodos){
				int AI=(ninodos * TAM_INODO) / BLOCKSIZE;
				if((ninodos * TAM_INODO) % BLOCKSIZE!=0){
					AI++;
				}
				return AI;
			}
			//This function initializes the superblock structure
			int initSB(unsigned int nbloques, unsigned int ninodos){
				int PadLenght = BLOCKSIZE - 12*sizeof(unsigned int);
				struct superbloque sb;
				//We initilize every node of the superblock structure
				sb.posPrimerBloqueMB = posSB + 1; //Tamaño SB = 1
				sb.posUltimoBloqueMB = sb.posPrimerBloqueMB + tamMB(nbloques) - 1;
				sb.posPrimerBloqueAI = sb.posUltimoBloqueMB + 1;
				sb.posUltimoBloqueAI = sb.posPrimerBloqueAI + tamAI(ninodos) - 1; 
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
			    printf("Error in initSB, while writing superblock, line 43, file ficheros_basicos.c\n");
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
			        printf("Error in initMB, while reading SB, line 54, file fichero_basico.c\n");
			        return -1;
			    }
			    //Memory space reserved for bit maps
			    memset(buf,0, BLOCKSIZE);
			    int i;
			    //Write all the blocks requiered
			    for(i=sb.posPrimerBloqueMB; i<=sb.posUltimoBloqueMB; i++){
			        if(bwrite(i,buf)==-1){
			            printf("Error in initMB, while writing block number %d, line 63, file fichero_basico.c\n", i);
			            return -1;
			        }
			        if(escribir_bit(i,1)==-1){
			        printf("Error in initMB, while wrtiting bit in MB refering to MB, line 67, file fichero_basico.c\n");
			        return -1;			    	
			    	}
			    	sb.cantBloquesLibres--;
			    }
			    for(i=sb.posPrimerBloqueAI; i<=sb.posUltimoBloqueAI; i++){
			        if(escribir_bit(i,1)==-1){
			        printf("Error in initMB, while wrtiting bit in MB refering to MB, line 74, file fichero_basico.c\n");
			        return -1;			    	
			    	}
			    	sb.cantBloquesLibres--;
			    }
			    if(escribir_bit(posSB,1)==-1){
			        printf("Error in initMB, while wrtiting bit in MB refering to SB, line 80, file fichero_basico.c\n");
			        return -1;			    	
			    }
			    sb.cantBloquesLibres--;			    
			    if(bwrite(posSB,&sb)==-1){
			        printf("Error in initMB, while writng SB, line 85, file fichero_basico.c\n");
			        return -1;
			    }	
                
			    return 0;
			}
			int initAI(unsigned int ninodos) {
			    int i,j;
			    int x =1;
			    struct inodo ai[BLOCKSIZE/TAM_INODO];
			    struct superbloque sb;
			    if(bread(posSB,&sb)==-1){
			        printf("Error in initAI, while reading SB, line 97, file fichero_basico.c\n");
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
			            printf("Error in initMB, while writing block number %d, line 115, file fichero_basico.c\n", i);
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
				        printf("Error in escribir_bit, while reading SB, line 135, file fichero_basico.c\n");
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
				        printf("Error in escribir_bit, while reading block in BM, line 146, file fichero_basico.c\n");
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
	                if(bwrite(posBlock,bufferMB)==-1){
			        	printf("Error in escribir_bit, while writing block in BM, line 162, file fichero_basico.c\n");
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
				        printf("Error in leer_bit, while reading SB, line 177, file fichero_basico.c\n");
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
				        printf("Error in leer_bit, while reading block in BM, line 188, file fichero_basico.c\n");
				        return -1;
	                }
	                //printf("%u", bufferMB[posbyte]);
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
				        printf("Error in reservar_bloque, while reading SB, line 216, file fichero_basico.c\n");
				        return -1;
				    }
	                if (sb.cantBloquesLibres>0)
	                {
	                    //We reserve, extra space for the auxiliar array
	                    memset (bufferAux, 255, BLOCKSIZE);
	                    bloqueMB = sb.posPrimerBloqueMB;
	                    if(bread(bloqueMB,bufferLec)==-1){
				        	printf("Error in reservar_bloque, while reading block in BM, line 225, file fichero_basico.c\n");
				        	return -1;
	                    }
	                    while(memcmp(bufferAux,bufferLec,BLOCKSIZE)==0){
                           if(bloqueMB<=sb.posUltimoBloqueMB){
                              bloqueMB++;
	                          if(bread(bloqueMB,bufferLec)==-1){
				              	printf("Error in reservar_bloque, while reading block in BM(loop), line 232, file fichero_basico.c\n");
				              	return -1;
	                          }                              
                           }else{
                           	  printf("Error in reservar_bloque, there are no free blocks in BM, line 220, file ficheros_basicos.c\n");
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
                        if (bufferLec[posbyte] < 255) {
                           while (bufferLec[posbyte] & mascara) {
                             bufferLec[posbyte] <<= 1;
                             posbit++;
                            }
                        }	 
                        //We find the real block number in the system
                        numbloque = ((bloqueMB - sb.posPrimerBloqueMB) * BLOCKSIZE + posbyte) * 8 + posbit;
                        if(escribir_bit(numbloque,1)!=-1){
                           	//We update the super block, with the new info	
                          	sb.cantBloquesLibres = sb.cantBloquesLibres-1;
                            if(bwrite(posSB,&sb)==-1){
				           		printf("Error in reservar_bloque, while writing SB, line 259, file fichero_basico.c\n");
				           		return -1;
				           	}
				           	//If everithing goes well, return the correct block
				           	return numbloque;
                        }else{
                        	printf("Error in reservar_bloque, while writing a bit, line 256, file fichero_basico.c\n");
				            return -1;
                        }
	                }else{
	                	printf("Error in reservar_bloque, There are no free blocks available, line 220, file ficheros_basicos.c\n");
	                	return -1;
	                }
			}
			//Frees a certain block, by writing a 0 in the correspondent bit in the BM
			int liberar_bloque(unsigned int nbloque){
				struct superbloque sb;
				//Read the sb
				if(bread(posSB,&sb)==-1){
				        printf("Error in liberar_bloque, while reading SB, line 278, file fichero_basico.c\n");
				        return -1;
				}
				//Free the block in question with 				
				if(escribir_bit(nbloque,0)==-1){
				        printf("Error in liberar_bloque, while writng bit, line 283, file fichero_basico.c\n");
				        return -1;                
				}
                //We update the super block, with the new info escribir_bit	
                sb.cantBloquesLibres = sb.cantBloquesLibres+1;
				if(bwrite(posSB,&sb)==-1){
				        printf("Error in liberar_bloque, while updating SB, line 289, file fichero_basico.c\n");
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
				        printf("Error in escribir_inodo, while reading SB, line 301, file fichero_basico.c\n");
				        return -1;
				}
               //We calculate the block where the inode is located
				nbloque = sb.posPrimerBloqueAI+(ninodo/(BLOCKSIZE/TAM_INODO));
				//We read the correspondent block
				if(bread(nbloque,ai)==-1){
				        printf("Error in escribir_inodo, while reading inode in IA, line 308, file fichero_basico.c\n");
				        return -1;
				}
				//We assign the inode the new value of the inode to the previous
				ai[(ninodo%(BLOCKSIZE/TAM_INODO))] = inodo;
				//Finally we write the new value of the block
				if(bwrite(nbloque,ai)==-1){
				        printf("Error in escribir_inodo, while writing inode in IA, line 315, file fichero_basico.c\n");
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
				    printf("Error in leer_inodo, while reading SB, line 327, file fichero_basico.c\n");
                    //Revisar como se tiene que controlar la exception
				}
                //We calculate the block where the inode is located
				nbloque = sb.posPrimerBloqueAI+(ninodo/(BLOCKSIZE/TAM_INODO));
				//We read the correspondent block
				if(bread(nbloque,ai)==-1){
				    printf("Error in leer_inodo, while reading inode in IA, line 334, file fichero_basico.c\n");	        
                    //Revisar como se tiene que controlar la exception
				}
				return ai[(ninodo%(BLOCKSIZE/TAM_INODO))];
			}
			//Reserves a Inode from the IA
			int reservar_inodo(unsigned char tipo, unsigned char permisos){
				struct superbloque sb;
				struct inodo inodo;
				int ninodo;
				//Read the sb
				if(bread(posSB,&sb)==-1){
				        //printf("Error in reservar_inodo, while reading SB, line 346, file fichero_basico.c\n");
				        return -1;
				}
				if(sb.cantInodosLibres>0){
					 time_t now;
					 //Read the corresponding inode					 
					 inodo = leer_inodo(sb.posPrimerInodoLibre);
					 ninodo = sb.posPrimerInodoLibre;
					 sb.posPrimerInodoLibre = inodo.punterosDirectos[0];
					 //Initialize the inode, with all the requiered variables
                     inodo.tipo = tipo;
                     inodo.permisos = permisos;
                     //inodo.atime = (time_t)NULL;
                     inodo.atime = time(&now);
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
                     	inodo.punterosIndirectos[i] = 0;
                     }
                     escribir_inodo(inodo, ninodo);
                     sb.cantInodosLibres=sb.cantInodosLibres-1;
				     if(bwrite(posSB,&sb)==-1){
				        printf("Error in reservar_inodo, while reading SB, line 376, file fichero_basico.c\n");
				        return -1;
				      } 
				      return ninodo;                    
				}else{
					printf("Error in reservar_inodo, there are no free inodes, line 350, file ficheros_basicos.c\n");
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
				}else{
					if(nblogico<punterosIndirectos1){
				    //The logical block is located in the 1st level of indirect pointers						
				    *ptr = inodo.punterosIndirectos[0];
				    rangoBL = 1;	
					}else{
						if (nblogico<punterosIndirectos2){
						//The logical block is located in the 2nd level of indirect pointers		
						*ptr = inodo.punterosIndirectos[1];
						rangoBL = 2;					 
						}else{
							 if (nblogico<punterosIndirectos3){
								//The logical block is located in the 3rd level of indirect pointers
								*ptr = inodo.punterosIndirectos[2];
								rangoBL = 3;
							}else{
								printf("Error in obtener_rangoBL, the logic block introduced is incorrect, line 411, file fichero_basico.c\n");
								rangoBL = -1;
							}
						}
					}

				}							
            	return rangoBL;
			}
			int obtener_indice (int nblogico, int nivel_punteros){
				//We calculate how many pointer are allowed
				int numPunteros = BLOCKSIZE/sizeof(unsigned int);
				//For each level of pointers, a limit variables is created 
				int punterosDirectos = 12;
				int punterosIndirectos0 = 12 + numPunteros;
				int punterosIndirectos1 = numPunteros*numPunteros + punterosIndirectos0;
				int punterosIndirectos2 = numPunteros*numPunteros*numPunteros + punterosIndirectos1;
				int index;
				if (nblogico<punterosDirectos){
					// We are currently located in the direct pointers list
					index = nblogico;
				}else{
					if(nblogico<punterosIndirectos0){
						// Returns the index of the 1st level of indirect pointers
						index = nblogico-punterosDirectos;
					}else{
						if(nblogico<punterosIndirectos1){
							if (nivel_punteros == 2){
								// Returns the index of the 2nd level of indirect pointers
								index = (nblogico - punterosIndirectos0) / numPunteros;
							}else{ 
								if (nivel_punteros == 1){
								// Returns the index of the 1st level of indirect pointers
								index = (nblogico - punterosIndirectos0) % numPunteros;
								}
							}
						}else{
							if (nblogico<punterosIndirectos2){
								if (nivel_punteros == 3){
									// Returns the index of the 3rd level of indirect pointers
									index = (nblogico - punterosIndirectos1)/(numPunteros*numPunteros);									
								}else{
									if (nivel_punteros == 2){
										// Returns the index of the 2nd level of indirect pointers
										index = ((nblogico - punterosIndirectos1)%(numPunteros*numPunteros))/numPunteros;	
									}else {
										if (nivel_punteros == 1){
											// Returns the index of the 1st level of indirect pointers
                                    		index = ((nblogico - punterosIndirectos1)%(numPunteros*numPunteros))%numPunteros;
										}
									}
								} 
							}
						}
					}
				}
                return index;
			}
			int traducir_bloque_inodo(unsigned int ninodo, unsigned int nblogico, char reservar){
				struct inodo ind;
				int ptr,ptr_ant,salvar_inodo,bloques_reservados = 0;
				int nivel_punteros;
				int rangoBL;
				int index;
				int bufferAux[BLOCKSIZE/sizeof(int)];
				//First we read the selected inode
				ind = leer_inodo(ninodo);
				bloques_reservados = ind.numBloquesOcupados;
				//Now we get the level that belongs to the logical block requested(Preguntar si el puntero se queda modificado al salir de la funcion)
				rangoBL = obtener_rangoBL(ind,nblogico,&ptr);
				nivel_punteros=rangoBL;			
				while(nivel_punteros>0){
					if (ptr==0){
						if (reservar==0){
							//printf("Error in traducir_bloque_inodo, reserve byte is incorrect(while), line 498, file ficheros_basicos.c\n");
							return -2;
						}else{
							salvar_inodo = 1;
							//Reserve the seleccted block
							ptr = reservar_bloque();
							//Fill a buffer with 0
							memset (bufferAux, 0, BLOCKSIZE);
							//Now we write the value of the buffer in the file system.
							if(bwrite(ptr,bufferAux)==-1){
								printf("Error in traducir_bloque_inodo while writing a block(while), line 508, file ficheros_basicos.c\n");
								return -1;								
							}
							bloques_reservados++;
						    if (nivel_punteros == rangoBL){
								ind.punterosIndirectos[rangoBL-1]=ptr;
							}else{
							   if(bread(ptr_ant,bufferAux)==-1){
							        printf("Error in traducir_bloque_inodo while reading a block(while y nivel_punteros == rangoBL), line 516, file ficheros_basicos.c\n");
							        return -1;								
								}
                                bufferAux[index] = ptr;
								if(bwrite(ptr_ant,bufferAux)==-1){
							        printf("Error in traducir_bloque_inodo while writing a block(while y nivel_punteros == rangoBL), line 521, file ficheros_basicos.c\n");
							        return -1;	
								}																							
							}
						}						
					}
					if(bread(ptr,bufferAux)==-1){
						printf("Error in traducir_bloque_inodo while writing a block, line 528, file ficheros_basicos.c\n");
						return -1;								
					}
					index = obtener_indice(nblogico,nivel_punteros);
					if(index==-1){
						printf("Error in traducir_bloque_inodo while getting the index, line 532, file ficheros_basicos.c\n");
						return -1;									
					}
					ptr_ant=ptr;
					ptr = bufferAux[index];
					nivel_punteros--;                
			}
			if(ptr==0){
				if(reservar == 0){
						//printf("Error in traducir_bloque_inodo while getting the index, line 544, file ficheros_basicos.c\n");
						return -2;						
					}else{
						salvar_inodo = 1;
					    ptr = reservar_bloque();
					    //printf("El bloque para reservar datos es: %d\n", ptr);
					    bloques_reservados++;
					    if (rangoBL==0){
					    	ind.punterosDirectos[nblogico] = ptr;
					    }else{
					    	if(bread(ptr_ant,bufferAux)==-1){
							    printf("Error in traducir_bloque_inodo while reading a block(ptr==0), line 555, file ficheros_basicos.c\n");
							    return -1;								
							}
                            bufferAux[index]=ptr;
					    	//printf("El buffer para reservar datos es: %d\n", bufferAux[index]);                            
							if(bwrite(ptr_ant,bufferAux)==-1){
							    printf("Error in traducir_bloque_inodo while writing a block(ptr==0), line 561, file ficheros_basicos.c\n");
							    return -1;	
							}	

					    }
					}
			}
			if (salvar_inodo==1){
				ind.numBloquesOcupados = bloques_reservados;
				ind.ctime = time(NULL);
				if(escribir_inodo(ind,ninodo)==-1){
						printf("Error in traducir_bloque_inodo while getting the index, line 572, file ficheros_basicos.c\n");
						return -1;						
				}
			}
			return ptr;
		}
		int liberar_inodo(unsigned int ninodo){
			struct inodo inodo;
			struct superbloque sb;
			if(liberar_bloques_inodo(ninodo,0)==-1){
					printf("Error in liberar_inodo while freeing the blocks of the inode, line 582, file ficheros_basicos.c\n");
					return -1;	
			}
			inodo = leer_inodo(ninodo);
			inodo.tipo = 'l';
			//We read the superblock to update the free inodes
	        if(bread(posSB,&sb)==-1){
					printf("Error in liberar_inodo while reading superblock, line 589, file ficheros_basicos.c\n");
					return -1;		        	
	        }
	        //We save the value of the previos free block block
	        inodo.punterosDirectos[0]=sb.posPrimerInodoLibre;
	        //Updates the values requiered for the sb
	        sb.posPrimerInodoLibre = ninodo;
	        sb.cantBloquesLibres++;
	        if(escribir_inodo(inodo,ninodo)==-1){
					printf("Error in liberar_inodo while writing inode, line 598, file ficheros_basicos.c\n");
					return -1;		        	
	        }
	        if(bwrite(posSB,&sb)==-1){
					printf("Error in liberar_inodo while writing superblock, line 602, file ficheros_basicos.c\n");
					return -1;		        	
	        }
	        return ninodo;
		}

	int liberar_bloques_inodo(unsigned int ninodo, unsigned int blogico){
		struct inodo in;
		unsigned int prof;
		in=leer_inodo(ninodo);
		unsigned int last=in.tamEnBytesLog%BLOCKSIZE==0?in.tamEnBytesLog/BLOCKSIZE:in.tamEnBytesLog/BLOCKSIZE+1;
		if(in.tamEnBytesLog==0) return 0;
		if(blogico >last) {
			return -1;
		}else {
			liberar_direct(last, blogico,in,ninodo);
			return 0;
		}
	}

	int liberar_direct(unsigned int last, unsigned int blogico,struct inodo in,unsigned int ninodo){
	/* 
	 * In this algorithm we run through all the levels and we liberate the data blocks.
	 * Once all the data blocks have been liberated, if we are in one of the indirect
	 * levels, we have to release the pointer blocks as well.
	 */
	unsigned int buf[BLOCKSIZE/sizeof(unsigned int)],buf1[BLOCKSIZE/sizeof(unsigned int)],buf2[BLOCKSIZE/sizeof(unsigned int)];
	unsigned char check[BLOCKSIZE];
	unsigned int i,j,k,l,tamfinal;
	i=blogico;
	tamfinal=in.tamEnBytesLog-(last-blogico)*BLOCKSIZE;
	memset(check,0,BLOCKSIZE);
	//~ if(last==blogico) return 0;
	//We free al the blocks in the direct pointers field
	while(i<12&&i<=last){
		if(in.punterosDirectos[i]!=0){
		liberar_bloque(in.punterosDirectos[i]);
		in.numBloquesOcupados--;
		in.punterosDirectos[i]=0;
		}
		i++;
	}
	
	//We free al the blocks in the first indirect pointer field
	if(i<last&&i<(BLOCKSIZE/sizeof(unsigned int))+12){  //we check if we have reached the last element, before we read the data blocks
		if(in.punterosIndirectos[0]!=0){
			if(bread(in.punterosIndirectos[0],buf)<0) return -1;
			j=(blogico)%(BLOCKSIZE/sizeof(unsigned int));
			while(j<(BLOCKSIZE/sizeof(unsigned int))&&i<last){
				if(buf[j]!=0){
					liberar_bloque(buf[j]);  //Free the data block
					in.numBloquesOcupados--; 
					buf[j]=0;
				}
				j++;
				i++;
			}
			if(memcmp(buf,check,BLOCKSIZE)==0){
				liberar_bloque(in.punterosIndirectos[0]); //Free the level 1 indirect block(if there are no more data blocks)
				in.punterosIndirectos[0]=0;
			}
		}else{
			i+=(BLOCKSIZE/sizeof(unsigned int));
		}
	}
	
	//We free al the blocks in the second indirect pointer field
	if(i<last&& i< (BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))+(BLOCKSIZE/sizeof(unsigned int))+12){
		if(in.punterosIndirectos[1]!=0){
			if(bread(in.punterosIndirectos[1],buf)<0) return -1;
			k=(i-((BLOCKSIZE/sizeof(unsigned int))+12))/(BLOCKSIZE/sizeof(unsigned int));
			j=(i-((BLOCKSIZE/sizeof(unsigned int))+12))%(BLOCKSIZE/sizeof(unsigned int));
			while(k<(BLOCKSIZE/sizeof(unsigned int))&&i<last){
				if(buf[k]!=0){
					if(bread(buf[k],buf1)<0) return -1;
					while(j<(BLOCKSIZE/sizeof(unsigned int))&&i<last){
						if(buf1[j]!=0){
							liberar_bloque(buf1[j]); //Free the data block
							in.numBloquesOcupados--;
							buf1[j]=0;
						}
						j++;
						i++;
					}
					if(bwrite(buf[k],buf1)<0) return -1;
					if(memcmp(buf1,check,BLOCKSIZE)==0){
						if(buf[k]!=0){
							liberar_bloque(buf[k]); //Free the level 2 indirect block(if there are no more data blocks)
							buf[k]=0;
						}
					}
				} else {
					i+=(BLOCKSIZE/sizeof(unsigned int));
				}
				j=0;
				k++;
			}
			if(bwrite(in.punterosIndirectos[1],buf)<0) return -1;
			if(memcmp(buf,check,BLOCKSIZE)==0){
				liberar_bloque(in.punterosIndirectos[1]); //Free the level 1 indirect block(if there are no more data blocks)
				in.punterosIndirectos[1]=0;
			}
		} else {
			i+=(BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int));
		}
	}
	
	//We free al the blocks in the third indirect pointer field
	if(i<last){
		if(in.punterosIndirectos[2]!=0){
			if(bread(in.punterosIndirectos[2],buf2)<0) return -1;
			l=(i-((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))+((BLOCKSIZE/sizeof(unsigned int))+12)))/((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int)));   //Posicion en el primer bloque de punteros
			k=((i-((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))+(BLOCKSIZE/sizeof(unsigned int))+12))%((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))))/(BLOCKSIZE/sizeof(unsigned int));  //Posicion en el segundo bloque de punteros 
			j=((i-((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))+(BLOCKSIZE/sizeof(unsigned int))+12))%((BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int))))%(BLOCKSIZE/sizeof(unsigned int));  //El puntero al bloque de datos en el tercer bloque de punteros
			while(l<(BLOCKSIZE/sizeof(unsigned int)) && i<last){
				if(buf2[l]!=0){
					if(bread(buf2[l],buf)<0) return -1;
					while(k<(BLOCKSIZE/sizeof(unsigned int))&&i<last){
						if(buf[k]!=0){
							if(bread(buf[k],buf1)<0) return -1;
							while(j<(BLOCKSIZE/sizeof(unsigned int))&&i<last){
								if(buf1[j]!=0){
									liberar_bloque(buf1[j]); ///Free the data block
									in.numBloquesOcupados--;
									buf1[j]=0;
								}
								j++;
								i++;
							}
							if(bwrite(buf[k],buf1)<0) return -1;
							if(memcmp(buf1,check,BLOCKSIZE)==0){
								if(buf[k]!=0){
									liberar_bloque(buf[k]); //Free the level 3 indirect block(if there are no more data blocks)
									buf[k]=0;
								}
							}
						} else {
							i+=(BLOCKSIZE/sizeof(unsigned int));
						}
						j=0;
						k++;
					}
					if(bwrite(buf2[l],buf)<0) return -1;
					if(memcmp(buf,check,BLOCKSIZE)==0){
						if(buf2[l]!=0){
							liberar_bloque(buf2[l]); //Free the level 2 indirect block(if there are no more data blocks)
							buf2[l]=0;
						}
					}
				} else {
					i+=(BLOCKSIZE/sizeof(unsigned int))*(BLOCKSIZE/sizeof(unsigned int));
				}
				l++;
				k=0;
			}
			if(memcmp(buf,check,BLOCKSIZE)==0){
				liberar_bloque(in.punterosIndirectos[2]); //Free the level 1 indirect block(if there are no more data blocks)
				in.punterosIndirectos[2]=0;
			}
		}
	}
	//We update the final size of the inode and we write it back
	in.tamEnBytesLog=tamfinal; 
	if(escribir_inodo(in,ninodo)<0) return -1;
	return 0;
}


