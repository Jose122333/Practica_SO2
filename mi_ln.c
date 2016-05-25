#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

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
	//We mount the file system
	descriptor = bmount(argv[1]);
	//Call to the mi_link function()
	if((mi_link(argv[2],argv[3]))<0) {
		printf("Error in mi_ln.c, while calling mi_link\n");
		return -1;
	}
	//We un-mount the file system
	bumount(descriptor);
	return 0;
}