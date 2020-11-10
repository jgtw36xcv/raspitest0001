#include <pigpio.h>
#include <stdio.h>
#include "newMotorDriver.h"


MotorDriver InitMotorDriverOpin(int forword, int back, int power)
{	MotorDriver ret;
	int tret;
	if((tret = gpioSetMode(forword, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO port" : "pi bad MODE port");
		return null;
	}
	if((tret = gpioSetMode(back, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO port" : "pi bad MODE port");
		return null;
	}
	if((tret = gpioSetMode(power, PI_OUTPUT)) != 0)
	{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO port" : "pi bad MODE port");
		return null;
	}
	ret.f=forword;
	ret.b=back;
	ret.p=power;
	return ret;
}

void SetMotorDriverMode(MotorDriver th, int mode)
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

void SetMotorDriverPower(MotorDriver th, int power)
{	int tret;
	if((tret = gpioPWM(th.p, power)) != 0)
	{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
	}
}

