#include "Display.hpp"
#include "U8g2lib.h"

#define DISPLAY_1_SDA 18 // PIN 18 for Diplay 1 Data 
#define DISPLAY_1_SCK 19 // PIN 19 for Display 1 CLock
#define DISPLAY_2_SDA 21 // PIN 21 for Diplay 2 Data 
#define DISPLAY_2_SCK 22 // PIN 22 for Display 2 CLock 

void init_Display()
{
    U8G2_SH1106_128X64_NONAME_F_SW_I2C display1(U8G2_R0, /* clock=*/ DISPLAY_1_SCK, /* data=*/ DISPLAY_1_SDA, /* reset=*/ U8X8_PIN_NONE);
    U8G2_SH1106_128X64_NONAME_F_SW_I2C display2(U8G2_R0, /* clock=*/ DISPLAY_2_SCK, /* data=*/ DISPLAY_2_SDA, /* reset=*/ U8X8_PIN_NONE);

    display1.begin();
    display2.begin();

    display1.setFont(u8g2_font_logisoso32_tf);
    display2.setFont(u8g2_font_logisoso32_tf);
}

void show_Temperature(int Temperature)
{

}

void show_current_Mode(int Mode)
{
    
}