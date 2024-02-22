#include "test_ui.h"
#include "lvgl.h"
#include "esp_log.h"
#include "lv_port_indev.h"
#include "xxxx.c"
#include "astro.c"
// #include "lv_gif.h"
// #include "lv_img.h"
#include "songti.c"
static const char *TAG = "test_ui";


void show_gif(void)
{
    lv_obj_t * screen = lv_scr_act();
    LV_IMG_DECLARE(astro);
    lv_obj_t* obj_gif = lv_gif_create(screen);
    lv_gif_set_src(obj_gif, &astro);
    // lv_obj_align(obj_gif, LV_ALIGN_BOTTOM_RIGHT, 10, 10);
    // lv_obj_set_pos(obj_gif, 40, 40);
    lv_obj_center(obj_gif);
    ESP_LOGW(TAG,"show_gif called\n");
}


void show_button(void)
{
    lv_obj_t * screen = lv_scr_act();
    lv_obj_t * obj_button = lv_btn_create(screen);
    lv_obj_t * label = lv_label_create(obj_button);
    
    lv_label_set_text(label, "Button");
    lv_obj_align(obj_button, LV_ALIGN_CENTER, 0, 40);
    // lv_obj_add_event_cb(obj_button, button_event_cb, LV_EVENT_CLICKED, NULL);
}
void show_text(void)
{
    LV_FONT_DECLARE(songti);

    static lv_style_t style1;
    lv_style_init(&style1);
    lv_style_set_text_font(&style1, &songti);
    lv_style_set_text_color(&style1, lv_palette_main(LV_PALETTE_RED));
    lv_obj_t * screen = lv_scr_act();
    lv_obj_t* label = lv_label_create(screen);
    lv_obj_add_style(label,&style1,0);
    lv_obj_set_pos(label,0,10);
    lv_label_set_text(label,"我在自学LVGL，哈哈哈哈!!!.");

    lv_obj_set_width(label,230);    
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);
 
        LV_LOG_USER("%s was pressed\n", txt);
    }
}
 
 
 
static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
                                                                  "6", "7", "8", "9", "0", "\n",
                                                                  "Action1", "Action2", ""};


void test_main(void)
{

    // lv_obj_t * obj = lv_obj_create(screen);
    // lv_obj_set_pos(obj, 10, 10);
    // lv_obj_t* obj_img = lv_img_create(screen);
    // lv_img_set_src(obj_img, &xxxx);
    // lv_obj_align(obj_img,LV_ALIGN_BOTTOM_LEFT,10,-10);

    // show_gif();
    // show_button();
    // show_text();
    lv_group_t *group = lv_group_create();

    lv_indev_set_group(indev_keypad, group);
 
    


    lv_obj_t * btnm1 = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_btnmatrix_set_btn_width(btnm1, 10, 1);        /*Make "Action1" twice as wide as "Action2"*/
    lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);

    lv_group_add_obj(group ,btnm1);
    ESP_LOGW(TAG,"test_main called\n");

}