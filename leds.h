#ifndef __LEDS_H__
#define __LEDS_H__

#include "i2c.h"
#include <task.h>
#include "utils.h"

#define LED_ON_BOARD 2

#define PCF_ADDRESS 0x38

// delamo v pozitivni logiki na konc invrtaš
#define LED1	0x01
#define LED2	0x02
#define LED3	0x04
#define LED4	0x08

#define AP_ON_LED LED1
#define DYNAMIC_ON_LED LED2
#define STATIC_ON_LED LED3
#define NO_INTERNET LED4

#define ALL_LEDS 0x0f
#define NO_LEDS 0x0

#define ERROR_LEDS 1
#define NO_ERROR_LEDS 0

extern void flash_leds(uint8_t leds, char err);
extern void set_leds(uint8_t leds);
extern void clear_leds();
extern void append_leds(uint8_t leds);
extern void remove_leds(uint8_t leds);
extern uint8_t get_led_state();




#endif