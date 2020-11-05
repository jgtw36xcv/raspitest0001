CC := gcc
CFLAGS := -g -Wall -Wextra
LOADLIBES := -pthread -lpigpio -lrt

main: main.o
	$(CC) $(CFLAGS) $(LOADLIBES) main.o -o main

mekanamu:: clean
	CFLAGS += -D__MEKANAMU
mekanamu:: main;

clean:
	$(RM) main main.o
