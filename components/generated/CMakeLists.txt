if(ESP_PLATFORM)

file(GLOB_RECURSE SOURCES *.c images/*.c  guider_fonts/*.c custom/*.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                                    guider_customer_fonts
                                    guider_fonts
                                    images
                                    custom
                                    # ../lvgl
                                    # ../lvgl/src/lv_core
                                    # ../lvgl/src/lv_draw
                                    # ../lvgl/src/lv_font
                                    # ../lvgl/src/lv_gpu
                                    # ../lvgl/src/lv_hal
                                    # ../lvgl/src/lv_misc
                                    # ../lvgl/src/lv_themes
                                    ../lvgl/src/widgets
                                    ../lvgl/src/extra/widgets/textprogress
                       REQUIRES lvgl)

else()
    message(FATAL_ERROR "LVGL LV examples: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()