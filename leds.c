#include "leds.h"




void flash_leds(uint8_t leds, char err){
	if(err==ERROR_LEDS){
		// 3 fast times the charm
		for(char i=0; i<3;i++){
			send_to_leds(leds);
			delay_ms(250);
			send_to_leds(NO_LEDS);
			delay_ms(150);
		}
	}else{
		// 2 slow times
		for(char i=0; i<2;i++){
			send_to_leds(leds);
			delay_ms(800);
			send_to_leds(NO_LEDS);
			delay_ms(500);
		}
	}

}

void send_to_leds(uint8_t leds){
	uint8_t leds_inv = ~leds;
	i2c_slave_write(I2C_BUS, PCF_ADDRESS, NULL, &leds_inv, 1);
}