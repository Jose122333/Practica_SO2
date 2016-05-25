#include <time.h>
#include "bloques.h"
#include <string.h>
#include <signal.h>
#include "directorios.h"
#include <sys/wait.h>
#include <stdlib.h>

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

struct registro {
	int fecha;
	int pid;
	int nEscritura;
	int posicion;
};

void reaper();