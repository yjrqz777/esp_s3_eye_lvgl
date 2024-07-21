/*
 * @Author: YJRQZ777 
 * @Date: 2024-03-15 13:22:42 
 * @Last Modified by:   YJRQZ777 
 * @Last Modified time: 2024-03-15 13:22:42 
 */

#ifndef __MY_WIFI_H
#define __MY_WIFI_H
#include <stdint.h>

extern void my_wifi_init(void);
extern uint8_t OtaFlag;
void wifi_connect( char *ssid, char * password);
void kill_wifi();
void my_wifi_scan();
#endif