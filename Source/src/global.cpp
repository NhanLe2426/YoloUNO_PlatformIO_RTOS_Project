#include "global.h"

QueueHandle_t qSensorData = NULL;
SemaphoreHandle_t xSemLedSync = NULL;
SemaphoreHandle_t xSemNeoSync = NULL;
SemaphoreHandle_t xSemLCDSync = NULL;
SemaphoreHandle_t xMutexI2C = NULL;
SemaphoreHandle_t xBinarySemaphoreInternet = NULL;

// This func will be called in the setup() in main.cpp to allocate memory
void initGlobal_RTOS_Objects() {
    // Create a queue which can store one SensorData element
    // (use xQueueOverwrite to update to the latest version)
    qSensorData = xQueueCreate(1, sizeof(SensorData));

    // Create Binary Semaphore for LED synchronization (Task 1)
    xSemLedSync = xSemaphoreCreateBinary();

    // Create Binary Semaphore for NeoPixel synchronization (Task 2)
    xSemNeoSync = xSemaphoreCreateBinary();

    // Create new RTOS objects for Task 3 (Binary Semaphore & Mutex Semaphore)
    xSemLCDSync = xSemaphoreCreateBinary();
    xMutexI2C = xSemaphoreCreateMutex();

    // Create Semaphore for Internet
    xBinarySemaphoreInternet = xSemaphoreCreateBinary();
}