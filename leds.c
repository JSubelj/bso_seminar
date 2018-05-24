#include "leds.h"

void set_leds(uint8_t leds){
	uint8_t leds_inv = ~leds;
	i2c_slave_write(I2C_BUS, PCF_ADDRESS, NULL, &leds_inv, 1);
}

void clear_leds(){
	set_leds(NO_LEDS);
}

void append_leds(uint8_t leds){
	set_leds(get_led_state() | leds);
}

void remove_leds(uint8_t leds){
	set_leds(get_led_state() & (~leds));
}

void flash_leds(uint8_t leds_state, char err){
	uint8_t old_state = get_led_state();
	uint8_t leds = old_state | leds_state;
	if(err==ERROR_LEDS){
		// 3 fast times the charm
		for(char i=0; i<3;i++){
			set_leds(leds);
			delay_ms(250);
			set_leds(old_state);
			delay_ms(150);
		}
	}else{
		// 2 slow times
		for(char i=0; i<2;i++){
			set_leds(leds);
			delay_ms(800);
			set_leds(old_state);
			delay_ms(500);
		}
	}
	set_leds(old_state);
}

uint8_t get_led_state(){
	uint8_t data;
	i2c_slave_read(I2C_BUS,PCF_ADDRESS,NULL,&data,1);
	data = ~data; 
	data &= 0xf;
	return data;	
}

