#include <time.h>
#include <limits.h>
#include "bloques.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define posSB 0 //el superbloque se escribe en el primer bloque de nuestro FS
#define TAM_INODO 128 //tamaño en bytes de un inodo

struct superbloque{
unsigned int posPrimerBloqueMB; //Posición del primer bloque del mapa de bits 
unsigned int posUltimoBloqueMB; //Posición del último bloque del mapa de bits 
unsigned int posPrimerBloqueAI; //Posición del primer bloque del array de inodos 
unsigned int posUltimoBloqueAI; //Posición del último bloque del array de inodos 
unsigned int posPrimerBloqueDatos; //Posición del primer bloque de datos 
unsigned int posUltimoBloqueDatos; //Posición del último bloque de datos 
unsigned int posInodoRaiz; //Posición del inodo del directorio raíz 
unsigned int posPrimerInodoLibre; //Posición del primer inodo libre 
unsigned int cantBloquesLibres; //Cantidad de bloques libres
unsigned int cantInodosLibres; //Cantidad de inodos libres 
unsigned int totBloques; //Cantidad total de bloques 
unsigned int totInodos; //Cantidad total de inodos 
char padding[BLOCKSIZE-12*sizeof(unsigned int)]; //Relleno
};


struct inodo{ //comprobar que ocupa 128 bytes haciendo un sizeof(inodo)!!!
unsigned char tipo; //Tipo (libre, directorio o fichero)
unsigned char permisos; //Permisos (lectura y/o escritura y/o ejecución)
unsigned char reservado_alineacion1 [6];
/* Por cuestiones internas de alineación de estructuras, si se está utilizando un tamaño de palabra de 4 bytes (microprocesadores de 32 bits): unsigned char reservado_alineacion1 [2]; 
en caso de que la palabra utilizada sea del tamaño de 8 bytes (microprocesadores de 64 bits): unsigned char reservado_alineacion1 [6]; */

time_t atime; //Fecha y hora del último acceso a datos: atime
time_t mtime; //Fecha y hora de la última modificación de datos: mtime
time_t ctime; //Fecha y hora de la última modificación del inodo: ctime

/* comprobar el tamaño del tipo time_t para vuestra plataforma/compilador: printf ("sizeof time_t is: %d\n", sizeof(time_t)); */

unsigned int nlinks; //Cantidad de enlaces de entradas en directorio
unsigned int tamEnBytesLog; //Tamaño en bytes lógicos
unsigned int numBloquesOcupados; //Cantidad de bloques ocupados en la zona de datos

unsigned int punterosDirectos[12]; //12 punteros a bloques directos
unsigned int punterosIndirectos[3]; /*3 punteros a bloques indirectos:1 puntero indirecto simple, 1 puntero indirecto doble, 1 puntero indirecto triple */
/* Utilizar una variable de alineación si es necesario para vuestra plataforma/compilador; 
*/
char padding[TAM_INODO-2*sizeof(unsigned char)-3*sizeof(time_t)-18*sizeof(unsigned int)-6*sizeof(unsigned char)]; //Last substract correspond to reservado_alineacion [6]
};



//Functions that belong to stage 2
int tamMB(unsigned int nbloques);
int tamAI(unsigned int ninodos);
int initSB(unsigned int nbloques, unsigned int ninodos);
int initMB();
int initAI();
//Functions that belong to stage 3
int escribir_bit(unsigned int nbloque, unsigned int bit);
unsigned char leer_bit(unsigned int nbloque);
int reservar_bloque();
int liberar_bloque(unsigned int nbloque);
int escribir_inodo(struct inodo inodo, unsigned int ninodo);
struct inodo leer_inodo(unsigned int ninodo);
int reservar_inodo(unsigned char tipo, unsigned char permisos);

void leer_sf();


