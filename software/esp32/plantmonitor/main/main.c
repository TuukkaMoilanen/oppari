#include <stdio.h>

#include "esp_err.h"

#include "time_service.h"
#include "wifilove.h"
#include "wificreds.h"
#include "camera_capture.h"
#include "http_client_service.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//temporary test main with wifi, http client and camera testing functionality.
void app_main(void)
{
    if(init_camera() != ESP_OK) 
    {
        return;
    }

    if( wifiInit() != ESP_OK)
    {
        return;
    }

    if( wifiConnect(SSID, wifiPass) != ESP_OK)
    {
        return;
    }

    if(sync_time() != ESP_OK)
    {
        return;
    }

    while (1)
    {
        send_pics();
        
        vTaskDelay(20000 / portTICK_RATE_MS);
    }
}
