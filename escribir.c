#include "ficheros.h"
#include "ficheros_basicos.h"
#include <stdlib.h>
#include <stdio.h> 

int main(int argc, char **argv){
	int descriptor,bytesEscribir,sz;
	unsigned int offset,ninodo,bytesWritten, bytesEscritos, longitudFichero;
	FILE *fptr;
	//if(argc<3) exit(1);
	descriptor = bmount(argv[1]);
	bytesEscritos = 0;
	ninodo=reservar_inodo('f',6);
	//ninodo = 1;
	printf("#El inodo creado es: %d\n",ninodo);
    offset = atoi(argv[2]);
    if ((fptr=fopen(argv[3],"r"))==NULL){
       printf("Error! opening file");
       exit(1);         /* Program exits if file pointer returns NULL. */
   	}
   	fseek(fptr, 0L, SEEK_END);
	sz = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);
	unsigned char input[sz];
	fscanf(fptr,"%[^\n]",input);
	fclose(fptr);
	//printf("%s\n",input);
    //strcpy(input, "nis dis parturient montesnascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculu, nascetur ridiculus ma consequat massa quis enim. Donec pede justo,fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquamlorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Eti am rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis HOLA");
	//longitudFichero = strlen(input);
    bytesWritten=mi_write_f(ninodo,input,offset,sz);
    if(bytesWritten<0){
    	printf("Error al escribir en el fichero");
    }
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
