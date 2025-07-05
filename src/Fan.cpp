#include "Fan.hpp"
#include <Arduino.h>
#include "TemperatureSensor.hpp"

#define DATA_PIN_FAN 33 // PIN 33 for Fan

void init_Fan()
{
    pinMode(DATA_PIN_FAN, OUTPUT);
    digitalWrite(DATA_PIN_FAN, HIGH); // Fan is running
}

void Fan_On_Off()
{
    if(temperature < 50)
    {
        digitalWrite(DATA_PIN_FAN, LOW); // Fan is running
    }
    else
    {
        digitalWrite(DATA_PIN_FAN, HIGH); // Fan is running
    }
}