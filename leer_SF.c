#include "bloques.h"
#include "ficheros_basicos.h"
int main(int argc, char **argv){
	struct superbloque SB;
	struct tm *ts;
	char atime[80], mtime[80], ctime[80],*tipo,perm[3];
	struct inodo in;
	struct inodo ar_in[BLOCKSIZE/TAM_INODO];
	int ninodo,i,j;
	if(argc<2) return -1;
	if(bmount(argv[1])<0){
		exit(1);
	}
	if(bread(posSB,&SB)<0) return -1;
	printf("-----Información del fichero %s-----\n", argv[1]);
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
	printf("\n\t*****Bloques Ocupados*****\n");
	/*j=0;
	for(ninodo=0;ninodo<SB.totBloques;ninodo++){
		i=leer_bit(ninodo);
		if(i==1) {
			if(j%6==0) printf("\n");
			printf("%d\t",ninodo);
			j++;
		}
	}
	printf("\n\n \t*****Array de Inodos*****\n");
	printf("#Tamaño Inodo: %d\n",TAM_INODO);
	int m;
	for (m=SB.posPrimerBloqueAI;m<=SB.posUltimoBloqueAI;m++) {
	    bread(m,ar_in);
	    int k;
	   for(k=0;k<BLOCKSIZE/TAM_INODO;k++){
	   		in = leer_inodo(k);
			if(in.tipo!='l'){
			perm[0]= ((unsigned char)in.permisos&(unsigned char)1)==0 ?'-':'X'; 
			perm[1]=((unsigned char)in.permisos&(unsigned char)2)==0?'-':'W';
			perm[2]=((unsigned char)in.permisos&(unsigned char)4)==0?'-':'R';
			tipo=in.tipo=='d'? "Directorio" : "Fichero";
			printf("#ID: %d TIPO: %s PERMISOS: %s NLINKS: %d TAMAÑO: %d BLOQUES OCUPADOS: %d \n",ninodo,tipo,perm,in.nlinks,in.tamEnBytesLog,in.numBloquesOcupados);
			printf(" ATIME: %s MTIME: %s CTIME: %s\n\n",atime,mtime,ctime);
		}
	   } 	
	}*/
}
