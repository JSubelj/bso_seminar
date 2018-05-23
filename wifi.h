#ifndef __WIFI_H__
#define __WIFI_H__

#define SERVER "10.6.4.105"
#define PORT "8000"

#include <espressif/user_interface.h>
#include <espressif/esp_common.h>

#include "private_ssid_config.h"
#include "ip_flash_storage.h"


extern void wifi_config();

#endif