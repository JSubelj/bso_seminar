#ifndef __I2C_USER_H__
#define __I2C_USER_H__

#define I2C_BUS	0
#define SCL_PIN 14
#define SDA_PIN 12

#include <i2c/i2c.h>
#include <FreeRTOS.h>

extern void init_i2c();

#endif