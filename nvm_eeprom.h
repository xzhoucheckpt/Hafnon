/*
 * nvm_eeprom.h
 *
 * Created: 6/3/2013 11:38:42 AM
 *  Author: dubes
 *
 * $History: nvm_eeprom.h $
 * 
 * *****************  Version 2  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings
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

#include "utility/compiler.h"
#include "utility/util.h"
// Take from the nvm.h function related with eeprom
//

#ifndef NVM_EEPROM_H_
#define NVM_EEPROM_H_

/*
 * \defgroup nvm_generic_group NVM driver generic module handling
 * \ingroup nvm_group
 * \brief Support functions for the NVM driver.
 *
 * These functions are helper functions for the functions of the
 * \ref nvm_group "NVM driver".
 *
 * @{
 */

/**
 * \brief Wait for any NVM access to finish.
 *
 * This function is blocking and waits for any NVM access to finish.
 * Use this function before any NVM accesses, if you are not certain that
 * any previous operations are finished yet.
 */
static inline void nvm_wait_until_ready( void )
{
	do {
		// Block execution while waiting for the NVM to be ready
	} while ((NVM.STATUS & NVM_NVMBUSY_bm) == NVM_NVMBUSY_bm);
}

/**
 * \brief Non-Volatile Memory Execute Command
 *
 * This function sets the CCP register before setting the CMDEX bit in the
 * NVM.CTRLA register.
 *
 * \note The correct NVM command must be set in the NVM.CMD register before
 *       calling this function.
 */
static inline void nvm_exec(void)
{
	ccp_write_io((uint8_t *)&NVM.CTRLA, NVM_CMDEX_bm);
}

/**
 * \brief Non-Volatile Memory Execute Specific Command
 *
 * This function sets a command in the NVM.CMD register, then performs an
 * execute command by writing the CMDEX bit to the NVM.CTRLA register.
 *
 * \note The function saves and restores the NVM.CMD register, but if this
 *       function is called from an interrupt, interrupts must be disabled
 *       before this function is called.
 *
 * \param nvm_command NVM Command to execute.
 */
static inline void nvm_issue_command(NVM_CMD_t nvm_command)
{
	uint8_t old_cmd;

	old_cmd = NVM.CMD;
	NVM.CMD = nvm_command;
	ccp_write_io((uint8_t *)&NVM.CTRLA, NVM_CMDEX_bm);
	NVM.CMD = old_cmd;
}

/**
 * \brief Read one byte using the LDI instruction
 * \internal
 *
 * This function sets the specified NVM_CMD, reads one byte using at the
 * specified byte address with the LPM instruction. NVM_CMD is restored after
 * use.
 *
 * \note Interrupts should be disabled before running this function
 *       if program memory/NVM controller is accessed from ISRs.
 *
 * \param nvm_cmd NVM command to load before running LPM
 * \param address Byte offset into the signature row
 */
uint8_t nvm_read_byte(uint8_t nvm_cmd, uint16_t address);  // was earlier listed in  util.h


/**
 * \brief Perform SPM write
 * \internal
 *
 * This function sets the specified NVM_CMD, sets CCP and then runs the SPM
 * instruction to write to flash.
 *
 * \note Interrupts should be disabled before running this function
 *       if program memory/NVM controller is accessed from ISRs.
 *
 * \param addr Address to perform the SPM on.
 * \param nvm_cmd NVM command to use in the NVM_CMD register
 */
//void nvm_common_spm(uint32_t addr, uint8_t nvm_cmd);

/**
 * \defgroup nvm_eeprom_group NVM driver EEPROM handling
 * \ingroup nvm_group
 * \brief Functions for handling internal EEPROM memory.
 *
 * The internal EEPROM can be used to store data that will persist after
 * power is removed. This can typically be used to store calibration data,
 * application state, encryption keys or other data that need to be preserved
 * when power is removed.
 *
 * The functions in this module uses IO register access to manipulate the
 * EEPROM.
 *
 * \note The functions in this module are modifying the NVM.CMD register.
 *       If the application are using program space access in interrupts
 *       (__flash pointers in IAR EW or pgm_read_byte in GCC) interrupts
 *       needs to be disabled when running EEPROM access functions. If not
 *       the program space reads will be corrupted.
 * @{
 */


#ifndef EEPROM_PAGE_SIZE
#  if XMEGA_A || XMEGA_AU || XMEGA_B || XMEGA_C || XMEGA_D || XMEGA_E
#    define EEPROM_PAGE_SIZE 32
#  else
#    error Unknown EEPROM page size
#  endif
#endif

#ifndef CONFIG_NVM_IGNORE_XMEGA_A3_D3_REVB_ERRATA
#  if XMEGA_A3 || XMEGA_D3
#    error This NVM driver does not support rev B of XMEGA A3/D3 devices. \
     Set CONFIG_NVM_IGNORE_XMEGA_A3_D3_REVB_ERRATA to disable this message
#  endif
#endif

/**
 * Data type for holding eeprom memory addresses.
 */
typedef uint16_t eeprom_addr_t;

/*! \brief Enable EEPROM mapping into data space.
 *
 *  This macro enables mapping of EEPROM into data space.
 *  EEPROM starts at EEPROM_START in data memory. Read access
 *  can be done similar to ordinary SRAM access.
 *
 *  \note This disables IO-mapped access to EEPROM, although page erase and
 *        write operations still needs to be done through IO register.
 */
static inline void eeprom_enable_mapping(void)
{
#if !XMEGA_E
	NVM_CTRLB = NVM_CTRLB | NVM_EEMAPEN_bm;
#endif
}


/*! \brief Disable EEPROM mapping into data space.
 *
 *  This macro disables mapping of EEPROM into data space.
 *  IO mapped access is now enabled.
 */
static inline void eeprom_disable_mapping(void)
{
#if !XMEGA_E
	NVM_CTRLB = NVM_CTRLB & ~NVM_EEMAPEN_bm;
#endif
}

// High Level Function used in the DMS code
uint8_t nvm_eeprom_read_byte(eeprom_addr_t addr);
void nvm_eeprom_write_byte(eeprom_addr_t address, uint8_t value);
void nvm_eeprom_read_buffer(eeprom_addr_t address, void *buf, uint16_t len);
void nvm_eeprom_erase_and_write_buffer(eeprom_addr_t address, const void *buf, uint16_t len);

// Low level functions
void nvm_eeprom_flush_buffer(void);
void nvm_eeprom_load_byte_to_buffer(uint8_t byte_addr, uint8_t value);
void nvm_eeprom_load_page_to_buffer(const uint8_t *values);
void nvm_eeprom_atomic_write_page(uint8_t page_addr);
void nvm_eeprom_split_write_page(uint8_t page_addr);
void nvm_eeprom_fill_buffer_with_value(uint8_t value);
void nvm_eeprom_erase_bytes_in_page(uint8_t page_addr);
void nvm_eeprom_erase_page(uint8_t page_addr);
void nvm_eeprom_erase_bytes_in_all_pages(void);
void nvm_eeprom_erase_all(void);


#endif /* NVM_EEPROM_H_ */