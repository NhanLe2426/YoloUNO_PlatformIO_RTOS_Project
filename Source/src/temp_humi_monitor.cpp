#include "temp_humi_monitor.h"

/* Access global RTOS handles defined in global.h */
extern QueueHandle_t qSensorData;
extern SemaphoreHandle_t xSemLedSync;
extern SemaphoreHandle_t xSemNeoSync;
extern SemaphoreHandle_t xSemLCDSync;
extern SemaphoreHandle_t xMutexI2C;

DHT20 dht20;    // Initialize the DHT20 sensor object

void temp_humi_monitor(void *pvParameters){
    // Initialize the I2C bus with specific SDA and SCL pins
    Wire.begin(SDA_PIN, SCL_PIN);
    dht20.begin();
    
    SensorData currentData;         // Local variable

    while (1) {
        // TAKE I2C MUTEX BEFORE READING SENSOR
        if (xSemaphoreTake(xMutexI2C, portMAX_DELAY) == pdTRUE) {
            dht20.read();
            // RELEASE I2C MUTEX IMMEDIATELY AFTER READING
            xSemaphoreGive(xMutexI2C);
        }
        
        // Reading temperature in Celsius
        float temperature = dht20.getTemperature();
        // Reading humidity
        float humidity = dht20.getHumidity();

        // Check if any reads failed and exit early
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("[ERROR:] Failed to read from DHT sensor!");
            // temperature = humidity =  -1;
            // return;
        } else {
            // Passing data into struct
            currentData.temperature = temperature;
            currentData.humidity = humidity;

            // Push data into queue (Use xQueueOverwrite() to always keep the most up-to-date data).
            xQueueOverwrite(qSensorData, &currentData);

            // Release the Semaphore signals to LED that a temperature update has been received.
            xSemaphoreGive(xSemLedSync);

            // Release the Semaphore signals to NeoPixel LED that a humidity update has been received
            xSemaphoreGive(xSemNeoSync);

            // Release the Semaphore signals to LCD that new data is available
            xSemaphoreGive(xSemLCDSync);

            // Print the results
            Serial.printf("Humidity: %.2f%%  Temperature: %.2f°C\n", humidity, temperature);
        }

        // Read the sensor every 5s
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}