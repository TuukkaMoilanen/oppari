#include "soil_measurement.h"

#include "esp_adc/adc_oneshot.h"
#include "soc/adc_channel.h"
#include "esp_log.h"

#define TAG "soil_measurement"

esp_err_t setup_adc()
{
    esp_err_t status = ESP_FAIL;

    adc_oneshot_unit_handle_t adc1_handle;
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

    int raw_out;

    status = adc_oneshot_read(adc1_handle, ADC1_GPIO1_CHANNEL, &raw_out);
    ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, ADC1_GPIO1_CHANNEL, raw_out);

    return status;
}
