/**
 * @file Interprete.cpp
 * @brief Implementación de la clase Interprete
 * @author Gear
 * @date 2025
 */

#include "Interprete.hpp"

Interprete::Interprete(Lector* lector)
{
	this->lector = lector;
}

Comando Interprete::procesar(uint8_t *parametros)
{
	if(this->lector != nullptr)
	{
		String comando = this->lector->leer();

		if(comando.length() > 0)
		{
			// TODO: Implementar parsing y procesamiento de comandos
			// Ejemplo: parseCommand(comando);
		}

		return SEGUIR_LINEA; // TODO quitar despues de probar
	}
}
