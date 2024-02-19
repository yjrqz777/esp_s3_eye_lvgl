#include "test_ui.h"
#include "lvgl.h"
#include "esp_log.h"
#include "xxxx.c"
#include "astro.c"
// #include "lv_gif.h"
// #include "lv_img.h"
static const char *TAG = "test_ui";
void test_main(void)
{
    lv_obj_t * screen = lv_scr_act();

    // lv_obj_t * obj = lv_obj_create(screen);
    // lv_obj_set_pos(obj, 10, 10);
    LV_IMG_DECLARE(astro);

    // lv_obj_t* obj_img = lv_img_create(screen);
    // lv_img_set_src(obj_img, &xxxx);
    // lv_obj_align(obj_img,LV_ALIGN_BOTTOM_LEFT,10,-10);


    lv_obj_t* obj_gif = lv_gif_create(screen);
    lv_gif_set_src(obj_gif, &astro);
    // lv_obj_align(obj_gif, LV_ALIGN_BOTTOM_RIGHT, 10, 10);
    // lv_obj_set_pos(obj_gif, 120, 120);
    ESP_LOGW(TAG,"test_main called\n");

}