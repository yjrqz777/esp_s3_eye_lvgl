idf_component_register(SRCS "blink_example_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES my_ui lvgl_esp32_drivers lvgl lvgl_porting
                       )
