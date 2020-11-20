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
{	int fd, Socket, *axis=NULL, num_of_axis=0, num_of_buttons=0, x, fl = 1;
	char *button=NULL, temstr[80], pstr[256];
	struct js_event js;
	struct sockaddr_in serverSockAddr;
	unsigned short serverPort = 12479;
	unsigned int sockAddrLen;

	sockAddrLen = sizeof(serverSockAddr);

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	if(inet_aton("127.0.0.1", &serverSockAddr.sin_addr) == 0)
	{	perror("inet_aton() failed.");
		exit(-1);
	}
	serverSockAddr.sin_port = htons(serverPort);

	while(1)
	{	if((Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		{	perror("socket() failed.");
			close(Socket);
			continue;
		}

		if(connect(Socket, (struct sockaddr*) &serverSockAddr, sizeof(serverSockAddr)) < 0)
		{	perror("connect() failed.");
			close(Socket);
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

			axis = (int *)calloc(num_of_axis, sizeof(int));
			button = (char *)calloc(num_of_buttons, sizeof(char));

			while(1)
			{	scanf("%s", pstr);
				if(send(Socket, pstr, (size_t) strlen(pstr)+1, 0) != strlen(pstr)+1)
				{	perror("send() failed.");
					fl = 0;
					break;
				}
				printf("\n%s\n",pstr);
				fflush(stdout);
			}
			free(axis);
			free(button);
			close(fd);
		}
		close(Socket);
	}
	return 0;
}
