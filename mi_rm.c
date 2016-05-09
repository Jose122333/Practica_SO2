#include "directorios.h"

int main(int argc, char **argv){
	int descriptor;
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_rm.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	if(mi_unlink(argv[2])<0) return -1;
	bumount(descriptor);
	return 0;
}