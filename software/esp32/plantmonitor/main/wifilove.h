#pragma once

#include "esp_err.h"


esp_err_t wifiInit(void);

esp_err_t wifiConnect(char* wifi_ssid, char* wifi_password);