idf_component_register(SRCS "blink_example_main.c"
                       INCLUDE_DIRS "."
                    #    INCLUDE_DIRS "./keys/include"
                       REQUIRES my_ui keys sd_fs main_cpp lvgl_esp32_drivers lvgl lvgl_porting 
                       )


# file(GLOB_RECURSE SOURCES "./include/astro.c" "./include/xxxx.c")
