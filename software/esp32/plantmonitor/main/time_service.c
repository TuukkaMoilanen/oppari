#include "time_service.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_netif_sntp.h"
#include "esp_sntp.h"
#include <stdlib.h>

#define TAG "time_service"

esp_err_t sync_time()
{
    esp_err_t status = ESP_FAIL;
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    config.start = false;
    esp_netif_sntp_init(&config);

    esp_netif_sntp_start();


    bool systemtimeupdated = false;
    while (!systemtimeupdated) 
    {
        if(esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK)
        {
            ESP_LOGI(TAG, "Failed to update system time !!");
            status = ESP_FAIL;
            continue;
        }
        else
        {
            systemtimeupdated = true;
            status = ESP_OK;
        }
    }
    
    setenv("TZ", "UTC0", 1);
    tzset();

    return status;
}

char* get_current_time_str()
{
    int dateTimeStrLength = 21;
    time_t now;
    char * time_str = malloc(dateTimeStrLength * sizeof(char));
    struct tm timeinfo;

    time(&now);

    localtime_r(&now, &timeinfo);
    strftime(time_str, dateTimeStrLength, "%Y.%m.%d-%H.%M.%S", &timeinfo);
    ESP_LOGI(TAG, "The current system date/time is: %s", time_str);

    return time_str;
}

