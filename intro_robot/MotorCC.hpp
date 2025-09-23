#ifndef __MOTOR_CC_H__
#define __MOTOR_CC_H__

#include "Arduino.h"

#define PWM_MAX 255

class MotorCC
{
private:
	int pinSentidoA;
	int pinSentidoB;
	bool iniciado = false;
public:
	MotorCC(int pinSentidoA, int pinSentidoB);
	void iniciar();
	void girarSentidoA(int velocidad);
	void girarSentidoB(int velocidad);
};

#endif //__MOTOR_CC_H__
