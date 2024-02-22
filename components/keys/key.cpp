/*
 * @Author: YJRQZ777 
 * @Date: 2024-02-20 10:44:43 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-02-21 20:23:45
 */
#include <iostream>
// #include <string.h>
#include <cstring>
#include "key.hpp"
#include "driver/adc.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "soc/soc_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_oneshot.h"
#include "soc/soc_caps.h" 




static const char *TAG = "key";

static adc_continuous_handle_t adc_handle_with_continuous = NULL;


extern "C" void Button::adc_init_with_continuous(void)
{   

    adc_continuous_handle_cfg_t adc_config = {
    .max_store_buf_size = 1024,
    .conv_frame_size = 100,
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &adc_handle_with_continuous));

    adc_digi_pattern_config_t adc_num[2] = {};

    adc_continuous_config_t adc_con_config = {
        .pattern_num = 1,
        .sample_freq_hz = 1000,
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,
        .format = ADC_DIGI_OUTPUT_FORMAT_TYPE2,
    };

    adc_num[0].atten = ADC_ATTEN_DB_0;
    adc_num[0].channel = ADC_CHANNEL_0;
    adc_num[0].unit = ADC_UNIT_1;
    adc_num[0].bit_width = ADC_BITWIDTH_12;
    adc_con_config.adc_pattern = adc_num;
    adc_continuous_config(adc_handle_with_continuous, &adc_con_config);
    ESP_LOGW(TAG,"  adc_continuous_config success");
    // std::cout << "adc init success" << std::endl;
    //     adc_continuous_evt_cbs_t cbs = {
    //     .on_conv_done = s_conv_done_cb,
    // };
    // ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(handle, &cbs, NULL));
    ESP_ERROR_CHECK(adc_continuous_start(adc_handle_with_continuous));
    // std::cout << "adc init success" << std::endl;
    std::cout << "adc init success" << adc_handle_with_continuous << std::endl;
    
}

void key_task_run_with_continuous( void *pvParameter)
{   
    // std::cout << "pvParameter = " << pvParameter << std::endl;
    // adc_continuous_handle_t adc_handle_with_continuous;
    // adc_handle_with_continuous = (adc_continuous_handle_t)pvParameter;
    std::cout << "adc_handle_with_continuous = " << adc_handle_with_continuous << std::endl;
    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t result[256] = {0};
    std::memset(result, 0xcc, 256);
    while(1)
    {
        vTaskDelay(1);
            ret = adc_continuous_read(adc_handle_with_continuous, result, 256, &ret_num, 0);

            if (ret == ESP_OK) {
                ESP_LOGI("TASK", "ret is %x, ret_num is %"PRIu32, ret, ret_num);
                // for(int i = 0; i < ret_num; i++)
                // {
                //     ESP_LOGI("TASK", "result[%d] is %x", i, result[i]);
                // }
                std::cout << "result = " << result << std::endl;
                for (int i = 0; i < ret_num; i += SOC_ADC_DIGI_RESULT_BYTES) {
                    adc_digi_output_data_t *p = (adc_digi_output_data_t *)&result[i];
                    ESP_LOGI(TAG, "Unit: %d,_Channel: %d, Value: %x", 1, p->type2.channel, p->type2.data);

                }
                /**
                 * Because printing is slow, so every time you call `ulTaskNotifyTake`, it will immediately return.
                 * To avoid a task watchdog timeout, add a delay here. When you replace the way you process the data,
                 * usually you don't need this delay (as this task will block for a while).
                 */
                
            }
            else
            {
                ESP_LOGE("TASK", "ret is %x", ret);
            }
    }
}



void Button::run_with_continuous()
{
    xTaskCreate(key_task_run_with_continuous, "key_task_run_with_continuous", 2048*10,NULL, 1, NULL);
}



adc_oneshot_unit_init_cfg_t init_config__with_oneshot = {
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

adc_oneshot_unit_handle_t adc_handle_with_oneshot = NULL;
adc_oneshot_chan_cfg_t config__with_oneshot = {
    .atten = ADC_ATTEN_DB_11,
    .bitwidth = ADC_BITWIDTH_12,    
};
void Button::adc_init_with_oneshot()
{
    adc_oneshot_new_unit(&init_config__with_oneshot,&adc_handle_with_oneshot); 
    adc_oneshot_config_channel(adc_handle_with_oneshot,ADC_CHANNEL_0,&config__with_oneshot);
    ESP_LOGI(TAG, "adc_init_with_oneshot success\n");
}

unsigned char button_flag = 0;
void key_task_run_with_oneshot(void *pvParameter)
{   
    int p = 0;
    float voltage = 0;
    ESP_LOGI(TAG, "key_task_run_with_oneshot begin\n");
    while (true)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle_with_oneshot,ADC_CHANNEL_0,&p));
        voltage = p *3.3/4096;
    if (p> 300 && p < 500)
    {
        button_flag = 1;
    }
    else if (p > 850 && p < 1050)
    {
        button_flag = 2;
    }
    else if (p > 2250 && p < 2450)
    {
        button_flag = 3;
    }
    else if (p > 2800 && p < 3000)
    {
        button_flag = 5;
    }
    else
    {
        button_flag = 0;
    }

// {BUTTON_MENU, 2800, 3000}, {BUTTON_PLAY, 2250, 2450}, {BUTTON_UP, 300, 500}, {BUTTON_DOWN, 850, 1050}

        std::cout << "adc_oneshot_read = " << voltage << std::endl;
        // if(*p != 0)
        // {
        //     ESP_LOGE(TAG, "adc_oneshot_read=%d\n",*p);
        // }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
}

void Button::run_with_oneshot()
{
    xTaskCreate(key_task_run_with_oneshot, "key_task_run_with_oneshot", 2048*10,NULL, 1, NULL);
}
