#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "MotorCC.hpp"
#include "LectorSerial.hpp"
#include "Interprete.hpp"
#include "comandos.hpp"
#include "SensorLinea.hpp"

#define PIN1_MOTOR_DERECHO 10
#define PIN2_MOTOR_DERECHO 11
#define PIN1_MOTOR_IZQUIERDO 12
#define PIN2_MOTOR_IZQUIERDO 13
#define PIN1_SENSOR_LINEA 2
#define PIN2_SENSOR_LINEA 4

SemaphoreHandle_t semaforoComandos = NULL;
const TickType_t esperaSemaforo = ( TickType_t ) 5;
const TickType_t esperaPoll = 50 / portTICK_PERIOD_MS;
const TickType_t esperaIntermedia = 20 / portTICK_PERIOD_MS;

MotorCC *motorIzquierdo = new MotorCC(PIN1_MOTOR_IZQUIERDO, PIN2_MOTOR_IZQUIERDO);
MotorCC *motorDerecho = new MotorCC(PIN1_MOTOR_DERECHO, PIN2_MOTOR_DERECHO);
SensorLinea *sensorLinea = new SensorLinea(PIN1_SENSOR_LINEA, PIN2_SENSOR_LINEA); 
Lector *lector = new LectorSerial();
Interprete *interprete = new Interprete(lector);

Comando comandoActual = SIN_COMANDO;
uint8_t parametros[100] = {0};

void iniciarElementos();
void iniciarSemaforos();

void lecturaComandos(void *pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake(semaforoComandos, esperaSemaforo) == pdTRUE)
        {
            comandoActual = interprete->procesar(parametros);
            xSemaphoreGive(semaforoComandos);
        }

        vTaskDelay(esperaPoll);
    }
}

void seguirLinea(void *pvParameters)
{
    for(;;)
    {
        EstadoLinea estadoLinea  = sensorLinea->leer();

        switch(estadoLinea)
        {
            case AMBOS_SENSORES_EN_LINEA:
            {

                break;
            }
            case IZQUIERDA_EN_LINEA:
            {
                
                break;
            }
            case DERECHA_EN_LINEA:
            {

                break;
            }
            case NINGUNO_EN_LINEA:
            {
                motorDerecho->girarSentidoA(255);
                motorIzquierdo->girarSentidoB(255);
                vTaskDelay(esperaIntermedia);
                
                break;
            }
        }

        vTaskDelay(esperaPoll);
    }
}

void setup()
{
    iniciarSemaforos();
    iniciarElementos();
}

void loop() {}

void iniciarElementos()
{
    lector->iniciar();
    motorDerecho->iniciar();
    motorIzquierdo->iniciar();
    sensorLinea->iniciar();
}

void iniciarSemaforos()
{
    if(semaforoComandos != NULL)
    {
        return;
    }

    semaforoComandos = xSemaphoreCreateMutex();

    if(semaforoComandos != NULL)
    {
        xSemaphoreGive(semaforoComandos);
    }
}