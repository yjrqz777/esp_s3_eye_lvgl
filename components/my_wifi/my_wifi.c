/*
 * @Author: YJRQZ777 
 * @Date: 2024-03-15 13:22:58 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-03-15 13:24:40
 */
#include "my_wifi.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_https_ota.h"
// F:\Espressif\frameworks\esp-idf-v5.0.2\components\esp_http_client\include\esp_http_client.h

#include "ui.h"
#include "to_time.h"

const char *TAG = "wifi";

uint8_t OtaFlag = 0;

uint8_t wifi_connect_flag = 0;

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
                .min=0,
                .max=50,
        },
            .passive=500,
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
    static char *wifi_ssid;
    static uint16_t ap_num =  0;
    static wifi_ap_record_t ap_info[50];


    esp_wifi_scan_get_ap_num(&ap_num);
    ESP_LOGI("wifi","%d",ap_num);

    memset(ap_info,0,sizeof(ap_info));
    esp_wifi_scan_get_ap_records(&ap_num,&ap_info);

    if(ap_num>20)
        ap_num = 10;

    wifi_ssid = (char *)malloc(ap_num * 15 * sizeof(char)); 
    memset(wifi_ssid, 0, ap_num * 15 * sizeof(char));

    ESP_LOGI("wifi","%d",ap_num);
    // printf("%30s %s %s %s\n", "SSID", "频道", "强度", "MAC地址");
    for (int i = 0; i < ap_num; i++)
    {
        //printf("%30s  %3d  %3d  %02X-%02X-%02X-%02X-%02X-%02X\n", ap_info[i].ssid, ap_info[i].primary, ap_info[i].rssi, ap_info[i].bssid[0], ap_info[i].bssid[1], ap_info[i].bssid[2], ap_info[i].bssid[3], ap_info[i].bssid[4], ap_info[i].bssid[5]);
        strcat(wifi_ssid, (const char *)ap_info[i].ssid);  
        if(i<ap_num-1)
        strcat(wifi_ssid, "\n");  
        
    }
    printf("---1%s\n", wifi_ssid);
    lv_roller_set_options(ui_wifiname, wifi_ssid, LV_ROLLER_MODE_INFINITE );
    // wifi_ssid[0] = "\0";
    // memset(wifi_ssid,0,sizeof(wifi_ssid));
    printf("---2%s\n--3%d\n", wifi_ssid,strlen(wifi_ssid));
    free(wifi_ssid);
    // start_show_pid();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    // esp_wifi_connect();
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    // printf("-----------------start_scan\n");
    // vTaskDelay(1000/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}


// s8.1：调用函数 esp_wifi_disconnect() 断开 Wi-Fi 连接。

// s8.2：调用函数 esp_wifi_stop() 终止 Wi-Fi 驱动程序。

// s8.3：调用函数 esp_wifi_deinit() 清理 Wi-Fi 驱动程序。
#include "esp_event.h"
void run_on_event(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
//   ESP_LOGI("EVENT_HANDLE", "BASE:%s, ID:%ld", base, id);



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
            wifi_connect_flag = 1;  
            ESP_LOGE("EVENT_HANDLE", "wifi连接成功");
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            wifi_connect_flag = 0;
            ESP_LOGE("EVENT_HANDLE", "wifi断开连接");
            OtaFlag = 0;
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
                xTaskCreate(http_test_task, "http_test_task", 8192, NULL, 5, NULL);
                OtaFlag = 1;
                break;
            case IP_EVENT_STA_LOST_IP:
                OtaFlag = 0;
                ESP_LOGE("EVENT_HANDLE", "IP_EVENT_STA_LOST_IP");
                break;
        }
    }
    else if(base == ESP_HTTPS_OTA_EVENT)
    {
    // ESP_HTTPS_OTA_START,                    /*!< OTA started */
    // ESP_HTTPS_OTA_CONNECTED,                /*!< Connected to server */
    // ESP_HTTPS_OTA_GET_IMG_DESC,             /*!< Read app description from image header */
    // ESP_HTTPS_OTA_VERIFY_CHIP_ID,           /*!< Verify chip id of new image */
    // ESP_HTTPS_OTA_DECRYPT_CB,               /*!< Callback to decrypt function */
    // ESP_HTTPS_OTA_WRITE_FLASH,              /*!< Flash write operation */
    // ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION,    /*!< Boot partition update after successful ota update */
    // ESP_HTTPS_OTA_FINISH,                   /*!< OTA finished */
    // ESP_HTTPS_OTA_ABORT,                    /*!< OTA aborted */        
        switch (id)
        {
            case ESP_HTTPS_OTA_START:
                ESP_LOGI("EVENT_HANDLE", "OTA 开始");
                break;
            case ESP_HTTPS_OTA_CONNECTED:
                ESP_LOGI("EVENT_HANDLE", "连接 to 服务器");
                break;
            case ESP_HTTPS_OTA_GET_IMG_DESC:
                ESP_LOGI("EVENT_HANDLE", "Read app 描述 from image 头");
                break;
            case ESP_HTTPS_OTA_VERIFY_CHIP_ID:
                ESP_LOGI("EVENT_HANDLE", "验证 chip id of new image");
                break;
            case ESP_HTTPS_OTA_DECRYPT_CB:
                ESP_LOGI("EVENT_HANDLE", "Callback to 解密 function");
                break;
            case ESP_HTTPS_OTA_WRITE_FLASH:
                // ESP_LOGI("EVENT_HANDLE", "Flash 写 运行");
                break;
            case ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION:
                ESP_LOGI("EVENT_HANDLE", "Boot 分区 更新 之后 成功 ota 更新");
                break;
            case ESP_HTTPS_OTA_FINISH:
                ESP_LOGI("EVENT_HANDLE", "OTA 完成");
                break;
            case ESP_HTTPS_OTA_ABORT:
                ESP_LOGI("EVENT_HANDLE", "OTA 中止");
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

void wifi_connect( char *ssid, char * password)
{   
    // esp_wifi_ap_get_sta_aid
    if(wifi_connect_flag==1)
    {
    ESP_LOGE("wifi_connect", "主动断开...");
    esp_wifi_disconnect();
    // esp_wifi_stop();
    }

    wifi_config_t *configs = malloc(sizeof(wifi_config_t));
    configs->sta.bssid_set = 0;
    configs->sta.channel = 0;
    configs->sta.listen_interval = 0;
    configs->sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
    configs->sta.threshold.rssi = -127;
    configs->sta.threshold.authmode = WIFI_AUTH_OPEN;
    configs->sta.pmf_cfg.capable = true;
    configs->sta.pmf_cfg.required = false;
    memcpy(configs->sta.ssid, ssid, 32);
    memcpy(configs->sta.password, password, 64);
    // configs.sta.ssid = "ssid[32]";
    // configs.sta.password = "password[64]";
    esp_wifi_set_config(ESP_IF_WIFI_STA,configs);

    esp_wifi_connect();
    // esp_wifi_start();
}








// esp_netif_t * my_ap=NULL;


void kill_wifi()
{
    esp_wifi_disconnect();
    esp_wifi_stop();
    esp_wifi_deinit();
    // esp_netif_destroy(my_ap);
    // vTaskDelete(NULL);
}

void my_wifi_init(void)
{
    // static uint8_t wifi_init_flag = 1;
    // if(wifi_init_flag)
    // {

    // wifi_init_flag =0;
    // }

    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());
    // esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    // assert(sta_netif);




    wifi_init_config_t wifi_init = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init));

    // esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    // assert(sta_netif);


    xTaskCreate(task_list, "task_list", 10240, NULL, 1, NULL);
    xTaskCreate(MyOta, "MyOta", 8192, NULL, 5, NULL);
    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_start();
    ESP_LOGW(TAG,"wifi init");


}

void my_wifi_scan()
{
        ESP_LOGI(TAG,"wifi start_scan");
        xTaskCreate(start_scan, "start_scan", 1024, NULL, 2, NULL);
}










