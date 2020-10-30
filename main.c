#include <pigpio.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

// BCM 4,5,6,7,8,9,10,11
// motr
#ifndef __MEKANAMU
int gpiostate[7][8]=
//   bl1 bl2 br1 br2 fl1 fl2 fr1 fr2	多分。	by takahasi
{	{  0,  0,  0,  0,  0,  0,  0,  0},	//空転
	{200,  0,200,  0,255,  0,255,  0},	//正転
	{  0,255,  0,255,  0,200,  0,200},	//逆転
	{255,255,255,255,255,255,255,255},	//停止
	{200,  0, 50,  0, 50,  0,255,  0},	//右
	{ 50,  0,200,  0,255,  0, 50,  0},	//左
	{  0,200,  0,200,200,  0,200,  0},	//伸び
};
#endif
#ifdef __MEKANAMU
int gpiostate[12][8]=
{	{  0,  0,  0,  0,  0,  0,  0,  0},	//空転
	{200,  0,200,  0,255,  0,255,  0},	//正転
	{  0,255,  0,255,  0,200,  0,200},	//逆転
	{255,255,255,255,255,255,255,255},	//停止
	{255,  0,  0,255,255,  0,  0,255},	//右怪転
	{  0,255,255,  0,  0,255,255,  0},	//左怪転
	{  0,255,255,  0,255,  0,  0,255},	//右進
	{255,  0,  0,255,  0,255,255,  0},	//左進
	{255,255,255,  0,255,  0,255,255},	//右前進
	{255,  0,255,255,255,255,255,  0},	//左前進
	{  0,255,255,255,255,255,  0,255},	//右後ろ進
	{255,255,  0,255,  0,255,255,255},	//左後ろ進
};
#endif

int main(int argc,char *argv[])
{	char str[256];
	int nstate=0, i;
	int inum,istate[8];

	_GPIO_INIT();

	_GPIO_SET_OUTPUT(4);
	_GPIO_SET_OUTPUT(5);
	_GPIO_SET_OUTPUT(6);
	_GPIO_SET_OUTPUT(7);
	_GPIO_SET_OUTPUT(8);
	_GPIO_SET_OUTPUT(9);
	_GPIO_SET_OUTPUT(10);
	_GPIO_SET_OUTPUT(11);

	_GPIO_SET_OUTPUT(17);

	_GPIO_SET_OUTPUT(18);
	_GPIO_SET_OUTPUT(19);
	_GPIO_SET_OUTPUT(20);

	_GPIO_SET_OUTPUT(23);
	_GPIO_SET_OUTPUT(24);
	_GPIO_SET_OUTPUT(25);
	_GPIO_SET_OUTPUT(26);

//	if((tret = gpioSetPWMfrequency(usepin, 250)) != 250)
//	{	printf("%s%d\n", tret == PI_BAD_USER_GPIO ? "error user gpio " : "pwm pals Hz ", tret);
//		goto programend;
//	}

	gpioSetPWMfrequency(4,5);
	gpioSetPWMfrequency(5,5);
	gpioSetPWMfrequency(6,5);
	gpioSetPWMfrequency(7,5);
	gpioSetPWMfrequency(8,5);
	gpioSetPWMfrequency(9,5);
	gpioSetPWMfrequency(10,5);
	gpioSetPWMfrequency(11,5);

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

/*		if(argc==2)
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

			if(strcmp(str,"6:on")==0)
			{	gpioWrite(19,1);
			}

			if(strcmp(str,"6:off")==0)
			{	gpioWrite(19,0);
			}

			if(strcmp(str,"7:on")==0)
			{	gpioWrite(20,1);
			}

			if(strcmp(str,"7:off")==0)
			{	gpioWrite(20,0);
			}

		}
*/
/*		int gpiostate[12][8]=
		{	{  0,  0,  0,  0,  0,  0,  0,  0},	//0空転
			{200,  0,200,  0,255,  0,255,  0},	//1正転
			{  0,255,  0,255,  0,200,  0,200},	//2逆転
			{255,255,255,255,255,255,255,255},	//3停止
			{255,  0,  0,255,255,  0,  0,255},	//4右怪転
			{  0,255,255,  0,  0,255,255,  0},	//5左怪転
			{  0,255,255,  0,255,  0,  0,255},	//6右進
			{255,  0,  0,255,  0,255,255,  0},	//7左進
			{255,255,255,  0,255,  0,255,255},	//8右前進
			{255,  0,255,255,255,255,255,  0},	//9左前進
			{  0,255,255,255,255,255,  0,255},	//10右後ろ進
			{255,255,  0,255,  0,255,255,255},	//11左後ろ進
		};
*/
		if(argc==2)
		{
			//十字キー
			if(strcmp(str,"6:")==0)		//右進
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=6;
				}
			}

			if(strcmp(str,"6:-32767")==0)	//左進
			{	nstate=7;
			}

			if(strcmp(str,"7:")==0)		//逆転
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=2;
				}
			}

			if(strcmp(str,"7:-32767")==0)	//正転
			{	nstate=1;
			}

			//右スティック横軸
			if(strcmp(str,"3:")==0)		//右回転
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=4;
				}
			}

			if(strcmp(str,"3:-32767")==0)	//左回転
			{	nstate=5;
			}

			//左スティック縦軸
			if(strcmp(str,"1:")==0)		//逆転
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=2;
				}
			}

			if(strcmp(str,"1:-32767")==0)	//正転
			{	nstate=1;
			}

			//左スティック横軸
			if(strcmp(str,"0:")==0)		//右進
			{	scanf("%s",str);
				if(strcmp(str,"32767")==0)
				{	nstate=6;
				}
			}

			if(strcmp(str,"0:-32767")==0)	//左進
			{	nstate=7;
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

			if(strcmp(str,"6:on")==0)
			{	gpioWrite(19,1);
			}

			if(strcmp(str,"6:off")==0)
			{	gpioWrite(19,0);
			}

			if(strcmp(str,"7:on")==0)
			{	gpioWrite(20,1);
			}

			if(strcmp(str,"7:off")==0)
			{	gpioWrite(20,0);
			}

			if(strcmp(str,"4:on")==0)//L1左進
			{	nstate=7;
			}

			if(strcmp(str,"5:on")==0)//R1右進
			{	nstate=6;
			}

		}

#ifndef __MEKANAMU

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

#endif
#ifdef __MEKANAMU

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

#endif
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

	_GPIO_TERMINATE();
}
