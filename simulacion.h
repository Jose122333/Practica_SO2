#include <time.h>
#include "bloques.h"
#include <string.h>
#include <signal.h>
#include "directorios.h"
#include <sys/wait.h>

struct registro {
	time_t fecha;
	pid_t pid;
	int nEscritura;
	int posicion;
};