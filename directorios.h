#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

struct entrada {
	char nombre[60]; //En el sistema de ficheros ext2 la longitud del nombre es 255
	unsigned int inodo;
};

int extraer_camino(const char *camino, char *inicial, char *final, unsigned char *tipo);
int buscar_entrada(const char *camino_parcial, unsigned int *p_inodo_dir, unsigned int *p_inodo, unsigned int *p_entrada, char reservar, unsigned char permisos);
