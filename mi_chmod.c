#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	int descriptor;
	if(argc<4){
		printf("Syntax error, not enough arguments, file mi_chmod.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Permissions\n"
			"Argument 3: Path\n");
		return -1;
	}
	//We mount the file system
	descriptor = bmount(argv[1]);
	//Launch the mi_chmod function
	if((mi_chmod(argv[3],atoi(argv[2])))<0) return -1;
	//Un-mount file system
	bumount(descriptor);
	return 0;
}