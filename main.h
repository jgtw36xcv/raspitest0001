#ifndef __MAINH__
#define __MAINH__

#define _GPIO_INIT() \
int tret; \
if(gpioInitialise() == PI_INIT_FAILED) \
{	puts("pi init failed."); \
	goto programend; \
}

#define _GPIO_SET_OUTPUT(port) \
if((tret = gpioSetMode(port, PI_OUTPUT)) != 0) \
{	puts(tret == PI_BAD_GPIO ? "pi bad GPIO port" : "pi bad MODE port"); \
	goto programend; \
}

#define _GPIO_TERMINATE() \
programend: \
	gpioTerminate() \
	return 0; \

#endif
