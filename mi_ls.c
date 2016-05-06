#include "directorios.h"

int main(int argc, char **argv){
	int descriptor;
	unsigned char buffer[2048];
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_mkdir.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	printf("Entramos en el mi_dir\n");
	if((mi_dir(argv[2],buffer))<0) return -1;
	//printf("%s\n",buffer);
	bumount();
	return 0;
}