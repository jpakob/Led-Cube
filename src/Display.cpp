#if 1

#include "Display.hpp"
#include "U8g2lib.h"
#include "TemperatureSensor.hpp"
#include "Website.hpp"
#include "Led.hpp"

#define DISPLAY_1_SDA 18 // PIN 18 for Diplay 1 Data 
#define DISPLAY_1_SCK 19 // PIN 19 for Display 1 CLock
#define DISPLAY_2_SDA 21 // PIN 21 for Diplay 2 Data 
#define DISPLAY_2_SCK 22 // PIN 22 for Display 2 CLock 

U8G2_SH1106_128X64_NONAME_F_SW_I2C display1(U8G2_R0, /* clock=*/ DISPLAY_1_SCK, /* data=*/ DISPLAY_1_SDA, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_SW_I2C display2(U8G2_R0, /* clock=*/ DISPLAY_2_SCK, /* data=*/ DISPLAY_2_SDA, /* reset=*/ U8X8_PIN_NONE);

void init_Display()
{
    display1.begin();
    display2.begin();

    display1.setFont(u8g2_font_logisoso32_tf);
    display2.setFont(u8g2_font_logisoso32_tf);

    display1.setDisplayRotation(U8G2_R2);  // 180° Rotation
    display2.setDisplayRotation(U8G2_R2);
}

void show_Temperature()
{   
    static unsigned long lastSwitchTime = 0;
    static bool showTemp = true;

    // Alle 1000 ms Anzeige wechseln
    if (millis() - lastSwitchTime >= 1000) 
    {
        showTemp = !showTemp;
        lastSwitchTime = millis();
    }

    display1.clearBuffer();
    display1.setCursor(10, 48);  // Je nach Font evtl. leicht anpassen

    if (showTemp) 
    {
        xSemaphoreTake(temperature_mutex, portMAX_DELAY);
        display1.print(temperature, 1);
        xSemaphoreGive(temperature_mutex);
        display1.print((char)176);  // Gradzeichen
        display1.print("C");
    } 
    else 
    {
        xSemaphoreTake(humidity_mutex, portMAX_DELAY);
        display1.print(humidity, 1);
        xSemaphoreGive(humidity_mutex);
        display1.print("%");
    }

    display1.sendBuffer();
}

void show_current_Mode()
{
    display2.clearBuffer();
    display2.setCursor(6, 48);
    xSemaphoreTake(current_Mode_Mutex, portMAX_DELAY);
    if(current_Mode == 1)
    {
        display2.print("Rocket");
    }
    if(current_Mode == 2)
    {
        display2.setCursor(12, 48);
        display2.print("Pulse");
    }  
    if(current_Mode == 3)
    {
        display2.print("Motion");
    }
    if(current_Mode == 4)
    {
        display2.print("Random");
    }
    if(current_Mode == 0 && Switch_On_Off == false)
    {
        display2.setCursor(30, 48);
        display2.print("Off");
    }
    if(current_Mode == 0 && Switch_On_Off == true)
    {
        display2.setCursor(35, 48);
        display2.print("On");
    }
    xSemaphoreGive(current_Mode_Mutex);        
    display2.sendBuffer();
}

#endif