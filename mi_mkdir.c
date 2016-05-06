#include "directorios.h"

int main(int argc, char **argv){
	int descriptor;
	if(argc<4){
		printf("Syntax error, not enough arguments, file mi_mkdir.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Permissions\n"
			"Argument 3: Path\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	if((mi_create(argv[3],atoi(argv[2])))<0) return -1;
	bumount();
	return 0;
}