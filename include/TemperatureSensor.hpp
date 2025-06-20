#ifndef _TEMPERATURESENSOR_HPP_
#define _TEMPERATURESENSOR_HPP_

#include "FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

extern float temperature;
extern float humidity;

extern SemaphoreHandle_t temperature_mutex;
extern SemaphoreHandle_t humidity_mutex;

void init_TempSensor();
void get_Temperature();

#endif