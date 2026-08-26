#pragma once

#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"

esp_err_t setup_adc();
double measure_soil_moisture();

//moisture sensor calibration values (maybe different between sensors, should probably test)
static const int max_moisture = 1500;
static const int min_moisture = 3000;

static const int min_max_moisture = min_moisture - max_moisture;

static adc_oneshot_unit_handle_t adc1_handle;