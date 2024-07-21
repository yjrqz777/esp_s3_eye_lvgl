


SET(include_dir "." "include")

SET(SRC_FILE "my_wifi.c" "to_time.c" "myota.c")

idf_component_register(
    SRCS ${SRC_FILE}
    INCLUDE_DIRS ${include_dir}
    REQUIRES driver nvs_flash spi_flash esp_netif esp_event esp_wifi esp_http_client json squareline_ui esp_https_ota mbedtls
    )

set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)