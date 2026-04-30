#ifndef __TASK_NEO_BLINKY__
#define __TASK_NEO_BLINKY__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "global.h"

#define NEO_PIN     45
#define LED_COUNT   1 

void NeoLED_control(void *pvParameters);


#endif