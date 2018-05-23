/*
 * HTTP server example.
 *
 * This sample code is in the public domain.
 */
#include <espressif/esp_common.h>
#include <espressif/user_interface.h>

#include <esp8266.h>
#include <esp/uart.h>
#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <ssid_config.h>
#include <httpd/httpd.h>


#include "ip_flash_storage.h"
#include "utils.h"
#include "telnet_server.h"
#include "i2c.h"
#include "input_output.h"





void httpd_task(void *pvParameters){
    httpd_init();
    while(1) delay_ms(1000);
}






void wifi_config(){
    struct ip_info ipconfig;
    /*struct whole_config full_config={
        .ip={10,0,0,83},
        .gw={10,6,4,210},
        .netmask={255,255,255,0},
        .ssid=WIFI_SSID,
        .pass=WIFI_PASS,
        .dhcp_static=1
    };**/

    

    //write_config_to_flash(&full_config);

    IP4_ADDR(&ipconfig.ip, 10,6,4,83); 
    IP4_ADDR(&ipconfig.gw, 10,6,4,210); 
    IP4_ADDR(&ipconfig.netmask, 255,255,255,0); 

    

    /* required to call wifi_set_opmode before station_set_config */
    sdk_wifi_set_opmode(STATION_MODE);
    
    sdk_wifi_station_dhcpc_stop();
 
    sdk_wifi_set_ip_info(0, &ipconfig);
    struct sdk_station_config config = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        };
    sdk_wifi_station_set_config(&config);
    
    sdk_wifi_station_connect();
}

void user_init(void){
    uart_set_baud(0, 115200);
    
    wifi_config();
    //read_flash();

    init_i2c();



    /* turn off LED */
    gpio_enable(LED_PIN, GPIO_OUTPUT);
    gpio_write(LED_PIN, true);

    /* initialize tasks */
    xTaskCreate(task_read_buttons, "task_read_buttons", 512, NULL, 2, NULL);
    xTaskCreate(telnet_server, "Telnet Server", 1024, NULL, 2, NULL);
    xTaskCreate(&httpd_task, "HTTP Daemon", 128, NULL, 2, NULL);
}
