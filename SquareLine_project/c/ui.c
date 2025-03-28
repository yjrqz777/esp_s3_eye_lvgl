// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
void ui_event_wifibtn(lv_event_t * e);
lv_obj_t * ui_wifibtn;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Roller1;
lv_obj_t * ui_date;
lv_obj_t * ui_time;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Container1;
void ui_event_backbtn2(lv_event_t * e);
lv_obj_t * ui_backbtn2;
lv_obj_t * ui_Label1;
void ui_event_nextbtn2(lv_event_t * e);
lv_obj_t * ui_nextbtn2;
lv_obj_t * ui_Label2;
void ui_event_scanbtn(lv_event_t * e);
lv_obj_t * ui_scanbtn;
lv_obj_t * ui_Label3;
void ui_event_Switch1(lv_event_t * e);
lv_obj_t * ui_Switch1;
lv_obj_t * ui_wifiname;
lv_obj_t * ui_Dropdown1;
lv_obj_t * ui_Switch2;
lv_obj_t * ui_conbtn;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label6;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Container2;
void ui_event_backbtn3(lv_event_t * e);
lv_obj_t * ui_backbtn3;
lv_obj_t * ui_Label7;
void ui_event_nextbtn3(lv_event_t * e);
lv_obj_t * ui_nextbtn3;
lv_obj_t * ui_Label8;
lv_obj_t * ui_scanbtn2;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Switch3;
lv_obj_t * ui_TextArea3;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_[1] = {&ui_img_333_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_wifibtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen2_screen_init);
    }
}
void ui_event_backbtn2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen1_screen_init);
    }
}
void ui_event_nextbtn2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen3_screen_init);
    }
}
void ui_event_scanbtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        test_wifi_sacn(e);
    }
}
void ui_event_Switch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        wifi_switch(e);
    }
}
void ui_event_backbtn3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen2_screen_init);
    }
}
void ui_event_nextbtn3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen1_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    ui_Screen3_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
