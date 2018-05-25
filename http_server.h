#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include <httpd/httpd.h>
#include "utils.h"
#include <string.h>
#include "wifi.h"
#include <ssid_config.h>



extern void httpd_task(void *pvParameters);
extern int32_t ssi_handler(int32_t iIndex, char *pcInsert, int32_t iInsertLen);


enum{
    IP_ADDR_SSI
};

#endif