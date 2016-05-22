#include "bloques.h"
#include <stdio.h>
#include "simulacion.h"

int main(int argc, char **argv){
	int descriptor,nEntradas,i=0,j;
	struct STAT fileStatus;
	char pathName[200];
	char childPathName[200];
	char *proceesID;
	int pid;
	const char ch = '_';
	struct entrada entr;
	//Check if the syntax is correct
	if(argc<2){
		printf("Syntax error, not enough arguments, file verificacion.c\n"
			"Correct Order:\n"
			"Argument 1: File system name\n"
			"Argument 2: Simulation directory name\n");
		return -1;
	}
	//Mount the file system
	descriptor = bmount(argv[1]);
	if(descriptor<0){
		printf("Error while mounting FS for the main process\n");
		return -1;
	}
	//Now we call the mi_stat to get the details of the file
	if(mi_stat(argv[2],&fileStatus)<0){
		printf("Error while calling mi_stat function, file verificacion.c\n");
		return -1;
	}
	//Now we calculate the number of entrances(they have to be 100)
	nEntradas = fileStatus.tamEnBytesLog/sizeof(struct entrada);
	if(nEntradas != 100){
		printf("Error, the number of entrances is not exactly 100\n");
		printf("Entrances found %d\n",nEntradas);
		return -1;
	}
	//Now we create a new file in the simulation directory
	memset(pathName,0,sizeof(pathName));
	strcat(pathName,argv[2]);
	printf("%s\n",pathName);
	strcat(pathName,"informe.txt");
	printf("%s\n",pathName);
	if(mi_create(pathName,6)<0){
		printf("Error while creating the informe.txt file, file verificacion.c\n");
		return -1;
	}
	//For each process
	for(i=0;i<nEntradas;i++){
		//First we read the entrance
		if(mi_read(argv[2],&entr,i*sizeof(struct entrada),sizeof(struct entrada))<0){
			printf("Error while reading process details for process number %d\n",i);
			return -1;
		}
		proceesID = strchr(entr.nombre,ch);
		proceesID = proceesID+1;
		pid = atoi(proceesID);
		//Now we read all all the registers written in the file prueba.dat	
		memset(childPathName,0,sizeof(childPathName));
		strcat(childPathName,argv[2]);
		strcat(childPathName,entr.nombre);
		strcat(childPathName,"/");
		strcat(childPathName,"prueba.dat");
		//printf("El nombre del directorio es para el proceso %d es: %s\n", i,childPathName);


	}

	//Un-mount the file system
	if(bumount(descriptor)<0){
		printf("Error while unmounting FS for the main process\n");
		return -1;
	}
	return 0;
}
