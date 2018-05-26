#ifndef __WIFI_H__
#define __WIFI_H__

#include <espressif/user_interface.h>
#include <espressif/esp_common.h>
#include <dhcpserver.h>
#include <lwip/api.h>

#include "ip_flash_storage.h"
#include "leds.h"


#define AP_SSID "ESP_BSO_WIFI"
#define AP_PASS "testtest1"

#define AP_CHANNEL 5
#define AP_MAX_CONNECTIONS 1
#define AP_AUTHMODE AUTH_WPA_WPA2_PSK
#define AP_BEACON_INTERVAL 100
#define AP_HIDDEN 0

#define AP_WIFI_FLAG 1
#define DYNAMIC_WIFI_FLAG 2
#define STATIC_WIFI_FLAG 3

extern char wifi_config();
extern void soft_ap_config();
extern char client_mode();
extern void client_mode_static();
extern void client_mode_dynamic();
extern void checking_connection(void *pvParameters);
extern void get_ip(uint8_t * ret_ip);
extern void get_gw(uint8_t * ret_gw);
extern void get_netmask(uint8_t * ret_netmask);
extern void get_pass(char * ret_pass);
extern void get_ssid(char * ret_ssid);


#endif