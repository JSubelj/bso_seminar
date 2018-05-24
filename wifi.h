#ifndef __WIFI_H__
#define __WIFI_H__

#include <espressif/user_interface.h>
#include <espressif/esp_common.h>
#include <dhcpserver.h>
#include <lwip/api.h>

#include "private_ssid_config.h"
#include "ip_flash_storage.h"

#define AP_SSID "ESP_BSO_WIFI"
#define AP_PASS "testtest1"

#define AP_CHANNEL 5
#define AP_MAX_CONNECTIONS 1
#define AP_AUTHMODE AUTH_WPA_WPA2_PSK
#define AP_BEACON_INTERVAL 100
#define AP_HIDDEN 0

extern void wifi_config();
extern void soft_ap_config();
extern void client_mode();
extern void client_mode_static();
extern void client_mode_dynamic();

#endif