/**
 * @file MotorCC.cpp
 * @brief Implementación de la clase MotorCC para control de motores DC
 * @author Gear
 * @date 2025
 */

#include "MotorCC.hpp"

MotorCC::MotorCC(int pinSentidoA, int pinSentidoB, int velocidad)
{
	this->pinSentidoA = pinSentidoA;
	this->pinSentidoB = pinSentidoB;
	this->pinVelocidad = velocidad;
}

void MotorCC::iniciar()
{
	if(!this->iniciado)
	{
		pinMode(this->pinSentidoA, OUTPUT);
		pinMode(this->pinSentidoB, OUTPUT);
		pinMode(this->pinVelocidad, OUTPUT);
		
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
		analogWrite(this->pinVelocidad, -velocidad);
		digitalWrite(this->pinSentidoA, LOW);
		digitalWrite(this->pinSentidoB, HIGH);
	}
	else
	{
		// Giro en sentido A: activa pinSentidoA
		analogWrite(this->pinVelocidad, velocidad);
		digitalWrite(this->pinSentidoA, HIGH);
		digitalWrite(this->pinSentidoB, LOW);
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
		analogWrite(this->pinVelocidad, -velocidad);
		digitalWrite(this->pinSentidoA, HIGH);
		digitalWrite(this->pinSentidoB, LOW);
	}
	else
	{
		// Giro en sentido B: activa pinSentidoB
		analogWrite(this->pinVelocidad, velocidad);
		digitalWrite(this->pinSentidoA, LOW);
		digitalWrite(this->pinSentidoB, HIGH);
	}
}

void MotorCC::detener()
{
	if(!this->iniciado) return;

	analogWrite(this->pinVelocidad, 0);
	digitalWrite(this->pinSentidoA, LOW);
	digitalWrite(this->pinSentidoB, LOW);
}
