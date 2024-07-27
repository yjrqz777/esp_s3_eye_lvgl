#include "test_ui.h"
#include "lvgl.h"
#include "esp_log.h"
#include "lv_port_indev.h"
#include "xxxx.c"
#include "astro.c"
// #include "lv_gif.h"
// #include "lv_img.h"
#include "songti.c"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include <dirent.h>

#include "ui.h"
#include "ui_helpers.h"


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



void test_btn(void)
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
    while (true)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    

}

#include<string.h>

static lv_group_t *g_btn_op_group = NULL;
bool i=false;
static void btn_event_cb(lv_event_t *event)
{
    lv_obj_t *img = (lv_obj_t *) event->user_data;
    if (i)
    {
        lv_obj_set_style_img_opa(img, LV_OPA_0, 0);
        i=false;
    }
    else
    {

    


    const char *file_name = strlwr(lv_list_get_btn_text(lv_obj_get_parent(event->target), event->target));

    // const char *file_name = lv_list_get_btn_text(lv_obj_get_parent(event->target), event->target);
    char *file_name_with_path = (char *) heap_caps_malloc(256, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    if (NULL != file_name_with_path) {
        /* Get full file name with mount point and folder path */
        strcpy(file_name_with_path, "A:sdcard/");
        strcat(file_name_with_path, file_name);

        /* Set src of image with file name */
        lv_img_set_src(img, file_name_with_path);
        lv_obj_set_style_img_opa(img, LV_OPA_100, 0);

        /* Align object */
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

        /* Only for debug */
        ESP_LOGI(TAG, "file_name_with_path : %s,file_name=%s", file_name_with_path,file_name);

        /* Don't forget to free allocated memory */
        free(file_name_with_path);
    }
    i=true;
    }


}
lv_obj_t *list;

static void list_btn_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        // _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 30, 0, &ui_Screen1_screen_init);
    lv_indev_set_group(indev_keypad, list);
    // lv_group_focus_obj(ui_wifibtn);
    }
}


void test_picture(lv_obj_t * ui_Screen4)
{
    // lv_indev_t *indev = lv_indev_get_next(NULL);

    // if ((lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD) || 
    //         lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
    //     ESP_LOGI(TAG, "Input device type is keypad");
    //     g_btn_op_group = lv_group_create();
    //     lv_indev_set_group(indev, g_btn_op_group);
    // }

    list = lv_list_create(ui_Screen4);
    lv_obj_set_size(list, 240, 190);
    lv_obj_set_style_border_width(list, 0, LV_STATE_DEFAULT);
    lv_obj_align(list, LV_ALIGN_BOTTOM_MID, 0, 0);

    // lv_obj_add_event_cb(list, list_btn_event_cb, LV_EVENT_CLICKED, (void *) NULL);

    lv_obj_t *img = lv_img_create(ui_Screen4);
    // lv_img_set_src(img, "A:sdcard/emo1.png");

    /* Align object */
    // lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    /* Get file name in storage */
    struct dirent *p_dirent = NULL;
    DIR *p_dir_stream = opendir("/sdcard");

    /* Scan files in storage */
    while (true) {
        p_dirent = readdir(p_dir_stream);
        if (NULL != p_dirent) {
            
            lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_IMAGE, strlwr(p_dirent->d_name));
            lv_group_add_obj(group4, btn);
            lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, (void *) img);
            // ESP_LOGE("test_picture", "while");
        } else {
            closedir(p_dir_stream);
            // ESP_LOGE("test_picture", "break");
            break;
        }
    }
    // ESP_LOGE("test_picture", "-------------------------------");
}


// void test_picture2(void)
// {
//     lv_indev_t *indev = lv_indev_get_next(NULL);

//     if ((lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD) || 
//             lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
//         ESP_LOGI(TAG, "Input device type is keypad");
//         g_btn_op_group = lv_group_create();
//         lv_indev_set_group(indev, g_btn_op_group);
//     }

//     lv_obj_t *list = lv_list_create(lv_scr_act());
//     lv_obj_set_size(list, 240, 190);
//     lv_obj_set_style_border_width(list, 0, LV_STATE_DEFAULT);
//     lv_obj_align(list, LV_ALIGN_LEFT_MID, 0, 0);

//     lv_obj_t *img = lv_img_create(lv_scr_act());
//     // lv_img_set_src(img, "A:sdcard/emo1.png");

//     /* Align object */
//     // lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

//     /* Get file name in storage */
//     struct dirent *p_dirent = NULL;
//     DIR *p_dir_stream = opendir("/sdcard");

//     /* Scan files in storage */
//     while (true) {
//         p_dirent = readdir(p_dir_stream);
//         if (NULL != p_dirent) {
            
//             lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_IMAGE, strlwr(p_dirent->d_name));
//             lv_group_add_obj(g_btn_op_group, btn);
//             lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, (void *) img);
//             // ESP_LOGE("test_picture", "while");
//         } else {
//             closedir(p_dir_stream);
//             // ESP_LOGE("test_picture", "break");
//             break;
//         }
//     }
//     // ESP_LOGE("test_picture", "-------------------------------");
// }


void test_main(void)
{
    // xTaskCreate(test_picture, "test_picture", 4096*10, NULL, 2, NULL);
    // test_picture();
    ESP_LOGW(TAG,"test_main called\n");

}


