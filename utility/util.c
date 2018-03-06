#include <avr/io.h>
#include "util.h"

// assembly routine to write the CCP register
void ccp_write_io(volatile uint8_t *addr, uint8_t value)
{
	volatile uint8_t * tmpAddr = addr;
	
	asm volatile(
	"movw r30,    %0"           "\n\t"
	"ldi r16,     %2"           "\n\t"
	"out %3,      r16"   "\n\t"
	"st Z,        %1"           "\n\t"
	:
	: "r" (tmpAddr), "r" (value), "M" (CCP_IOREG_gc), "i" (&CCP)
	: "r16", "r30", "r31");
}


