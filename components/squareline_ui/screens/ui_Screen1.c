// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image3 = lv_img_create(ui_Screen1);
lv_img_set_src(ui_Image3, &ui_img_333_png);
lv_obj_set_width( ui_Image3, LV_SIZE_CONTENT);  /// 240
lv_obj_set_height( ui_Image3, LV_SIZE_CONTENT);   /// 240
lv_obj_set_align( ui_Image3, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image3, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Button1 = lv_btn_create(ui_Screen1);
lv_obj_set_width( ui_Button1, 100);
lv_obj_set_height( ui_Button1, 50);
lv_obj_add_flag( ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0x0EEA1E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button1, 200, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label1 = lv_label_create(ui_Button1);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label1,"WIFI");
lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label1, &ui_font_Font1, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Roller1 = lv_roller_create(ui_Screen1);
lv_roller_set_options( ui_Roller1, "Option 1\nOption 2\nOption 3\nOption 1\nOption 2\nOption 3", LV_ROLLER_MODE_INFINITE );
lv_obj_set_height( ui_Roller1, 175);
lv_obj_set_width( ui_Roller1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_Roller1, -72 );
lv_obj_set_y( ui_Roller1, 25 );
lv_obj_set_align( ui_Roller1, LV_ALIGN_CENTER );
lv_obj_set_style_bg_color(ui_Roller1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Roller1, 20, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

}