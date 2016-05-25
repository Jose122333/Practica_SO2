#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

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
	//We mount the file system
	descriptor = bmount(argv[1]);
	//Call the mi_create function
	if((mi_create(argv[3],atoi(argv[2])))<0) {
		printf("Error in mi_mkdir.c, while calling mi_create\n");
		return -1;
	}
	//We un-mount the file system
	bumount(descriptor);
	return 0;
}