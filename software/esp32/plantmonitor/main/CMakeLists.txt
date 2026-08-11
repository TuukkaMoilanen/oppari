idf_component_register(SRCS "camera_capture.c" "main.c" "wifilove.c" "http_client_service.c" "time_service.c"
                        PRIV_INCLUDE_DIRS .
                        PRIV_REQUIRES nvs_flash esp_psram esp_http_client esp_timer esp_wifi
                        INCLUDE_DIRS ".")
