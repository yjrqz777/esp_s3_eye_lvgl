/*
 * @Author: YJRQZ777 
 * @Date: 2024-02-20 10:44:59 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-02-21 19:54:51
 */






#ifndef _KEY_HPP
#define _KEY_HPP

// #include <iostream>
#include "esp_adc/adc_oneshot.h"

// extern "C" void adc_init(void);
// // extern "C" void adc_init(void);
// // void adc_init(void);

#define ADC_1 ADC_UNIT_1
#define CH_0 ADC_CHANNEL_0


#ifdef __cplusplus
extern "C" {
#endif

// void adc_init(void);
void key_task_run_with_continuous(void *pvParameter);
void key_task_run_with_oneshot(void *pvParameter);

// extern unsigned char button_flag;
extern adc_oneshot_unit_handle_t adc_handle_with_oneshot;

#ifdef __cplusplus
}

class Button 
{
    public:
        void adc_init_with_continuous();
        void run_with_continuous();

        void adc_init_with_oneshot();
        void run_with_oneshot();

};


#endif



#endif // _KEY_H_

