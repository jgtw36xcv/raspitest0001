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
{	int Socket;
	char str[256];
	struct sockaddr_in serverSockAddr;
	unsigned short serverPort = 12479;

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &serverSockAddr.sin_addr);
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

		while(1)
		{	scanf("%s", pstr);
			if(send(Socket, pstr, (size_t) strlen(pstr)+1, 0) != strlen(pstr)+1)
			{	perror("send() failed.");
				break;
			}
			printf("\n%s\n",pstr);
			fflush(stdout);
		}
		close(Socket);
	}
	return 0;
}
