idf_component_register(
    SRCS "MyTinyUSB.c"
    INCLUDE_DIRS "include" 
    REQUIRES sd_fs
)

# file(GLOB_RECURSE SOURCES "./include/astro.c" "./include/xxxx.c" "./include/songti.c")