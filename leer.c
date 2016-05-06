#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	int descriptor,ninodo,offset,bytesLeidos,totalBytes;
	unsigned char input[1500];
	//if(argc<3) exit(1);
	char string[128];
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_chmod.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Inode number\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	ninodo = atoi(argv[2]);
  	if(descriptor<0) exit(1);
    offset = 0;
    totalBytes = 0;
    memset(input,0, sizeof(input));
    while((bytesLeidos=mi_read_f(ninodo,input,offset,sizeof(input)))>0){
    	offset=offset + bytesLeidos;
    	write(1,input,bytesLeidos);
    	totalBytes += bytesLeidos;
    	memset(input,0, sizeof(input));
    }
    sprintf(string,"El número total de bytes leídos es: %d \n", totalBytes);
    write(2,string, strlen(string));
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
// Nota: Primer Argumento es el nombreDelFichero, Segundo es el nombre del inodo, Tercero es el offset
