#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	int descriptor,ninodo;
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_stat.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path\n");
		return -1;
	}
	char atime[80], mtime[80],cttime[80],*tipo,perm[3];
	struct tm *ts;
	struct STAT out;
	descriptor = bmount(argv[1]);	
	ninodo=mi_stat(argv[2],&out);
	if(ninodo<0) return -1;
	ts = localtime(&out.atime);
	strftime(atime, sizeof(atime), "%a %Y-%m-%d %H:%M:%S", ts);
	ts = localtime(&out.mtime);
	strftime(mtime, sizeof(mtime), "%a %Y-%m-%d %H:%M:%S", ts);
	ts = localtime(&out.ctime);
	strftime(cttime, sizeof(cttime), "%a %Y-%m-%d %H:%M:%S", ts);	
	perm[0]= ((unsigned char)out.permisos&(unsigned char)1)==0 ?'-':'X'; 
	perm[1]=((unsigned char)out.permisos&(unsigned char)2)==0?'-':'W';
	perm[2]=((unsigned char)out.permisos&(unsigned char)4)==0?'-':'R';
	tipo=out.tipo=='d'? "Directorio" : "Fichero";
	printf("#ID: %d TIPO: %s PERMISOS: %c%c%c NLINKS: %d TAMAÑO: %d BLOQUES OCUPADOS: %d \n",ninodo,tipo,perm[0],perm[1], perm[2], out.nlinks,out.tamEnBytesLog,out.numBloquesOcupados);
	printf(" ATIME: %s MTIME: %s CTIME: %s\n\n",atime,mtime,cttime);
	bumount(descriptor);
	return 0;
}