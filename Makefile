CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = main.o map.o pso.o utils.o logger.o

all: pso

pso: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o pso

main.o: main.c map.h pso.h logger.h utils.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

pso.o: pso.c pso.h map.h utils.h
	$(CC) $(CFLAGS) -c pso.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

logger.o: logger.c logger.h pso.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f *.o pso

