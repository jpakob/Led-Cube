#include "Led.hpp"
#include <FastLED.h>
#include "Website.hpp"
#include "MotionSensor.hpp"

#define NUM_LEDS_X 8
#define NUM_LEDS_Y 8
#define NUM_LEDS_Z 8
#define NUM_LEDS_Con 128
#define DATA_PIN_0 12 // Plate 1 and 2           
#define DATA_PIN_1 14 // Plate 3 and 4   
#define DATA_PIN_2 27 // Plate 5 and 6   
#define DATA_PIN_3 26 // Plate 7 and 8
#define DATA_PIN_FAN 33 // PIN 33 for Fan
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS_X][NUM_LEDS_Y][NUM_LEDS_Z];

struct Star_led
{
    int x;
    int y;
    int z;
    int brightnes= 0;
};

// Mutex für LED-Daten und Puls-Variablen
SemaphoreHandle_t leds_mutex;

unsigned long lastPulseUpdate = 0;
int pulseRadius = 0;
bool expanding = true;

const int maxRadius = 4;  // oder mehr, je nach LED-Array
const uint8_t center = 4; // Zentrum (anpassen!)
const CRGB pulseColor = CRGB::Blue;
const uint16_t pulseInterval = 5; // in ms

bool Switch_On_Off = true;
bool initialized = false;

void init_Leds()
{
    leds_mutex = xSemaphoreCreateMutex();

    FastLED.addLeds<LED_TYPE, DATA_PIN_0, COLOR_ORDER>(leds[0][0], NUM_LEDS_Con);
    FastLED.setBrightness(BRIGHTNESS);

    FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds[2][0], NUM_LEDS_Con);
    FastLED.setBrightness(BRIGHTNESS);

    FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds[4][0], NUM_LEDS_Con);
    FastLED.setBrightness(BRIGHTNESS);

    FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds[6][0], NUM_LEDS_Con);
    FastLED.setBrightness(BRIGHTNESS);
}

void Mode_1()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        Switch_On_Off = true;
        static const int maxStars = 20; // Weniger Sterne
        static Star_led stars[maxStars];
        static int starIndex = 0;
        static uint8_t hue = 43;

        if (!initialized) {
            // Cube löschen beim ersten Start
            for (int x = 0; x < NUM_LEDS_X; x++) {
                for (int y = 0; y < NUM_LEDS_Y; y++) {
                    for (int z = 0; z < NUM_LEDS_Z; z++) {
                        leds[x][y][z] = CRGB::Black;
                    }
                }
            }
            for (int i = 0; i < maxStars; i++) 
            {
                stars[i].x = 0;
                stars[i].y = 0;
                stars[i].z = 0;
                stars[i].brightnes = 0;  
            }
            initialized = true;
        }

        // Bestehende Sterne dimmen
        for (int i = 0; i < maxStars; i++) {
            if (stars[i].brightnes > 0) {
                stars[i].brightnes -= 8; // schneller dimmen
                if (stars[i].brightnes < 0) stars[i].brightnes = 0;
                leds[stars[i].x][stars[i].y][stars[i].z] = CHSV(hue, 255, stars[i].brightnes);
            }
        }

        // Neue Sterne nur mit kleiner Wahrscheinlichkeit
        if (random(0, 100) < 10) { // ~10% Chance pro update
            stars[starIndex].x = random(NUM_LEDS_X);
            stars[starIndex].y = random(NUM_LEDS_Y);
            stars[starIndex].z = random(NUM_LEDS_Z);
            stars[starIndex].brightnes = 160 + random(40); // weniger hell
            starIndex = (starIndex + 1) % maxStars;
        }

        FastLED.show();
        xSemaphoreGive(leds_mutex);
    }
}



int max(int a, int b, int c) 
{
    return std::max(std::max(a, b), c);
}

int max3(int a, int b, int c) 
{
    return std::max(std::max(a, b), c);
}

void Mode_2()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        Switch_On_Off = true;
        initialized = false;
        const uint8_t centerMin = 3;
        const uint8_t centerMax = 4;

        unsigned long currentMillis = millis();
        if (currentMillis - lastPulseUpdate >= pulseInterval)
        {
            lastPulseUpdate = currentMillis;

            for (int x = 0; x < NUM_LEDS_X; x++) 
            {
                for (int y = 0; y < NUM_LEDS_Y; y++) 
                {
                    for (int z = 0; z < NUM_LEDS_Z; z++) 
                    {
                        int dx = max(centerMin - x, 0, x - centerMax);
                        int dy = max(centerMin - y, 0, y - centerMax);
                        int dz = max(centerMin - z, 0, z - centerMax);
                        int dist = max3(dx, dy, dz);

                        if (dist == pulseRadius) 
                        {
                            leds[x][y][z] = expanding ? pulseColor : CRGB::Black;
                        }
                    }
                }
            }

            // Radiussteuerung
            if (expanding) 
            {
                pulseRadius++;
                if (pulseRadius > maxRadius) 
                {
                    pulseRadius = maxRadius;
                    expanding = false;
                }
            } 
            else 
            {
                pulseRadius--;
                if (pulseRadius < 0) 
                {
                    pulseRadius = 0;
                    expanding = true;
                }
            }

            FastLED.show();
        }
        xSemaphoreGive(leds_mutex);
    }
}

void Mode_3()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        Switch_On_Off = true;
        if(Person_detected() == true)
        {
            initialized = false;
            const int colorSteps = 100;
            static CRGB colorPalette[colorSteps];
            static bool initialized = false;
            static int colorIndex = 0;
            CRGB color;
            const int delayTime = 100; // nicht genutzt hier, ggf. externes Delay sinnvoll

            if (!initialized) 
            {
                for (int i = 0; i < colorSteps; i++) 
                {
                    uint8_t hue = (i * 256L / colorSteps) % 256;
                    colorPalette[i] = CHSV(hue, 255, 255);
                }
                initialized = true;
            }

            color = colorPalette[colorIndex];
            colorIndex = (colorIndex + 1) % colorSteps;

            for (int x = 0; x < NUM_LEDS_X; x++) 
            {
                for (int y = 0; y < NUM_LEDS_Y; y++) 
                {
                    for (int z = 0; z < NUM_LEDS_Z; z++) 
                    {
                        leds[x][y][z] = color;
                    }
                }
            }
            FastLED.show();
        }
        else if(Person_detected() == false)
        {
            for(int x=0; x < 255 ; x++)
            {
                for (int i = 0; i < NUM_LEDS_X; i++)
                {
                    for(int n = 0; n < NUM_LEDS_Y; n++)
                    {
                        for(int p = 0; p < NUM_LEDS_Z; p++)
                        {
                            leds[i][n][p] = CRGB::Black;
                        }
                    }
                }
                FastLED.setBrightness(x);
                FastLED.show();
            }
        }
        xSemaphoreGive(leds_mutex);
    }
}

void Mode_4()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        Switch_On_Off = true;
        initialized = false;
        
        for (int x = 0; x < NUM_LEDS_X; x++) 
        {
            for (int y = 0; y < NUM_LEDS_Y; y++) 
            {
                for (int z = 0; z < NUM_LEDS_Z; z++) 
                {
                    uint8_t randomHue = random8();  // Zufälliger Farbton (0–255)
                    leds[x][y][z] = CHSV(randomHue, 255, 255);  // Volle Sättigung & Helligkeit
                }
            }
        }
        FastLED.show();
        xSemaphoreGive(leds_mutex);
    }
}

void Switch_Off()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        initialized = false;
        Switch_On_Off = false;
        for(int x=0; x < 255 ; x++)
        {
            for (int i = 0; i < NUM_LEDS_X; i++)
            {
                for(int n = 0; n < NUM_LEDS_Y; n++)
                {
                    for(int p = 0; p < NUM_LEDS_Z; p++)
                    {
                        leds[i][n][p] = CRGB::Black;
                    }
                }
            }
            FastLED.setBrightness(x);
            FastLED.show();
        }
        set_current_Mode(0);
        xSemaphoreGive(leds_mutex);
    }
}


void Switch_On()
{
    if (xSemaphoreTake(leds_mutex, portMAX_DELAY)) 
    {
        initialized = false;
        Switch_On_Off = true;
        for(int x=0; x < 255 ; x++)
        {
            for (int i = 0; i < NUM_LEDS_X; i++)
            {
                for(int n = 0; n < NUM_LEDS_Y; n++)
                {
                    for(int p = 0; p < NUM_LEDS_Z; p++)
                    {
                        leds[i][n][p] = CRGB::Red;
                    }
                }
            }
            FastLED.setBrightness(x);
            FastLED.show();
        }
        set_current_Mode(0);
        xSemaphoreGive(leds_mutex);
    }
}

void update_Leds()
{
    int mode = get_current_Mode();
    switch (mode)
    {
        case 0:
            // LEDs aus oder Standardmuster
            break;
        case 1:
            Mode_1();
            break;
        case 2:
            Mode_2();
            break;
        case 3: 
            Mode_3();
            break;
        case 4:
            Mode_4();
            break;
        case 5:
            if (Switch_On_Off) 
            {
                Switch_Off();
            } 
            else 
            {
                Switch_On();
            }
            break;
        default:
            break;
    }
}
