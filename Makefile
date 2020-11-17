CC := gcc
CFLAGS := -g -Wall -Wextra
LOADLIBES := -pthread -lpigpio -lrt

main: main.o newMotorDriver.o
	$(CC) $(CFLAGS) $(LOADLIBES) -o $@ main.o newMotorDriver.o

.PHONY: mekanamu
mekanamu:: clean
	make "CFLAGS=$(CFLAGS) -D__MEKANAMU"

.PHONY: clean
clean:
	$(RM) main main.o
