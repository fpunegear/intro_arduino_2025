/**
 * @file MotorCC.cpp
 * @brief Implementación de la clase MotorCC para control de motores DC
 * @author Gear
 * @date 2025
 */

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
	
	// Limita la velocidad al rango válido
	velocidad = constrain(velocidad, -PWM_MAX, PWM_MAX);

	if(velocidad < 0)
	{
		// Giro en sentido inverso: activa pinSentidoB
		analogWrite(this->pinSentidoA, 0);
		analogWrite(this->pinSentidoB, -velocidad);
	}
	else
	{
		// Giro en sentido A: activa pinSentidoA
		analogWrite(this->pinSentidoA, velocidad);
		analogWrite(this->pinSentidoB, 0);
	}
}

void MotorCC::girarSentidoB(int velocidad)
{
	if(!this->iniciado) return;
	
	// Limita la velocidad al rango válido
	velocidad = constrain(velocidad, -PWM_MAX, PWM_MAX);

	if(velocidad < 0)
	{
		// Giro en sentido inverso: activa pinSentidoA
		analogWrite(this->pinSentidoA, -velocidad);
		analogWrite(this->pinSentidoB, 0);
	}
	else
	{
		// Giro en sentido B: activa pinSentidoB
		analogWrite(this->pinSentidoA, 0);
		analogWrite(this->pinSentidoB, velocidad);
	}
}

