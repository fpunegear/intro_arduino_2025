/**
 * @file SensorLinea.cpp
 * @brief Implementación de la clase SensorLinea
 * @author Gear
 * @date 2025
 */

#include "SensorLinea.hpp"

SensorLinea::SensorLinea(int pinIzquierdo, int pinDerecho)
{
    this->pinIzquierdo = pinIzquierdo;
    this->pinDerecho = pinDerecho;
}

void SensorLinea::iniciar()
{
    if(!this->iniciado)
	{
		pinMode(this->pinIzquierdo, INPUT);
		pinMode(this->pinDerecho, INPUT);

		this->iniciado = true;
	}
}

EstadoLinea SensorLinea::leer()
{
    if(!this->iniciado) return AMBOS_SENSORES_EN_LINEA;

    // Lee el estado digital de ambos sensores (HIGH = línea detectada)
    bool estadoIzquierdo = digitalRead(this->pinIzquierdo) == HIGH;
    bool estadoDerecho = digitalRead(this->pinDerecho) == HIGH;

    // Determina el estado según qué sensores detectan la línea
    if(estadoIzquierdo && estadoDerecho)
    {
        return AMBOS_SENSORES_EN_LINEA;
    }
    else if(estadoIzquierdo)
    {
        return IZQUIERDA_EN_LINEA;
    }
    else if(estadoDerecho)
    {
        return DERECHA_EN_LINEA;
    }
    else
    {
        return NINGUNO_EN_LINEA;
    }
}