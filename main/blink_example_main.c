
#include <stdio.h>
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "lvgl.h"
#include "lvgl_helpers.h"
 
#include "demos/lv_demos.h"
#include "esp_timer.h"

#include "lv_port_disp.h"
#include "lv_port_indev.h"

#include "test_ui.h"

#include "key.hpp"

#include "main_cpp.hpp"

#define TAG "main"
 
 
void lv_tick_task(void *arg)
{
    lv_tick_inc(1);
}
 


// static void event_handler(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * obj = lv_event_get_target(e);
//     if(code == LV_EVENT_VALUE_CHANGED) {
//         uint32_t id = lv_btnmatrix_get_selected_btn(obj);
//         const char * txt = lv_btnmatrix_get_btn_text(obj, id);
 
//         LV_LOG_USER("%s was pressed\n", txt);
//     }
// }
 
 
 
// static const char * btnm_map[] = {"1", "2", "3",""};

void app_main(void)
{
    
    /* Initialize SPI or I2C bus used by the drivers */
    
    lv_init();
    // lvgl_driver_init(); 
    lv_port_disp_init();
    // lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    // assert(buf1 != NULL);
    // static lv_color_t *buf2 = NULL;
 
    // static lv_disp_draw_buf_t disp_buf;
 
    // uint32_t size_in_px = DISP_BUF_SIZE;
    // lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);
    // lv_disp_drv_t disp_drv;
    // lv_disp_drv_init(&disp_drv);
    // disp_drv.hor_res = LV_HOR_RES_MAX;
    // disp_drv.ver_res = LV_VER_RES_MAX;
    // disp_drv.flush_cb = disp_driver_flush;
    // disp_drv.draw_buf = &disp_buf;
    // lv_disp_drv_register(&disp_drv);



    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1 * 1000));
    // lvgl demo演示
    // lv_demo_music();
    // lv_demo_stress();
    // extern void adc_init(void);
    main_cpp();
    lv_port_indev_init();    
    test_main();
    // Butten qqqq;
    // extern int main_cpp();


    // lv_group_t *group = lv_group_create();

    // lv_indev_set_group(indev_keypad, group);
 
    


    // lv_obj_t * btnm1 = lv_btnmatrix_create(lv_scr_act());
    // lv_btnmatrix_set_map(btnm1, btnm_map);
    // lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    // lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    // lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
    // lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);

    // lv_group_add_obj(group ,btnm1);




    

    while (true)
    {

        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        lv_task_handler();
        // lv_tick_inc(10);
        vTaskDelay(pdMS_TO_TICKS(10));     
        // vTaskDelay(10 / portTICK_PERIOD_MS);
        
    }
}