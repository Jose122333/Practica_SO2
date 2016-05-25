#include "ficheros.h"
#include "ficheros_basicos.h"
#include <stdlib.h>
#include <stdio.h> 

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	int descriptor,bytesEscribir,sz;
	unsigned int offset,ninodo,bytesWritten, bytesEscritos, longitudFichero;
	FILE *fptr;
	if(argc<4){
		printf("Syntax error, not enough argumentes, file mi_escribir.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: offset\n"
			"Argument 3: input text to write in file\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	bytesEscritos = 0;
	ninodo=reservar_inodo('f',6);
	//ninodo = 1;
	printf("#El inodo creado es: %d\n",ninodo);
    offset = atoi(argv[2]);
    if ((fptr=fopen(argv[3],"r"))==NULL){
       printf("Error! opening file");
       exit(1);         /* Program exits if file pointer returns NULL. */
   	}
   	fseek(fptr, 0L, SEEK_END);
	sz = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	unsigned char input[sz];
	fscanf(fptr,"%[^\n]",input);
	fclose(fptr);
	//We write all the file, in one take, to the FS
    bytesWritten=mi_write_f(ninodo,input,offset,sz);
    if(bytesWritten<0){
    	printf("Error al escribir en el fichero");
    }
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
