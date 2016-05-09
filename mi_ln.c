#include "directorios.h"

int main(int argc, char **argv){
	int descriptor;
	if(argc<4){
		printf("Syntax error, not enough argumentes, file mi_ln.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path 1\n"
			"Argument 3: Path 2\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	//  const char *sig_camino = strchr(argv[2] + 1,'/');
	//  const char *sig_camino2 = strchr(argv[3] + 1,'/');
	//  printf("%s\n",sig_camino);
	//  printf("%s\n",sig_camino2);

	// //Check if rutes are files
	//  if ((sig_camino != NULL)) {
	//  	printf("La primera ruta no es un fichero\n");
	//  	return -1;
	//  }
	//  if ((sig_camino2 != NULL)){
	//  	printf("La segunda ruta no es un fichero\n");
	//  	return -1;		
	//  }

	if((mi_link(argv[2],argv[3]))<0) return -1;
	bumount(descriptor);
	return 0;
}