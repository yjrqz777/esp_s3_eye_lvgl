/*
 * @Author: YJRQZ777 
 * @Date: 2024-02-20 10:44:43 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-02-20 12:40:18
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
#include "soc/soc_caps.h" 

static const char *TAG = "key";

// typedef struct {
//     uint32_t pattern_num;                   ///< Number of ADC channels that will be used
//     adc_digi_pattern_config_t *adc_pattern; ///< List of configs for each ADC channel that will be used
//     uint32_t sample_freq_hz;                /*!< The expected ADC sampling frequency in Hz. Please refer to `soc/soc_caps.h` to know available sampling frequency range*/
//     adc_digi_convert_mode_t conv_mode;      ///< ADC DMA conversion mode, see `adc_digi_convert_mode_t`.
//     adc_digi_output_format_t format;        ///< ADC DMA conversion output format, see `adc_digi_output_format_t`.
// } adc_continuous_config_t;


// typedef struct {
//     uint8_t atten;      ///< Attenuation of this ADC channel
//     uint8_t channel;    ///< ADC channel
//     uint8_t unit;       ///< ADC unit
//     uint8_t bit_width;  ///< ADC output bit width
// } adc_digi_pattern_config_t;


extern "C" void adc_init(void)
{   
    adc_continuous_handle_t adc_handle;
    adc_continuous_handle_cfg_t adc_config = {
    .max_store_buf_size = 1024,
    .conv_frame_size = 100,
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &adc_handle));

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
    adc_continuous_config(adc_handle, &adc_con_config);
    ESP_LOGW(TAG,"  adc_continuous_config success");

    // std::cout << "adc init success" << std::endl;

    //     adc_continuous_evt_cbs_t cbs = {
    //     .on_conv_done = s_conv_done_cb,
    // };
    // ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(handle, &cbs, NULL));
    ESP_ERROR_CHECK(adc_continuous_start(adc_handle));
    // std::cout << "adc init success" << std::endl;
    std::cout << "adc init success" << adc_handle << std::endl;
    xTaskCreate(key_task, "key_task", 2048*10,adc_handle, 1, NULL);
}

// sp_err_t adc_continuous_read(adc_continuous_handle_t handle, uint8_t *buf, uint32_t length_max, uint32_t *out_length, uint32_t timeout_ms)
// extern "C" 
void key_task( void *pvParameter)
{   


    std::cout << "pvParameter = " << pvParameter << std::endl;

    adc_continuous_handle_t adc_handle;
    adc_handle = (adc_continuous_handle_t)pvParameter;
    std::cout << "adc_handle = " << adc_handle << std::endl;
    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t result[256] = {0};
    std::memset(result, 0xcc, 256);
    while(1)
    {
        vTaskDelay(1);
            ret = adc_continuous_read(adc_handle, result, 256, &ret_num, 0);

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