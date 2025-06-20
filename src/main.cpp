#if 1

#include "Display.hpp"
#include "Fan.hpp"
#include "Led.hpp"
#include "MotionSensor.hpp"
#include "TemperatureSensor.hpp"
#include "Website.hpp"
#include "Wifi.hpp"
#include "FastLED.h"
#include "FreeRTOSConfig.h"

#define NUM_LEDS_X 8
#define NUM_LEDS_Y 8
#define NUM_LEDS_Z 8
#define NUM_LEDS_Con 128
 
void startCubeTask(void *pvParameters)
{
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

        vTaskDelay(pdMS_TO_TICKS(10));  // 10 ms Pause pro Schleifendurchlauf
    }
    vTaskDelete(NULL);  // Task beenden, wenn fertig
}


void TaskLeds(void *pvParameters) 
{
  while(1)
  {
    update_Leds();
    vTaskDelay(pdMS_TO_TICKS(40));  // 10 ms Pause
  }
}

void TaskTemp(void *pvParameters) 
{
  while(1)
  {
    get_Temperature();
    show_Temperature();
    show_current_Mode();
    Fan_On_Off();
    vTaskDelay(pdMS_TO_TICKS(50));  // 500 ms Pause
  }  
}


void setup()
{
  Serial.begin(115200);
  init_Website();
  init_Leds();
  init_Display();
  init_TempSensor();
  init_Fan();

  xTaskCreate(startCubeTask, "Start Cube", 4096, NULL, 2, NULL);
  xTaskCreate(TaskLeds, "LED Task", 8192, NULL, 3, NULL);
  xTaskCreate(TaskTemp, "Temp Task", 8192, NULL, 1, NULL);
}

void loop()
{
  /**/
}

#endif

#if 0

#include "MotionSensor.hpp"
#include "Arduino.h"

void setup()
{
  Serial.begin(115200);
  init_Motion();
}

void loop()
{
    if(Person_detected() == true)
    {
      Serial.print("HIGH");
      Serial.printf("\n");
    }
    else if(Person_detected() == false)
    {
      Serial.print("LOW");
      Serial.printf("\n");
    }
    delay(500);
}

#endif