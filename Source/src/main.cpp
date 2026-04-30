#include "global.h"

#include "task_led.h"
#include "task_neo_led.h"
#include "temp_humi_monitor.h"
// #include "mainserver.h"
// #include "tinyml.h"
#include "coreiot.h"

// include task
#include "task_check_info.h"
#include "task_toogle_boot.h"
#include "task_wifi.h"
#include "task_webserver.h"
#include "task_core_iot.h"

/* Reference to the initialization function in global.cpp */
extern void initGlobal_RTOS_Objects();

void setup()
{
    // Initialize Serial communication for debugging
    Serial.begin(115200);
    
    // Initialize RTOS communication objects.
    initGlobal_RTOS_Objects();
    
    check_info_File(0);

    // Create Sensor Task: Reading temp and humi from DHT20 sensor and sending it to queue
    xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 4096, NULL, 2, NULL);
    // Create LED Task: Receiving temperature data via Queue/Semaphore and adjusting the blink rate
    xTaskCreate(LED_control, "Task LED Blink", 4096, NULL, 2, NULL);
    // Create Neo LED Task: Receiving humidity data via Queue/Semaphore and adjustint the color
    xTaskCreate(NeoLED_control, "Task NEO LED", 4096, NULL, 2, NULL);

    // xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
    // xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
    // xTaskCreate(main_server_task, "Task Main Server" ,8192  ,NULL  ,2 , NULL);
    // xTaskCreate( tiny_ml_task, "Tiny ML Task" ,2048  ,NULL  ,2 , NULL);
    // xTaskCreate(coreiot_task, "CoreIOT Task" ,4096  ,NULL  ,2 , NULL);
    // xTaskCreate(Task_Toogle_BOOT, "Task_Toogle_BOOT", 4096, NULL, 2, NULL);
}

void loop()
{
    if (check_info_File(1))
    {
        if (!Wifi_reconnect())
        {
            Webserver_stop();
        }
        else
        {
            //CORE_IOT_reconnect();
        }
    }
    Webserver_reconnect();
    /* In an RTOS-based project, the loop() function is typically left empty or  
     * used for very low-priority background maintenance.
     */
    vTaskDelay(pdMS_TO_TICKS(1000));
}