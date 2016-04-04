#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	int descriptor,i,ninodo,offset,bytesLeidos,bytesEscritos;
	char perm[3];
	unsigned char input[BLOCKSIZE];
	if(argc<3) exit(1);
	descriptor = bmount(argv[1]);
	ninodo = atoi(argv[2]);
  	if(descriptor<0) exit(1);
    offset = atoi(argv[3]);
    printf("El contenido del fichero es: \n");
    while((bytesLeidos=mi_read_f(ninodo,input+bytesEscritos,offset,BLOCKSIZE))>0){
    	offset=offset+ bytesLeidos;
    	bytesEscritos = bytesLeidos + bytesEscritos;
    	   	printf("%s\n", input);
    	   		memset(input,0, sizeof(input));

    }
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
// Nota: Primer Argumento es el nombreDelFichero, Segundo es el nombre del inodo, Tercero es el offset
