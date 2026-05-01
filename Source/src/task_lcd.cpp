#include "global.h"
#include "task_lcd.h"

/* Access global RTOS handles defined in global.h */
extern QueueHandle_t qSensorData;
extern SemaphoreHandle_t xSemLCDSync;
extern SemaphoreHandle_t xMutexI2C;

// Initialize the LCD object (I2C Address: 33, Columns: 16, Rows: 2)
LiquidCrystal_I2C lcd(33, 16, 2);

void displayLCD(void *pvParameters) {
    /* I2C MUTEX PROTECTION: Accquire the I2C bus lock before Initialize the LCD hardware
     * This prevents collisions if another task is currently using the I2C bus (e.g., Sensor Task)
     */
    if (xSemaphoreTake(xMutexI2C, portMAX_DELAY) == pdTRUE) {
        lcd.begin();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("System Ready...");
        // Always release the Mutex after finishing I2C operations
        xSemaphoreGive(xMutexI2C);
    }

    SensorData localData;           // Local Variable

    while (1) {
        /* Wait indefinitely for the Sensor Task to release the semaphore.
         * This task will sleep until new sensor data is available.
         */
        if (xSemaphoreTake(xSemLCDSync, portMAX_DELAY) == pdTRUE) {
            // Peek the latest sensor data from the queue
            float temp = localData.temperature;
            float humi = localData.humidity;

            String stateMsg = "";

            /* Define 3 different display states (NORMAL, WARNING, CRITICAL) */

            // Condition 1: Critical (Extremely hot or highly humid)
            if (temp > 32.0 || humi > 60.0) {
                stateMsg = "CRITICAL!";
            }
            // Condition 2: Warning (Hot or dry)
            else if ((temp >= 28.0 && temp <= 32.0) || (humi >= 40.0 && humi <= 60.0)) {
                stateMsg = "WARNING! ";
            } 
            // Condition 3: Normal
            else {
                stateMsg = "NORMAL   ";
            }

            // I2C MUTEX PROTECTING: Safely update data to the LCD
            if (xSemaphoreTake(xMutexI2C, portMAX_DELAY) == pdTRUE) {
                // Clear previous screen to prevent text overlapping
                lcd.clear();
                
                // Row 0: Display the system state
                lcd.setCursor(0, 0);
                lcd.print("STATE: ");
                lcd.print(stateMsg);

                // Row 1: Display Temperature and Humidity values
                lcd.setCursor(0, 1);
                lcd.print("T:");
                lcd.print(temp, 1);     // Print with 1 decimal place
                lcd.print("C H:");
                lcd.print(humi, 1);
                lcd.print("%");

                // Release the I2C Mutex so the Sensor Task can read again
                xSemaphoreGive(xMutexI2C);
            }
        }
    }
}