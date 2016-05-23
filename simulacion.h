#include <time.h>
#include "bloques.h"
#include <string.h>
#include <signal.h>
#include "directorios.h"
#include <sys/wait.h>
#include <stdlib.h>

struct registro {
	int fecha;
	int pid;
	int nEscritura;
	int posicion;
};

void reaper();