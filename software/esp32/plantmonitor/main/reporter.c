#include "reporter.h"
#include "camera_capture.h"
#include "esp_err.h"
#include "soil_measurement.h"
#include "ambient_measurement.h"
#include "time_service.h"
#include <string.h>

#define TAG "reporter"

enum file_type
{
    txt,
    jpg
};

char * make_file_name(const char * timestamp, enum file_type type)
{
    char name[10];
    char extension[10];
    switch (type) 
    {
        case jpg:
        {
            strncpy(name, "pic", strlen("pic") + 1);
            strncpy(extension, ".jpg", strlen(".jpg") + 1);
            break;
        }
        case txt:
        {
            strncpy(name, "report", strlen("report") + 1);
            strncpy(extension, ".txt", strlen(".txt") + 1);
            break;
        }
    }

    int length = snprintf( NULL, 0, "%s%s%s", name , timestamp, extension);
    char* file_name = malloc( length + 1 );
    snprintf( file_name, length + 1, "%s%s%s", name , timestamp, extension);
    ESP_LOGI(TAG,"created file name: %s", file_name);
    return file_name;
}


esp_err_t gather_report(report_struct *report)
{
    esp_err_t status = ESP_FAIL;

    double soil_moisture;
    double ambient_temperature;
    double ambient_humidity;

    report->report_timestamp = get_current_time_str();

    soil_moisture = measure_soil_moisture();

    status = measure_ambient_data(&ambient_temperature, &ambient_humidity);

    report->report_pic = take_pic();

    report->report_pic_name = make_file_name(report->report_timestamp, jpg);

    report->report_name = make_file_name(report->report_timestamp, txt);


    int length = snprintf( NULL, 0, "%s%s%s%s%f%s%s%f%s%s%f%s",
                            "associated picture: ", report->report_pic_name, "\n", 
                            "soil moisture: ", soil_moisture, "\n" ,
                            "ambient temperature: ", ambient_temperature, "\n",
                            "ambient humidity: ", ambient_humidity, "\n");
    report->report_string = malloc( length + 1 );
    snprintf(report->report_string, length + 1, "%s%s%s%s%f%s%s%f%s%s%f%s",
                            "associated picture: ", report->report_pic_name, "\n", 
                            "soil moisture: ", soil_moisture, "\n" ,
                            "ambient temperature: ", ambient_temperature, "\n",
                            "ambient humidity: ", ambient_humidity, "\n");
    ESP_LOGI(TAG,"created report string: %s", report->report_string);

    return status;
}