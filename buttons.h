#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "i2c.h"
#include <task.h>
#include "utils.h"
#include "leds.h"
#include "ip_flash_storage.h"

#define PCF_ADDRESS 0x38

#define BUTTON1	0x20
#define BUTTON2	0x10
#define BUTTON3	0x80
#define BUTTON4	0x40

#define BUTTON1_ID 1
#define BUTTON2_ID 2
#define BUTTON3_ID 3
#define BUTTON4_ID 4


extern void task_read_buttons(void *pvParameters);

extern void button1_task(void *pvParameters);
extern void button2_task(void *pvParameters);
extern void button3_task(void *pvParameters);
extern void button4_task(void *pvParameters);




#endif