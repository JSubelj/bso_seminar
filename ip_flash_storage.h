#ifndef __IP_FLASH_STORAGE_H__
#define __IP_FLASH_STORAGE_H__

#include "read_write_flash.h"
#include <string.h>

#define PASS_SIZE 64
#define SSID_SIZE 32
#define IP_SIZE 4
#define DHCP_STATIC_SIZE 1
#define DOES_CONFIG_EXIST_SIZE 2
#define AP_MODE_SIZE 1
#define FULL_SIZE 3*IP_SIZE+PASS_SIZE+SSID_SIZE+DHCP_STATIC_SIZE+DOES_CONFIG_EXIST_SIZE+AP_MODE_SIZE
#define FULL_STRING_SIZE 240

#define STATIC_IP_FLAG 0xff
#define DYNAMIC_IP_FLAG 0
#define AP_MODE_ON_FLAG 0
#define AP_MODE_OFF_FLAG 0xff

#define NO_ERROR 0
#define ERR_CONF_DOSENT_EXIST 1
#define ERR_AP_MODE 2

// na konc bojo bli ip pa ssid pa pass sharnjeni

// 0-3 - so ipaddr
// 4-7 - netmask
// 8-11 - default gw

// 12-[75]SSID_SIZE+11 - SSID
// [76]SSID_SIZE+12-[139]SSID_SIZE+PASS_SIZE+11 - PASS
// [140]SSID_SIZE+PASS_SIZE+12 - DHCP(0)/STATIC(1)
// [141]SSID_SIZE+PASS_SIZE+13-[141]SSID_SIZE+PASS_SIZE+13 - AP_MODE
// [142]SSID_SIZE+PASS_SIZE+13-[143]SSID_SIZE+PASS_SIZE+13 - does_config_exist

// SUM: 144

struct whole_config {
    char ip[4];
    char netmask[4];
    char gw[4];
    char ssid[SSID_SIZE];
    char pass[PASS_SIZE];
    char dhcp_static;
    char ap_mode;
    char does_config_exist[DOES_CONFIG_EXIST_SIZE];
};


extern char get_config_from_flash(struct whole_config * conf);
extern void write_config_to_flash(struct whole_config * conf);
extern void update_ip_config(struct whole_config * conf_ip);
extern void update_wifi_config(struct whole_config * conf_wifi);
extern bool is_ip_static();
extern void set_dhcp_static_flag(char flag);
extern void get_full_conf_string(struct whole_config * conf, char* string);
extern bool is_AP_mode();
extern char set_AP_mode(char mode);
 


#endif
