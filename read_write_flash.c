#include "read_write_flash.h"

void write_to_flash(char* buffer, uint32_t size){
    sdk_spi_flash_erase_sector(CONFIG_START_SECTOR);
    sdk_spi_flash_write(CONFIG_ADDR,(uint32_t*)buffer,size);
}

void read_flash(char* buffer, uint32_t size){
    sdk_spi_flash_read(CONFIG_ADDR, (uint32_t*)buffer, size);
}

