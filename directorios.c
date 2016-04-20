#include "directorios.h"
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

int buscar_entrada(const char *camino_parcial, unsigned int *p_inodo_dir, unsigned int *p_inodo, unsigned int *p_entrada, char reservar, unsigned char permisos){
	return 0;
}
