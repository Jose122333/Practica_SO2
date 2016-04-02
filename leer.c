#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	struct inodo in;
	int descriptor,i.ninodo;
	char perm[3];
	unsigned char input[insize];
	if(argc<3) exit(1);
	descriptor = argv[0];
	ninodo = argv[0];
	if(bmount(argv[0])<0) exit(1);
	if(bread(posSB,&SB)<0) {
		printf("Ha ocurrido algun error");
		return -1;
	}
    in = leer_inodo(ninodo);
	//scanf("%d",&offset);
	
	//i=mi_write_f(inode,argv[2],offset,insize);
	if(bumount()<0) exit(1);
	return 0;
}
