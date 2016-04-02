SOURCES=bloques.c ficheros_basicos.c my_mkfs.c leer_SF.c ficheros.c escribir.c
LIBRARIES=bloques.o ficheros_basicos.o ficheros.o
INCLUDES=bloques.h ficheros_basicos.h ficheros.h
PROGRAMS=my_mkfs leer_SF escribir
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

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *~ $(PROGRAMS)
