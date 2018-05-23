#ifndef __READ_WRITE_FLASH_H__
#define __READ_WRITE_FLASH_H__

#include <FreeRTOS.h>
#include <espressif/spi_flash.h>
#include <stdio.h>

#include "utils.h"

// https://www.espressif.com/sites/default/files/documentation/99a-sdk-espressif_iot_flash_rw_operation_en_v1.0_0.pdf
#define CONFIG_START_SECTOR 0x01
#define CONFIG_SECTOR (CONFIG_START_SECTOR + 0)
#define OFFSET 124 // ker se na začetku krneki prepisuje
#define CONFIG_ADDR (SPI_FLASH_SEC_SIZE * CONFIG_SECTOR) + OFFSET

extern void write_to_flash(char* buffer, uint32_t size);
extern void read_flash(char* buffer, uint32_t size);

#endif