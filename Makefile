CC := gcc
CFLAGS := -g -Wall -Wextra

main: main.o
	$(CC) main.o -pthread -lpigpio -lrt -o main

mekanamu:
	make clean
	make hoge "CFLAGS=-g -Wall -Wextra -D__MEKANAMU"

main.o: main.c
	$(CC) -c main.c

clean:
	$(RM) main main.o
