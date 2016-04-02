#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	struct inodo in;
	int descriptor,i;
	unsigned int offset,ninodo,insize;
	char perm[3];
	unsigned char input[BLOCKSIZE];
	//if(argc<3) exit(1);
	descriptor = bmount(argv[1]);
	if(bread(posSB,&SB)<0) {
		printf("Ha ocurrido algun error");
		return -1;
	}
	//offset = argv[1];
	ninodo=reservar_inodo('f',6);
	printf("#El inodo creado es: %d\n",ninodo);
    offset = 0;
	printf("#El offset es %d\n",offset);
    strcpy(input, "blablablablablablablablablablablablablablablablablablablablablablablablablablabla...blablablablablabla....");
    /*if(mi_write_f(ninodo,input,offset,BLOCKSIZE)<0){
    	printf("Error al escribir en el fichero");
    }
    memset(input,0, BLOCKSIZE);
    if(mi_read_f(ninodo,input,offset,BLOCKSIZE)<0){
    	printf("Error al leer en el fichero");
    }*/
    input[BLOCKSIZE]=0;
	printf("%s", input);
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
