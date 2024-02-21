
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

#include "test_ui.h"

#include "key.hpp"

#include "main_cpp.hpp"

#define TAG "main"
 
 
void lv_tick_task(void *arg)
{
    lv_tick_inc(1);
}
 
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

    test_main();
    // Butten qqqq;
    // extern int main_cpp();
    main_cpp();

    while (true)
    {

        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        lv_task_handler();
        // lv_tick_inc(10);
        vTaskDelay(pdMS_TO_TICKS(10));     
        // vTaskDelay(10 / portTICK_PERIOD_MS);
        
    }
}