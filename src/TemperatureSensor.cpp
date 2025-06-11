#include "TemperatureSensor.hpp"
#include "SimpleDHT.h"

#define DATA_PIN_TEMPERATURE_SENSOR 16 // PIN 2 for Temperature Sensor

int pinDHT11 = DATA_PIN_TEMPERATURE_SENSOR; // Pin, an dem der DHT11 angeschlossen ist
SimpleDHT11 dht11(pinDHT11);

float temperature = 0.0;
float humidity = 0.0;

void init_TempSensor()
{
    Serial.begin(115200);
    Serial.println("Initialisiere DHT11 Sensor...");
}

void get_Temperature()
{
    dht11.read2(&temperature, &humidity, NULL);
}
