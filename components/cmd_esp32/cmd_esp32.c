/*
 * @Descripttion: 文件描述
 * @version: 文件版本
 * @Author: jinsc
 * @Date: 2022-04-09 12:12:33
 * @LastEditors: jinsc
 * @LastEditTime: 2022-04-19 23:00:23
 * @FilePath: \my_esp32_s3\components\cmd_esp32\cmd_esp32.c
 */
/* Console example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <cmd_esp32.h>

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"
#include "cmd_decl.h"
#include "esp_vfs_fat.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
// #include "sd_card.h"


#ifdef CONFIG_ESP_CONSOLE_USB_CDC
#error This example is incompatible with USB CDC console. Please try "console_usb" example instead.
#endif // CONFIG_ESP_CONSOLE_USB_CDC

const char* cmd_TAG = "CMD";

#define PROMPT_STR CONFIG_IDF_TARGET

/* Console command history can be stored to and loaded from a file.
 * The easiest way to do this is to use FATFS filesystem on top of
 * wear_levelling library.
 */
#if CONFIG_CONSOLE_STORE_HISTORY

#define MOUNT_PATH "/sdcard"
#define HISTORY_PATH MOUNT_PATH "/history.txt"

// static void initialize_filesystem(void)//这里是使用内部文件系统保存数据的初始化
// {
//     static wl_handle_t wl_handle;
//     const esp_vfs_fat_mount_config_t mount_config = {
//             .max_files = 4,
//             .format_if_mount_failed = true
//     };
//     esp_err_t err = esp_vfs_fat_spiflash_mount(MOUNT_PATH, "storage", &mount_config, &wl_handle);
//     if (err != ESP_OK) {
//         ESP_LOGE(cmd_TAG, "Failed to mount FATFS (%s)", esp_err_to_name(err));
//         return;
//     }
// }
#endif // CONFIG_STORE_HISTORY

static void initialize_nvs(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

void cmd_esp32_init(void)
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.task_stack_size = 1024*20;//设置console线程栈
    
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    /* Prompt to be printed before each line.
     * This can be customized, made dynamic, etc.
     */
    repl_config.prompt = "msh>";
    repl_config.max_cmdline_length = CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH;

    initialize_nvs();

#if CONFIG_CONSOLE_STORE_HISTORY
    // initialize_filesystem();//这里是使用内部文件系统保存数据的
    repl_config.history_save_path = HISTORY_PATH;
    ESP_LOGI(cmd_TAG, "Command history enabled");
#else
    ESP_LOGI(cmd_TAG, "Command history disabled");
#endif

    /* Register commands */
    esp_console_register_help_command();
    register_system();
    // register_nvs();
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
    
}

/**
 * @name: CONSOLE_REGISTER
 * @test: 使用旁边的代码注册函数CONSOLE_REGISTER("my_set","我的测试",NULL,my_set_f);
 *        static int my_set_f(int argc, char **argv)
 * @msg: 相关信息
 * @param {char} *command
 * @param {char} *help
 * @param {char} *hint
 * @param {esp_console_cmd_func_t} func
 * @return {*}
 */
void CONSOLE_REGISTER( const char *command,const char *help,const char *hint, esp_console_cmd_func_t func)
{
    const esp_console_cmd_t cmd = {
        .command = command,
        .help = help,
        .hint = hint,
        .func = func,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

