#include "task_led.h"

/* Access global RTOS handles defined in global.h */
extern QueueHandle_t qSensorData;
extern SemaphoreHandle_t xSemLedSync;

void LEDcontrol(void *pvParameters){
    // Initialize the LED pin as an output mode
    pinMode(LED_GPIO, OUTPUT);

    int blink_delay = 1000;       // Default blinking interval
    bool ledState = false;

    SensorData localData;         // Local variable

    while (1){
        /* Check if the Sensor Task has released the semaphore (new data available)
         * Timeout is 0 to ensure the blinking loop is never blocked
         * If there is no signal, skip and move on to the LED blinking behaviors
         */ 
        if (xSemaphoreTake(xSemLedSync, 0) == pdTRUE) {
            /* If a signal is received, read the temperature from the queue using xQueuePeek()
             * (xQueuePeek() helps read data WITHOUT losing data in the queue)
             */ 
            if (xQueuePeek(qSensorData, &localData, 0) == pdPASS) {
                float temp = localData.temperature;

                /* Define 3 different behaviors based on temperature conditions */
                
                // Condition 1: Cold (Temperature < 28°C) => Blink twice as slow
                if (temp < 28.0) {
                    blink_delay = 2000;
                }
                // Condition 2: Normal (28°C to 32°C) => Blink every 1s
                else if (temp >= 28.0 && temp <= 32.0) {
                    blink_delay = 1000;
                } 
                // Condition 3: Hot (Temperature > 32°C) => Blink twice as fast
                else {
                    blink_delay = 500;
                }
            }
        }

        // Toggle the LED hardware state
        ledState = !ledState;
        if (!ledState) {
            digitalWrite(LED_GPIO, HIGH);   // Turn LED ON
        } else {
            digitalWrite(LED_GPIO, LOW);    // Turn LED OFF
        }

        // Block the task for the calculated duration to control blink interval
        vTaskDelay(pdMS_TO_TICKS(blink_delay));
    }
}