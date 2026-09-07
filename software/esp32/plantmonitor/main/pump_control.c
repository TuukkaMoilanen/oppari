#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "hal/gpio_types.h"

#define TAG "pump_control"

#define PUMP_GPIO 2

esp_err_t setup_pump_control()
{
    esp_err_t status = ESP_FAIL;

    gpio_config_t gpioconfig = 
    {
    .pin_bit_mask = (1ULL << PUMP_GPIO),
    .mode = GPIO_MODE_OUTPUT,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .intr_type = GPIO_INTR_DISABLE,
    };

    status = gpio_config(&gpioconfig);
    status = gpio_set_drive_capability(PUMP_GPIO, GPIO_DRIVE_CAP_3);

    return status;
};

esp_err_t enable_pump_for_ms(int ms)
{
    esp_err_t status = ESP_FAIL;

    ESP_LOGI(TAG, "Enabling pump for %d ms !", ms);

    status = gpio_set_level(PUMP_GPIO, 1);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to ENABLE pump !!!");
        return status;
    }

    vTaskDelay(ms / portTICK_PERIOD_MS);

    status = gpio_set_level(PUMP_GPIO, 0);
    if (status != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to DISABLE pump !!!");
        return status;
    }

    return status;
}