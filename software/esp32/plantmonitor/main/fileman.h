#pragma once

#include "esp_err.h"

esp_err_t init_fs();

esp_err_t save_str_to_file(const char * filename, const char * string);
char * load_str_from_file(const char * filename);
