SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    screens/ui_Screen3.c
    screens/ui_Screen4.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_333_png.c
    fonts/ui_font_songtibpp4.c)

    idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS "."
    REQUIRES 
    lvgl
    lvgl_porting
    my_wifi
    my_ui
        )
