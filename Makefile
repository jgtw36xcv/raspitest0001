CC := gcc
CFLAGS := -g -Wall -Wextra
LOADLIBES := -pthread -lpigpio -lrt

main: main.o
	$(CC) $(CFLAGS) $(LOADLIBES) -o $@ main.o

.PHONY: mekanamu
mekanamu:: clean
	CFLAGS += -D__MEKANAMU
mekanamu:: main;

.PHONY: clean
clean:
	$(RM) main main.o
