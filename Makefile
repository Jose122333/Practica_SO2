SOURCES=bloques.c ficheros_basicos.c my_mkfs.c
LIBRARIES=bloques.o ficheros_basicos.o
INCLUDES=bloques.h ficheros_basicos.h
PROGRAMS=my_mkfs
OBJS=$(SOURCES:.c=.o)

all: $(OBJS) $(PROGRAMS)

#$(PROGRAMS): $(LIBRARIES) $(INCLUDES)
#	$(CC) $(LDFLAGS) $(LIBRARIES) $@.o -o $@

my_mkfs: my_mkfs.o $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *~ $(PROGRAMS)
