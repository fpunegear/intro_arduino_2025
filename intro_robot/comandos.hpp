/**
 * @file comandos.hpp
 * @brief Definición de comandos disponibles para el robot
 * @author Gear
 * @date 2025
 */

#ifndef __COMANDO_H__
#define __COMANDO_H__

/**
 * @enum Comando
 * @brief Enumeración de comandos que puede procesar el robot
 */
enum Comando
{
    /** @brief No hay comando pendiente */
    SIN_COMANDO,

    /** @brief Activar algoritmo de seguimiento de línea */
    SEGUIR_LINEA,

    /** @brief Detener todos los motores */
    DETENERSE,
};

#endif //__COMANDO_H__