/**
 * @file Lector.hpp
 * @brief Interfaz base para lectores de datos
 * @author Gear
 * @date 2025
 */

#ifndef __LECTOR_H__
#define __LECTOR_H__

#include "Arduino.h"

/**
 * @class Lector
 * @brief Interfaz base para implementar diferentes tipos de lectores de datos
 *
 * Esta interfaz permite crear diferentes implementaciones de lectores
 * (Serial, Bluetooth, WiFi, etc.) que pueden ser intercambiadas fácilmente.
 */
class Lector
{
public:
	/**
	 * @brief Destructor virtual
	 */
	virtual ~Lector() {}

	/**
	 * @brief Inicializa el lector
	 */
	virtual void iniciar() = 0;

	/**
	 * @brief Lee datos desde la fuente configurada
	 * @return String con los datos leídos
	 */
	virtual String leer() = 0;
};

#endif //__LECTOR_H__
