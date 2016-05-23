#include "bloques.h"
#include <stdio.h>
#include "simulacion.h"

int main(int argc, char **argv){
	int descriptor,nEntradas,i=0,j,k;
	struct STAT fileStatus;
	char pathName[200],buf[22], informe[200], informeGlobal[50000];
	char childPathName[200];
	char *proceesID;
	int pid,offset,registros_correctos;
	struct registro info[4];//first,last,first pos,last pos
	struct registro leer;
	//char leer[BLOCKSIZE];//We will use this array to save
	const char ch = '_';
	struct entrada entr;
	int bytesRead;
	struct tm ts;
	time_t now;
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
	/*if(nEntradas != 100){
		printf("Error, the number of entrances is not exactly 100\n");
		printf("Entrances found %d\n",nEntradas);
		return -1;
	}*/
	//Now we create a new file in the simulation directory
	memset(pathName,0,sizeof(pathName));
	strcat(pathName,argv[2]);
	//printf("%s\n",pathName);
	strcat(pathName,"informe.txt");
	//printf("%s\n",pathName);
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
		//Now we read all the registers written in the file prueba.dat	
		memset(childPathName,0,sizeof(childPathName));
		strcat(childPathName,argv[2]);
		strcat(childPathName,entr.nombre);
		strcat(childPathName,"/");
		strcat(childPathName,"prueba.dat");
		//We initialize all the information fields
		info[0]=(struct registro){INT_MAX,INT_MAX,INT_MAX,INT_MAX};
		info[1]=(struct registro){0,0,0,0};
		info[2]=(struct registro){0,0,0,0};
		info[3]=(struct registro){0,0,0,0};
		//Now we have start runnig through all the files
		offset = 0;
		registros_correctos = 0;
		bytesRead = mi_read(childPathName,&leer,offset,sizeof(struct registro));
		int cont = 0;
		while(bytesRead > 0 || bytesRead == -2){
			if(bytesRead == -2){
				//printf("Rocio Aprueba\n");
				bytesRead = BLOCKSIZE;
			}else{
				//for(k = 0; k < BLOCKSIZE;k++){
					//memcpy(&comparar,leer+k,sizeof(comparar));
					if(leer.pid==pid){
						if(leer.nEscritura<info[0].nEscritura){
							//Check if it is the first register
							if(leer.fecha<=info[0].fecha){
								info[0]=leer;
							}
						}						
						if(info[1].nEscritura<leer.nEscritura){
							//Check if it is the last register
							if(info[1].fecha<=leer.fecha){
								info[1]=leer;
							}
						}
						//Check is it is the first position	
						if(info[2].pid==0){
							info[2]=leer;
						}
						//Check if it is the last position
						if(leer.posicion>info[3].posicion){
							info[3]=leer;
						}
						registros_correctos++;
					}
				}
			//}
			offset+=bytesRead;
			//memset(&leer,0,BLOCKSIZE);
			bytesRead = mi_read(childPathName,&leer,offset,sizeof(struct registro));
		}
		//memset(informeGlobal,0,sizeof(informeGlobal));
		//General process info
		sprintf(informe,"\nPID: %d \nCORRECTOS: %d \n",pid,registros_correctos);
		strcat(informeGlobal,informe);
		//First register info
		memset(buf,0,22);
		now=(time_t) info[0].fecha;
		ts = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
		sprintf(informe,"<Primer registro:\tNum Escritura: %d | Fecha: %s | Posicion: %d \n",info[0].nEscritura,buf,info[0].posicion);
		strcat(informeGlobal,informe);
		//Last register info
		memset(buf,0,22);
		now=(time_t) info[1].fecha;
		ts = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
		sprintf(informe,"<Ultimo registro:\tNum Escritura: %d | Fecha: %s | Posicion: %d \n",info[1].nEscritura,buf,info[1].posicion);
		strcat(informeGlobal,informe);
		//First position register		
		memset(buf,0,22);
		now=(time_t) info[2].fecha;
		ts = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
		sprintf(informe,"<Primera posicion:\tNum Escritura: %d | Fecha: %s | Posicion: %d \n",info[2].nEscritura,buf,info[2].posicion);
		strcat(informeGlobal,informe);
		//Last postion register		
		memset(buf,0,22);
		now=(time_t) info[3].fecha;
		ts = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
		sprintf(informe,"<Ultima posicion:\tNum Escritura: %d | Fecha: %s | Posicion: %d \n",info[3].nEscritura,buf,info[3].posicion);
		strcat(informeGlobal,informe);		
	}
	//Now we write all the process info in the file informe.txt		
	if(mi_write(pathName,informeGlobal,0,strlen(informeGlobal))<0){
		printf("Error while writing the results into the informe.txt, file verificacion.c\n");
		return -1;
	}
	write(1,informeGlobal,strlen(informeGlobal));
	//Un-mount the file system
	if(bumount(descriptor)<0){
		printf("Error while unmounting FS for the main process\n");
		return -1;
	}
	return 0;
}
