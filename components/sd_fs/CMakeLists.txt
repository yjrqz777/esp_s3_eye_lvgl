idf_component_register(
    SRCS "sd_fat_fs.c"
    INCLUDE_DIRS "include" 
    # INCLUDE_DIRS "../lvgl/src/extra/libs/gif"
    REQUIRES driver sdmmc fatfs
)

# file(GLOB_RECURSE SOURCES "./include/astro.c" "./include/xxxx.c" "./include/songti.c")