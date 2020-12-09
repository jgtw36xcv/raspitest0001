CC := gcc
CFLAGS := -g -Wall -Wextra
LOADLIBES := -pthread -lpigpio -lrt

.PHONY: all
all: main testkey testjoystick
	

main: main.o newMotorDriver.o
	$(CC) $(CFLAGS) $(LOADLIBES) -o $@ main.o newMotorDriver.o

.PHONY: clean
clean:
	$(RM) main *.o testjoystick testkey

.PHONY: install
install: main
	if [ -f "installd" ]; then\
	  echo "Already installed";\
	else\
	  sudo cp plesio.service /etc/systemd/system/;\
	  sudo systemctl daemon-reload;\
	  touch "installd";\
	fi

.PHONY: uninstall
uninstall:
	if [ -f "/etc/systemd/system/plesio.service" ]; then\
	  sudo rm /etc/systemd/system/plesio.service;\
	  sudo systemctl daemon-reload;\
	  rm "installd";\
	else\
	  echo "Not installed";\
	fi;

.PHONY: start
start:
	if [ -f "installd" ]; then sudo systemctl start plesio; else echo "Not installd"; fi;

.PHONY: stop
stop:
	if [ -f "installd" ]; then sudo systemctl stop plesio; else echo "Not installd"; fi;

.PHONY: autostart
autostart:
	if [ -f "installd" ]; then sudo systemctl enable plesio; else echo "Not installd"; fi;

.PHONY: autostop
autostop:
	if [ -f "installd" ]; then sudo systemctl disable plesio; else echo "Not installd"; fi;
