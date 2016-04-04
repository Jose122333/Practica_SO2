#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	struct inodo in;
	int descriptor,i.ninodo,offset;
	char perm[3];
	unsigned char buf[BLOCKSIZE];
	if(argc<3) exit(1);
	descriptor = argv[0];
	ninodo = argv[0];
	if(descriptor<0) exit(1);
    offset = 0;
    while(offset>=0){
    	if(mi_read_f(ninodo,buf,offset,BLOCKSIZE)<0){
    		printf("Error in my leer.c while reading with my_read_f");
    		offset += BLOCKSIZE;
    		//FALTA ESCRIBIR LA INFORMACIÓN DE BUF ANTES DE CONTINUAR
    		//limpiamos el bucle si hay menos de 1024 bytes de informacion
    		memset(buf,0, BLOCKSIZE);
    	}
    }
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
