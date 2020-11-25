#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include "main.h"
#include "newMotorDriver.h"

void programExit(int m);

// motr
int MDstate[12][4]=
{	{Mo_idle	,Mo_idle	,Mo_idle	,Mo_idle	},	//空転
	{Mo_forward	,Mo_forward	,Mo_forward	,Mo_forward	},	//正転
	{Mo_backward,Mo_backward,Mo_backward,Mo_backward},	//逆転
	{Mo_brake	,Mo_brake	,Mo_brake	,Mo_brake	},	//停止
	{Mo_forward	,Mo_backward,Mo_forward	,Mo_backward},	//右怪転
	{Mo_backward,Mo_forward	,Mo_backward,Mo_forward	},	//左怪転
	{Mo_backward,Mo_forward	,Mo_forward	,Mo_backward},	//右進
	{Mo_forward	,Mo_backward,Mo_backward,Mo_forward	},	//左進
	{Mo_brake	,Mo_forward	,Mo_forward	,Mo_brake	},	//右前進
	{Mo_forward	,Mo_brake	,Mo_brake	,Mo_forward	},	//左前進
	{Mo_backward,Mo_brake	,Mo_brake	,Mo_backward},	//右後ろ進
	{Mo_brake	,Mo_backward,Mo_backward,Mo_brake	},	//左後ろ進
};

volatile int serverSock, clientSock;

void signal_handler(int sig)
{	programExit(EXIT_SUCCESS);
}

void programExit(int m)
{	int ret = 0;
	gpioTerminate();
	close(serverSock);
	close(clientSock);

	if((m&EXIT_ERROR) != 0)
		ret = -1;

	if((m&EXIT_SHUTDOWN) != 0)
		system("bash ./sys_shutdown.sh");

	exit(ret);
}

void shutdwnTimerFunc(void)
{	static int i = 0;
	if(gpioRead(24) == 1)
		i++;
	else
	{	i--;
		if(i<0)
			i=0;
	}
	if(i > 30)
		programExit(EXIT_SHUTDOWN);
}

int main()
{	char str[256];
	int nstate=0, inum, size, tret, axes0, axes1, axes3;
	struct sockaddr_in serverSockAddr, clientSockAddr;
	unsigned short serverPort = 12479;
	unsigned int sockAddrLen;

	sockAddrLen = sizeof(clientSockAddr);

	signal(SIGINT, signal_handler);
	signal(SIGSTOP, SIG_DFL);

	if((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{	perror("socket() failed.");
		programExit(EXIT_ERROR);
	}

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverSockAddr.sin_port = htons(serverPort);

	if(bind(serverSock, (struct sockaddr *) &serverSockAddr, sizeof(serverSockAddr)) < 0)
	{	perror("bind() failed.");
		programExit(EXIT_ERROR);
	}

	if(listen(serverSock, 3) < 0)
	{	perror("listen() failed.");
		programExit(EXIT_ERROR);
	}

	if(gpioInitialise() == PI_INIT_FAILED)
	{	puts("pi init failed.");
		programExit(EXIT_ERROR);
	}

	MotorDriver blMD = InitMotorDriverOpin(4,  8, 12),
				brMD = InitMotorDriverOpin(5,  9, 13),
				flMD = InitMotorDriverOpin(6, 10, 14),
				frMD = InitMotorDriverOpin(7, 11, 15);

#define _GPIO_SET_OUTPUT(port) \
	if((tret = gpioSetMode(port, PI_OUTPUT)) != 0) \
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO port" : "pi bad MODE port"); \
		programExit(EXIT_ERROR); \
	}

	_GPIO_SET_OUTPUT(17);

	_GPIO_SET_OUTPUT(18);
	_GPIO_SET_OUTPUT(19);
	_GPIO_SET_OUTPUT(20);

	_GPIO_SET_OUTPUT(23);
	_GPIO_SET_OUTPUT(24);
	_GPIO_SET_OUTPUT(25);
	_GPIO_SET_OUTPUT(26);

	gpioSetMode(24, PI_INPUT);
	gpioSetPullUpDown(24, PI_PUD_DOWN);
	gpioSetTimerFunc(0, 100, shutdwnTimerFunc);

	gpioSetPWMfrequency(4,5);
	gpioSetPWMfrequency(5,5);
	gpioSetPWMfrequency(6,5);
	gpioSetPWMfrequency(7,5);

	while(1)
	{	if((clientSock = accept(serverSock, (struct sockaddr *) &clientSockAddr, &sockAddrLen)) < 0)
		{	perror("accept() failed.");
			programExit(EXIT_ERROR);
		}

		while(1)
		{	SetMotorDriverStatus(blMD, MDstate[nstate][0]);
			SetMotorDriverStatus(brMD, MDstate[nstate][1]);
			SetMotorDriverStatus(flMD, MDstate[nstate][2]);
			SetMotorDriverStatus(frMD, MDstate[nstate][3]);

			if((size = recv(clientSock, str, sizeof(str), 0)) == -1)
			{	perror("recv() failed.");
				close(clientSock);
				break;
			}else if(size==0)
			{	fprintf(stderr, "connection closed by remote host.\n");
				close(clientSock);
				break;
			}

			puts(str);

			if(str[0]=='0'&&str[1]==':'&& str[2]!='o')
				sscanf(str+2,"%d",&axes0);

//			printf("axes0 = %d\n",axes0);

			if(str[0]=='1'&&str[1]==':'&& str[2]!='o')
				sscanf(str+2,"%d",&axes1);

//			printf("axes1 = %d\n",axes1);

			if(str[0]=='3'&&str[1]==':'&& str[2]!='o')
				sscanf(str+2,"%d",&axes3);

//			printf("axes3 = %d\n",axes3);

#define FLAG_L (axes0 < -5000)
#define FLAG_R (axes0 > 5000)
#define FLAG_U (axes1 < -5000)
#define FLAG_D (axes1 > 5000)

			if(FLAG_L&&!(FLAG_U||FLAG_D))
			{	nstate=7;
			}
			if(FLAG_R&&!(FLAG_U||FLAG_D))
			{	nstate=6;
			}
			if(FLAG_U&&!(FLAG_L||FLAG_R))
			{	nstate=1;
			}
			if(FLAG_D&&!(FLAG_L||FLAG_R))
			{	nstate=2;
			}
			if(FLAG_L&&FLAG_U)
			{	if(abs(axes0-axes1)<(abs(axes0+axes1)/4))
				{	nstate=9;
				}
				else if((axes0-axes1)<0)
				{	nstate=7;
				}
				else
				{	nstate=1;
				}
			}
			if(FLAG_L&&FLAG_D)
			{	if(abs(axes0+axes1)<(abs(axes0-axes1)/4))
				{	nstate=11;
				}
				else if((axes0+axes1)<0)
				{	nstate=7;
				}
				else
				{	nstate=2;
				}
			}
			if(FLAG_R&&FLAG_U)
			{	if(abs(axes0+axes1)<(abs(axes0-axes1)/4))
				{	nstate=8;
				}
				else if((axes0+axes1)<0)
				{	nstate=1;
				}
				else
				{	nstate=6;
				}
			}
			if(FLAG_R&&FLAG_D)
			{	if(abs(axes0-axes1)<(abs(axes0+axes1)/4))
				{	nstate=10;
				}
				else if((axes0-axes1)<0)
				{	nstate=2;
				}
				else
				{	nstate=6;
				}
			}

			if(!(FLAG_L||FLAG_R||FLAG_U||FLAG_D))
			{	if(axes3 < -5000)
					nstate=5;
				else if(axes3 > 5000)
					nstate=4;
				else
					nstate=0;
			}

			if(strcmp(str, "6:-32767")==0)
				nstate=5;
			else if(strcmp(str, "6:0")==0)
				nstate=0;
			else if(strcmp(str, "6:32767")==0)
				nstate=4;

			if(strcmp(str, "7:-32767")==0)
				gpioWrite(19,1);
			else if(strcmp(str, "7:0")==0)
			{	gpioWrite(19,0);
				gpioWrite(20,0);
			}
			else if(strcmp(str, "7:32767")==0)
				gpioWrite(20,1);

			if(strcmp(str,"3:on")==0)
			{	static int ledstate = 0;
				ledstate++;
				gpioWrite(23,ledstate&1);
			}

			if(strcmp(str,"2:on")==0)
			{	static int temp = 0;
				temp++;
				gpioWrite(18,temp&1);
			}

			if(strcmp(str,"1:on")==0)
			{	axes0 = 0;
				axes1 = 0;
				nstate=0;
			}

			if(strcmp(str,"0:on")==0)
			{	gpioWrite(17,1);
			}

			if(strcmp(str,"0:off")==0)
			{	gpioWrite(17,0);
			}

			if(strcmp(str,"s")==0)
			{	nstate=0;
			}

			if(strcmp(str,"w")==0)
			{	nstate=1;
			}

			if(strcmp(str,"x")==0)
			{	nstate=2;
			}

			if(strcmp(str,"1")==0)
			{	nstate=3;
			}

			if(strcmp(str,"r")==0)
			{	nstate=4;
			}

			if(strcmp(str,"f")==0)
			{	nstate=5;
			}

			if(strcmp(str,"d")==0)
			{	nstate=6;
			}

			if(strcmp(str,"a")==0)
			{	nstate=7;
			}

			if(strcmp(str,"e")==0)
			{	nstate=8;
			}

			if(strcmp(str,"q")==0)
			{	nstate=9;
			}

			if(strcmp(str,"c")==0)
			{	nstate=10;
			}

			if(strcmp(str,"z")==0)
			{	nstate=11;
			}

			if(strcmp(str,"exit")==0)
			{	programExit(EXIT_SUCCESS);
			}

			if(strcmp(str,"quit")==0)
			{	programExit(EXIT_SUCCESS);
			}

			if(strcmp(str,"shutdown")==0)
			{	programExit(EXIT_SHUTDOWN);
			}

			if(strcmp(str,"funmu")==0)
			{	scanf("%d",&inum);
				if(inum==0)
					scanf("%s",str);
				if(strcmp(str,"ex")==0)
				{	gpioWrite(17,1);
					scanf("%d",&inum);
					gpioWrite(17,0);
					continue;
				}
				gpioWrite(17,1);
				gpioDelay(inum*1000*1000);
				gpioWrite(17,0);
			}
		}
	}

	nstate = 0;

	SetMotorDriverStatus(blMD, MDstate[nstate][0]);
	SetMotorDriverStatus(brMD, MDstate[nstate][1]);
	SetMotorDriverStatus(flMD, MDstate[nstate][2]);
	SetMotorDriverStatus(frMD, MDstate[nstate][3]);

	programExit(EXIT_SUCCESS);
}
