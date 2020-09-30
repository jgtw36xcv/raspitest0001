CC := gcc
CFLAGS := -g -Wall -Wextra

main: main.o
	$(CC) main.o -pthread -lpigpio -lrt -o main

main.o: main.c
	$(CC) -c main.c

clean:
	$(RM) main main.o
