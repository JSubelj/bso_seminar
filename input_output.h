#ifndef __INPUT_OUTPUT_H__
#define __INPUT_OUTPUT_H__

#include "i2c.h"
#include <task.h>
#include "utils.h"

#define LED_PIN 2

#define PCF_ADDRESS 0x38

#define BUTTON1	0x20
#define BUTTON2	0x10
#define BUTTON3	0x80
#define BUTTON4	0x40

#define BUTTON1_ID 1
#define BUTTON2_ID 2
#define BUTTON3_ID 3
#define BUTTON4_ID 4
 

#define LED1	0xfe
#define LED2	0xfd
#define LED3	0xfb
#define LED4	0xf7

extern void task_read_buttons(void *pvParameters);


#endif