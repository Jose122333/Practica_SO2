SOURCES=bloques.c ficheros_basicos.c my_mkfs.c leer_SF.c ficheros.c escribir.c leer.c stat_chmod.c directorios.c test_trunk.c mi_mkdir.c mi_chmod.c mi_stat.c mi_ln.c mi_ls.c mi_escribir.c mi_cat.c
LIBRARIES=bloques.o ficheros_basicos.o ficheros.o directorios.o
INCLUDES=bloques.h ficheros_basicos.h ficheros.h directorios.h
PROGRAMS=my_mkfs leer_SF escribir leer stat_chmod test_trunk mi_mkdir mi_chmod mi_stat mi_ln mi_ls mi_escribir mi_cat

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

mi_chmod: mi_chmod.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

mi_stat: mi_stat.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

mi_ln: mi_ln.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@	

mi_ls: mi_ls.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@	

mi_escribir: mi_escribir.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@	

mi_cat: mi_cat.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@	

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *~ $(PROGRAMS)
