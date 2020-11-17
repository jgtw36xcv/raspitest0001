#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "newMotorDriver.h"

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

int main(void)
{	char str[256];
	int nstate=0;
	int inum;
	int exstate = 0;

	_GPIO_INIT();

	MotorDriver blMD = IintMortorDriverOpin(4,  8, 12),
				brMD = InitMortorDriverOpin(5,  9, 13),
				flMD = InitMortotDriverOpin(6, 10, 14),
				frMD = InitMortotDriverOpin(7, 11, 15);

	_GPIO_SET_OUTPUT(17);

	_GPIO_SET_OUTPUT(18);
	_GPIO_SET_OUTPUT(19);
	_GPIO_SET_OUTPUT(20);

	_GPIO_SET_OUTPUT(23);
	_GPIO_SET_OUTPUT(24);
	_GPIO_SET_OUTPUT(25);
	_GPIO_SET_OUTPUT(26);

	gpioSetPWMfrequency(4,5);
	gpioSetPWMfrequency(5,5);
	gpioSetPWMfrequency(6,5);
	gpioSetPWMfrequency(7,5);

	while(1)
	{	MotorDriverStatus(blMD, MDstate[nstate][0]);
		MotorDriverStatus(brMD, MDstate[nstate][1]);
		MotorDriverStatus(flMD, MDstate[nstate][2]);
		MotorDriverStatus(frMD, MDstate[nstate][3]);

		scanf("%s",str);

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

		if(strcmp(str,"4:on")==0)//L1左旋回
		{	nstate=7;
		}

		if(strcmp(str,"5:on")==0)//R1右旋回
		{	nstate=6;
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
		{	break;
		}

		if(strcmp(str,"quit")==0)
		{	break;
		}

		if(strcmp(str,"shutdown")==0)
		{	exstate = 1;
			break;
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

	nstate = 0;

	MotorDriverStatus(blMD, MDstate[nstate][0]);
	MotorDriverStatus(brMD, MDstate[nstate][1]);
	MotorDriverStatus(flMD, MDstate[nstate][2]);
	MotorDriverStatus(frMD, MDstate[nstate][3]);

	_GPIO_TERMINATE();

	if(exstate == 1){
		system("bash ./sys_shutdown.sh");
	}

	return 0;
}
