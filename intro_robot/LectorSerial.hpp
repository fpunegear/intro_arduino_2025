/**
 * @file LectorSerial.hpp
 * @brief Implementación de lector de datos vía puerto serie
 * @author Gear
 * @date 2025
 */

#ifndef __LECTOR_SERIAL_H__
#define __LECTOR_SERIAL_H__

#include "Lector.hpp"

/** @brief Velocidad de comunicación serie en baudios */
#define BAUD_RATE 9600

/**
 * @class LectorSerial
 * @brief Implementación concreta de Lector para comunicación serie
 *
 * Esta clase implementa la interfaz Lector para leer datos desde
 * el puerto serie usando la clase Serial de Arduino.
 */
class LectorSerial : public Lector
{
private:
	/** @brief Indica si el lector ha sido inicializado */
	bool iniciado = false;

public:
	/**
	 * @brief Constructor de la clase LectorSerial
	 */
	LectorSerial();

	/**
	 * @brief Inicializa la comunicación serie
	 */
	void iniciar() override;

	/**
	 * @brief Lee una línea de datos desde el puerto serie
	 * @return String con los datos leídos (vacío si no hay datos disponibles)
	 */
	String leer() override;
};

#endif //__LECTOR_SERIAL_H__