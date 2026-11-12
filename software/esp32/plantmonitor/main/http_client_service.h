#pragma once

#include "esp_err.h"
#include "reporter.h"


esp_err_t send_report(const report_struct * report);
void send_pics();