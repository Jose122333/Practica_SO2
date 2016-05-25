#include <time.h>
#include <limits.h>
#include "bloques.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define posSB 0 //The position of the superblock
#define TAM_INODO 128 //Size(in bytes) of each inode

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

//Superblock structure format
struct superbloque{
unsigned int posPrimerBloqueMB;  
unsigned int posUltimoBloqueMB; 
unsigned int posPrimerBloqueAI; 
unsigned int posUltimoBloqueAI;
unsigned int posPrimerBloqueDatos;
unsigned int posUltimoBloqueDatos;
unsigned int posInodoRaiz;
unsigned int posPrimerInodoLibre;
unsigned int cantBloquesLibres;
unsigned int cantInodosLibres;
unsigned int totBloques;
unsigned int totInodos;
char padding[BLOCKSIZE-12*sizeof(unsigned int)]; //Padding
};

//Inode structure format
struct inodo{ 
unsigned char tipo; 
unsigned char permisos; 
unsigned char reservado_alineacion1 [6];
time_t atime;
time_t mtime; 
time_t ctime; 
unsigned int nlinks; 
unsigned int tamEnBytesLog; 
unsigned int numBloquesOcupados; 
unsigned int punterosDirectos[12]; 
unsigned int punterosIndirectos[3]; 
char padding[TAM_INODO-2*sizeof(unsigned char)-3*sizeof(time_t)-18*sizeof(unsigned int)-6*sizeof(unsigned char)]; 
};



//Functions that belong to stage 2
int tamMB(unsigned int nbloques);
int tamAI(unsigned int ninodos);
int initSB(unsigned int nbloques, unsigned int ninodos);
int initMB();
int initAI(unsigned int ninodos);
//Functions that belong to stage 3
int escribir_bit(unsigned int nbloque, unsigned int bit);
unsigned char leer_bit(unsigned int nbloque);
int reservar_bloque();
int liberar_bloque(unsigned int nbloque);
int escribir_inodo(struct inodo inodo, unsigned int ninodo);
struct inodo leer_inodo(unsigned int ninodo);
int reservar_inodo(unsigned char tipo, unsigned char permisos);
//Functions that belong to stage 4(Part 1)
int traducir_bloque_inodo(unsigned int ninodo, unsigned int nblogico, char reservar);
int obtener_rangoBL(struct inodo inodo, int nblogico, int *ptr);
int obtener_indice (int nblogico, int nivel_punteros);
//Functions that belong to stage 4(Part 2)
int liberar_inodo(unsigned int ninodo);
int liberar_bloques_inodo(unsigned int ninodo, unsigned int nblogico);

void leer_sf();



