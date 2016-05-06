#include "directorios.h"

int main(int argc, char **argv){
	int descriptor;
	descriptor = bmount(argv[1]);

	if((mi_chmod(argv[3],atoi(argv[2])))<0) return -1;

	return 0;
}