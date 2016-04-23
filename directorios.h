#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ficheros_basicos.h"
#include "ficheros.h"
struct entrada {
	char nombre[60]; //En el sistema de ficheros ext2 la longitud del nombre es 255
	unsigned int inodo;
};
//Functions that belong to the 7th stage
int extraer_camino(const char *camino, char *inicial, char *final, unsigned char *tipo);
int buscar_entrada(const char *camino_parcial, unsigned int *p_inodo_dir, unsigned int *p_inodo, unsigned int *p_entrada, char reservar, unsigned char permisos);
//Functions that belong to the 8th stage
int mi_create(const char *camino, unsigned char permisos);
int mi_dir(const char *camino, char *buffer);
int mi_link(const char *camino1, const char *camino2);
int mi_unlink(const char *camino);
int mi_chmod(const char *camino, unsigned char permisos);
int mi_stat(const char *camino, struct STAT *p_stat);
int mi_read(const char *camino, void *buf, unsigned int offset, unsigned int nbytes);
int mi_write(const char *camino, const void *buf, unsigned int offset, unsigned int nbytes);
//Auxiliar functions
int getResponse(int BuscarEntradaRS);