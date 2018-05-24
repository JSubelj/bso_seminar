#include "utils.h"
#include "telnet_server.h"
#include "i2c.h"
#include "buttons.h"
#include "wifi.h"
#include "http_server.h"
#include "leds.h"

void test(void* k){
    printf("ERR\n");
    flash_leds(ALL_LEDS, ERROR_LEDS);
    delay_ms(2000);
    printf("NoERR\n");
    flash_leds(ALL_LEDS, NO_ERROR_LEDS);
    vTaskDelete(NULL);
}

void user_init(void){
    uart_set_baud(0, 115200);
    
    wifi_config();

    init_i2c();
    


    gpio_enable(LED_ON_BOARD, GPIO_OUTPUT);
    gpio_write(LED_ON_BOARD, true);

    xTaskCreate(&test, "test", 128, NULL, 2, NULL);

    xTaskCreate(task_read_buttons, "task_read_buttons", 512, NULL, 2, NULL);
    xTaskCreate(telnet_server, "Telnet Server", 1024, NULL, 2, NULL);
    xTaskCreate(&httpd_task, "HTTP Daemon", 128, NULL, 2, NULL);
    
}
