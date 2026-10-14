#include "settingsman.h"
#include "esp_err.h"
#include "esp_log.h"
#include "fileman.h"
#include <stdlib.h>
#include <string.h>

#define TAG "settings_manager"

#define POWER_SAVE_SETTING_NAME "p_save_mode"
#define REPORT_INTERVAL_SETTING_NAME "report_int"
#define SOIL_MOISTURE_SETTING_NAME "soil_mt"


esp_err_t load_settings()
{
    esp_err_t status = ESP_FAIL;
    char * settings_str = load_str_from_file("settings.txt");
    if (settings_str == NULL)
    {
        ESP_LOGE(TAG, "Failed to load settings !!");
        settings.powersavemode = false;
        return status;
    }
    char delim[] = " ";
    char delim2[] = "\n";
    char * setting_name = strtok(settings_str, delim);

    while (setting_name != NULL)
    {
        if(strcmp(setting_name, POWER_SAVE_SETTING_NAME) == 0)
        {
            char * fax = strtok(NULL, delim2);
            (strcmp(fax, "true" ) == 0) ? settings.powersavemode = true : false;
            ESP_LOGI(TAG, "Loaded setting powersavemode = %s", settings.powersavemode ? "true" : "false");
        }
        else if(strcmp(setting_name, REPORT_INTERVAL_SETTING_NAME) == 0)
        {
            settings.report_interval = strtol(strtok(NULL, delim2), NULL, 10);
            ESP_LOGI(TAG, "Loaded setting report_interval = %d" , settings.report_interval);
        }
        else if(strcmp(setting_name, SOIL_MOISTURE_SETTING_NAME) == 0)
        {
            settings.soil_moisture_target = strtof(strtok(NULL,delim2), NULL);
            ESP_LOGI(TAG, "Loaded setting soil_moisture_target = %f" , settings.soil_moisture_target);
        }
        else
        {
            ESP_LOGE(TAG, "Unknown setting name: %s", setting_name);
            return status;
        }
        setting_name = strtok(NULL, delim);
    }

    free(setting_name);
    free(settings_str);

    status = ESP_OK;

    return status;
}