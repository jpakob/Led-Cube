#include "Fan.hpp"
#include <Arduino.h>

#define DATA_PIN_FAN 33 // PIN 33 for Fan

void init_Fan()
{
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH); // Fan is running
}

void Fan_On_Off(int Temperature)
{
    
}