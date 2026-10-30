#pragma once

#include "esp_err.h"

typedef struct
{
    bool powersavemode;
    int report_interval;
    int watering_interval;
    double soil_moisture_target;
}settings_struct;

static settings_struct settings;

esp_err_t load_settings();