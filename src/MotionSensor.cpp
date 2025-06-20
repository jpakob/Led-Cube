#include "MotionSensor.hpp"
#include "Arduino.h"

#define DATA_PIN_MOTION_SENSOR 15 // PIN 15 for Motion Sensor

void init_Motion()
{
    pinMode(DATA_PIN_MOTION_SENSOR, INPUT);
}

bool Person_detected()
{
    int motion = digitalRead(DATA_PIN_MOTION_SENSOR);
    if (motion == HIGH) 
    {
        return true;
    }
    else
    {
        return false;
    }
}