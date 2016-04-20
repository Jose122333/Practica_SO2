#include "directorios.h"
#include <string.h>
//Function that splits the name and the location
int extraer_camino(const char *camino, char *inicial, char *final, unsigned char *tipo){
	int i=1, size=strlen(camino);
	while(i<size&&camino[i]!='/') i++;
	if(i==size){
		final="";
		strcpy(inicial,camino+1);
		return 0;
	}else{
		strncpy(inicial, camino+1,i-1);
		strncpy(final, camino+i,size-i);
		return 1;
	}
}