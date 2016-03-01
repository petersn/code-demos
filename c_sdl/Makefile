
CFLAGS=-g -Wall `sdl-config --cflags` -O3 -ffast-math -std=c99

all: main

main: main.o Makefile
	$(CC) -o $@ $< `sdl-config --libs`

clean:
	rm -f main main.o

.PHONY: all clean

