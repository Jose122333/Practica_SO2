#include "ficheros.h"
#include "ficheros_basicos.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

void showStats(struct STAT status, int ninodo);

int main(int argc, char **argv){
	int descriptor,ninodo,offset,bytesLeidos,totalBytes;
    struct STAT status;
	unsigned char input[1500];
	char string[128];
	descriptor = bmount(argv[1]);
	ninodo = atoi(argv[2]);
  	if(descriptor<0) exit(1);
    mi_stat_f(ninodo,&status);
    showStats(status, ninodo);
    mi_chmod_f(ninodo,4);
    mi_stat_f(ninodo,&status);
    showStats(status, ninodo);
    mi_chmod_f(ninodo,2);
    mi_stat_f(ninodo,&status);
    showStats(status, ninodo);
    mi_chmod_f(ninodo,6);
    mi_stat_f(ninodo,&status);
    showStats(status, ninodo);
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
void showStats(struct STAT status,	int ninodo){
    char atime[80], mtime[80],cttime[80],*tipo,perm[3];
    struct tm *ts;
    printf("\n\t*****Metainformacion del inodo*****\n");    
    ts = localtime(&status.atime);
    strftime(atime, sizeof(atime), "%a %Y-%m-%d %H:%M:%S", ts);
    ts = localtime(&status.mtime);
    strftime(mtime, sizeof(mtime), "%a %Y-%m-%d %H:%M:%S", ts);
    ts = localtime(&status.ctime);
    strftime(cttime, sizeof(cttime), "%a %Y-%m-%d %H:%M:%S", ts);   
    perm[0]= ((unsigned char)status.permisos&(unsigned char)1)==0 ?'-':'X'; 
    perm[1]=((unsigned char)status.permisos&(unsigned char)2)==0?'-':'W';
    perm[2]=((unsigned char)status.permisos&(unsigned char)4)==0?'-':'R';
    tipo=status.tipo=='d'? "Directorio" : "Fichero";
    printf("#ID: %d TIPO: %s PERMISOS: %s NLINKS: %d TAMAÑO: %d BLOQUES OCUPADOS: %d \n",ninodo,tipo,perm,status.nlinks,status.tamEnBytesLog,status.numBloquesOcupados);
    printf(" ATIME: %s MTIME: %s CTIME: %s\n\n",atime,mtime,cttime);
}
// Nota: Primer Argumento es el nombreDelFichero, Segundo es el nombre del inodo
