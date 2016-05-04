SOURCES=bloques.c ficheros_basicos.c my_mkfs.c leer_SF.c ficheros.c escribir.c leer.c stat_chmod.c directorios.c test_trunk.c mi_mkdir.c
LIBRARIES=bloques.o ficheros_basicos.o ficheros.o directorios.o
INCLUDES=bloques.h ficheros_basicos.h ficheros.h directorios.h
PROGRAMS=my_mkfs leer_SF escribir leer stat_chmod test_trunk mi_mkdir
OBJS=$(SOURCES:.c=.o)

all: $(OBJS) $(PROGRAMS)

#$(PROGRAMS): $(LIBRARIES) $(INCLUDES)
#	$(CC) $(LDFLAGS) $(LIBRARIES) $@.o -o $@

my_mkfs: my_mkfs.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@
	
leer_SF: leer_SF.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@	
	
escribir: escribir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@
	
leer: 	leer.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

stat_chmod: stat_chmod.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

test_trunk: test_trunk.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

mi_mkdir: mi_mkdir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *~ $(PROGRAMS)
