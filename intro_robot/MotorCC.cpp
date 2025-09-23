#include "MotorCC.hpp"

MotorCC::MotorCC(int pinSentidoA, int pinSentidoB)
{
	this->pinSentidoA = pinSentidoA;
	this->pinSentidoB = pinSentidoB;
}

void MotorCC::iniciar()
{
	if(!this->iniciado)
	{
		pinMode(this->pinSentidoA, OUTPUT);
		pinMode(this->pinSentidoB, OUTPUT);
		
		this->iniciado = true;
	}
}

void MotorCC::girarSentidoA(int velocidad)
{
	if(!this->iniciado) return;
	
	velocidad = constrain(velocidad, -PWM_MAX, PWM_MAX);
	
	if(velocidad < 0)
	{
		analogWrite(this->pinSentidoA, 0);
		analogWrite(this->pinSentidoB, -velocidad);
	}
	else
	{
		analogWrite(this->pinSentidoA, velocidad);
		analogWrite(this->pinSentidoB, 0);
	}
}

void MotorCC::girarSentidoB(int velocidad)
{
	if(!this->iniciado) return;
	
	velocidad = constrain(velocidad, -PWM_MAX, PWM_MAX);
	
	if(velocidad < 0)
	{
		analogWrite(this->pinSentidoA, -velocidad);
		analogWrite(this->pinSentidoB, 0);
	}
	else
	{
		analogWrite(this->pinSentidoA, 0);
		analogWrite(this->pinSentidoB, velocidad);
	}
}

