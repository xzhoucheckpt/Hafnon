/*
 * rs232.h
 *
 * Created: 5/24/2013 12:22:26 PM
 *  Author: dubes
 * $History: rs232.h $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:08p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Added files to support DMS tool
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 7/07/13    Time: 6:44p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * 1.The functionality related with DMS interface and GPIO is     unit
 * tested and checked in2.Test Code Commented out
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 7/05/13    Time: 4:37p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * Final Tested Code , This Code is Functionaly completewith 7 Test Cases
 * Should be used for Debug if we have problem
 * 
 * *****************  Version 1  *****************
 * User: Dubes        Date: 7/04/13    Time: 1:18p
 * Created in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * DMS interface code with the Test Code test cases are listed in main
 * while loop Cases 1 to 6
 */ 

#include "lowlevel.h"
#include "utility/status_codes.h"

#ifndef RS232_H_
#define RS232_H_

/*
* Taken from usart.h, not including it since it may increase the foot print
*/

// For testing on Halfnon H/W  Revert back from D to C for Thorite
#define DMS_RS232					USARTC1
//-> for Half non#define DMS_RS232					USARTD1
#define DMS_RS232_PORT				PORTC
//-> for Halfnon#define DMS_RS232_PORT				PORTD

#define DMS_RS232_PIN_OUT				PIN7_bm

#define DMS_RS232_PIN_IN				PIN6_bm

#define DMS_RS232_PINCTRL			PIN4CTRL
#define DMS_RS232_NCS				PIN4_bm
#define DMS_RS232_SCK				PIN5_bm
#define DMS_RS232_MOSI				PIN7_bm

//#define RS23_DMS				&USARTC0
#define RS232_DMS_BAUDRATE		115200
// Changed from 8 to 9
#define RS232_DMS_CHAR_LENGTH    USART_CHSIZE_8BIT_gc
//#define RS232_DMS_CHAR_LENGTH    USART_CHSIZE_9BIT_gc
#define RS232_DMS_PARITY         USART_PMODE_DISABLED_gc
//#define RS232_DMS_STOP_BIT       false
#define RS232_DMS_STOP_BIT       true


//! Input parameters when initializing RS232 and similar modes.
typedef struct usart_rs232_options {
	//! Set baud rate of the USART (unused in slave modes).
	uint32_t baudrate;

	//! Number of bits to transmit as a character (5 to 9).
	USART_CHSIZE_t charlength;

	//! Parity type: USART_PMODE_DISABLED_gc, USART_PMODE_EVEN_gc,
	//! USART_PMODE_ODD_gc.
	USART_PMODE_t paritytype;

	//! Number of stop bits between two characters:
	//! true: 2 stop bits
	//! false: 1 stop bit
	bool stopbits;

} usart_rs232_options_t;

//! USART interrupt levels
enum usart_int_level_t {
	USART_INT_LVL_OFF = 0x00,
	USART_INT_LVL_LO = 0x01,
	USART_INT_LVL_MED = 0x02,
	USART_INT_LVL_HI = 0x03,
};

// A simplified version of set baud rate see usart.c bool usart_set_baudrate(USART_t *usart, uint32_t baud, uint32_t cpu_hz) for more details
int8_t usart_set_baudrate(void);
void dms_rs232_init(void);
void dms_rs232_enable(void);
void dms_rs232_disable(void);
// A simplified version of put char and get char taken from usart.c
enum status_code dms_rs232_putchar(uint8_t c);

// There are three variation of getchar
// 1. Blocking getchar : original dms_rs232_getchar
// 2. Blocking With timer : to be used inside the DMS interface dms_rs232_getchar_block_timer
// 3. Non Blocking : to be used in the main to get the first char from the DMS dms_rs232_getchar_non_block
uint8_t dms_rs232_getchar(void);
uint8_t dms_rs232_getchar_block_timer(void);
uint8_t dms_rs232_getchar_non_block(void);
 
// Test Code
//void dms_rs232_send_data( uint16_t data );
void dms_rs232_send_data_length( uint8_t tx_length );
// Test Code
//void dms_rs232_receive_data( uint16_t data );

// Test code
//void dms_rs232_send_data_in( uint16_t data );

#endif /* RS232_H_ */