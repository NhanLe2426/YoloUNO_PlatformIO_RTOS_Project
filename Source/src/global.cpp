#include "global.h"

QueueHandle_t qSensorData = NULL;
SemaphoreHandle_t xSemLedSync = NULL;
SemaphoreHandle_t xBinarySemaphoreInternet = NULL;

// This func will be called in the setup() in main.cpp to allocate memory
void initGlobal_RTOS_Objects() {
    // Create a queue which can store one SensorData element
    // (use xQueueOverwrite to update to the latest version)
    qSensorData = xQueueCreate(1, sizeof(SensorData));

    // Create Binary Semaphore for LED synchronization
    xSemLedSync = xSemaphoreCreateBinary();

    // Create Binary Semaphore for NeoPixel synchronization

    // Create Semaphore Internet
    xBinarySemaphoreInternet = xSemaphoreCreateBinary();
}