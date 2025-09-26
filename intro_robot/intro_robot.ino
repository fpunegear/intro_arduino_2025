#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "MotorCC.hpp"
#include "LectorSerial.hpp"
#include "Interprete.hpp"
#include "comandos.hpp"
#include "SensorLinea.hpp"

#define STACK_SIZE 128

#define PIN1_MOTOR_IZQUIERDO 13
#define PIN2_MOTOR_IZQUIERDO 12
#define PIN_VELOCIDAD_MOTOR_IZQUIERDO 6
#define PIN1_MOTOR_DERECHO 10
#define PIN2_MOTOR_DERECHO 11
#define PIN_VELOCIDAD_MOTOR_DERECHO 5
#define PIN1_SENSOR_LINEA 4
#define PIN2_SENSOR_LINEA 2
#define VELOCIDAD_MOTORES 200

SemaphoreHandle_t semaforoComandos = NULL;
TaskHandle_t handleLecturaComandos = NULL;
TaskHandle_t handleEjecutarComandos = NULL;
TaskHandle_t handleSeguirLinea = NULL;
const TickType_t esperaSemaforo = ( TickType_t ) 5;
const TickType_t esperaPoll = 20 / portTICK_PERIOD_MS;

MotorCC *motorIzquierdo = new MotorCC(PIN1_MOTOR_IZQUIERDO, PIN2_MOTOR_IZQUIERDO, PIN_VELOCIDAD_MOTOR_IZQUIERDO);
MotorCC *motorDerecho = new MotorCC(PIN1_MOTOR_DERECHO, PIN2_MOTOR_DERECHO, PIN_VELOCIDAD_MOTOR_DERECHO);
SensorLinea *sensorLinea = new SensorLinea(PIN1_SENSOR_LINEA, PIN2_SENSOR_LINEA); 
Lector *lector = new LectorSerial();
Interprete *interprete = new Interprete(lector);

Comando comandoActual = SIN_COMANDO;
uint8_t parametros[100] = {0};

void iniciarElementos();
void iniciarSemaforos();
void iniciarTareas();

void delayMS(int milisegundos);

void lecturaComandos(void *pvParameters);
void ejecutarComandos(void *pvParameters);
void seguirLinea(void *pvParameters);

void setup()
{
    iniciarSemaforos();
    iniciarElementos();
    iniciarTareas();
}

void loop() {}

void iniciarElementos()
{
    lector->iniciar();
    motorIzquierdo->iniciar();
    motorDerecho->iniciar();
    sensorLinea->iniciar();

    motorIzquierdo->detener();
    motorDerecho->detener();
}

void iniciarSemaforos()
{
    if(semaforoComandos != NULL) return;

    semaforoComandos = xSemaphoreCreateMutex();

    if(semaforoComandos != NULL)
    {
        xSemaphoreGive(semaforoComandos);
    }
}

void iniciarTareas()
{
    xTaskCreate
    (
        lecturaComandos,
        "LecturaComandos",
        STACK_SIZE,
        NULL,
        1,
        &handleLecturaComandos
    );

    xTaskCreate
    (
        seguirLinea,
        "SeguirLinea",
        STACK_SIZE,
        NULL,
        1,
        &handleSeguirLinea
    );

    xTaskCreate
    (
        ejecutarComandos,
        "EjecutarComandos",
        STACK_SIZE,
        NULL,
        1,
        &handleEjecutarComandos
    );
}

void delayMS(int milisegundos)
{
    vTaskDelay(milisegundos / portTICK_PERIOD_MS);
}

void lecturaComandos(void *pvParameters)
{
    for(;;)
    {
        if(semaforoComandos && xSemaphoreTake(semaforoComandos, esperaSemaforo) == pdTRUE)
        {
            comandoActual = interprete->procesar(parametros);
            xSemaphoreGive(semaforoComandos);
        }

        vTaskDelay(esperaPoll);
    }
}

void ejecutarComandos(void *pvParameters)
{
    vTaskSuspend(handleSeguirLinea);

    for(;;)
    {
        if(semaforoComandos && xSemaphoreTake(semaforoComandos, esperaSemaforo) == pdTRUE)
        {
            Comando comando = comandoActual;

            xSemaphoreGive(semaforoComandos);

            switch(comando)
            {
                case SIN_COMANDO:
                {
                    break;
                }
                case SEGUIR_LINEA:
                {
                    vTaskResume(handleSeguirLinea);
                    break;
                }
                case DETENERSE:
                {
                    vTaskSuspend(handleSeguirLinea);
        
                    motorIzquierdo->detener();
                    motorDerecho->detener();
                    break;
                }
            }
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
                motorIzquierdo->detener();
                motorDerecho->detener();

                break;
            }
            case IZQUIERDA_EN_LINEA:
            {
                motorIzquierdo->detener();
                motorDerecho->detener();
                delayMS(25);
                motorIzquierdo->girarSentidoA(VELOCIDAD_MOTORES);

                break;
            }
            case DERECHA_EN_LINEA:
            {
                motorIzquierdo->detener();
                motorDerecho->detener();
                delayMS(25);
                motorDerecho->girarSentidoA(VELOCIDAD_MOTORES);

                break;
            }
            case NINGUNO_EN_LINEA:
            {
                motorIzquierdo->girarSentidoA(VELOCIDAD_MOTORES);
                motorDerecho->girarSentidoA(VELOCIDAD_MOTORES);
                delayMS(25);
                motorIzquierdo->detener();
                motorDerecho->detener();

                break;
            }
        }

        vTaskDelay(esperaPoll);
    }
}