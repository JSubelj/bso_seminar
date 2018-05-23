#include "http_server.h"


void httpd_task(void *pvParameters){
    httpd_init();
    while(1) delay_ms(1000);
}