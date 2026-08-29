#pragma once

#include "esp_err.h"


esp_err_t setup_i2c_controller();
esp_err_t measure_ambient_data(double * temperature, double * humidity);