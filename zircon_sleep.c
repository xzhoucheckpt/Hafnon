/*******************************************************************
 *
 * File name: zircon_sleep.c
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
 * Creator: Joe Galanti
 *
 * Date Created:
 *
 * $History: zircon_sleep.c $
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 1/28/14    Time: 8:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Use new dac_write_data() function
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:19p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Reducing resource needs by consoladating
 * 
 ******************************************************************/

#if HALFNON

#include "globals.h"
#include "zircon_sleep.h"
#include "analog.h"

void prepare_for_sleep(void)
{
	
	#if HALFNON
	// turn off everything that is not needed during sleep...that means most everything!
	ac_disable();
	#endif
	
	//host_spi_disable();
	
	#if USE_DDS
	// Disable the DSS and the disable the spi
	DDS_mclk_timer_stop();
	ad9833_set_mode(AD_OFF); // The DDS is turned off
	dds_spi_disable();
	#else
	// Disable DAC and set the index to zero
	dac_disable();
	#endif

	// Set the index for TX frequencies to zero
	gDACIndexLoaded = 0;
	
	pwm_stop();
	rtc_interlock_timer_stop();
	frame_timer_stop();
	
	//cycle_timer_stop();
	
	#if 0
	// set all I/O pins to inputs
	// JRG some of the pins to the HW are active low so they may needed to be set high
	// when in sleep mode
	PORTA.OUT = 0x00;
	PORTA.DIR = 0x00;
	//PORTCFG.MPCMASK = 0xf7;
	//PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc;
	
	PORTB.OUT = 0x00;
	PORTB.DIR = 0x00;
	//PORTCFG.MPCMASK = 0xff;
	//PORTB.PIN0CTRL = PORT_OPC_PULLUP_gc;
	
	PORTC.OUT = 0x00;
	PORTC.DIR = 0x00;
	//PORTCFG.MPCMASK = 0xfe;
	//PORTC.PIN0CTRL = PORT_OPC_PULLUP_gc;
	
	PORTD.OUT = 0x00;
	PORTD.DIR = 0x00;
	//PORTCFG.MPCMASK = 0xff;
	//PORTD.PIN0CTRL = PORT_OPC_PULLUP_gc;
	
	PORTE.OUT = 0x00;
	PORTE.DIR = 0x00;
	//PORTCFG.MPCMASK = 0xfb;
	//PORTE.PIN0CTRL = PORT_OPC_PULLUP_gc;
	#endif
	
	#if 0
	// PR.PRGEN = (PR_USB_bm | PR_AES_bm | PR_EBI_bm | PR_RTC_bm | PR_EVSYS_bm | PR_DMA_bm);
	PR.PRPA = (/*PR_DAC_bm | PR_ADC_bm |*/ PR_AC_bm);
	PR.PRPB = (PR_DAC_bm | /*PR_ADC_bm | PR_AC_bm*/);
	PR.PRPC = (/*PR_TWI_bm | PR_USART1_bm | PR_USART0_bm |*/ PR_SPI_bm | /*PR_HIRES_bm |*/ PR_TC1_bm | PR_TC0_bm | PR_USART1_bm); // USARTC1 code PR_USART1_bm
	PR.PRPD = (/*PR_TWI_bm |*/ PR_USART1_bm |/* PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm |*/ PR_TC1_bm | PR_TC0_bm);
	PR.PRPE = (/*PR_TWI_bm | PR_USART1_bm | PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC1_bm |*/ PR_TC0_bm);
	#endif

	PR.PRGEN = 0x5f;
	PR.PRPA = 0x07;
	PR.PRPB = 0x07;
	PR.PRPC = 0x7f;
	PR.PRPD = 0x7f;
	PR.PRPE = 0x7f;
}


void restore_from_sleep(void)
{
	PWM_PORT.OUTSET = PWM_OUT;
	PWM_PORT.DIRSET = PWM_OUT;
	
	PR.PRGEN &=~(PR_RTC_bm | PR_EVSYS_bm);
	PR.PRPA &=~(PR_AC_bm);
	PR.PRPB &=~(PR_DAC_bm);
	PR.PRPC &=~(PR_SPI_bm | PR_TC0_bm | PR_TC1_bm | PR_USART1_bm); // USARTC1 code PR_USART1_bm
	PR.PRPD &=~(PR_USART1_bm | PR_TC1_bm | PR_TC0_bm);
	PR.PRPE &=~(PR_TC0_bm);

	#if HALFNON
	ac_init();
	ac_enable();
	#endif
	
	//host_spi_enable();

	// Set the index for TX frequencies to zero
	gDACIndexLoaded = 0;
	
	#if USE_DDS
	DDS_mclk_timer_init();
	#endif
	
	#if USE_DDS
	// Enable SPI for the DDS if used
	dds_spi_enable();

	// Set the absolute value
	ad9833_set_frequency_abs(0, gFrequencyTable[gDACIndexLoaded]);
	#else
	// Sandeep
	dac_enable();
	dac_write_data(1);
	#endif

	#if HALFNON
	// Make sure both the VPA rail and RF rail is enabled. This will be enabled
	// during the sleep mode.
	VPA_EN_PORT.OUTSET = VPA_EN_PIN;
	#endif
	
	#if HALFNON
	RF_EN_PORT.OUTSET = RF_EN_PIN;
	#endif
}

void enter_sleep(void)
{
	SLEEP.CTRL = (SLEEP_SMODE_PDOWN_gc | SLEEP_SEN_bm);
	sleep_cpu();
	SLEEP.CTRL &=~(SLEEP_SEN_bm);
}

#endif

