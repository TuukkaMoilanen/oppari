#pragma once

#include "esp_err.h"
#include "reporter.h"
#define SERVER_URL "192.168.101.105:8000"

esp_err_t send_report(const report_struct * report);
void send_pics();