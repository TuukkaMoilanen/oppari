#include "esp_err.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "reporter.h"
#include "time_service.h"

#include "http_client_service.h"
#include "camera_capture.h"

static const char *TAG = "http_client_service";

#define HTTP_OUTPUT_BUFFER_MAX_LENGTH 256

char local_response_buffer[HTTP_OUTPUT_BUFFER_MAX_LENGTH + 1] = {0};
//char* url = SERVER_URL;
    esp_http_client_config_t config = {
    .host = SERVER_URL,
    .path = "/get",
    .query = "esp",
    .timeout_ms = -1,
    //.event_handler = _http_event_handler,
    .user_data = local_response_buffer,        // Pass address of local buffer to get response
    .disable_auto_redirect = true,
};

char * make_file_url(char * url, char * file_name)
{
    int length = snprintf( NULL, 0, "%s%s%s%s", "http://", url, "/" ,file_name);
    char* fullsendurl = malloc( length + 1 );
    snprintf( fullsendurl, length + 1, "%s%s%s%s", "http://", url, "/" ,file_name);
    ESP_LOGI(TAG,"created pic url: %s", fullsendurl);
    return fullsendurl;
}

esp_err_t check_http_response(const esp_http_client_handle_t * client)
{
    esp_err_t status = ESP_FAIL;

    char output_buffer[HTTP_OUTPUT_BUFFER_MAX_LENGTH + 1] = {0};
    int content_length = 0;

    content_length = esp_http_client_fetch_headers(* client);
    if (content_length < 0)
    {
        ESP_LOGE(TAG, "Failed to fetch HTTP headers !!");
    }
    else
    {
        ESP_LOGI(TAG, "HTTP header content length: %d", content_length);
        int data_length = esp_http_client_read_response(* client, output_buffer, HTTP_OUTPUT_BUFFER_MAX_LENGTH);
        if (data_length >= 0)
        {
            ESP_LOGI(TAG, "local response buffer: %s", output_buffer);
            status = ESP_OK;
        }
        else
        {
            ESP_LOGE(TAG, "Failed to read HTTP response !!");
        }
    }

    return status;
}

esp_err_t send_report(const report_struct * report)
{
    esp_err_t status = ESP_FAIL;

    esp_http_client_handle_t client = esp_http_client_init(&config);

    char * reporturl = make_file_url(SERVER_URL, report->report_name);
    int reportlength = (strlen(report->report_string) + 1) * sizeof(char);

    status = esp_http_client_set_url(client, reporturl);
    status = esp_http_client_set_method(client, HTTP_METHOD_PUT);
    status = esp_http_client_open(client, reportlength);
    status = esp_http_client_write(client, report->report_string, reportlength);
    status = check_http_response(&client);

    esp_http_client_close(client);

    free(reporturl);

    if(status != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to send report");
        return status;
    }

    char * picurl = make_file_url(SERVER_URL, report->report_pic_name);

    status = esp_http_client_set_url(client, picurl);
    status = esp_http_client_set_method(client, HTTP_METHOD_PUT);
    status = esp_http_client_open(client, report->report_pic.jpglen);
    status = esp_http_client_write(client, (char *)report->report_pic.jpg, report->report_pic.jpglen);
    status = check_http_response(&client);

    esp_http_client_close(client);

    free(picurl);

    if(status != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to send picture");
        return status;
    }
    
    //esp_http_client_cleanup(client);
    //free(jpg2send.jpg);

    return status;
}

void send_pics()
{
    char * picurl = make_file_url(SERVER_URL, "pic.jpg");
    jpg_struct jpg2send = take_pic();
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_url(client, picurl);
    esp_http_client_set_method(client, HTTP_METHOD_PUT);
    esp_http_client_open(client, jpg2send.jpglen);
    esp_http_client_write(client, (char *)jpg2send.jpg, jpg2send.jpglen);
    check_http_response(&client);
    esp_http_client_close(client);
    //esp_http_client_cleanup(client);
    free(jpg2send.jpg);
    free(picurl);
}