#include "esp_err.h"
#include "esp_littlefs.h"
#include "esp_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAG "fileman"

esp_vfs_littlefs_conf_t conf = 
{
    .base_path = "/littlefs",
    .partition_label = "littlefs",
    .format_if_mount_failed = true,
    .dont_mount = false,
};


esp_err_t init_fs()
{
    esp_err_t status = ESP_FAIL;

    status = esp_vfs_littlefs_register(&conf);

    size_t total = 0, used = 0;
    status = esp_littlefs_info(conf.partition_label, &total, &used);

    if(status != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed initialize filesystem: %s", esp_err_to_name(status));
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return status;
}

char * get_filepath(const char * filename)
{
    int length = snprintf( NULL, 0, "%s%s%s", conf.base_path , "/", filename);
    char* filepath = malloc( length + 1 );
    snprintf( filepath, length + 1, "%s%s%s", conf.base_path , "/", filename);
    ESP_LOGI(TAG,"filepath: %s", filepath);
    return filepath;
}

esp_err_t save_str_to_file(const char * filename, const char * string)
{
    esp_err_t status = ESP_FAIL;

    char * filepath = get_filepath(filename);

    FILE * file = fopen(filepath,"w");
    if (file == NULL) 
    {
        ESP_LOGE(TAG, "Failed to open file for writing");
        free(filepath);
        return status;
    }

    fprintf(file, "%s", string);
    fclose(file);
    status = ESP_OK;
    

    free(filepath);

    return status;
}

char * load_str_from_file(const char * filename)
{

    char * filepath = get_filepath(filename);
    FILE * file = fopen(filepath,"r");
    if (file == NULL) 
    {
        ESP_LOGE(TAG, "Failed to open file for reading");
        free(filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char * file_string = malloc(file_length + 1);

    int itr;
    for (itr = 0 ; itr < file_length; itr++) 
    {
        file_string[itr] = fgetc(file);
    }   
    file_string[itr] = '\0';
    
    fclose(file);

    ESP_LOGI(TAG, "Read from %s: %s", filepath, file_string);
    free(filepath);

    return file_string;
}