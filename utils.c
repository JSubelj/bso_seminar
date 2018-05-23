#include "utils.h"

void delay_ms(int m_sec){
	vTaskDelay(m_sec / portTICK_PERIOD_MS);
}
