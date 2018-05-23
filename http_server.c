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

#include <i2c/i2c.h>

#include "ip_flash_storage.h"
#include "utils.h"
#include "telnet_server.h"


#define LED_PIN 2


#define PCF_ADDRESS 0x38

#define I2C_BUS	0
#define SCL_PIN 14
#define SDA_PIN 12

#define BUTTON1	0x20
#define BUTTON2	0x10
#define BUTTON3	0x80
#define BUTTON4	0x40

#define LED1	0xfe
#define LED2	0xfd
#define LED3	0xfb
#define LED4	0xf7


void httpd_task(void *pvParameters){
    httpd_init();
    while(1) delay_ms(1000);
}

void init_i2c(){
    i2c_init(I2C_BUS, SCL_PIN, SDA_PIN, I2C_FREQ_100K);
	gpio_enable(SCL_PIN, GPIO_OUTPUT);
}




void task_read_buttons(void *pvParameters){
	uint8_t data;
	uint8_t tmp;
	while(1){
		i2c_slave_read(I2C_BUS,PCF_ADDRESS,NULL,&data,1);
		tmp = 0xff;
		i2c_slave_write(I2C_BUS, PCF_ADDRESS, NULL, &tmp, 1);
		if((data & BUTTON1) == 0){
			tmp = LED1;
		}else if((data & BUTTON2) == 0){
			tmp = LED2;
		}else if((data & BUTTON3) == 0){
			tmp = LED3;
		}else if((data & BUTTON4) == 0){
			tmp = LED4;
		}
		i2c_slave_write(I2C_BUS, PCF_ADDRESS, NULL, &tmp, 1);

		delay_ms(10);


	}

}

void wifi_config(){
    struct ip_info ipconfig;
    struct whole_config full_config={
        .ip={10,6,4,83},
        .gw={10,6,4,210},
        .netmask={255,255,255,0},
        .ssid=WIFI_SSID,
        .pass=WIFI_PASS,
        .dhcp_static=1
    };

    

    write_config_to_flash(&full_config);

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

    struct whole_config full_config;

    /*update_wifi_config(&full_config);*/
    get_config_from_flash(&full_config);
    printf("\nTUKI: %d\n", full_config.dhcp_static);

    set_dhcp_static_flag(0);
    get_config_from_flash(&full_config);
    printf("\nTUKI: %d\n", full_config.dhcp_static);


    /* turn off LED */
    gpio_enable(LED_PIN, GPIO_OUTPUT);
    gpio_write(LED_PIN, true);

    /* initialize tasks */
    //xTaskCreate(read_flash_prog, "read_flash", 512, NULL, 2, NULL);
    xTaskCreate(task_read_buttons, "task_read_buttons", 512, NULL, 2, NULL);
    xTaskCreate(telnet_server, "Telnet Server", 1024, NULL, 2, NULL);
    xTaskCreate(&httpd_task, "HTTP Daemon", 128, NULL, 2, NULL);
}
