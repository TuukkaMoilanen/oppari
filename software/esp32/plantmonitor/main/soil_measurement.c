#include "soil_measurement.h"

#include "esp_adc/adc_oneshot.h"
#include "soc/adc_channel.h"
#include "esp_log.h"
#include <math.h>

#define TAG "soil_measurement"

esp_err_t setup_adc()
{
    esp_err_t status = ESP_FAIL;

    adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    status = adc_oneshot_new_unit(&init_config1, &adc1_handle);

    adc_oneshot_chan_cfg_t config = {
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_12,
    };
    status = adc_oneshot_config_channel(adc1_handle, ADC1_GPIO1_CHANNEL, &config);

    return status;
}

int read_raw()
{
    int raw_out;

    adc_oneshot_read(adc1_handle, ADC1_GPIO1_CHANNEL, &raw_out);
    ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, ADC1_GPIO1_CHANNEL, raw_out);
    return raw_out;
}

double measure_soil_moisture()
{
    double soil_moisture_percentage;
    int current_moist = read_raw();

    if (current_moist < max_moisture)
    {
        ESP_LOGI(TAG, "Moisture above maximum, clamping value.");
        current_moist = max_moisture;
    }
    else if (current_moist > min_moisture)
    {
        ESP_LOGI(TAG, "Moisture below minimum, clamping value.");
        current_moist = min_moisture;
    }

    soil_moisture_percentage = fabs((double)(current_moist - max_moisture)/min_max_moisture * 100.0 - 100.0);
    ESP_LOGI(TAG, "Current soil moisture %f%%", soil_moisture_percentage);

    return soil_moisture_percentage;
}