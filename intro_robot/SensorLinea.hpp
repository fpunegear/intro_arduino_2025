/**
 * @file SensorLinea.hpp
 * @brief Clase para lectura de sensores de línea
 * @author Gear
 * @date 2025
 */

#ifndef __SENSOR_LINEA_H__
#define __SENSOR_LINEA_H__

#include "Arduino.h"

/**
 * @enum EstadoLinea
 * @brief Estados posibles de los sensores de línea
 */
enum EstadoLinea
{
    /** @brief Ambos sensores detectan la línea */
    AMBOS_SENSORES_EN_LINEA,

    /** @brief Solo el sensor izquierdo detecta la línea */
    IZQUIERDA_EN_LINEA,

    /** @brief Solo el sensor derecho detecta la línea */
    DERECHA_EN_LINEA,

    /** @brief Ningún sensor detecta la línea */
    NINGUNO_EN_LINEA
};

/**
 * @class SensorLinea
 * @brief Clase para manejar sensores de detección de línea
 *
 * Esta clase permite leer el estado de dos sensores digitales
 * para determinar la posición de una línea respecto al robot.
 */
class SensorLinea
{
private:
    /** @brief Pin digital del sensor izquierdo */
    int pinIzquierdo;

    /** @brief Pin digital del sensor derecho */
    int pinDerecho;

    /** @brief Indica si el sensor ha sido inicializado */
    bool iniciado = false;

public:
    /**
     * @brief Constructor de la clase SensorLinea
     * @param pinIzquierdo Pin digital del sensor izquierdo
     * @param pinDerecho Pin digital del sensor derecho
     */
    SensorLinea(int pinIzquierdo, int pinDerecho);

    /**
     * @brief Inicializa los pines de los sensores como entradas
     */
    void iniciar();

    /**
     * @brief Lee el estado actual de ambos sensores
     * @return EstadoLinea que indica qué sensores detectan la línea
     */
    EstadoLinea leer();
};

#endif //__SENSOR_LINEA_H__