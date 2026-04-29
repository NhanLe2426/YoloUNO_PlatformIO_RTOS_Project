#include "global.h"

#include "task_led.h"
#include "temp_humi_monitor.h"

/* Reference to the initialization function in global.cpp */
extern void initGlobal_RTOS_Objects();

void setup()
{
    // Initialize Serial communication for debugging
    Serial.begin(115200);
    
    // Initialize RTOS communication objects.
    initGlobal_RTOS_Objects();

    // Create Sensor Task: Reading temp and humi from DHT20 sensor and sending it to queue
    xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 4096, NULL, 2, NULL);
    // Create LED Task: Receiving temperature data via Queue/Semaphore and adjusting the blink rate
    xTaskCreate(led_control, "Task LED Blink", 4096, NULL, 2, NULL);
}

void loop()
{
    /* In an RTOS-based project, the loop() function is typically left empty or  
     * used for very low-priority background maintenance.
     */
    vTaskDelay(pdMS_TO_TICKS(1000));
}