#include "Website.hpp"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include "Wifi.hpp"
#include "Led.hpp"

AsyncWebServer server(80);

int current_Mode = 0;

int get_current_Mode()
{
    return current_Mode;
}

void set_current_Mode(int mode)
{
    current_Mode = mode;
    Serial.printf("Modus geändert auf %d\n", mode);
    update_Leds();
}

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

