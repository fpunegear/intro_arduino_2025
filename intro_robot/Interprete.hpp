/**
 * @file Interprete.hpp
 * @brief Clase para interpretar comandos de entrada
 * @author Gear
 * @date 2025
 */

#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include "Arduino.h"
#include "Lector.hpp"

/**
 * @class Interprete
 * @brief Clase para interpretar y procesar comandos
 *
 * Esta clase recibe comandos a través de un objeto Lector
 * y los procesa según el formato establecido.
 */
class Interprete
{
private:
	/** @brief Puntero al objeto lector de datos */
	Lector* lector;

public:
	/**
	 * @brief Constructor de la clase Interprete
	 * @param lector Puntero al objeto que implementa la interfaz Lector
	 */
	Interprete(Lector* lector);

	/**
	 * @brief Procesa comandos disponibles del lector
	 */
	void procesar();
};

#endif //__INTERPRETE_H__
