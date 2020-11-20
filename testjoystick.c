#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define JOY_DEV "/dev/input/js0"

int main(void)
{	int fd, Socket, fl = 1;
	char str[256];
	struct js_event js;
	struct sockaddr_in serverSockAddr;
	unsigned short serverPort = 12479;
//	unsigned int sockAddrLen;

//	sockAddrLen = sizeof(serverSockAddr);

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &serverSockAddr.sin_addr);
	serverSockAddr.sin_port = htons(serverPort);

	if((Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{	perror("socket() failed.");
		close(Socket);
		free(serverSockAddr);
		exit(-1);
	}


	while(1)
	{	
		if(connect(Socket, (struct sockaddr*) &serverSockAddr, sizeof(serverSockAddr)) < 0)
		{	close(Socket);
			continue;
		}

		fl = 1;
		while(fl)
		{	if((fd=open(JOY_DEV, O_RDONLY)) == -1)
			{	printf( "Couldn't open joystick device %s\n", JOY_DEV);
				return -1;
			}

			ioctl(fd, JSIOCGAXES, &num_of_axis);
			ioctl(fd, JSIOCGBUTTONS, &num_of_buttons);
			ioctl(fd, JSIOCGNAME(80), &temstr);

			while(1)
			{	if(read(fd, &js, sizeof(struct js_event)) < 0)
				{	break;
				}
				switch(js.type&~JS_EVENT_INIT)
				{	case JS_EVENT_AXIS:
						sprintf(str, "%d:%6d ", js.number, js.value);
						break;
					case JS_EVENT_BUTTON:
						sprintf(str, "%d:%s ", js.number, js.value == 1 ? "on " : "off");
						break;
					default:
						continue;
				}

				x = strlen(str)+1;
				if(send(Socket, str, (size_t) x, 0) != x)
				{	perror("send() failed.");
					fl = 0;
					break;
				}
			}
			close(fd);
		}
		close(Socket);
	}
	return 0;
}
