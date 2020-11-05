#ifndef __NEW_MOTOR_DRIVER
#define __NEW_MOTOR_DRIVER

typedef struct MotorDriver {
	int f, b, p;
};

MotorDriver InitMotorDriverOpin(int forword, int back, int power);

int SetMotorDriverMode(int mode);

int SetMotorDriverPower(int power);

#endif