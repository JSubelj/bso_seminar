#include "utils.h"
#include "telnet_server.h"
#include "i2c.h"
#include "input_output.h"
#include "wifi.h"
#include "http_server.h"


void user_init(void){
    uart_set_baud(0, 115200);
    
    wifi_config();

    init_i2c();

    /* turn off LED */
    gpio_enable(LED_PIN, GPIO_OUTPUT);
    gpio_write(LED_PIN, true);

    /* initialize tasks */
    xTaskCreate(task_read_buttons, "task_read_buttons", 512, NULL, 2, NULL);
    xTaskCreate(telnet_server, "Telnet Server", 1024, NULL, 2, NULL);
    xTaskCreate(&httpd_task, "HTTP Daemon", 128, NULL, 2, NULL);
}
