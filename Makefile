CC=gcc
CFLAGS=-Wall -O2

all:
	$(CC) main.c map.c pso.c utils.c logger.c -o pso

