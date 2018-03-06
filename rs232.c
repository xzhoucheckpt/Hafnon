/*
 * rs232.c
 *
 * Created: 5/24/2013 12:22:48 PM
 *  Author: dubes
 *
 * $History: rs232.c $
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * code to stop RTC properly  timer if the timer times out
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/28/13    Time: 2:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * use tx_length insted of COM_BUF_SIZE 
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
 * *****************  Version 3  *****************
 * User: Dubes        Date: 7/07/13    Time: 6:44p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * 1.The functionality related with DMS interface and GPIO is     unit
 * tested and checked in2.Test Code Commented out
 * 
 * *****************  Version 2  *****************
 * User: Dubes        Date: 7/04/13    Time: 6:42p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * 3 different get char function for rs 232 and reset functionility
 * 
 * *****************  Version 1  *****************
 * User: Dubes        Date: 7/04/13    Time: 1:18p
 * Created in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * DMS interface code with the Test Code test cases are listed in main
 * while loop Cases 1 to 6
*/


#include "rs232.h"
#include "globals.h"
#include "timers.h"
#include "interface.h"
#include "dms_interface.h"

/**
 * \brief Set the baudrate value in the USART module
 *
 * This function sets the baudrate register with scaling regarding the CPU
 * frequency and makes sure the baud rate is supported by the hardware.
 * The function can be used if you don't want to calculate the settings
 * yourself or changes to baudrate at runtime is required.
 *
 *
 * \retval true if the hardware supports the baud rate
 * \retval false if the hardware does not support the baud rate (i.e. it's
 *               either too high or too low.)
 */
// Used Function
int8_t usart_set_baudrate(void)
{
	int8_t exp;
	int8_t ret_value = 0;
	uint32_t div;
	uint32_t limit;
	uint32_t ratio;
	uint32_t min_rate;
	uint32_t max_rate;
	uint32_t cpu_hz = F_CPU;
	uint32_t baud = RS232_DMS_BAUDRATE;

	/*
	 * Check if the hardware supports the given baud rate
	 */
	/* 8 = (2^0) * 8 * (2^0) = (2^BSCALE_MIN) * 8 * (BSEL_MIN) */
	max_rate = cpu_hz / 8;
	/* 4194304 = (2^7) * 8 * (2^12) = (2^BSCALE_MAX) * 8 * (BSEL_MAX+1) */
	min_rate = cpu_hz / 4194304;

	if (!(DMS_RS232.CTRLB & USART_CLK2X_bm)) {
		max_rate /= 2;
		min_rate /= 2;
	}

	if ((baud > max_rate) || (baud < min_rate)) {
		ret_value = 0;
		
	} 
	else
	{

		/* Check if double speed is enabled. */
		if (!(DMS_RS232.CTRLB & USART_CLK2X_bm)) {
			baud *= 2;
		}

		/* Find the lowest possible exponent. */
		limit = 0xfffU >> 4;
		ratio = cpu_hz / baud;

		for (exp = -7; exp < 7; exp++) {
			if (ratio < limit) {
				break;
			}

			limit <<= 1;

			if (exp < -3) {
				limit |= 1;
			}
		}

		/*
		 * Depending on the value of exp, scale either the input frequency or
		 * the target baud rate. By always scaling upwards, we never introduce
		 * any additional inaccuracy.
		 *
		 * We are including the final divide-by-8 (aka. right-shift-by-3) in
		 * this operation as it ensures that we never exceeed 2**32 at any
		 * point.
		 *
		 * The formula for calculating BSEL is slightly different when exp is
		 * negative than it is when exp is positive.
		 */
		if (exp < 0) {
			/* We are supposed to subtract 1, then apply BSCALE. We want to
			 * apply BSCALE first, so we need to turn everything inside the
			 * parenthesis into a single fractional expression.
			 */
			cpu_hz -= 8 * baud;

			/* If we end up with a left-shift after taking the final
			 * divide-by-8 into account, do the shift before the divide.
			 * Otherwise, left-shift the denominator instead (effectively
			 * resulting in an overall right shift.)
			 */
			if (exp <= -3) {
				div = ((cpu_hz << (-exp - 3)) + baud / 2) / baud;
			} else {
				baud <<= exp + 3;
				div = (cpu_hz + baud / 2) / baud;
			}
		} else {
			/* We will always do a right shift in this case, but we need to
			 * shift three extra positions because of the divide-by-8.
			 */
			baud <<= exp + 3;
			div = (cpu_hz + baud / 2) / baud - 1;
		}

		DMS_RS232.BAUDCTRLB = (uint8_t)(((div >> 8) & 0X0F) | (exp << 4));
		DMS_RS232.BAUDCTRLA = (uint8_t)div;
		ret_value = 1;
	
	} // end of if	

	return ret_value;
}


// Used Function
void dms_rs232_init(void)
{
	//int8_t result = 0;
	
	//DMS_RS232_PIN_OUT				PIN7_bm

     //DMS_RS232_PIN_IN				PIN6_bm
	
	
	//#define DMS_RS232_PORT				PORTC
	// Set the TxD pin high - set PORTC DIR register bit 3 to 1
	//PORTC.OUTSET = PIN3_bm;
	//PORTD.OUTSET = 0x80;
//  Out put
	DMS_RS232_PORT.OUTSET = DMS_RS232_PIN_OUT;
	// Set the TxD pin as an output - set PORTC OUT register bit 3 to 1
	//	PORTC.DIRSET = PIN3_bm;
	// PORTD.DIRSET = 0x80;
	DMS_RS232_PORT.DIRSET = DMS_RS232_PIN_OUT;
// Input 
	//  Out put
	//DMS_RS232_PORT.OUTCLR = DMS_RS232_PIN_IN;
	// Set the TxD pin as an output - set PORTC OUT register bit 3 to 1
	//	PORTC.DIRSET = PIN3_bm;
	// PORTD.DIRSET = 0x80;
	DMS_RS232_PORT.DIRCLR = DMS_RS232_PIN_IN;
		
	// RS232_DMS_BAUDRATE	   115200
	// RS232_DMS_CHAR_LENGTH    USART_CHSIZE_8BIT_gc
	// RS232_DMS_PARITY         USART_PMODE_DISABLED_gc
	// RS232_DMS_STOP_BIT       false
		
	// sysclk_enable_module(SYSCLK_PORT_C, SYSCLK_USART1);  // The name of the function is misleading
	// Done in restore from sleep 
	//PR.PRPC &=~(PR_SPI_bm | PR_TC0_bm | PR_TC1_bm | PR_USART1_bm); // USARTC1 code PR_USART1_bm
		
	// Setting the mode
	// usart_set_mode(usart, USART_CMODE_ASYNCHRONOUS_gc);
	DMS_RS232.CTRLC = ( DMS_RS232.CTRLC & (~USART_CMODE_gm)) | USART_CMODE_ASYNCHRONOUS_gc;

	// Setting the Format USART_SERIAL_DMS_CHAR_LENGTH, USART_SERIAL_DMS_PARITY, USART_SERIAL_DMS_STOP_BIT
	//usart_format_set(usart, opt->charlength, opt->paritytype, opt->stopbits);
		
	//DMS_RS232.CTRLC = (uint8_t)RS232_DMS_CHAR_LENGTH | RS232_DMS_PARITY | ( RS232_DMS_STOP_BIT ? USART_SBMODE_bm : 0 );
	
	DMS_RS232.CTRLC = RS232_DMS_CHAR_LENGTH | RS232_DMS_PARITY | ( RS232_DMS_STOP_BIT ? USART_SBMODE_bm : 0 );
	
		
	// Setting the Baud Rate RS232_DMS_BAUDRATE
	// result = usart_set_baudrate(usart, opt->baudrate, sysclk_get_per_hz());
		
	//result = usart_set_baudrate( );
	usart_set_baudrate( );
		
	// Enable the transmission
	//usart_tx_enable(usart);
	DMS_RS232.CTRLB |= USART_TXEN_bm;
		
	// Enable the receiver
	//usart_rx_enable(usart);
	DMS_RS232.CTRLB |= USART_RXEN_bm;
		
}	
// Used Function
void dms_rs232_enable(void)
{
	// Enable the transmission
	DMS_RS232.CTRLB |= USART_TXEN_bm;
	// Enable the receiver
	DMS_RS232.CTRLB |= USART_RXEN_bm;

}
// Used Function
void dms_rs232_disable(void)
{
	// Disable the transmission
	DMS_RS232.CTRLB &= ~USART_TXEN_bm;
	// Disable the receiver
	DMS_RS232.CTRLB &= ~USART_RXEN_bm;
}


/**
 * \brief Send a data with the USART module
 *
 * This function outputs a data using the USART module.
 *
 * \param usart The USART module.
 * \param c The data to send.
 *
 * \return STATUS_OK
 */
// Used Function
enum status_code dms_rs232_putchar(uint8_t c)
{
	while ( (DMS_RS232.STATUS & USART_DREIF_bm ) == 0) {
	}
	
	DMS_RS232.DATA = c;
	return STATUS_OK;
}

/**
 * \brief Receive a data with the USART module
 *
 * This function returns the received data from the USART module.
 *
 * \param usart The USART module.
 *
 * \return The received data.
 */
// There are three variation of getchar
// 1. Blocking getchar : original
// 2. Blocking With timer : to be used inside the DMS interface
// 3. Non Blocking : to be used in the main to get the first char from the DMS

// Used Function
// 1. Blocking getchar : original
uint8_t dms_rs232_getchar(void)
{
	while ( (DMS_RS232.STATUS & USART_RXCIF_bm) == 0 ) {		
	}
	
	return (DMS_RS232.DATA);
}

// Used Function
// 2. Blocking With timer : to be used inside the DMS interface
uint8_t dms_rs232_getchar_block_timer(void)
{
	uint16_t counterValue = 0;

	while ( (DMS_RS232.STATUS & USART_RXCIF_bm) == 0 ) {
		
		counterValue = INTERLOCK_TIMER.CNT ;
		if ( counterValue >  DMS_TIMEOUT)
		{
			bAborted = DMS_DISCONNECT_INDICATION_NOCOM; // If the time out occurs we want to abort the session
			do
			{
				// Wait until RTC is not busy.
			} while ( RTC.STATUS & RTC_SYNCBUSY_bm );			
			rtc_interlock_timer_stop();
			break; // Break the loop
		}
	}
	
	return (DMS_RS232.DATA);
}

// Used Function
// 3. Non Blocking : to be used in the main to get the first char from the DMS
uint8_t dms_rs232_getchar_non_block(void)
{	
	return (DMS_RS232.DATA);
}

/*
// Test Code
void dms_rs232_send_data( uint16_t data )
{
	uint8_t tx_buf[] = "\n\rHello AVR world ! : "; // For testing will be take out later
	uint8_t tx_length = 22;
	uint8_t i, j = 0;
	
	while ( j < 10){
//	while (1){
		// Send "message header"
		for (i = 0; i < tx_length; i++) {
			dms_rs232_putchar(tx_buf[i]);
		}
		j = j+ 1;
	}

}
*/
/*
// Test code
void dms_rs232_send_data_in( uint16_t data )
{
	uint8_t tx_buf[] = "\n\rHello ATT world ! : "; // For testing will be take out later
	uint8_t tx_length = 22;
	uint8_t i, j = 0;
	
	while ( j < 10){
		//	while (1){
		// Send "message header"
		for (i = 0; i < tx_length; i++) {
			dms_rs232_putchar(tx_buf[i]);
		}
		j = j+ 1;
	}

}
*/
// One of the function used

void dms_rs232_send_data_length( uint8_t tx_length )
{
	uint8_t i;
	
	// Send "message header" COM_BUF_SIZE tx_length
	/*
	for (i = 0; i < COM_BUF_SIZE ; i++) {
		dms_rs232_putchar(messageBufferOut[i]);
	}
	*/
	for (i = 0; i < tx_length ; i++) {
		dms_rs232_putchar(messageBufferOut[i]);
	}

}

/*
// Test Code
void dms_rs232_receive_data( uint16_t data )
{
	uint8_t received_byte;
// For testing it is while loop the while loop will be out side 
	// Get and echo a character forever, specific '\r' processing.
	while (true)
	{
		received_byte = dms_rs232_getchar( );
		if (received_byte == '\r') 
		{
			dms_rs232_send_data_in( 16 ); //for testing we are just sending some data
		} else
		{
			dms_rs232_putchar(received_byte) ;
		}			
	}
}
*/

