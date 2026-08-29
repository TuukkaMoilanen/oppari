#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "hal/i2c_types.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <sys/_types.h>

#define TAG "ambient_measurement"

#define TEST_I2C_PORT 0
#define I2C_CONTROLLER_SCL_IO 19
#define I2C_CONTROLLER_SDA_IO 20
#define I2C_CONTROLLER_FREQ_HZ 10000

#define SCC30DB_SENSOR_ADDR 0x44


i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;


esp_err_t setup_i2c_controller()
{
    esp_err_t status = ESP_FAIL;

    i2c_master_bus_config_t i2c_controller_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = TEST_I2C_PORT,
    .scl_io_num = I2C_CONTROLLER_SCL_IO,
    .sda_io_num = I2C_CONTROLLER_SDA_IO,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
    };

    status = i2c_new_master_bus(&i2c_controller_config, &bus_handle);

    //status = i2c_master_probe(bus_handle, SCC30DB_SENSOR_ADDR,100);

    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = I2C_DEVICE_ADDRESS_NOT_USED,
        .scl_speed_hz = I2C_CONTROLLER_FREQ_HZ,
        .scl_wait_us = 1000
    };

    status = i2c_master_bus_add_device(bus_handle,&device_config,&dev_handle);


    return status;
}

esp_err_t query_sensor_data(uint16_t * temp_value,  uint16_t * humd_value)
{
    esp_err_t status = ESP_FAIL;

    uint8_t write_msb = 0x24;
    uint8_t write_lsb = 0x00;

    uint8_t temp_data[3];
    uint8_t humd_data[3];

    uint8_t write_addr = (SCC30DB_SENSOR_ADDR << 1 | 0);
    i2c_operation_job_t write_op[] = {
        {.command = I2C_MASTER_CMD_START},
        {.command = I2C_MASTER_CMD_WRITE, .write = {.ack_check = false, .data = (const uint8_t *) &write_addr, .total_bytes = 1}},
        {.command = I2C_MASTER_CMD_WRITE, .write = {.ack_check = false, .data = (const uint8_t *) &write_msb, .total_bytes = 1}},
        {.command = I2C_MASTER_CMD_WRITE, .write = {.ack_check = false, .data = (const uint8_t *) &write_lsb, .total_bytes = 1}},
        {.command = I2C_MASTER_CMD_STOP}
    };

    uint8_t read_addr = (SCC30DB_SENSOR_ADDR << 1 | 1);
    i2c_operation_job_t read_op[] = {
        {.command = I2C_MASTER_CMD_START},
        {.command = I2C_MASTER_CMD_WRITE, .write ={.ack_check= false, .data = (uint8_t *) &read_addr, .total_bytes = 1}},
        {.command = I2C_MASTER_CMD_READ, .read = {.ack_value = I2C_ACK_VAL, .data = (uint8_t *) temp_data, .total_bytes = 3}},
        {.command = I2C_MASTER_CMD_READ, .read = {.ack_value = I2C_ACK_VAL, .data = (uint8_t *) humd_data, .total_bytes = 2}},
        {.command = I2C_MASTER_CMD_READ, .read = {.ack_value = I2C_NACK_VAL,.data = (uint8_t *) (humd_data + 2) , .total_bytes = 1}},
        {.command = I2C_MASTER_CMD_STOP}
    };

    status = i2c_master_execute_defined_operations(dev_handle, write_op, sizeof(write_op) / sizeof(i2c_operation_job_t), -1);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    status = i2c_master_execute_defined_operations(dev_handle, read_op, sizeof(read_op) / sizeof(i2c_operation_job_t), -1);

    ESP_LOGI(TAG, "temp data msb: %d temp data lsb = %d", temp_data[0], temp_data[1]);
    ESP_LOGI(TAG, "humd data msb: %d humd data lsb = %d", humd_data[0], humd_data[1]);

    * temp_value = ((uint16_t)temp_data[0] << 8) | temp_data[1];
    * humd_value = ((uint16_t)humd_data[0] << 8) | humd_data[1];

    return status;
}

esp_err_t measure_ambient_data(double * temperature, double * humidity)
{   
    esp_err_t status = ESP_FAIL;

    uint16_t temp_value; 
    uint16_t humd_value; 
    status = query_sensor_data(&temp_value, &humd_value);

    * temperature = (double)(-45 + 175 * temp_value / pow(2.0, 16.0) -1);
    * humidity = (double)(100* humd_value / pow(2.0, 16.0) -1);

    ESP_LOGI(TAG, "Current ambient temperature: %f °C", *temperature);
    ESP_LOGI(TAG, "Current ambient humidity: %f %%", *humidity);

    return status;
} 