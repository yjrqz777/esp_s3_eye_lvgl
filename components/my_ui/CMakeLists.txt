idf_component_register(
    SRCS "test_ui.c"
    INCLUDE_DIRS "include" 
    # INCLUDE_DIRS "../lvgl/src/extra/libs/gif"
    REQUIRES lvgl 
)

file(GLOB_RECURSE SOURCES "./include/astro.c" "./include/xxxx.c")