#include "directorios.h"
#include "ficheros_basicos.h"
#include <string.h>
//Function that splits the name and the location
int extraer_camino(const char *camino, char *inicial, char *final, unsigned char *tipo){
	int i = 0;
	const char *sig_camino = strchr(camino + 1,'/');
	memset(inicial,0,strlen(inicial));
	if(sig_camino==NULL){
		//It's a file
		strcpy(inicial, camino+1);
		*final = '\0';		
		*tipo = 'f';
	}else{
		//It's a directory
		i = sig_camino - camino - 1;
		strncpy(inicial, camino + 1,i);
		strcpy(final, sig_camino);
		*tipo = 'd';
	}
}
/*
	Errors:
		-1 := Error EC (Extraer Camino)
		-2 := Error NO_PERMISOS_LECTURA
		-3 := Error LECTURA
		-4 := Error ERROR_NO_EXISTE_ENTRADA_CONSULTA
		-5 := Error RESERVAR_INODO
		-6 := Error NO_DIRECTORIO_INTERMEDIO
		-7 := Error LIBERAR_INODO
		-8 := Error ESCRITURA
	    -9 := Error YA_EXISTE_ENTRADA

*/
int buscar_entrada(const char *camino_parcial, unsigned int *p_inodo_dir, unsigned int *p_inodo, unsigned int *p_entrada, char reservar, unsigned char permisos){
	struct inodo ind;
	int numentradas;
	struct entrada entr;
	char inicial[64];
  	char final[strlen(camino_parcial)];
  	unsigned char tipo;
	//First we check if we are located at the root
	if(strcmp(camino_parcial,"/") == 0){
		*p_inodo = 0;
		*p_entrada = 0;
		return 0;
	}
  	//We initialize the values of both strings
  	memset(inicial,0,60);
	memset(final,0,strlen(camino_parcial));
	//Now we extract the different way
	if(extraer_camino(camino_parcial,inicial,final,&tipo)<0){
		printf("Error in buscar_entrada while using function extraer_camino, file directorios.c \n");
		return -1;
	}
	printf("%s\n",inicial);
	printf("%s\n",final);
	ind = leer_inodo(*p_inodo_dir);
	entr.nombre[0] = '\0';

	int numEntr = ind.tamEnBytesLog/sizeof(struct entrada);
	int nentrada = 0; //Num. entrada inicial
	if(numEntr>0){
		if((ind.permisos & 4) == 4){
		printf("Error in buscar_entrada, file does not have the correct permissions, file directorios.c \n");
		return -2;			
		}
		if(mi_read_f(*p_inodo_dir,&entr,nentrada*sizeof(struct entrada),sizeof(struct entrada)) < 0){
			printf("Error in buscar_entrada, file does not have the correct permissions, file directorios.c \n");
 			return -3;			
		}
		while(nentrada<numEntr && strcmp(inicial,entr.nombre)!=0){
			nentrada++;
			if(mi_read_f(*p_inodo_dir,&entr,nentrada*sizeof(struct entrada),sizeof(struct entrada)) < 0){
				printf("Error in buscar_entrada, file does not have the correct permissions, file directorios.c \n");
 				return -3;			
			}			
		}
	}
	if(nentrada == numEntr){
		switch(reservar) {
		 	case '0':
		 		printf("Error in buscar_entrada, not the correct mode, file directorios.c \n");
 				return -4; 
 				break;
 			case '1':
 				strcpy(entr.nombre,inicial);
 				if(tipo == 'd'){
 					if(strcmp(final,"/") == 0){
 						entr.inodo = reservar_inodo('d','7');
 						if(entr.inodo<0){
 							printf("Error in buscar_entrada, cannot book a inode(directory), file directorios.c \n");
 							return -5;
 						}
					}else{
						printf("Error in buscar_entrada, there is no intermediate directory, file directorios.c \n");
 						return -6;
					}
 				}else{
 					entr.inodo = reservar_inodo('f','7');
 					if(entr.inodo<0){
 						printf("Error in buscar_entrada, cannot book a inode(file), file directorios.c \n");
 						return -5;
 					}
 				}
 				if(mi_write_f(*p_inodo_dir,&entr,nentrada*sizeof(struct entrada),sizeof(struct entrada)) < 0){
 					if(entr.inodo!=-1){
 						if(liberar_inodo(entr.inodo)<0){
 							printf("Error in buscar_entrada, while liberating a inode, file directorios.c \n");
 							return -7; 							
 						}
 						printf("Error in buscar_entrada, error while writing, file directorios.c \n");
 						return -8; 						
 					}
 				}
 				break;			
			}		
		}
	if((strcmp(final,"/")==0) || tipo =='f'){
		if((numEntr<numentradas) && reservar == 1){
 			printf("Error in buscar_entrada, the entrance already exists, file directorios.c \n");
 			return -9; 	
		}
		*p_inodo = entr.inodo;
		*p_entrada = nentrada;
		return 0;
	}else{
		*p_inodo_dir = entr.inodo;
		return buscar_entrada (final, p_inodo_dir, p_inodo, p_entrada, reservar, permisos);
	}
}
