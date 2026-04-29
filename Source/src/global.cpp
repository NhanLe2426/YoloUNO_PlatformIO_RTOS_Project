#include "global.h"

QueueHandle_t qSensorData = NULL;
SemaphoreHandle_t xSemLedSync = NULL;
SemaphoreHandle_t xBinarySemaphoreInternet = NULL;

// This func will be called in the setup() in main.cpp to allocate memory
void initGlobal_RTOS_Objects() {
    // Create a queue which can store one SensorData element
    // (use xQueueOverwrite to update to the latest version)
    qSensorData = xQueueCreate(1, sizeof(SensorData));

    // Create Binary Semaphore for LED
    xSemLedSync = xSemaphoreCreateBinary();

    // Create Semaphore Internet
    xBinarySemaphoreInternet = xSemaphoreCreateBinary();
}

// float glob_temperature = 0;
// float glob_humidity = 0;

// String WIFI_SSID;
// String WIFI_PASS;
// String CORE_IOT_TOKEN;
// String CORE_IOT_SERVER;
// String CORE_IOT_PORT;

// String ssid = "ESP32-YOUR NETWORK HERE!!!";
// String password = "12345678";
// String wifi_ssid = "abcde";
// String wifi_password = "123456789";
// boolean isWifiConnected = false;
// SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();