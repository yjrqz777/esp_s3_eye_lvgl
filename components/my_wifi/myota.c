/*
 * @Author: YJRQZ777
 * @Date: 2024-03-15 13:22:34
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-03-15 14:14:24
 */

#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_https_ota.h"
#include "esp_crt_bundle.h"

#include "my_wifi.h"

#include "esp_log.h"
#include "to_time.h"
#define MAX_HTTP_OUTPUT_BUFFER 2048

static const char *TAG = "to_time";


#define CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL "http://bin.bemfa.com/b/3BcYzViMjAyMGU3YTIwNGM2MGJiMjIwYjE1ODI4MDJkMmY=Esp32OTA.bin"

#define CONFIG_EXAMPLE_USE_CERT_BUNDLE 1

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
        break;
    }
    return ESP_OK;
}




esp_err_t my_esp_https_ota(const esp_https_ota_config_t *ota_config,esp_app_desc_t *desc)
{
    if (ota_config == NULL || ota_config->http_config == NULL) {
        ESP_LOGE(TAG, "esp_https_ota: Invalid argument");
        return ESP_ERR_INVALID_ARG;
    }

    esp_https_ota_handle_t https_ota_handle = NULL;
    esp_err_t err = esp_https_ota_begin(ota_config, &https_ota_handle);
    if (https_ota_handle == NULL) {
        return ESP_FAIL;
    }
    // vTaskDelay(1000 / portTICK_PERIOD_MS);

    esp_app_desc_t new_app_info;
    err = esp_https_ota_get_img_desc(https_ota_handle,&new_app_info);
    ESP_LOGE("-------------", "version: %s", desc->version);
    ESP_LOGI(TAG, "version: %s", new_app_info.version);
    ESP_LOGI(TAG, "strcmp: %d", strcmp(desc->version, new_app_info.version));
    ESP_LOGI(TAG, "大: %d", strcmp("asd", "a"));
    ESP_LOGI(TAG, "小: %d", strcmp("asd", "asdf"));
    ESP_LOGI(TAG, "等: %d", strcmp("asd", "asd"));
    ESP_LOGI(TAG, "project_name: %s", new_app_info.project_name);
    ESP_LOGI(TAG, "time: %s", new_app_info.time);
    ESP_LOGI(TAG, "date: %s", new_app_info.date);
    ESP_LOGI(TAG, "idf_ver: %s", new_app_info.idf_ver);
    // ESP_LOGI(TAG, "app_elf_sha256: %s", new_app_info.app_elf_sha256);
    // ESP_LOGI(TAG, "size: %d", new_app_info.size);
    // ESP_LOGI(TAG, "secure_version: %d", new_app_info.secure_version);
    // ESP_LOGI(TAG, "magic_word: %d", new_app_info.magic_word);
    // ESP_LOGI(TAG, "reserv1: %d", new_app_info.reserv1);
    ESP_LOGE("OOOOOOOOO","---------err---------%d",err);
    if (err != ESP_OK) {
        return err;
    }
    while (1) {
        err = esp_https_ota_perform(https_ota_handle);
        if (err != ESP_ERR_HTTPS_OTA_IN_PROGRESS) {
            break;
        }
    }

    if (err != ESP_OK) {
        esp_https_ota_abort(https_ota_handle);
        return err;
    }

    esp_err_t ota_finish_err = esp_https_ota_finish(https_ota_handle);
    if (ota_finish_err != ESP_OK) {
        return ota_finish_err;
    }
    return ESP_OK;
}








void MyOta(void *pvParameter)
{
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "开始 OTA  任务");

    esp_http_client_config_t config = {
        .url = CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL,
        .crt_bundle_attach = esp_crt_bundle_attach,//components/mbedtls/esp_crt_bundle/include/esp_crt_bundle.h
        .event_handler = _http_event_handler,
        .keep_alive_enable = true,
    };


    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };



    while (1) {
        if(OtaFlag)
        {
            esp_app_desc_t *desc= NULL;
        desc = esp_app_get_description();
        // print_sha256(desc->app_elf_sha256, "SHA-2561111 for current firmware: ");
        ESP_LOGI(TAG, "尝试 to download update from %s", config.url);
            esp_err_t ret = my_esp_https_ota(&ota_config,desc);
            if (ret == ESP_OK) {
                ESP_LOGI(TAG, "OTA 成功, Rebooting...");
                OtaFlag =0;
                // esp_restart();
            } else {
                ESP_LOGE(TAG, "Firmware upgrade 失败");
            }
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        ESP_LOGE(TAG, "------------等待启动OTA----------------");

    }
}



// void MyOta(void *pvParameters)
// {

//     // 关闭连接
//     while (1)
//     {
//         vTaskDelay(3000 / portTICK_PERIOD_MS);
//         vTaskDelete(NULL);
//     }
// }
