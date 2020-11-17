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
{	gpioWrite(th.f,mode&1);
	gpioWrite(th.b,(mode>>1)&1);
}

void SetMotorDriverPower(MotorDriver th, int power)
{	int tret;
	if((tret = gpioPWM(th.p, gpioGetPWMrange(th.p)-power-1)) != 0)
	{	puts(tret == PI_BAD_USER_GPIO ? "pi bad user gpio" : "pi bad dutycycle");
	}
}

void SetMotorDriverStatus(MotorDriver th, int status)
{	SetMotorDriverMode(th, status>>16);
	SetMotorDriverPower(th, status&0xffff);
}
