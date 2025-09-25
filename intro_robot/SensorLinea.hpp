#ifndef __SENSOR_LINEA_H__
#define __SENSOR_LINEA_H__

#include "Arduino.h"

enum EstadoLinea
{
    AMBOS_SENSORES_EN_LINEA,
    IZQUIERDA_EN_LINEA,
    DERECHA_EN_LINEA,
    NINGUNO_EN_LINEA
};

class SensorLinea
{
private:
    int pinIzquierdo;
    int pinDerecho;
    bool iniciado = false;

public:
    SensorLinea(int pinIzquierdo, int pinDerecho);
    void iniciar();
    EstadoLinea leer();
};

#endif //__SENSOR_LINEA_H__