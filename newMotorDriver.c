#include <pigpio.h>
#include "newMotorDriver.h"


MotorDriver InitMotorDriverOpin(int forword, int back, int power)
{	MotorDriver ret;
	ret.f=forword;
	ret.b=back;
	ret.p=power;
	return ret;
}

int SetMotorDriverMode(MotorDriver th, int mode)
{	if(mode == 1)
	{	gpioWrite(th.f,1);
		gpioWrite(th.b,0);
	}else if(mode == 2)
	{	gpioWrite(th.f,0);
		gpioWrite(th.b,1);
	}else
	{	gpioWrite(th.f,0);
		gpioWrite(th.b,0);
	}
}

int SetMotorDriverPower(MotorDriver th, int power)
{	if((tret = gpioPWM(th.p, power)) != 0)
	{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
		break;
	}
}

