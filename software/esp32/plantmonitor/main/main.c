#include <stdio.h>

#include "esp_err.h"

#include "esp_log.h"
#include "reporter.h"
#include "time_service.h"
#include "wifilove.h"
#include "wificreds.h"
#include "camera_capture.h"
#include "http_client_service.h"
#include "soil_measurement.h"
#include "ambient_measurement.h"
#include "pump_control.h"

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

    // if(setup_pump_control() != ESP_OK) 
    // {
    //     ESP_LOGE(TAG, "Failed to setup pump control !!!");
    //     return;
    // }


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
        //enable_pump_for_ms(3000);
        report_struct report;
        gather_report(&report);
        send_report(&report);
        free(report.report_pic.jpg);
        
        vTaskDelay(20000 / portTICK_PERIOD_MS);
    }
}
