/**
 * @file LectorSerial.cpp
 * @brief Implementación de la clase LectorSerial
 * @author Gear
 * @date 2025
 */

#include "LectorSerial.hpp"

LectorSerial::LectorSerial()
{
}

void LectorSerial::iniciar()
{
	if(!this->iniciado)
	{
		Serial.begin(BAUD_RATE);

		this->iniciado = true;
	}
}

String LectorSerial::leer()
{
	String lecturaSerial = "";

	if(!this->iniciado) return lecturaSerial;

	if(Serial.available() > 0)
	{
		lecturaSerial = Serial.readStringUntil('\n');
	}

	return lecturaSerial;
}