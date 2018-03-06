/*
 * nvm_eeprom.c
 *
 * Created: 6/3/2013 11:38:17 AM
 *  Author: dubes
 *
 * $History: nvm_eeprom.c $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:08p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Added files to support DMS tool
 * 
 * *****************  Version 2  *****************
 * User: Dubes        Date: 7/07/13    Time: 6:44p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * 1.The functionality related with DMS interface and GPIO is     unit
 * tested and checked in2.Test Code Commented out
 * 
 * *****************  Version 1  *****************
 * User: Dubes        Date: 7/04/13    Time: 1:18p
 * Created in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * DMS interface code with the Test Code test cases are listed in main
 * while loop Cases 1 to 7
 */ 

// Taken from nvm.c eeprom related function.


#include "utility/compiler.h"
#include "utility/util.h"
#include "lowlevel.h"
//#include "ccp.h"
#include "nvm_eeprom.h"
#include <string.h>


/**
 * \weakgroup nvm_eeprom_group
 * @{
 */

/**
 * \brief Read one byte from EEPROM using mapped access.
 *
 * This function reads one byte from EEPROM using mapped access.
 *
 * \param  addr       EEPROM address, between 0 and EEPROM_SIZE
 *
 *  \return  Byte value read from EEPROM.
 */
uint8_t nvm_eeprom_read_byte(eeprom_addr_t addr)
{
	uint8_t data;
	Assert(addr <= EEPROM_SIZE);

	/* Wait until NVM is ready */
	nvm_wait_until_ready();
	eeprom_enable_mapping();
	data = *(uint8_t*)(addr + MAPPED_EEPROM_START),
	eeprom_disable_mapping();
	return data;
}

/**
 * \brief Read buffer within the eeprom
 *
 * \param address   the address to where to read
 * \param buf       pointer to the data
 * \param len       the number of bytes to read
 */
void nvm_eeprom_read_buffer(eeprom_addr_t address, void *buf, uint16_t len)
{
	nvm_wait_until_ready();
	eeprom_enable_mapping();
	memcpy( buf,(void*)(address+MAPPED_EEPROM_START), len );
	eeprom_disable_mapping();
}


/**
 * \brief Write one byte to EEPROM using IO mapping.
 *
 * This function writes one byte to EEPROM using IO-mapped access.
 * This function will cancel all ongoing EEPROM page buffer loading
 * operations, if any.
 *
 * \param  address    EEPROM address (max EEPROM_SIZE)
 * \param  value      Byte value to write to EEPROM.
 */
void nvm_eeprom_write_byte(eeprom_addr_t address, uint8_t value)
{
	uint8_t old_cmd;

	Assert(address <= EEPROM_SIZE);
	/*  Flush buffer to make sure no unintentional data is written and load
	 *  the "Page Load" command into the command register.
	 */
	old_cmd = NVM.CMD;
	nvm_eeprom_flush_buffer();
	// Wait until NVM is ready
	nvm_wait_until_ready();
	nvm_eeprom_load_byte_to_buffer(address, value);

	// Set address to write to
	NVM.ADDR2 = 0x00;
	NVM.ADDR1 = (address >> 8) & 0xFF;
	NVM.ADDR0 = address & 0xFF;

	/*  Issue EEPROM Atomic Write (Erase&Write) command. Load command, write
	 *  the protection signature and execute command.
	 */
	NVM.CMD = NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc;
	nvm_exec();
	NVM.CMD = old_cmd;
}

/**
 * \brief Write buffer within the eeprom
 *
 * \param address   the address to where to write
 * \param buf       pointer to the data
 * \param len       the number of bytes to write
 */
void nvm_eeprom_erase_and_write_buffer(eeprom_addr_t address, const void *buf, uint16_t len)
{
	while (len) {
		if (((address%EEPROM_PAGE_SIZE)==0) && (len>=EEPROM_PAGE_SIZE)) {
			// A full page can be written
			nvm_eeprom_load_page_to_buffer((uint8_t*)buf);
			nvm_eeprom_atomic_write_page(address/EEPROM_PAGE_SIZE);
			address += EEPROM_PAGE_SIZE;
			buf = (uint8_t*)buf + EEPROM_PAGE_SIZE;
			len -= EEPROM_PAGE_SIZE;
		} else {
			nvm_eeprom_write_byte(address++, *(uint8_t*)buf);
			buf = (uint8_t*)buf + 1;
			len--;
		}
	}
}


/**
 * \brief Flush temporary EEPROM page buffer.
 *
 * This function flushes the EEPROM page buffers. This function will cancel
 * any ongoing EEPROM page buffer loading operations, if any.
 * This function also works for memory mapped EEPROM access.
 *
 * \note An EEPROM write operations will automatically flush the buffer for you.
 * \note The function does not preserve the value of the NVM.CMD register
 */
void nvm_eeprom_flush_buffer(void)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Flush EEPROM page buffer if necessary
	if ((NVM.STATUS & NVM_EELOAD_bm) != 0) {
		NVM.CMD = NVM_CMD_ERASE_EEPROM_BUFFER_gc;
		nvm_exec();
	}
}

/**
 * \brief Load single byte into temporary page buffer.
 *
 * This function loads one byte into the temporary EEPROM page buffers.
 * If memory mapped EEPROM is enabled, this function will not work.
 * Make sure that the buffer is flushed before starting to load bytes.
 * Also, if multiple bytes are loaded into the same location, they will
 * be ANDed together, thus 0x55 and 0xAA will result in 0x00 in the buffer.
 *
 * \note Only one page buffer exist, thus only one page can be loaded with
 *       data and programmed into one page. If data needs to be written to
 *       different pages, the loading and writing needs to be repeated.
 *
 * \param  byte_addr EEPROM Byte address, between 0 and EEPROM_PAGE_SIZE.
 * \param  value     Byte value to write to buffer.
 */
void nvm_eeprom_load_byte_to_buffer(uint8_t byte_addr, uint8_t value)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	eeprom_enable_mapping();
	*(uint8_t*)(byte_addr + MAPPED_EEPROM_START) = value;
	eeprom_disable_mapping();
}


/**
 * \brief Load entire page into temporary EEPROM page buffer.
 *
 * This function loads an entire EEPROM page from an SRAM buffer to
 * the EEPROM page buffers. If memory mapped EEPROM is enabled, this
 * function will not work. Make sure that the buffer is flushed before
 * starting to load bytes.
 *
 * \note Only the lower part of the address is used to address the buffer.
 *       Therefore, no address parameter is needed. In the end, the data
 *       is written to the EEPROM page given by the address parameter to the
 *       EEPROM write page operation.
 *
 * \param  values   Pointer to SRAM buffer containing an entire page.
 */
void nvm_eeprom_load_page_to_buffer(const uint8_t *values)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Load multiple bytes into page buffer
	uint8_t i;
	for (i = 0; i < EEPROM_PAGE_SIZE; ++i) {
		nvm_eeprom_load_byte_to_buffer(i, *values);
		++values;
	}
}

/**
 * \brief Erase and write bytes from page buffer into EEPROM.
 *
 * This function writes the contents of an already loaded EEPROM page
 * buffer into EEPROM memory.
 *
 * As this is an atomic write, the page in EEPROM will be erased
 * automatically before writing. Note that only the page buffer locations
 * that have been loaded will be used when writing to EEPROM. Page buffer
 * locations that have not been loaded will be left untouched in EEPROM.
 *
 * \param  page_addr  EEPROM Page address, between 0 and EEPROM_SIZE/EEPROM_PAGE_SIZE
 */
void nvm_eeprom_atomic_write_page(uint8_t page_addr)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Calculate page address
	uint16_t address = (uint16_t)(page_addr * EEPROM_PAGE_SIZE);

	Assert(address <= EEPROM_SIZE);

	// Set address
	NVM.ADDR2 = 0x00;
	NVM.ADDR1 = (address >> 8) & 0xFF;
	NVM.ADDR0 = address & 0xFF;

	// Issue EEPROM Atomic Write (Erase&Write) command
	nvm_issue_command(NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc);
}

/**
 * \brief Write (without erasing) EEPROM page.
 *
 * This function writes the contents of an already loaded EEPROM page
 * buffer into EEPROM memory.
 *
 * As this is a split write, the page in EEPROM will _not_ be erased
 * before writing.
 *
 * \param  page_addr  EEPROM Page address, between 0 and EEPROM_SIZE/EEPROM_PAGE_SIZE
 */
void nvm_eeprom_split_write_page(uint8_t page_addr)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Calculate page address
	uint16_t address = (uint16_t)(page_addr * EEPROM_PAGE_SIZE);

	Assert(address <= EEPROM_SIZE);

	// Set address
	NVM.ADDR2 = 0x00;
	NVM.ADDR1 = (address >> 8) & 0xFF;
	NVM.ADDR0 = address & 0xFF;

	// Issue EEPROM Split Write command
	nvm_issue_command(NVM_CMD_WRITE_EEPROM_PAGE_gc);
}

/**
 * \brief Fill temporary EEPROM page buffer with value.
 *
 * This fills the the EEPROM page buffers with a given value.
 * If memory mapped EEPROM is enabled, this function will not work.
 *
 * \note Only the lower part of the address is used to address the buffer.
 *       Therefore, no address parameter is needed. In the end, the data
 *       is written to the EEPROM page given by the address parameter to the
 *       EEPROM write page operation.
 *
 * \param  value Value to copy to the page buffer.
 */
void nvm_eeprom_fill_buffer_with_value(uint8_t value)
{
	nvm_eeprom_flush_buffer();
	// Wait until NVM is ready
	nvm_wait_until_ready();
	// Load multiple bytes into page buffer
	uint8_t i;
	for (i = 0; i < EEPROM_PAGE_SIZE; ++i) {
		nvm_eeprom_load_byte_to_buffer(i, value);
	}
}

/**
 * \brief Erase bytes from EEPROM page.
 *
 * This function erases bytes from one EEPROM page, so that every location
 * written to in the page buffer reads 0xFF.
 *
 * \param page_addr EEPROM Page address, between 0 and EEPROM_SIZE/EEPROM_PAGE_SIZE
 */
void nvm_eeprom_erase_bytes_in_page(uint8_t page_addr)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Calculate page address
	uint16_t address = (uint16_t)(page_addr * EEPROM_PAGE_SIZE);

	Assert(address <= EEPROM_SIZE);

	// Set address
	NVM.ADDR2 = 0x00;
	NVM.ADDR1 = (address >> 8) & 0xFF;
	NVM.ADDR0 = address & 0xFF;

	// Issue EEPROM Erase command
	nvm_issue_command(NVM_CMD_ERASE_EEPROM_PAGE_gc);
}

/**
 * \brief Erase EEPROM page.
 *
 * This function erases one EEPROM page, so that every location reads 0xFF.
 *
 * \param page_addr EEPROM Page address, between 0 and EEPROM_SIZE/EEPROM_PAGE_SIZE
 */
void nvm_eeprom_erase_page(uint8_t page_addr)
{
	// Mark all addresses to be deleted
	nvm_eeprom_fill_buffer_with_value(0xff);
	// Erase bytes
	nvm_eeprom_erase_bytes_in_page(page_addr);
}


/**
 * \brief Erase bytes from all EEPROM pages.
 *
 * This function erases bytes from all EEPROM pages, so that every location
 * written to in the page buffer reads 0xFF.
 */
void nvm_eeprom_erase_bytes_in_all_pages(void)
{
	// Wait until NVM is ready
	nvm_wait_until_ready();

	// Issue EEPROM Erase All command
	nvm_issue_command(NVM_CMD_ERASE_EEPROM_gc);
}

/**
 * \brief Erase entire EEPROM memory.
 *
 * This function erases the entire EEPROM memory block to 0xFF.
 */
void nvm_eeprom_erase_all(void)
{
	// Mark all addresses to be deleted
	nvm_eeprom_fill_buffer_with_value(0xff);
	// Erase all pages
	nvm_eeprom_erase_bytes_in_all_pages();
}


