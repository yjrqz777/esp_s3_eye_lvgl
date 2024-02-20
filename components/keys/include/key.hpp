/*
 * @Author: YJRQZ777 
 * @Date: 2024-02-20 10:44:59 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-02-20 10:52:41
 */
#ifndef _KEY_H
#define _KEY_H


// extern "C" void adc_init(void);
// // extern "C" void adc_init(void);
// // void adc_init(void);

#ifdef __cplusplus
extern "C" {
#endif

void adc_init(void);
void key_task(void *pvParameter);
#ifdef __cplusplus
}
#endif

#endif // _KEY_H_
