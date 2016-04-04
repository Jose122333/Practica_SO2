#include "ficheros.h"
#include "ficheros_basicos.h"

int main(int argc, char **argv){
	struct superbloque SB;
	struct inodo in;
	int descriptor,i, bytesEscribir, o;
	unsigned int offset,ninodo,bytesWritten, bytesLeidos, bytesEscritos;
	char perm[3];
	unsigned char input[10000];
	//if(argc<3) exit(1);
	descriptor = bmount(argv[1]);
	if(bread(posSB,&SB)<0) {
		printf("Ha ocurrido algun error");
		return -1;
	}
	//offset = argv[1];
	bytesEscritos = 0;
	ninodo=reservar_inodo('f',6);
	printf("#El inodo creado es: %d\n",ninodo);
    offset = 71680000;
	printf("#El offset es %d\n",offset);
    strcpy(input, "nis dis parturient montesnascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculunascetur ridiculu, nascetur ridiculus ma consequat massa quis enim. Donec pede justo,fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquamlorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Eti am rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis HOLA");
    bytesEscribir=strlen(input);
    printf("Input tiene bytes:%d\n",bytesEscribir );
    bytesWritten = mi_write_f(ninodo,input,offset,bytesEscribir);
    if(bytesWritten<0){
    	printf("Error al escribir en el fichero");
    }
    //printf("El numero bytes escritos es: %d\n", bytesWritten);
	printf("El contenido del fichero es: \n");
    while((bytesLeidos=mi_read_f(ninodo,input+bytesEscritos,offset,BLOCKSIZE))>0){
    	offset=offset+ bytesLeidos;
    	bytesEscritos = bytesLeidos + bytesEscritos;
    	   	printf("%s\n", input);
    	   		memset(input,0, sizeof(input));

    }

    //printf("El numero bytes leidos es: %d\n", bytesWritten);
    //printf("El contenido del fichero es: \n");
    //input[BLOCKSIZE]=0;
	//printf("%s", input);
	if(bumount(descriptor)<0) exit(1);
	return 0;
}
