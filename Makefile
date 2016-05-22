CC = gcc
LDFLAGS = -g -pthread
POSIX = semaforo_mutex_posix.c

SOURCES=bloques.c ficheros_basicos.c mi_mkfs.c leer_sf.c ficheros.c escribir.c leer.c stat_chmod.c directorios.c test_trunk.c mi_mkdir.c mi_chmod.c mi_stat.c mi_ln.c mi_ls.c mi_escribir.c mi_cat.c mi_rm.c simulacion.c verificacion.c
LIBRARIES=bloques.o ficheros_basicos.o ficheros.o directorios.o
INCLUDES=bloques.h ficheros_basicos.h ficheros.h directorios.h
PROGRAMS=mi_mkfs leer_sf escribir leer stat_chmod test_trunk mi_mkdir mi_chmod mi_stat mi_ln mi_ls mi_escribir mi_cat mi_rm simulacion verificacion
OBJS=$(SOURCES:.c=.o)

all: $(OBJS) $(PROGRAMS)

#$(PROGRAMS): $(LIBRARIES) $(INCLUDES)
#	$(CC) $(LDFLAGS) $(LIBRARIES) $@.o -o $@

mi_mkfs: mi_mkfs.o $(LIBRARIES) $(INCLUDES) 
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@
	
leer_sf: leer_sf.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	
	
escribir: escribir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@
	
leer: leer.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

stat_chmod: stat_chmod.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

test_trunk: test_trunk.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

mi_mkdir: mi_mkdir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

mi_chmod: mi_chmod.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

mi_stat: mi_stat.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

mi_ln: mi_ln.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	

mi_ls: mi_ls.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	

mi_escribir: mi_escribir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	

mi_cat: mi_cat.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	
	
mi_rm: mi_rm.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@

simulacion: simulacion.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@	

verificacion: verificacion.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $(POSIX) $< -o $@				


%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *~ $(PROGRAMS)
