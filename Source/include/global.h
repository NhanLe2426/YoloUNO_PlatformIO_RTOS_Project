#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

// Sensor Data Structure
struct SensorData
{
    float temperature;
    float humidity;
};

// RTOS HANDLES
extern QueueHandle_t qSensorData;           // The queue contains sensor data
extern SemaphoreHandle_t xSemLedSync;       // Semaphore signal for Task 1 (LED)
extern SemaphoreHandle_t xBinarySemaphoreInternet;

#endif