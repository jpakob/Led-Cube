#include "Website.hpp"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include "Wifi.hpp"

AsyncWebServer server(80);

void init_Website()
{
    Serial.begin(115200);

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

    server.begin();
}

int get_CurrentMode()
{
    
}