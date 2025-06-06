#include "TemperatureSensor.hpp"
#include "SimpleDHT.h"

#define DATA_PIN_TEMPERATURE_SENSOR 2 // PIN 2 for Temperature Sensor

int pinDHT11 = DATA_PIN_TEMPERATURE_SENSOR; // Pin, an dem der DHT11 angeschlossen ist
SimpleDHT11 dht11(pinDHT11);

void init_TempSensor()
{
    Serial.begin(115200);
    Serial.println("Initialisiere DHT11 Sensor...");
    
    float temperature = 0;
    float humidity = 0;
    int err = SimpleDHTErrSuccess;
  
    if ((err = dht11.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
    {
        Serial.print("Fehler beim Initialisieren des DHT11 (Lesefehler), Fehlercode: ");
        Serial.println(err);
    } 
    else 
    {
        Serial.println("DHT11 erfolgreich initialisiert.");
        Serial.print("Erste Messung: ");
        Serial.print(temperature);
        Serial.print(" °C, ");
        Serial.print(humidity);
        Serial.println(" % RH");
    }
}

float get_Temperature()
{
    float temperature = 0.0;
    float humidity = 0.0;
    dht11.read2(&temperature, &humidity, NULL);

    return temperature;
}
