#pragma once

#include "camera_capture.h"
#include "esp_err.h"


typedef struct
{
    char * report_name;
    char * report_timestamp;
    char * report_string;
    char * report_pic_name;
    jpg_struct report_pic;
}report_struct;

esp_err_t gather_report(report_struct * report);