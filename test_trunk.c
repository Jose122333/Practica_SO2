#include "ficheros_basicos.h"
#include <stdlib.h>
#include <stdio.h>

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	unsigned int a, descriptor, b;
		descriptor = bmount(argv[1]);
		b = atoi(argv[2]);

	a = liberar_inodo(b);
	printf("El inodo liberado es: %d\n", a);
	if(bumount(descriptor)<0) exit(1);

}