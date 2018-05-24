#include "utils.h"


void delay_ms(int m_sec){
    vTaskDelay(m_sec / portTICK_PERIOD_MS);
}
void os_delay_ms(int m_sec){
    sdk_os_delay_us(1000*1000*m_sec);
}