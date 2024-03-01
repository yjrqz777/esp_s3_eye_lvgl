# SET(SOURCES screens/ui_Screen1.c
#     screens/ui_Screen3.c
#     ui.c
#     components/ui_comp_hook.c
#     ui_helpers.c
#     images/ui_img_333_png.c
#     fonts/ui_font_Font1.c)

# add_library(ui ${SOURCES})
file(GLOB_RECURSE SOURCES screens/ui_Screen1.c
    screens/ui_Screen3.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_333_png.c
    fonts/ui_font_Font1.c)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS "."
                    REQUIRES 
                    lvgl
                    lvgl_porting
                        )