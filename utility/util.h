#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>

void ccp_write_io(volatile uint8_t *addr, uint8_t value);
uint8_t nvm_read_byte(uint8_t nvm_cmd, uint16_t address);


#endif