#include "task_neo_led.h"

/* Access global RTOS handles defined in global.h */
extern QueueHandle_t qSensorData;
extern SemaphoreHandle_t xSemNeoSync;

void NeoLED_control(void *pvParameters){
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();

    // Set all pixels to off to start
    strip.clear();
    strip.show();

    SensorData localData;           // Local variable

    while (1) {                          
        /* Wait indefinitely for the Sensor Task to release the semaphore.
         * This task will sleep until new sensor data is available.
         */
        if (xSemaphoreTake(xSemNeoSync, portMAX_DELAY) == pdTRUE) {
            // Peek the humidity value from the queue without removing it
            if (xQueuePeek(qSensorData, &localData, 0) == pdPASS) {
                float humi = localData.humidity;

                /* Define 3 different color patterns based on humidity levels */

                // Condition 1: Dry (Humidity < 40%) => Red Color
                if (humi < 40.0) {
                    strip.setPixelColor(0, strip.Color(255, 0, 0));
                }
                // Condition 2: Comfortable (40% to 60%) => Green Color
                else if (humi >= 40.0 && humi <= 60.0) {
                    strip.setPixelColor(0, strip.Color(0, 255, 0));
                }
                // Condition 3: Humid (Humidity > 60%) => Blue Color
                else {
                    strip.setPixelColor(0, strip.Color(0, 0, 255));
                }

                // Update the strip with the new color
                strip.show();
            }
        }
    }
}