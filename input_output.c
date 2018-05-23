#include "input_output.h"



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