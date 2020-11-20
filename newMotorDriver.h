#ifndef __NEW_MOTOR_DRIVER
#define __NEW_MOTOR_DRIVER

#define Mo_forward	0x100ff
#define Mo_backward	0x200ff
#define Mo_brake	0x300ff
#define Mo_idle		0x00000

typedef struct MotorDriver_s {
	int f, b, p;
} MotorDriver;

MotorDriver InitMotorDriverOpin(int power, int forword, int back);

void SetMotorDriverMode(MotorDriver th, int mode);

void SetMotorDriverPower(MotorDriver th, int power);

void SetMotorDriverStatus(MotorDriver th, int status);

#endif
