#include "camera_capture.h"


static const char *TAG = "camera_capture";

esp_err_t init_camera()
{
    //initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

jpg_struct take_pic()
{
    jpg_struct peggy;
    peggy.jpg = NULL;
    peggy.jpglen = 0;

    ESP_LOGI(TAG, "Taking picture...");
    camera_fb_t *pic = esp_camera_fb_get();
    ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);

    frame2jpg(pic, 90, &peggy.jpg, &peggy.jpglen);
    ESP_LOGI(TAG, "Picture jpegged! Jpg output buffer size: %zu", peggy.jpglen);
    esp_camera_fb_return(pic);
    return peggy;
}