/*
 * @Author: YJRQZ777 
 * @Date: 2024-03-15 13:22:34 
 * @Last Modified by: YJRQZ777
 * @Last Modified time: 2024-03-15 14:14:24
 */


#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "to_time.h"
#include "ui.h"
#define MAX_HTTP_OUTPUT_BUFFER 2048

static const char *TAG = "to_time";

// void format_datetime(long long datetime, char *year,char *month,char *day,char *hour,char *minute,char *second) {  
//     int year = datetime / 100000000;  
//     int month = (datetime % 100000000) / 1000000;  
//     int day = (datetime % 1000000) / 10000;  
//     int hour = (datetime % 10000) / 100;  
//     int minute = (datetime % 100) / 10;  
//     int second = datetime % 10;  

//     sprintf(year, "%04d", year);
//     sprintf(month, "%02d", month);
//     sprintf(day, "%02d", day);
//     sprintf(hour, "%02d", hour);
//     sprintf(minute, "%02d", minute);
//     sprintf(second, "%02d", second);

// }  

// int main() {  
//     long long datetime = 20240315124632;  
//     char formatted_datetime[20];  

//     format_datetime(datetime, formatted_datetime);  
//     printf("Formatted datetime: %s\n", formatted_datetime);  

//     return 0;  
// }




void my_time(void *pvParameters)
{
    printf("%p\n",pvParameters);

    cJSON* root = NULL;
    root = pvParameters;
    // char formatted_datetime[10];  
    // char formatted_datetime2[10];  
    long long datetime = strtoll(root->valuestring, NULL, 10); 
    printf("%lld\n",datetime);

    uint16_t year = datetime / 10000000000;  
    uint8_t month = (datetime % 1000000000) / 100000000;  
    uint8_t day = (datetime % 100000000) / 1000000;  
    uint8_t hour = (datetime % 1000000) / 10000;  
    uint8_t minute = (datetime % 10000) / 100;  
    uint8_t second = datetime % 100;  
    printf("%d-%d-%d %d:%d:%d\n",year,month,day,hour,minute,second);
    char dates[30];
    char times[20];
    // format_datetime(sysTime1_num, formatted_datetime,formatted_datetime2);  
    while(1)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
        snprintf(dates, sizeof(dates), "%04d年%02d月%02d日", year, month, day);
        snprintf(times, sizeof(times), "%02d:%02d:%02d",hour, minute, second);  
        // printf("The current time is %s %s\n",dates,times);
        lv_label_set_text(ui_Label8,dates);
        lv_label_set_text(ui_Label9,times);
        second++;
        if(second == 60)
        {
            second = 0;
            minute++;
        }
        if(minute == 60)
        {
            minute = 0;
            hour++;
        }
        if(hour == 24)
        {
            hour = 0;
            day++;
        }
        if(day == 31)
        {
            
            day = 1;
            month++;
        }
        if(month == 13)
        {
            month = 1;
            year++;
        }
        if(month == 2 && day == 29)
        {
            day = 1;
            month++;
        }
        // long long sysTime1_num = strtoll(root->valuestring, NULL, 10); 
        // printf("The current %lld\n",sysTime1_num);
    }
}









void http_test_task(void *pvParameters)
{

//02-1 定义需要的变量
      char output_buffer[MAX_HTTP_OUTPUT_BUFFER] = {0};   //用于接收通过http协议返回的数据
    int content_length = 0;  //http协议头的长度
    

    //02-2 配置http结构体
   
   //定义http配置结构体，并且进行清零
    esp_http_client_config_t config ;
    memset(&config,0,sizeof(config));

    //向配置结构体内部写入url
    static const char *URL = "http://quan.suning.com/getSysTime.do";
    config.url = URL;
    //初始化结构体
    esp_http_client_handle_t client = esp_http_client_init(&config);	//初始化http连接
    //设置发送请求 
    esp_http_client_set_method(client, HTTP_METHOD_GET);
    //02-3 循环通讯
    while(1)
    {
    // 与目标主机创建连接，并且声明写入内容长度为0
    esp_err_t err = esp_http_client_open(client, 0);

    //如果连接失败
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
    } 
    //如果连接成功
    else {

        //读取目标主机的返回内容的协议头
        content_length = esp_http_client_fetch_headers(client);

        //如果协议头长度小于0，说明没有成功读取到
        if (content_length < 0) {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
        } 

        //如果成功读取到了协议头
        else {

            //读取目标主机通过http的响应内容
            int data_read = esp_http_client_read_response(client, output_buffer, MAX_HTTP_OUTPUT_BUFFER);
            if (data_read >= 0) {

                //打印响应内容，包括响应状态，响应体长度及其内容
                ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %lld",
                esp_http_client_get_status_code(client),				//获取响应状态信息
                esp_http_client_get_content_length(client));			//获取响应信息长度
                printf("data:%s\n", output_buffer);
				//对接收到的数据作相应的处理
                cJSON* root = NULL;
                root = cJSON_Parse(output_buffer);
                cJSON* time =cJSON_GetObjectItem(root,"sysTime1");
                printf("%s\n",time->valuestring);
                printf("%p\n",(void *)time);
                xTaskCreate(my_time,"my_time",1024*10,time,2,NULL);
                // lv_label_set_text(ui_Label8,"2024年03月14日");
                // LCD_ShowString(0,0,(u8 *)time->valuestring,RED,WHITE,12,0);
            } 
            //如果不成功
            else {
                ESP_LOGE(TAG, "Failed to read response");
            }
        }
    }

    //关闭连接
    esp_http_client_close(client);

    //延时
    vTaskDelay(3000/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
    }
}
