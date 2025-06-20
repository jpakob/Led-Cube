#include "Website.hpp"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include "Wifi.hpp"
#include "Led.hpp"

AsyncWebServer server(80);

int current_Mode = 0;
SemaphoreHandle_t current_Mode_Mutex;

int get_current_Mode()
{
    xSemaphoreTake(current_Mode_Mutex, portMAX_DELAY);
    int mode = current_Mode;
    xSemaphoreGive(current_Mode_Mutex);
    return mode;
}

void set_current_Mode(int mode)
{
    xSemaphoreTake(current_Mode_Mutex, portMAX_DELAY);
    current_Mode = mode;
    xSemaphoreGive(current_Mode_Mutex);
    Serial.printf("Modus geändert auf %d\n", mode);
    //update_Leds();
}

void init_Website()
{
    current_Mode_Mutex = xSemaphoreCreateMutex();

    if (!SPIFFS.begin(true)) 
    {
        Serial.println("SPIFFS konnte nicht gestartet werden");
        return;
    }

    // starting Access Point
    initWiFi();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/style.css", "text/css");
    });

      server.on("/setPattern", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("pattern")) {
        int mode = request->getParam("pattern")->value().toInt();
        set_current_Mode(mode); // Speichern + LED-Muster aktualisieren
        request->send(200, "text/plain", "Pattern geändert zu " + String(mode));
    } else {
        request->send(400, "text/plain", "Fehlender Parameter");
    }
});

    server.begin();
}

