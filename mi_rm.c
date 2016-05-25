#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	int descriptor;
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_rm.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path\n");
		return -1;
	}
	//We mount the file system
	descriptor = bmount(argv[1]);
	//Call to the mi_unlink call
	if(mi_unlink(argv[2])<0) {
		printf("Error in mi_rm.c, while calling mi_unlink\n");
		return -1;
	}
	//We un-mount the file system
	bumount(descriptor);
	return 0;
}