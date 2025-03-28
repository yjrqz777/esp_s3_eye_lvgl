
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
#include "lv_port_fs.h"

#include "test_ui.h"

#include "key.hpp"

#include "main_cpp.hpp"
#include "driver/gpio.h"
#define TAG "main"
 
#include "sd_fat_fs.h"
// #include <cmd_esp32.h>
#include "qma7981.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"



#include "ui.h"
#include "ui_helpers.h"

/***************************************************************************************************
 * 功能描述: 
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 * 其它说明: 
 * param {void} *arg
***************************************************************************************************/
void lv_tick_task(void *arg)
{
    lv_tick_inc(1);
}



/***************************************************************************************************
 * 功能描述: 
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 * 其它说明: 
***************************************************************************************************/
void LVGL()
{
    /*LVGL 初始化*/
    lv_init();

    /*LVGL 显示驱动初始化*/
    lv_port_disp_init();

    /*LVGL 文件系统初始化*/
    lv_port_fs_init();
    // fat_fs();
    /* test ui */
    // test_main();

    /*squareline ui init  */
    ui_init();

    /*LVGL控制设备初始化*/
    lv_port_indev_init();

    // lv_obj_t *img = lv_img_create(lv_scr_act());
    // lv_img_set_src(img, "A:sdcard/emo2.png");
    // lv_obj_set_style_img_opa(img, LV_OPA_100, 0);

    // /* Align object */
    // lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    /*sd_fat_fs test*/
//     fat_fs();

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    

}






/***************************************************************************************************
 * 功能描述: 
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 * 其它说明: 
***************************************************************************************************/
void app_main(void)
{


    /* lv_tick_task */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick_task"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1 * 1000));


    nvs_flash_init();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    
    
    /*注释 key*/
    main_cpp();
    


    /*qma7981 test*/
    // xTaskCreate(qma7981_main, "qma7981_main", 4096, NULL, 2, NULL);
    // xTaskCreate(MyTinyUSB_Main, "MyTinyUSB_Main", 4096, NULL, 2, NULL);
    xTaskCreate(LVGL, "LVGL", 4096*2, NULL, 4, NULL);


    /* while 1*/
    while (true)
    {

        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        lv_task_handler();
        // lv_tick_inc(10);
        vTaskDelay(pdMS_TO_TICKS(10));     
        // vTaskDelay(10 / portTICK_PERIOD_MS);
        
    }
}