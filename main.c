﻿#include <pigpio.h>
#include <stdio.h>
#include <string.h>

// BCM 4,5,6,7,8,9,10,11
// motr 
int gpiostate[7][8]=
{	{  0,  0,  0,  0,  0,  0,  0,  0},	//空転
	{200,  0,200,  0,255,  0,255,  0},	//正転
	{  0,255,  0,255,  0,200,  0,200},	//逆転
	{255,255,255,255,255,255,255,255},	//停止
	{200,  0,120,  0,120,  0,255,  0},	//右
	{120,  0,200,  0,255,  0,120,  0},	//左
	{  0,200,  0,200,200,  0,200,  0},	//伸び
};

int main(int argc,char *argv[])
{	char str[256];
	int nstate=0, i, tret;
	int inum,istate[8];

	if(gpioInitialise() == PI_INIT_FAILED)
	{	puts("pi init failed.");
		goto programend;
	}

	if((tret = gpioSetMode(4, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(5, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(6, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(7, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(8, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(9, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(10, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(11, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(17, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(18, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(23, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(24, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(25, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

	if((tret = gpioSetMode(26, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO" : "pi bad MODE");
		goto programend;
	}

//	if((tret = gpioSetPWMfrequency(usepin, 250)) != 250)
//	{	printf("%s%d\n", tret == PI_BAD_USER_GPIO ? "error user gpio " : "pwm pals Hz ", tret);
//		goto programend;
//	}

	while(1)
	{	for(i=0;i<8;i++)
		{	if((tret = gpioPWM(4+i, gpiostate[nstate][i])) != 0)
			{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
				break;
			}
		}

		scanf("%s",str);
/*
		if(strcmp(str,"s")==0)
		{	nstate=0;
		}

		if(strcmp(str,"f")==0)
		{	nstate=1;
		}

		if(strcmp(str,"b")==0)
		{	nstate=2;
		}

		if(strcmp(str,"r")==0)
		{	nstate=4;
		}

		if(strcmp(str,"l")==0)
		{	nstate=5;
		}
*/

		if(argc==2)
		{
			if(strcmp(str,"6:")==0)		//左右
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=4;
				}
			}

			if(strcmp(str,"6:-32767")==0)
			{	nstate=5;
			}

			if(strcmp(str,"7:")==0)
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=2;
				}
			}

			if(strcmp(str,"7:-32767")==0)
			{	nstate=1;
			}

			if(strcmp(str,"3:on")==0)
			{	static int ledstate = 0;
				ledstate++;
				gpioWrite(23,(ledstate>>0)&1);
				gpioWrite(24,(ledstate>>1)&1);
				gpioWrite(25,(ledstate>>2)&1);
				gpioWrite(26,(ledstate>>3)&1);
			}

			if(strcmp(str,"3:off")==0)
			{
			}

			if(strcmp(str,"2:on")==0)
			{	gpioWrite(18,1);
			}

			if(strcmp(str,"2:off")==0)
			{	gpioWrite(18,0);
			}

			if(strcmp(str,"1:on")==0)
			{	nstate=0;
			}

			if(strcmp(str,"1:off")==0)
			{	
			}

			if(strcmp(str,"0:on")==0)
			{	gpioWrite(17,1);
			}

			if(strcmp(str,"0:off")==0)
			{	gpioWrite(17,0);
			}

		}

		if(strcmp(str,"e")==0)
		{	nstate=0;
		}

		if(strcmp(str,"w")==0)
		{	nstate=1;
		}

		if(strcmp(str,"s")==0)
		{	nstate=2;
		}

		if(strcmp(str,"d")==0)
		{	nstate=4;
		}

		if(strcmp(str,"a")==0)
		{	nstate=5;
		}

		if(strcmp(str,"ex")==0)
		{	nstate=6;
		}

		if(strcmp(str,"exit")==0)
		{	break;
		}

		if(strcmp(str,"quit")==0)
		{	break;
		}

		if(strcmp(str,"funmu")==0)
		{	scanf("%d",&inum);
			gpioWrite(17,1);
			gpioDelay(inum*1000*1000);
			gpioWrite(17,0);
		}

/*
		if((tret = gpioPWM(usepin, 6)) != 0)
		{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
			break;
		}

		gpioDelay(500000);

		if((tret = gpioPWM(usepin, 10)) != 0)
		{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
			break;
		}

		gpioDelay(500000);

		if((tret = gpioPWM(usepin, 14)) != 0)
		{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
			break;
		}

		gpioDelay(500000);
*/
	}

	nstate = 0;

	for(i=0;i<8;i++)
	{	if((tret = gpioPWM(4+i, gpiostate[nstate][i])) != 0)
		{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
			break;
		}
	}

programend:
	gpioTerminate();
	return 0;
}
