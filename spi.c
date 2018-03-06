/*******************************************************************
 *
 * File name: spi.c
 *
 * Copyright 2005-2006 by Checkpoint Systems as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential 
 * property of Checkpoint Systems. The use, copying, 
 * transfer or disclosure of such information is 
 * prohibited except by express written consent 
 * from Checkpoint Systems.
 *
 * Description: 
 * 
 * Creator:
 *
 * Date Created:
 *
 * $History: spi.c $
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:09p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added pre-defines to comment out Hafnon code for host SPI.
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:49p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * File header added
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:03p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * This is initial checkin
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 1:56p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#include "spi.h"

#define HOST_BUFFER_SIZE		128
#define DDS_BUFFER_SIZE			32
volatile uint8_t host_buffer[HOST_BUFFER_SIZE];
volatile uint8_t dds_buffer[DDS_BUFFER_SIZE];
volatile uint8_t *host_ptr;
volatile uint8_t *dds_ptr;

#if HALFNON

ISR(HOST_SPI_vect)
{
	// really simple ring buffer for example - handle wrap
	if (host_ptr == (host_buffer + HOST_BUFFER_SIZE)) {
		host_ptr = host_buffer;
	}
	
	// get data from peripheral data holding register and increment pointer
	*host_ptr = HOST_SPI.DATA;
	host_ptr++;
}

void host_spi_init(void)
{
	// initialize pointer to buffer
	host_ptr = host_buffer;
	
	// enable SPI peripheral in MODE3, slave mode
	HOST_SPI.CTRL = (SPI_ENABLE_bm | SPI_MODE_0_gc | SPI_DORD_bm);
	
	// setup SPI peripheral interrupts before enabling the port
	HOST_SPI.INTCTRL = SPI_INTLVL_HI_gc;
}

void host_spi_enable(void)
{
	HOST_SPI_PORT.DIRSET = HOST_MISO;
	
	HOST_SPI.CTRL |= (SPI_ENABLE_bm);
}

void host_spi_disable(void)
{
	HOST_SPI_PORT.DIRCLR = HOST_MISO;
	
	HOST_SPI.CTRL &=~(SPI_ENABLE_bm);
}

#endif

#if USE_DDS
void dds_spi_init(void)
{
	
	uint16_t bsel_value;
	
	// Note :
	// for setting the USART as a SPI master Look ate the 
	// example USART_EXAMPLE1 of the ATMEL studio example 
	// usart.h and usart.c ( specially usart_init_spi function).
	
	// Setting the Clock direction 
	DDS_SPI_PORT.DIRSET = DDS_SCK;
	
	// Setting the mode for the clock 
	// Pin5 is CLK so we have to use that control register
	// Please refer to the SPI mode page 284 (Table 23-2) XMEGA Manual 
	// for AD9833 we have to set it us as Mode 2 (see below) 
	// Mode 1 : UPCHA == 1 INVEN == 0
	// Mode 2 : UPCHA == 0 INVEN == 1
	// for Mode 2 INVEN == 1 set IOPORT_MODE_INVERT_PIN 
	DDS_SPI_PORT.PIN5CTRL  = PORT_OPC_TOTEM_gc | IOPORT_MODE_INVERT_PIN ;
	
		
	// Seting the CLockoutpit to High
	DDS_SPI_PORT.OUTSET = DDS_SCK;
	
	// Setting the USART Control Registers Register C
	// We have to Set it as a SPI master 
	DDS_SPI.CTRLC = 0;
	//DDS_SPI.CTRLC = (USART_CMODE_MSPI_gc | USART_CHSIZE_8BIT_gc);
	DDS_SPI.CTRLC = USART_CMODE_MSPI_gc;

	// UPCHA	
	// Please refer to the SPI mode page 284 (Table 23-2) XMEGA Manual 
	// for AD9833 we have to set it us as Mode 2 (see below) 
	// Mode 1 : UPCHA == 1 INVEN == 0
	// Mode 2 : UPCHA == 0 INVEN == 1	
	// DDS_SPI.CTRLC |= USART_UCPHA_bm;  // UCPHA == 1
	DDS_SPI.CTRLC &= ~USART_UCPHA_bm;   // UCPHA == 0
		
	//DATA Order
	//DDS_SPI.CTRLC |= USART_DORD_bm;  // LSB first
	DDS_SPI.CTRLC &= ~USART_DORD_bm;  // MSB first
	
	// Set the BAUD rate
	// 2.4 MHz @ 24 MHz
	// Set both the registers for BAUD
	bsel_value = DDS_SPI_BAUD(2400000);
	DDS_SPI.BAUDCTRLB = (uint8_t)((~USART_BSCALE_gm) & (bsel_value >> 8));
	DDS_SPI.BAUDCTRLA = (uint8_t)(bsel_value);
	//DDS_SPI.BAUDCTRLA = DDS_SPI_BAUD(2400000);
	
	// Enable the transmit and receive of the USART
	DDS_SPI.CTRLB = (USART_TXEN_bm | USART_RXEN_bm);
			
}

void dds_spi_enable(void)
{
	DDS_SPI_PORT.OUTSET = DDS_NCS;

	DDS_SPI_PORT.DIRSET = (DDS_MOSI | DDS_NCS | DDS_SCK);
	
	//DDS_SPI.CTRLB = (USART_TXEN_bm | USART_RXEN_bm);	 // Only enable the the transmit
	DDS_SPI.CTRLB = (USART_TXEN_bm );

}

void dds_spi_disable(void)
{
	DDS_SPI_PORT.DIRCLR = (DDS_MOSI | DDS_NCS | DDS_SCK);
	
	DDS_SPI.CTRLB = 0x00;
}


/*

void dds_send_data(uint8_t *data, uint8_t len)
{
	uint8_t cnt = len;
	
	// assert NCS pin
	DDS_SPI_PORT.OUTCLR = DDS_NCS;
	
	do {
		// load USART/SPI Transmit holding register
		DDS_SPI.DATA = *data;
		
		// wait until TX complete flag is set
		while (!(DDS_SPI.STATUS & USART_RXCIF_bm));
		
		// clear TX complete flag
		DDS_SPI.STATUS = USART_RXCIF_bm;
		
		// get received data
		*data++ = DDS_SPI.DATA;
		
	} while (--cnt);
	
	// de-assert NCS pin
	DDS_SPI_PORT.OUTSET = DDS_NCS;
	
}

*/

#if 1  // still need to test
void dds_send_data( uint16_t data )
{

	//Send the first 8 Bits of data (MSW)
 
	// See if the data register is Empty
	while ( 0 == (DDS_SPI.STATUS & USART_DREIF_bm));
		
	// Set up the data register
	DDS_SPI.DATA = ((uint8_t)(data>>8));

	// Bring the FSYNC of the SPI down see timing of DDS9833
	// Data sheet page 4
	// assert NCS pin
	DDS_SPI_PORT.OUTCLR = DDS_NCS;
			
	// Checks if the TX complete interrupt flag is set.
	while (!(DDS_SPI.STATUS & USART_TXCIF_bm));

	// clear TX complete flag
	DDS_SPI.STATUS = USART_TXCIF_bm;
	
	//Send the second 8 Bits of data (LSW)	

	// See if the data register is Empty
	while ( 0 == (DDS_SPI.STATUS & USART_DREIF_bm));
		
	// Set up the data register
	DDS_SPI.DATA = ((uint8_t)data);
	
	// Checks if the TX complete interrupt flag is set.
	while (!(DDS_SPI.STATUS & USART_TXCIF_bm));	
	
	// de-assert NCS pin , bring the FSYNC up again
	DDS_SPI_PORT.OUTSET = DDS_NCS;
	
	// clear TX complete flag
	DDS_SPI.STATUS = USART_TXCIF_bm;
	
}
#endif

#endif
