#if 0

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

#endif

#if 0

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Access Point Daten
const char* ssid = "LED_Cube";
const char* password = "12345678";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // SPIFFS starten
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS konnte nicht gestartet werden");
    return;
  }

  // Access Point starten
  WiFi.softAP(ssid, password);
  Serial.println("Access Point gestartet");
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.softAPIP());

  // index.html beim Root-Pfad ausliefern
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // style.css ausliefern
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Server starten
  server.begin();
}

void loop() {
  // nichts hier
}

#endif

#if 0

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

#endif

#if 0

#include <FastLED.h>

#define NUM_LEDS 64
#define DATA_PIN 12 // Anpassen je nach Verdrahtung
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Alle LEDs auf Weiß setzen
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = CRGB::White;
  }

  FastLED.show();
}

void loop() 
{
  // Nichts tun – LEDs bleiben an
}
#endif

#if 0

#include <U8g2lib.h>

// Zwei Displays mit Software-I2C
U8G2_SH1106_128X64_NONAME_F_SW_I2C display1(U8G2_R0, /* clock=*/ 22, /* data=*/ 21, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_SW_I2C display2(U8G2_R0, /* clock=*/ 18, /* data=*/ 19, /* reset=*/ U8X8_PIN_NONE);

unsigned long lastUpdate = 0;
int counter = 0;

void setup() {
  display1.begin();
  display2.begin();

  display1.setFont(u8g2_font_logisoso32_tf);
  display2.setFont(u8g2_font_logisoso32_tf);
}

void loop() {
  // Einmal pro Sekunde erhöhen
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    counter++;
  }

  char buf1[10];
  char buf2[10];
  snprintf(buf1, sizeof(buf1), "%d", counter);
  snprintf(buf2, sizeof(buf2), "%d", counter * 2);  // Einfach zum Testen: zweiter Zähler ist doppelt so schnell

  // Erstes Display zeigt Zähler 1
  display1.firstPage();
  do {
    display1.drawUTF8(20, 48, buf1);
  } while (display1.nextPage());

  // Zweites Display zeigt Zähler 2
  display2.firstPage();
  do {
    display2.drawUTF8(20, 48, buf2);
  } while (display2.nextPage());

  // Kurze Pause
  delay(50);
}
#endif

#if 0

#include <Arduino.h>

void setup() {
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);  // Transistor schaltet durch → 5V an Last
}

void loop() {
  // nichts tun
}

#endif

#if 0
#include <FastLED.h>

#define LEDS_PER_STRIP 128
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define NUM_STRIPS 4

#define DATA_PIN_1 12
#define DATA_PIN_2 14
#define DATA_PIN_3 27
#define DATA_PIN_4 26

CRGB leds1[LEDS_PER_STRIP];
CRGB leds2[LEDS_PER_STRIP];
CRGB leds3[LEDS_PER_STRIP];
CRGB leds4[LEDS_PER_STRIP];

void setup() 
{
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds1, LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds2, LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds3, LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDER>(leds4, LEDS_PER_STRIP);

  // Alle LEDs auf Weiß setzen
  for (int i = 0; i < LEDS_PER_STRIP; i++) {
    leds1[i] = CRGB::White;
    leds2[i] = CRGB::White;
    leds3[i] = CRGB::White;
    leds4[i] = CRGB::White;
  }

  FastLED.show();
}

void loop() 
{
  // Nichts tun – LEDs bleiben an
}

#endif

#if 1


#include "Display.hpp"
#include "Fan.hpp"
#include "Led.hpp"
#include "MotionSensor.hpp"
#include "TemperatureSensor.hpp"
#include "Website.hpp"
#include "Wifi.hpp"
 

void setup()
{
  Serial.begin(115200);
  init_Website();
  init_Leds();
  init_Display();
  init_TempSensor();
  init_Fan();
}

void loop()
{
  //Serial.println(get_current_Mode());
  update_Leds();
  get_Temperature();
  show_Temperature();
  show_current_Mode();
  Fan_On_Off();
  delay(20);
}

#endif



#if 0


#include "U8g2lib.h"



#define DISPLAY_1_SDA 18 // PIN 18 for Diplay 1 Data 
#define DISPLAY_1_SCK 19 // PIN 19 for Display 1 CLock
#define DISPLAY_2_SDA 21 // PIN 21 for Diplay 2 Data 
#define DISPLAY_2_SCK 22 // PIN 22 for Display 2 CLock 

U8G2_SH1106_128X64_NONAME_F_SW_I2C display1(U8G2_R0, /* clock=*/ DISPLAY_1_SCK, /* data=*/ DISPLAY_1_SDA, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_SW_I2C display2(U8G2_R0, /* clock=*/ DISPLAY_2_SCK, /* data=*/ DISPLAY_2_SDA, /* reset=*/ U8X8_PIN_NONE);
 

void setup()
{
  Serial.begin(115200);

  display1.begin();
  display2.begin();

  display1.setFont(u8g2_font_logisoso32_tf);
  display2.setFont(u8g2_font_logisoso32_tf);

  display1.setDisplayRotation(U8G2_R2);  // 180° Rotation
  display2.setDisplayRotation(U8G2_R2);


}

void loop()
{
  // Beispielwerte (ersetz das durch z. B. get_Temperature())
  float temperature = 23.5;
  float humidity = 57.2;

  // === Display 1 (z. B. Temperatur) ===
  display1.clearBuffer();                 // Bildschirm löschen (nur im Speicher)
  display1.setCursor(0, 40);              // Position setzen
  display1.print(temperature, 1);         // z. B. "23.5"
  display1.print(" C");
  display1.sendBuffer();                 // Anzeige aktualisieren

  // === Display 2 (z. B. Luftfeuchtigkeit) ===
  display2.clearBuffer();
  display2.setCursor(0, 40);
  display2.print(humidity, 1);           // z. B. "57.2"
  display2.print(" %");
  display2.sendBuffer();

  delay(1000);  // Warte 1 Sekunde bis zur nächsten Anzeigeaktualisierung
}


#endif