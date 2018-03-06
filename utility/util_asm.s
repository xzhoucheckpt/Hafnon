#include "assembler.h"

#if defined(__GNUC__)
//! Value to write to CCP for access to protected IO registers.
#  define CCP_SPM_gc 0x9D

//! NVM busy flag
#  define NVM_NVMBUSY_bp 7

//! NVM command for loading flash buffer
#  define NVM_CMD_LOAD_FLASH_BUFFER_gc 0x23
#elif defined(__IAR_SYSTEMS_ASM__)
// All values are defined for IAR
#else
# error Unknown assembler
#endif

PUBLIC_FUNCTION(nvm_read_byte)
#if defined(__GNUC__)
	lds r20, NVM_CMD          ; Store NVM command register
	mov ZL, r22               ; Load byte index into low byte of Z.
	mov ZH, r23               ; Load high byte into Z.
	sts NVM_CMD, r24          ; Load prepared command into NVM Command register.
	lpm r24, Z                ; Perform an LPM to read out byte
	sts NVM_CMD, r20          ; Restore NVM command register
#elif defined(__IAR_SYSTEMS_ASM__)
	lds r20, NVM_CMD          ; Store NVM command register
	mov ZL, r18               ; Load byte index into low byte of Z.
	mov ZH, r19               ; Load high byte into Z.
	sts NVM_CMD, r16          ; Load prepared command into NVM Command register.
	lpm r16, Z                ; Perform an LPM to read out byte
	sts NVM_CMD, r20          ; Restore NVM command register
#endif

	ret

END_FUNC(nvm_read_byte)


/**
	* \brief Perform SPM command
	*/
	//PUBLIC_FUNCTION_SEGMENT(nvm_common_spm, BOOT)

//	PUBLIC_FUNCTION(nvm_common_spm)

//#if defined(__GNUC__)
	/**
	 * For GCC:
	 * \param address uint32_t r22:r25
	 * \param nvm_cmd uint8_t  r20
	 */
//	in r25, RAMPZ         ; Store RAMPZ. Highest address byte is ignored, so using that
//	out RAMPZ, r24        ; Load R24 into RAMPZ
//	movw ZL, r22          ; Load R22:R23 into Z.
//	lds r24, NVM_CMD      ; Store NVM command register (r24 is no longer needed)
//	sts NVM_CMD, r20      ; Load prepared command into NVM Command register.
//	ldi r23, CCP_SPM_gc   ; Prepare Protect SPM signature (r23 is no longer needed)
//	sts CCP, r23          ; Enable SPM operation (this disables interrupts for 4 cycles).
//	spm                   ; Self-program.
//	sts NVM_CMD, r24      ; Restore NVM command register
//	out RAMPZ, r25        ; Restore RAMPZ register.
//#elif defined(__IAR_SYSTEMS_ASM__)
	/**
	 * For IAR:
	 * \param address uint32_t r16:r19
	 * \param nvm_cmd uint8_t  r20
	 */
//	in r19, RAMPZ         ; Store RAMPZ. Highest address byte is ignored, so using that
//	out RAMPZ, r18        ; Load R18 into RAMPZ
//	movw ZL, r16          ; Load R16:R17 into Z.
//	lds r18, NVM_CMD      ; Store NVM command register (r18 is no longer needed)
//	sts NVM_CMD, r20      ; Load prepared command into NVM Command register.
//	ldi r19, CCP_SPM_gc   ; Prepare Protect SPM signature (r19 is no longer needed)
//	sts CCP, r19          ; Enable SPM operation (this disables interrupts for 4 cycles).
//	spm                   ; Self-program.
//	sts NVM_CMD, r18      ; Restore NVM command register
//	out RAMPZ, r19        ; Restore RAMPZ register.
//#endif

//	ret

//	END_FUNC(nvm_common_spm)
