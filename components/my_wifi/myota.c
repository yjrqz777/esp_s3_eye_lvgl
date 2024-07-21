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
            ESP_LOGI(TAG, "尝试 to download update from %s", config.url);
            esp_err_t ret = esp_https_ota(&ota_config);
            if (ret == ESP_OK) {
                ESP_LOGI(TAG, "OTA 成功, Rebooting...");
                esp_restart();
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
