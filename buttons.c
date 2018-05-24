#include "buttons.h"


void task_read_buttons(void *pvParameters){
	uint8_t data;
	char flag=0;
	while(1){
		i2c_slave_read(I2C_BUS,PCF_ADDRESS,NULL,&data,1);
		if((data & BUTTON1) == 0){
			flag++;
			xTaskCreate(&button1_task, "button1_task", 256, NULL, 2, NULL);
		}else if((data & BUTTON2) == 0){
			flag++;
			xTaskCreate(&button2_task, "button2_task", 256, NULL, 2, NULL);
			
		}else if((data & BUTTON3) == 0){
			flag++;
			xTaskCreate(&button3_task, "button3_task", 256, NULL, 2, NULL);
		
		}else if((data & BUTTON4) == 0){
			flag++;
			xTaskCreate(&button4_task, "button4_task", 256, NULL, 2, NULL);
	
		}
		if(flag){
			delay_ms(250);
			flag=0;
		}else{
			delay_ms(10);
		}

	}

}

void button1_task(void *pvParameters){
	char err=set_AP_mode(AP_MODE_OFF_FLAG);
	if(err==NO_ERROR){
		flash_leds(ALL_LEDS, NO_ERROR_LEDS);
	}else{
		flash_leds(ALL_LEDS, ERROR_LEDS);
	}
	
	
	vTaskDelete(NULL);
}

void button2_task(void *pvParameters){
	char err=set_AP_mode(AP_MODE_ON_FLAG);
	if(err==NO_ERROR){
		flash_leds(ALL_LEDS, NO_ERROR_LEDS);
	}else{
		flash_leds(ALL_LEDS, ERROR_LEDS);
	}
	vTaskDelete(NULL);
}

void button3_task(void *pvParameters){
	
	
	
	vTaskDelete(NULL);
}

void button4_task(void *pvParameters){
	
	
	
	vTaskDelete(NULL);
}