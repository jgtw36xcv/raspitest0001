#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "netTcpCon.h"

#define _INITIALISED_ 1
#define _SERVERMODE_ 2
#define _NOCONECT_ 4

volatile int Server, Client, Flag=0;
struct sockaddr_in serverSockAddr, clientSockAddr;

void InitNetConClient(char *ipaddress, short port)
{	Flag=1;
	
}

void InitNetConServer(short port)
{	Flag=3;
	unsigned int sockAddrLen;
	sockAddrLen = sizeof(clientSockAddr);

	Server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(Server < 0)
	{	perror("socket() failed.");
		exit(1);
	}

	memset(&serverSockAddr, 0, sizeof(serverSocAddr));
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverSockAddr.sin_port = htons(port);

	if(bind(Server, (struct sockaddr *) &serverSockAddr, sizeof(serverSockAddr)) < 0)
	{	perror("bind() failed.");
		programExit(1);
	}

	if(listen(serverSock, 3) < 0)
	{	perror("listen() failed.");
		programExit(1);
	}
}

int nConSend(int type, char *data, int length)
{	
	
}

int nConRecv(char *data, int length)
{	if(!Flag&(1<<2))
	{	if(Flag&(1<<1))
		{	
			
		}
		else
		{	
			
		}
	}
	if(Flag&(1<<1))
	{	
		
		
	}
	else
	{	
		
	}
}
