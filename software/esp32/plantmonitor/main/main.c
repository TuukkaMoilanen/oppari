#include <stdio.h>

#include "esp_err.h"

#include "esp_log.h"
#include "time_service.h"
#include "wifilove.h"
#include "wificreds.h"
#include "camera_capture.h"
#include "http_client_service.h"
#include "soil_measurement.h"
#include "ambient_measurement.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "main"

//temporary test main with wifi, http client and camera testing functionality.
void app_main(void)
{
    if(setup_adc() != ESP_OK) 
    {
        ESP_LOGE(TAG, "Failed to setup adc !!!");
        return;
    }
    
    if(setup_i2c_controller() != ESP_OK) 
    {
        ESP_LOGE(TAG, "Failed to setup i2c controller !!!");
        return;
    }

    if(init_camera() != ESP_OK) 
    {
        ESP_LOGE(TAG, "Failed to initialize camera !!!");
        return;
    }

    if( wifiInit() != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize WiFi !!!");
        return;
    }

    if( wifiConnect(SSID, wifiPass) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to connect WiFi !!!");
        return;
    }

    if(sync_time() != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to sync time !!!");
        return;
    }

    while (1)
    {
        send_pics();

        double temperature;
        double humidity;
        measure_ambient_data(&temperature, &humidity);
        measure_soil_moisture();
        
        vTaskDelay(20000 / portTICK_RATE_MS);
    }
}
