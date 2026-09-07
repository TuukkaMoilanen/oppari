idf_component_register(SRCS "pump_control.c" "ambient_measurement.c" "soil_measurement.c" "camera_capture.c" "main.c" "wifilove.c" "http_client_service.c" "time_service.c"
                        PRIV_INCLUDE_DIRS .
                        PRIV_REQUIRES nvs_flash esp_psram esp_http_client esp_timer esp_wifi esp_adc esp_driver_i2c esp_driver_gpio
                        INCLUDE_DIRS ".")
