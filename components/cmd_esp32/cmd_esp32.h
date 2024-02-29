/*
 * @Descripttion: 文件描述
 * @version: 文件版本
 * @Author: jinsc
 * @Date: 2022-04-10 11:39:58
 * @LastEditors: jinsc
 * @LastEditTime: 2022-04-10 22:31:56
 * @FilePath: \my_esp32_s3\components\cmd_esp32\cmd_esp32.h
 */
#ifndef CMD_ESP32_H
#define CMD_ESP32_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "stdio.h"
#include "stdint.h"
#include "string.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "sdkconfig.h"

/*********************
 *      DEFINES
 *********************/
extern const char* cmd_TAG;
#ifndef cmd_printf
// #define cmd_printf( format, args... ) ESP_LOGI( cmd_TAG, format, ##args )
#define cmd_printf( format, args... ) printf( format, ##args )
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void cmd_esp32_init(void);
void CONSOLE_REGISTER( const char *command,const char *help,const char *hint, esp_console_cmd_func_t func);//向cmd注册功能 CONSOLE_REGISTER("my_set","我的测试",NULL,my_set_f);
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*CMD_ESP32_H*/
