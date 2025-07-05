#ifndef _LED_HPP_
#define _LED_HPP_

#include <FastLED.h>

#define NUM_LEDS_X 8
#define NUM_LEDS_Y 8
#define NUM_LEDS_Z 8

extern CRGB leds[NUM_LEDS_X][NUM_LEDS_Y][NUM_LEDS_Z];
extern bool Switch_On_Off;

void init_Leds();
//void start_Cube();
void update_Leds();
void Mode_1();
void Mode_2();
void Mode_3();
void Mode_4();
void Switch_Off();
void Switch_On();

#endif