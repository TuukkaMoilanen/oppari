#include "esp_http_client.h"
#include "esp_rtc_time.h"

#include "http_client_service.h"
#include "camera_capture.h"

static const char *TAG = "http_client_service";


char * make_pic_url( char * url)
{
    int time = esp_rtc_get_time_us();
    int length = snprintf( NULL, 0, "%s%s%s%d%s", "http://", url, "/pic" , time, ".jpg");
    char* fullsendurl = malloc( length + 1 );
    snprintf( fullsendurl, length + 1, "%s%s%s%d%s", "http://", url, "/pic" , time, ".jpg");
    ESP_LOGI(TAG,"created pic url: %s", fullsendurl);
    return fullsendurl;
}

void send_pics()
{
    char* url = SERVER_URL;
        esp_http_client_config_t config = {
        .host = url,
        .path = "/get",
        .query = "esp",
        .timeout_ms = -1,
        //.event_handler = _http_event_handler,
        //.user_data = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect = true,
    };


    char * picurl = make_pic_url(url);
    jpg_struct jpg2send = take_pic();
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_url(client, picurl);
    esp_http_client_set_method(client, HTTP_METHOD_PUT);
    esp_http_client_open(client, jpg2send.jpglen);
    esp_http_client_write(client, (char *)jpg2send.jpg, jpg2send.jpglen);
    esp_http_client_close(client);
    //esp_http_client_cleanup(client);
    free(picurl);
}