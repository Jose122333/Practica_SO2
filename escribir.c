#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	struct inodo in;
	int descriptor,i;
	unsigned int offset,ninodo,bytesWritten;
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
    strcpy(input, "blablablablablablablablablablablablablablablablablablablablablablablablablablablablablablablablabla....");
    bytesWritten = mi_write_f(ninodo,input,offset,BLOCKSIZE);
    if(bytesWritten<0){
    	printf("Error al escribir en el fichero");
    }
    //printf("El numero bytes escritos es: %d\n", bytesWritten);
	memset(input,0, BLOCKSIZE);
	bytesWritten = mi_read_f(ninodo,input,offset,BLOCKSIZE);
    if(bytesWritten<0){
    	printf("Error al leer en el fichero");
    }
    //printf("El numero bytes leidos es: %d\n", bytesWritten);
    printf("El contenido del fichero es: \n");
    input[BLOCKSIZE]=0;
	printf("%s", input);
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
