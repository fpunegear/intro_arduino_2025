/**
 * @file MotorCC.hpp
 * @brief Clase para el control de motores de corriente continua
 * @author Gear
 * @date 2025
 */

#ifndef __MOTOR_CC_H__
#define __MOTOR_CC_H__

#include "Arduino.h"

/** @brief Valor máximo de PWM para control de velocidad */
#define PWM_MAX 255

/**
 * @class MotorCC
 * @brief Clase para controlar un motor de corriente continua con dos pines de sentido
 *
 * Esta clase permite controlar la velocidad y sentido de rotación de un motor DC utilizando
 * dos pines digitales con capacidad PWM para implementar control bidireccional.
 */
class MotorCC
{
private:
	/** @brief Pin para control de sentido A del motor */
	int pinSentidoA;

	/** @brief Pin para control de sentido B del motor */
	int pinSentidoB;

	/** @brief Pin para control de velocidad del motor */
	int pinVelocidad;

	/** @brief Indica si el motor ha sido inicializado */
	bool iniciado = false;

public:
	/**
	 * @brief Constructor de la clase MotorCC
	 * @param pinSentidoA Pin digital para controlar sentido A
	 * @param pinSentidoB Pin digital para controlar sentido B
	 * @param velocidad Pin PWM para controlar velocidad del motor
	 */
	MotorCC(int pinSentidoA, int pinSentidoB, int velocidad);

	/**
	 * @brief Inicializa los pines del motor como salidas
	 */
	void iniciar();

	/**
	 * @brief Hace girar el motor en sentido A
	 * @param velocidad Velocidad del motor (-255 a 255)
	 *                  Valores positivos: giro en sentido A
	 *                  Valores negativos: giro en sentido B
	 */
	void girarSentidoA(int velocidad);

	/**
	 * @brief Hace girar el motor en sentido B
	 * @param velocidad Velocidad del motor (-255 a 255)
	 *                  Valores positivos: giro en sentido B
	 *                  Valores negativos: giro en sentido A
	 */
	void girarSentidoB(int velocidad);

	/**
	 * @brief Detiene completamente el motor
	 *
	 * Pone la velocidad en 0 y desactiva ambos pines de sentido,
	 * deteniendo cualquier movimiento del motor.
	 */
	void detener();
};

#endif //__MOTOR_CC_H__
