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

void Interprete::procesar()
{
	if(this->lector != nullptr)
	{
		String comando = this->lector->leer();
		
		if(comando.length() > 0)
		{
			// TODO: Implementar parsing y procesamiento de comandos
			// Ejemplo: parseCommand(comando);
		}
	}
}
