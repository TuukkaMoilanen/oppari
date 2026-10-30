#include "settingsman.h"
#include "esp_err.h"
#include "esp_log.h"
#include "fileman.h"
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define TAG "settings_manager"

#define SETTINGS_FILENAME "settings.json"

#define POWER_SAVE_SETTING_NAME "power_saving"
#define REPORT_INTERVAL_SETTING_NAME "report_interval"
#define WATERING_INTERVAL_SETTING_NAME "watering_check_interval"
#define SOIL_MOISTURE_SETTING_NAME "moisture_target"



esp_err_t parse_settings_json(const char * settings_str)
{
    esp_err_t status = ESP_FAIL;

    const cJSON * moisture_target;
    const cJSON * report_interval;
    const cJSON * watering_check_interval;
    const cJSON * power_saving;

    cJSON * settings_json = cJSON_Parse(settings_str);

    if (settings_json == NULL) 
    {
        const char * error_ptr = cJSON_GetErrorPtr() ;
        if(error_ptr != NULL)
        {
            ESP_LOGE(TAG, "JSON parse error, error_ptr: %s", error_ptr);
        }
        return status;    
    }

    power_saving = cJSON_GetObjectItemCaseSensitive(settings_json, POWER_SAVE_SETTING_NAME);
    if (!cJSON_IsBool(power_saving) || cJSON_IsNull(power_saving)) 
    {
        ESP_LOGW(TAG, "Power saving setting not set!! Defaulting to false.");
        settings.powersavemode = false;
    }
    
    cJSON_IsTrue(power_saving) == cJSON_True ? settings.powersavemode = true : false;

    report_interval = cJSON_GetObjectItemCaseSensitive(settings_json, REPORT_INTERVAL_SETTING_NAME);
    if (!cJSON_IsNumber(report_interval) || cJSON_IsNull(report_interval)) 
    {
        ESP_LOGE(TAG, "Report interval setting not set!!");
        return status;
    }

    settings.report_interval = report_interval->valueint;

    watering_check_interval = cJSON_GetObjectItemCaseSensitive(settings_json, WATERING_INTERVAL_SETTING_NAME);
    if (!cJSON_IsNumber(watering_check_interval) || cJSON_IsNull(watering_check_interval)) 
    {
        ESP_LOGE(TAG, "Watering interval setting not set!!");
        return status;
    }

    settings.watering_interval = watering_check_interval->valueint;

    moisture_target = cJSON_GetObjectItemCaseSensitive(settings_json, SOIL_MOISTURE_SETTING_NAME);
    if (!cJSON_IsNumber(moisture_target) || cJSON_IsNull(moisture_target)) 
    {
        ESP_LOGE(TAG, "Soil moisture target setting not set!!");
        return status;
    }

    settings.soil_moisture_target = moisture_target->valuedouble;

    cJSON_Delete(settings_json);

    status = ESP_OK;

    return status;
}

esp_err_t load_settings()
{
    esp_err_t status = ESP_FAIL;
    char * settings_str = load_str_from_file(SETTINGS_FILENAME);
    if (settings_str == NULL)
    {
        ESP_LOGE(TAG, "Failed to load settings !!");
        settings.powersavemode = false;
        return status;
    }

    status = parse_settings_json(settings_str);

    free(settings_str);

    status = ESP_OK;

    return status;
}