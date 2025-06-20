#include "TemperatureSensor.hpp"
#include "SimpleDHT.h"

#define DATA_PIN_TEMPERATURE_SENSOR 16 // PIN 2 for Temperature Sensor

int pinDHT11 = DATA_PIN_TEMPERATURE_SENSOR; // Pin, an dem der DHT11 angeschlossen ist
SimpleDHT11 dht11(pinDHT11);

float temperature = 0.0;
float humidity = 0.0;
SemaphoreHandle_t temperature_mutex;
SemaphoreHandle_t humidity_mutex;

void init_TempSensor()
{
    temperature_mutex = xSemaphoreCreateMutex();
    humidity_mutex = xSemaphoreCreateMutex();
    Serial.println("Initialisiere DHT11 Sensor...");
}

void get_Temperature()
{
    xSemaphoreTake(temperature_mutex, portMAX_DELAY);
    xSemaphoreTake(humidity_mutex, portMAX_DELAY);
    dht11.read2(&temperature, &humidity, NULL);
    xSemaphoreGive(humidity_mutex);
    xSemaphoreGive(temperature_mutex);
}
