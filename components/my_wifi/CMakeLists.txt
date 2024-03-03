


SET(include_dir "." "include")


idf_component_register(
    SRCS "my_wifi.c"
    INCLUDE_DIRS ${include_dir}
    REQUIRES driver nvs_flash spi_flash esp_netif esp_event esp_wifi esp_http_client json squareline_ui
    )

set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)