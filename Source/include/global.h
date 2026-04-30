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
// extern float glob_temperature;
// extern float glob_humidity;

// extern String WIFI_SSID;
// extern String WIFI_PASS;
// extern String CORE_IOT_TOKEN;
// extern String CORE_IOT_SERVER;
// extern String CORE_IOT_PORT;

// extern boolean isWifiConnected;
// extern SemaphoreHandle_t xBinarySemaphoreInternet;

// RTOS HANDLES
extern QueueHandle_t qSensorData;           // The queue contains sensor data
extern SemaphoreHandle_t xSemLedSync;       // Semaphore signal for Task 1 (LED)
extern SemaphoreHandle_t xSemNeoSync;       // Semaphore signal for Task 2 (NeoPixel)
extern SemaphoreHandle_t xBinarySemaphoreInternet;
#endif