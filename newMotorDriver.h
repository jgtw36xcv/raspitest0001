#ifndef __NEW_MOTOR_DRIVER
#define __NEW_MOTOR_DRIVER

typedef struct MotorDriver_s {
	int f, b, p;
} MotorDriver;

MotorDriver InitMotorDriverOpin(int forword, int back, int power);

int SetMotorDriverMode(MotorDriver th, int mode);

int SetMotorDriverPower(MotorDriver th, int power);

#endif