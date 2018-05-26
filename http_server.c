#include "http_server.h"

enum{
    SSI_IP_ADDR,
    SSI_NETMASK,
    SSI_GW,
    SSI_AP_OR_CLIENT,
    SSI_SSID,
    SSI_PASS,
    SSI_DYNAMIC_STATIC
};

int32_t ssi_handler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    switch (iIndex) {
        case SSI_IP_ADDR:{
            uint8_t ip[4];
            get_ip(ip);
            snprintf(pcInsert, iInsertLen, "%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
            break;
        }
        case SSI_NETMASK:{
            uint8_t netmask[4];
            get_netmask(netmask);
            snprintf(pcInsert, iInsertLen, "%d.%d.%d.%d", netmask[0],netmask[1],netmask[2],netmask[3]);
            break;
        }
        case SSI_GW:{
            uint8_t gw[4];
            get_gw(gw);
            snprintf(pcInsert, iInsertLen, "%d.%d.%d.%d", gw[0],gw[1],gw[2],gw[3]);
            break;
        }
        case SSI_AP_OR_CLIENT:{
            snprintf(pcInsert, iInsertLen, "%s", is_AP_mode() ? "Access point" : "Client");
            break;
        }
        case SSI_SSID:{
            char ssid[SSID_SIZE];
            get_ssid(ssid);
            snprintf(pcInsert, iInsertLen, "%s", ssid);
            break;
        }
        case SSI_PASS:{
            char pass[PASS_SIZE];
            get_pass(pass);
            snprintf(pcInsert, iInsertLen, "%s", pass);
            break;
        }
        case SSI_DYNAMIC_STATIC:{
            snprintf(pcInsert, iInsertLen, "%s", is_ip_static() ? "static" : "dynamic");
            break;
        }
        default:
            snprintf(pcInsert, iInsertLen, "N/A");
            break;
    }

    /* Tell the server how many characters to insert */
    return (strlen(pcInsert));
}

void httpd_task(void *pvParameters)
{
    const char *pcConfigSSITags[] = {
        "ip_addr", 
        "netmask",
        "gw",
        "AP",
        "ssid",
        "pass",
        "stat_dyn",
    };

    http_set_ssi_handler((tSSIHandler) ssi_handler, pcConfigSSITags,
            sizeof (pcConfigSSITags) / sizeof (pcConfigSSITags[0]));
    httpd_init();

    while(1);
}
