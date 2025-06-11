#include "Led.hpp"
#include <FastLED.h>
#include "Website.hpp"

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

void init_Leds()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN_0, COLOR_ORDER>(leds[0][0], NUM_LEDS_Con);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds[2][0], NUM_LEDS_Con);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds[4][0], NUM_LEDS_Con);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds[6][0], NUM_LEDS_Con);
  FastLED.setBrightness(BRIGHTNESS);
}


void start_Cube()
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

  FastLED.show();
}

void update_Leds()
{
  int mode = get_current_Mode();

  switch (mode) 
  {
        case 0:
            start_Cube();
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
        default:
            // LEDs aus oder Standardmuster
            break;
    }
}

void Mode_1()
{
  for (int i = 0; i < NUM_LEDS_X; i++)
  {
    for(int n = 0; n < NUM_LEDS_Y; n++)
    {
      for(int p = 0; p < NUM_LEDS_Z; p++)
      {
          leds[i][n][p] = CRGB::Green;
      }
    }
  }

  FastLED.show();
}

void Mode_2()
{
    const int center = 4; // Zentrum bei 0-7 → 4
    const CRGB color = CRGB::Blue; // Oder jede beliebige Farbe
    const int delayTime = 100; // Zeit zwischen den Schritten in ms

    // Expansionsphase (aus der Mitte nach außen)
    for (int r = 0; r <= 4; r++) 
    {
        for (int x = center - r; x <= center + r; x++) 
        {
            for (int y = center - r; y <= center + r; y++) 
            {
                for (int z = center - r; z <= center + r; z++) 
                {
                    if (x >= 0 && x < NUM_LEDS_X && y >= 0 && y < NUM_LEDS_Y && z >= 0 && z < NUM_LEDS_Z) 
                    {
                            leds[x][y][z] = color;
                    }
                }
            }
        }
        FastLED.show();
        delay(delayTime);
    }

    // Kontraktionsphase (zurück zur Mitte)
    for (int r = 4; r >= 0; r--) 
    {
        for (int x = center - r; x <= center + r; x++) 
        {
            for (int y = center - r; y <= center + r; y++) 
            {
                for (int z = center - r; z <= center + r; z++) 
                {
                    if (x >= 0 && x < NUM_LEDS_X && y >= 0 && y < NUM_LEDS_Y && z >= 0 && z < NUM_LEDS_Z) 
                    {
                        leds[x][y][z] = CRGB::Black;
                    }
                }
            }
        }
        FastLED.show();
        delay(delayTime);
    }   
}

void Mode_3()
{
    //init des Farbverlaufes für Mode 3
    const int colorSteps = 100;
    static CRGB colorPalette[colorSteps];
    static bool initialized = false;
    static int colorIndex = 0;
    CRGB color;
    const int delayTime = 100; // Zeit zwischen den Schritten in ms
    

     if (!initialized) {
        for (int i = 0; i < colorSteps; i++) {
            uint8_t hue = (i * 256L / colorSteps) % 256;
            colorPalette[i] = CHSV(hue, 255, 255);
        }
        initialized = true;
    }
    


    
   
    color = colorPalette[colorIndex];
    colorIndex = (colorIndex + 1);
    if(colorIndex>=colorSteps)
    {
        colorIndex=0;
    }

        for (int x = 0; x <= 7; x++) {
            for (int y = 0; y <=7; y++) {
                for (int z = 0;z <= 7; z++) {
                    if (x >= 0 && x < NUM_LEDS_X &&
                        y >= 0 && y < NUM_LEDS_Y &&
                        z >= 0 && z < NUM_LEDS_Z) {
                        leds[x][y][z] = color;
                    }
                }
            }
        }
        FastLED.show();
        
        

    
}