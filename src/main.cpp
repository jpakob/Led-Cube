/*
#include "WLANsupport.h"
#include <NTPClient.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "iPhone von Jakob";
const char* password = "mercedes";

AsyncWebServer server(80);  // Webserver auf Port 80 starten

// NTP-Client
WiFiUDP ntpUDP;

void setup(void)
{
  Serial.begin(115200);
  initWiFi();
  server.begin();
}

void loop(void)
{
  delay(600);
}
*/


/*
#include <FastLED.h>

#define NUM_LEDS 64
#define DATA_PIN 12
#define BRIGHTNESS 50

CRGB leds[NUM_LEDS];

int step = 0;
bool turningOn = true;
unsigned long lastUpdate = 0;
const int interval = 100;

void setup()
{
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop()
{
  unsigned long currentTime = millis();
  if(currentTime - lastUpdate < interval)
  {
     return;
  }

  lastUpdate = currentTime;

  if(turningOn)
  {
    leds[step] = CRGB::Blue;
  }
  else
  {
    leds[step] = CRGB::Black;
  }

  FastLED.show();
  step++;

  if(step >= NUM_LEDS)
  {
    step = 0;
    turningOn = !turningOn;
  }
}
*/


#include <FastLED.h>

#define NUM_LEDS 64
#define DATA_PIN 12            // Anpassen je nach Verdrahtung
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Alle LEDs auf Weiß setzen
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }

  FastLED.show();
}

void loop() {
  // Nichts tun – LEDs bleiben an
}


