#ifndef _WEBSITE_HPP_
#define _WEBSITE_HPP_

#include "FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

extern int current_Mode;
extern SemaphoreHandle_t current_Mode_Mutex;

void init_Website();
int get_current_Mode();
void set_current_Mode(int mode);


#endif