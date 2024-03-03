

#include "my_wifi.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
// F:\Espressif\frameworks\esp-idf-v5.0.2\components\esp_http_client\include\esp_http_client.h


#include "esp_http_client.h"
#include "cJSON.h"

#include "ui.h"


const char *TAG = "wifi";

void start_scan()
{
    wifi_country_t config = {
        .cc = "CN",
        .schan = 1,
        .nchan = 13,
        .policy = WIFI_COUNTRY_POLICY_AUTO,
    };
    esp_wifi_set_country(&config);
    wifi_scan_config_t scan_config = {
     .ssid= NULL,             /**< SSID of AP */
     .bssid= NULL,              /**< MAC address of AP */
     .channel = 0,           /**< channel, scan the specific channel */
     .show_hidden = false,            /**< enable to scan AP whose SSID is hidden */
     .scan_type=WIFI_SCAN_TYPE_ACTIVE,  /**< scan type, active or passive */
     .scan_time={
        .active = {
                .min=120,
                .max=150,
        },
            .passive=1200,
        },  /**< scan time per channel */
    };
    esp_wifi_scan_start(&scan_config,false);
    vTaskDelete(NULL);
}
void show_pid()
{   
    char ptrTaskList[300];
    vTaskList(ptrTaskList);
    printf("Task        State   prio    Stack   Num\n");
    printf(ptrTaskList);
    vTaskDelete(NULL);
}

void start_show_pid()
{
    xTaskCreate(show_pid,"show_pid",1024,NULL,2,NULL);
};

void show_scan()
{
    char wifi_ssid[500] = "";
    uint16_t ap_num =  0;
    esp_wifi_scan_get_ap_num(&ap_num);
    ESP_LOGI("wifi","%d",ap_num);
    wifi_ap_record_t ap_info[20];
    memset(ap_info,0,sizeof(ap_info));
    esp_wifi_scan_get_ap_records(&ap_num,&ap_info);
    ESP_LOGI("wifi","%d",ap_num);
    // printf("%30s %s %s %s\n", "SSID", "频道", "强度", "MAC地址");
    for (int i = 0; i < ap_num; i++)
    {
        //printf("%30s  %3d  %3d  %02X-%02X-%02X-%02X-%02X-%02X\n", ap_info[i].ssid, ap_info[i].primary, ap_info[i].rssi, ap_info[i].bssid[0], ap_info[i].bssid[1], ap_info[i].bssid[2], ap_info[i].bssid[3], ap_info[i].bssid[4], ap_info[i].bssid[5]);
        strcat(wifi_ssid, (const char *)ap_info[i].ssid);  
        strcat(wifi_ssid, "\n");  
        
    }
    printf("--%s", wifi_ssid);
    lv_roller_set_options(ui_wifiname, wifi_ssid, LV_ROLLER_MODE_INFINITE );
    // start_show_pid();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    // esp_wifi_connect();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    // printf("-----------------start_scan\n");
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}

void kill_wifi()
{
    esp_wifi_disconnect();
    esp_wifi_stop();
    esp_wifi_deinit();
    vTaskDelete(NULL);
}
// s8.1：调用函数 esp_wifi_disconnect() 断开 Wi-Fi 连接。

// s8.2：调用函数 esp_wifi_stop() 终止 Wi-Fi 驱动程序。

// s8.3：调用函数 esp_wifi_deinit() 清理 Wi-Fi 驱动程序。


void run_on_event(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
  ESP_LOGI("EVENT_HANDLE", "BASE:%s, ID:%ld", base, id);
  if(base == WIFI_EVENT)
  {
    switch (id)
    {
        case WIFI_EVENT_STA_START:
            ESP_LOGE("EVENT_HANDLE", "WIFI_EVENT_STA_START");
            xTaskCreate(start_scan, "start_scan", 1024, NULL, 2, NULL);
            break;
        case WIFI_EVENT_SCAN_DONE:
            ESP_LOGE("EVENT_HANDLE", "WIFI_EVENT_SCAN_DONE");
            xTaskCreate(show_scan, "show_scan", 1024*20, NULL, 2, NULL);
            break;
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGE("EVENT_HANDLE", "连接成功");
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            ESP_LOGE("EVENT_HANDLE", "连接失败");
            break;
    }
  }
    else if(base == IP_EVENT)
    {
        switch (id)
        {
            case IP_EVENT_STA_GOT_IP:
                ESP_LOGE("EVENT_HANDLE", "IP_EVENT_STA_GOT_IP");
                vTaskDelay(2000/portTICK_PERIOD_MS);
                // xTaskCreate(kill_wifi, "kill_wifi", 1024, NULL, 2, NULL);
                // xTaskCreate(&http_test_task, "http_test_task", 8192, NULL, 5, NULL);
                break;
            case IP_EVENT_STA_LOST_IP:
                ESP_LOGE("EVENT_HANDLE", "IP_EVENT_STA_LOST_IP");
                break;
        }
    }
}



void task_list(void)
{   
    // char ptrTaskList2[200];
    esp_event_handler_register(ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID, run_on_event, NULL);
    while (1)
    {
        // 
        // vTaskList(ptrTaskList2);
        // printf("Task        State   prio    Stack   Num\n");
        // printf(ptrTaskList2);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}


void my_wifi_init(void)
{
    static bool init_flag = false;
    if (init_flag == false)
    {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_init = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_init);

    xTaskCreate(task_list, "task_list", 10240, NULL, 1, NULL);

    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t configs = {
        .sta = {
            .ssid = "duan",
            .password = "13417319586",
            .bssid_set = 0,
            .channel = 0,
            .listen_interval = 0,
            .sort_method = WIFI_CONNECT_AP_BY_SIGNAL,
            .threshold.rssi = -127,
            .threshold.authmode = WIFI_AUTH_OPEN,
        },            
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA,&configs);
    esp_wifi_start();
    ESP_LOGI(TAG,"wifi init");
    init_flag = true;
    }
    else
    {   
        ESP_LOGI(TAG,"wifi start_scan");
        xTaskCreate(start_scan, "start_scan", 1024, NULL, 2, NULL);
    }

}


