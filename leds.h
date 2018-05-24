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

#define ALL_LEDS 0x0f
#define NO_LEDS 0x0

#define ERROR_LEDS 1
#define NO_ERROR_LEDS 0

extern void flash_leds(uint8_t leds, char err);
extern void send_to_leds(uint8_t leds);
extern void turn_on_led1();



#endif