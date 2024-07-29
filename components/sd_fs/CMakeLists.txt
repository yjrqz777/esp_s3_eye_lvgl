idf_component_register(
    SRCS "sd_fat_fs.c" "MyTinyUSB_test.c"
    INCLUDE_DIRS "include" 
    # INCLUDE_DIRS "../lvgl/src/extra/libs/gif"
    REQUIRES driver sdmmc fatfs esp_tinyusb
)

# file(GLOB_RECURSE SOURCES "./include/astro.c" "./include/xxxx.c" "./include/songti.c")