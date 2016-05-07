#include "directorios.h"
#include "string.h"

int main(int argc, char **argv){
	int descriptor,offset,bytesLeidos,totalBytes;
	unsigned char input[1500];
	char string[128];
	if(argc<3){
		printf("Syntax error, not enough arguments, file mi_chmod.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: Path\n");
		return -1;
	}
	descriptor = bmount(argv[1]);
	if(descriptor<0){
		printf("Error while opening file sistem, file mi_cat.c\n");
		return -1;
	}
    offset = 0;
    totalBytes = 0;
    memset(input,0, sizeof(input));
    while((bytesLeidos=mi_read(argv[2],input,offset,sizeof(input)))>0){
    	offset=offset + bytesLeidos;
    	write(1,input,bytesLeidos);
    	totalBytes += bytesLeidos;
    	memset(input,0, sizeof(input));
    }
    sprintf(string,"El número total de bytes leídos es: %d \n", totalBytes);
    write(2,string, strlen(string));
	if(bumount()<0){
		printf("Error while closing file sistem, file mi_cat.c\n");
		return -1;		
	}
	return 0;
}