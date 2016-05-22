#include "simulacion.h"

static int acabados = 0;
void reaper();
int main(int argc, char **argv){
	int descriptor,cid,i=0,j,posMax=500000;
	time_t now;
	struct tm *ts;
	char currentTime[80];
	char pathName[200];
	char childPathName[200];
	char processID[80];
	//Check if the syntax is correct
	if(argc<1){
		printf("Syntax error, not enough arguments, file simulacion.c\n"
			"Correct Order:\n"
			"Argument 1: File system name\n");
		return -1;
	}
	//Mount the file system
	descriptor = bmount(argv[1]);
	if(descriptor<0){
		printf("Error while mounting FS for the main process, file simulacion.c\n");
		return -1;
	}
	/* We preapre the date*/
	time(&now);
	ts = localtime(&now);
	strftime(currentTime,sizeof(currentTime),"%Y%m%d%H%M%S",ts);
	//We create the directory file
	memset(pathName,0,sizeof(pathName));
	strcat(pathName,"/");
	strcat(pathName,"simul_");
	strcat(pathName,currentTime);
	strcat(pathName,"/");
	printf("%s\n",pathName);
	if(mi_create(pathName,7)<0){
		printf("Error in while calling mi_create, file simulacion.c\n");
		return -1;
	}
	//We call the reaper to clear the zombie processes
	signal(SIGCHLD, reaper);
	//We start creating the child processes
	cid = fork();
	if(cid<0){
		printf("Error in fork function, file simulacion.c\n");
		return -1;
	}
	//We run through all the 100 processes
	memset(childPathName,0,sizeof(childPathName));
	memset(processID,0,sizeof(processID));
	while(i<100){
		//Check if the process is indeed a child
		if(cid == 0){
			//Mount the file system
			descriptor = bmount(argv[1]);
			if(descriptor<0){
				printf("Error while mounting FS for the %d child process, file simulacion.c\n",i);
				return -1;
			}
			strcat(childPathName,pathName);
			sprintf(processID,"proceso_%d/",getpid());
			strcat(childPathName,processID);
			//printf("%s\n",childPathName);
			if(mi_create(childPathName,7)<0){
				printf("Error in while calling mi_create for the %d child process path, file simulacion.c\n",i);
				return -1;
			}
			strcat(childPathName,"prueba.dat");
			if(mi_create(childPathName,7)<0){
				printf("Error in while calling mi_create for the %d child process file, file simulacion.c\n",i);
				return -1;
			}
			j=0;
			struct registro rgstr;
			//Now we write 50 times in the new file created
			while(j<50){
				rgstr.fecha = time(NULL);
				rgstr.pid = getpid();
				rgstr.nEscritura = j+1;
				srand(rgstr.fecha-rgstr.pid+(i+1)*j);
				rgstr.posicion = rand() % posMax;
				if(mi_write(childPathName,&rgstr,rgstr.posicion*sizeof(struct registro),sizeof(struct registro))<0){
					printf("Error while write number %d of the child number %d, file simulacion.c\n",j,i);
					return -1;
				}
				// We wait 0.05 seconds before the next write operation
				usleep(5000);
				j++;
			}
			memset(childPathName,0, sizeof(childPathName));
			memset(processID,0,sizeof(processID));
			return 0;
		}else{
			//We give time for the next child process to access
			usleep(200000);
			cid=fork();
			i++;
		}
	}
	//We wait for all the child process to finish
	while(acabados<100){
		printf("%d\n",acabados);
		pause();
	}
	//Un-mount the file system
	if(bumount(descriptor)<0){
		printf("Error while unmounting FS for the main process, file simulacion.c\n");
		return -1;
	}
	return 0;
}

void reaper(){ 
	while(wait3(NULL, WNOHANG, NULL) > 0) acabados++; 
}