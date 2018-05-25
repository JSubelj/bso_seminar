#include "http_server.h"

enum{
    SSI_UPTIME,
    SSI_FREE_HEAP,
    SSI_LED_STATE
};

int32_t ssi_handler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    switch (iIndex) {
        case SSI_UPTIME:{
            char ip[4];
            get_ip(ip);
            snprintf(pcInsert, iInsertLen, "%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
            break;
        }
        case SSI_FREE_HEAP:
            snprintf(pcInsert, iInsertLen, "%d", (int) xPortGetFreeHeapSize());
            break;
        case SSI_LED_STATE:
            snprintf(pcInsert, iInsertLen, "On");
            break;
        default:
            snprintf(pcInsert, iInsertLen, "N/A");
            break;
    }

    /* Tell the server how many characters to insert */
    return (strlen(pcInsert));
}

char *gpio_cgi_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    for (int i = 0; i < iNumParams; i++) {
        if (strcmp(pcParam[i], "on") == 0) {
            /*uint8_t gpio_num = atoi(pcValue[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);*/
        } else if (strcmp(pcParam[i], "off") == 0) {
            /*uint8_t gpio_num = atoi(pcValue[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, false);*/
        } else if (strcmp(pcParam[i], "toggle") == 0) {
            /*uint8_t gpio_num = atoi(pcValue[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_toggle(gpio_num);*/
        }
    }
    return "/index.ssi";
}

char *about_cgi_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    return "/about.html";
}




void httpd_task(void *pvParameters)
{
    tCGI pCGIs[] = {
        {"/gpio", (tCGIHandler) gpio_cgi_handler},
        {"/about", (tCGIHandler) about_cgi_handler},
    };

    const char *pcConfigSSITags[] = {
        "uptime", // SSI_UPTIME
        "heap",   // SSI_FREE_HEAP
        "led"     // SSI_LED_STATE
    };

    /* register handlers and start the server */
    //http_set_cgi_handlers(pCGIs, sizeof (pCGIs) / sizeof (pCGIs[0]));
    http_set_ssi_handler((tSSIHandler) ssi_handler, pcConfigSSITags,
            sizeof (pcConfigSSITags) / sizeof (pcConfigSSITags[0]));
    httpd_init();

    for (;;);
}
/*

void httpd_task(void *pvParameters){
    const char *pcConfigSSITags[] = {
        "ip_address", //IP_address
    };

    http_set_ssi_handler((tSSIHandler) ssi_handler, pcConfigSSITags,
            sizeof (pcConfigSSITags) / sizeof (pcConfigSSITags[0]));

    httpd_init();
    while(1);
}

int32_t ssi_handler(int32_t iIndex, char *pcInsert, int32_t iInsertLen)
{
    printf("TUKI!");
    switch (iIndex) {
        case IP_ADDR_SSI:{
            char ip[4];
            get_ip(ip);
            printf("%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
            snprintf(pcInsert, iInsertLen, "%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
            break;
        }
        default:
            snprintf(pcInsert, iInsertLen, "N/A");
            break;
    }

    return (strlen(pcInsert));
}
*/