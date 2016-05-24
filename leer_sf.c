#include "bloques.h"
#include "ficheros_basicos.h"

void mostrarSB(struct superbloque SB);
void mostrarBM(struct superbloque SB);
void mostrarIA(struct superbloque SB);

int main(int argc, char **argv){
	struct superbloque SB;
	struct tm *ts;
	struct inodo in;
	unsigned char buf[BLOCKSIZE];
	int nbloque,i,j,descriptor;
	if(argc<2){
		printf("Syntax error, not enough arguments, file mi_chmod.c\n"
			"Correct Order:\n"
			"Argument 1: File system name\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	if(descriptor<0){
		exit(1);
	}
	if(bread(posSB,&SB)<0) return -1;
	printf("-----Información del fichero %s-----\n", argv[1]);
	mostrarSB(SB);
	mostrarBM(SB);
	mostrarIA(SB);

	if(bumount(descriptor)<0){
		exit(1);
	}
}

void mostrarSB(struct superbloque SB){
	printf("\t*****Tamaños*****\n");
	printf("#Cantidad total de bloques para el mapa de bits son: %d \n",tamMB(SB.totBloques));
	printf("#Cantidad total de bloques para el array de inodos son: %d \n",tamAI(SB.totInodos));
	printf("\t*****Superbloque*****\n");
	printf("#Posición del primer bloque del mapa de bits: %d \n",SB.posPrimerBloqueMB);
	printf("#Posición del último bloque del mapa de bits: %d \n",SB.posUltimoBloqueMB);
	printf("#Posición del primer bloque del array de inodos: %d \n",SB.posPrimerBloqueAI);
	printf("#Posición del último bloque del array de inodos: %d \n",SB.posUltimoBloqueAI);
	printf("#Posición del primer bloque de datos: %d \n",SB.posPrimerBloqueDatos);
	printf("#Posición del último bloque de datos: %d \n",SB.posUltimoBloqueDatos);
	printf("#Posición del inodo del directorio raíz: %d \n",SB.posInodoRaiz);
	printf("#Posición del primer inodo libre: %d \n",SB.posPrimerInodoLibre);
	printf("#Cantidad de bloques libres: %d \n",SB.cantBloquesLibres);
	printf("#Cantidad de inodos libres: %d \n",SB.cantInodosLibres);
	printf("#Cantidad total de bloques: %d \n",SB.totBloques);
	printf("#Cantidad total de inodos: %d \n",SB.totInodos);
}

void mostrarIA(struct superbloque SB){
	char atime[80], mtime[80],cttime[80],*tipo,perm[3];
	struct inodo in;
	int ninodo;
	struct tm *ts;
	printf("\n\n \t*****Array de Inodos*****\n");
	printf("#Tamaño Inodo: %d\n",TAM_INODO);
	for(ninodo=0;ninodo<SB.totInodos;ninodo++){
	   		in = leer_inodo(ninodo);
			if(in.tipo!='l'){
			ts = localtime(&in.atime);
			strftime(atime, sizeof(atime), "%a %Y-%m-%d %H:%M:%S", ts);
			ts = localtime(&in.mtime);
			strftime(mtime, sizeof(mtime), "%a %Y-%m-%d %H:%M:%S", ts);
			ts = localtime(&in.ctime);
			strftime(cttime, sizeof(cttime), "%a %Y-%m-%d %H:%M:%S", ts);	
			perm[0]= ((unsigned char)in.permisos&(unsigned char)1)==0 ?'-':'X'; 
			perm[1]=((unsigned char)in.permisos&(unsigned char)2)==0?'-':'W';
			perm[2]=((unsigned char)in.permisos&(unsigned char)4)==0?'-':'R';
			tipo=in.tipo=='d'? "Directorio" : "Fichero";
			printf("#ID: %d TIPO: %s PERMISOS: %c%c%c NLINKS: %d TAMAÑO: %d BLOQUES OCUPADOS: %d \n",ninodo,tipo,perm[0], perm[1], perm[2], in.nlinks,in.tamEnBytesLog,in.numBloquesOcupados);
			printf(" ATIME: %s MTIME: %s CTIME: %s\n\n",atime,mtime,cttime);
		}
	}
}

void mostrarBM(struct superbloque SB){
	int nbloque,i,j;
	printf("\n\t*****Bloques Ocupados*****\n");
	j=0;
	for(nbloque=0;nbloque<SB.totBloques;nbloque++){
		i=leer_bit(nbloque);
		if(i==1) {
			if(j%6==0) printf("\n");
			printf("%d\t",nbloque);
			j++;
		}
	}
	printf("\n");
	printf("Numero de Bloques Ocupados totales es: %d\n",j);
}
