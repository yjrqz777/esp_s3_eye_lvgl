#ifndef __MY_WIFI_H
#define __MY_WIFI_H
#include <stdint.h>

extern void my_wifi_init(void);
void wifi_connect( char *ssid, char * password);
void kill_wifi();
void my_wifi_scan();
#endif