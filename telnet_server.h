#ifndef __TELNET_SERVER_H__
#define __TELNET_SERVER_H__

#include <lwip/api.h>

#include <string.h>

#include <espressif/esp_common.h>
#include <espressif/user_interface.h>

#include <esp/uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include "utils.h"
#include "ip_flash_storage.h"
#include "commands.h"

#define TELNET_PORT 23
#define MAX_TELNET_CONNECTIONS 5

extern void telnet_server(void *pvParameters);
extern void telnet_connection(void *pvParameters);

extern char what_command(char* command);
extern void act_on_command(char* org_command, struct whole_config * conf, char * ret);


#endif