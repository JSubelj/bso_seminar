#include "utils.h"
#include "telnet_server.h"
#include "i2c.h"
#include "buttons.h"
#include "wifi.h"
#include "http_server.h"
#include "leds.h"

void user_init(void){
    uart_set_baud(0, 115200);
    init_i2c();

    set_leds(NO_INTERNET);
    wifi_config();
    
    gpio_enable(LED_ON_BOARD, GPIO_OUTPUT);
    gpio_write(LED_ON_BOARD, true);

    //xTaskCreate(&test, "test", 128, NULL, 2, NULL);

    xTaskCreate(checking_connection, "Connection checker", 512, NULL, 2, NULL);    
    xTaskCreate(task_read_buttons, "task_read_buttons", 512, NULL, 2, NULL);
    xTaskCreate(telnet_server, "Telnet Server", 1024, NULL, 2, NULL);
    xTaskCreate(httpd_task, "HTTP Daemon", 128, NULL, 2, NULL);
    
}
