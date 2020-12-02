#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "netUdpCon.h"

#define _INITIALISED_ (1<<0)
#define _SERVERMODE_ (1<<1)
#define _CONECT_ (1<<2)

int redcCon(void);
void socket_close(void);
void initNUC(void);

volatile int Server, Client, Flag=0;
unsigned int sockAddrLen;
struct sockaddr_in serverSockAddr, clientSockAddr;

void InitNetConClient(char *ipaddress, short port)
{	if(Flag & _INITIALISED_)
		return;
	Flag |= _INITIALISED_;
	
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	
	serverSockAddr.sin_family = AF_INET;
	inet_aton(ipaddress, &serverSockAddr.sin_addr);
	serverSockAddr.sin_port = htons(port);
}

void InitNetConServer(short port)
{	if(Flag & _INITIALISED_)
		return;
	Flag = _INITIALISED_ | _SERVERMODE_;
	sockAddrLen = sizeof(clientSockAddr);

	Server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
		exit(1);
	}

	if(listen(serverSock, 3) < 0)
	{	perror("listen() failed.");
		exit(1);
	}
}

void initNUC(viod)
{	
	
}

int nConSend(int type, char *data, int length)
{	int ret;
	if(!Flag&_CONECT_)
	{	redcCon();
	}
	ret = send(Client, data, (size_t)length, 0);
	if(ret != length)
	{	Flag &= !_CONECT_;
	}
	return ret;
}

int nConRecv(char *data, int length)
{	int size;
	if(!Flag&_CONECT_)
	{	redcCon();
	}
	size = recv(Client, data, length, 0))
	if(size == -1)
	{	Flag &= !_CONECT_;
	}
	return size;
}

int redcCon()
{	if(Flag&_SERVERMODE_)
	{	Client = accept(Server, (struct sockaddr *) &clientSockAddr, sockAddrLen);
		if(Client < 0)
		{	perror("accept() failed.");
			exit(1);
		}
		Flag |= _CONECT_;
	}
	else
	{	Client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(Client < 0)
		{	perror("socket() failed.");
			close(Client);
			return -1;
		}
		if(connect(Client, (struct sockaddr *) &serverSockAddr, sizeof(serverSockAddr)) < 0)
		{	perror("connect() failed.");
			close(Client);
			return -1;
		}
	}
}
