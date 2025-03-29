idf_component_register(SRCS "lv_port_indev.c" "lv_port_disp.c" "lv_port_fs.c"
                    INCLUDE_DIRS "include"
                    REQUIRES lvgl keys squareline_ui lvgl_esp32_drivers )