#include <Arduino_FreeRTOS.h>

#include "MotorCC.hpp"
#include "LectorSerial.hpp"
#include "Interprete.hpp"

#define PIN1_MOTOR_DERECHO 10
#define PIN2_MOTOR_DERECHO 11
#define PIN1_MOTOR_IZQUIERDO 12
#define PIN2_MOTOR_IZQUIERDO 13

MotorCC *motorIzquierdo = new MotorCC(PIN1_MOTOR_IZQUIERDO, PIN2_MOTOR_IZQUIERDO);
MotorCC *motorDerecho = new MotorCC(PIN1_MOTOR_DERECHO, PIN2_MOTOR_DERECHO);
Lector *lector = new LectorSerial();
Interprete *interprete = new Interprete(lector);

void iniciarElementos();

void lecturaComandos(void *pvParameters)
{
    for (;;)
    {
        interprete->procesar();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    iniciarElementos();
}

void loop()
{
}

void iniciarElementos()
{
    lector->iniciar();
    motorDerecho->iniciar();
    motorIzquierdo->iniciar();
}