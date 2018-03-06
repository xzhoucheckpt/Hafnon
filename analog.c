/*******************************************************************
 *
 * File name: analog.c
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
 * $History: analog.c $
 * 
 * *****************  Version 16  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 5/13/15    Time: 1:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the initiaization of "pulseNumber" for the 40 mS TX/RX delay.
 * 
 * *****************  Version 14  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 1/28/14    Time: 7:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added an input parameter to dac_write_data() to allow enable/disable
 * the VCO via the DAC. There are now three conditions; normal operation,
 * disable, enable. 
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created data structure to give an option for reversing the transmit
 * frequency (via macro define) from high to low, to low to high. This
 * seem to help with detection repeatablity. This is the default fo rthe
 * next release.
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to allow the transmit frequency to be either seq or
 * interleaved by selecting the macro define "SEQ_FREQ"
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the VPA rail voltage structure in this file from the .h file to
 * remove warnings and used hardcoded cal data for both DACs
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 8/09/13    Time: 10:35a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Hardcoded the freq generator DAC cal values because the factory
 * settings are not correct. 
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:09p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Moved "extern"'s in header file and removed the DAC cal because of
 * supisious cal values for DAC1. Email pending from Atmel
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added HAFNON define to comment out VBAT monitor (comparitor)
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added low level interface (ADC) for reading ant current from HW
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added second DAC channel for VPA Rail adj and developed the low level
 * driver
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:46p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * File header checkin
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Test checkin
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:03p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * This is initial checkin
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 1:55p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#include "lowlevel.h"
#include "analog.h"
#include "utility/util.h"

// 27 VPA rail level settings (DMS:0-26)
uint16_t gVPA_Adj_CE[] = {
	
	VPA_4V, VPA_5V, VPA_7V, VPA_8V, VPA_10V,
	VPA_11V, VPA_12V, VPA_14V, VPA_15V, VPA_17V,
	VPA_18V, VPA_20V, VPA_21V, VPA_22V, VPA_24V,
	VPA_25V, VPA_27V, VPA_28V, VPA_30V, VPA_31V,
	VPA_32V, VPA_34V, VPA_35V, VPA_37V, VPA_38V,
	VPA_40V, VPA_41V
};

void adc_init(void)
{
	volatile uint16_t temp;
	
	// read factory calibration data in user signature row
	temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1)));
	temp <<= 8;
	temp |= nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0)));
	
	ADC.CAL = temp;
	
	// enable ADC with 12-bit resolution
	ADC.CTRLB = ADC_RESOLUTION_12BIT_gc;
	
	// use AREF set for 2.5 volts reference
	ADC.REFCTRL = ADC_REFSEL_AREFA_gc;
	
	// set ADC pre-scaler to 32 --> 750 KHz ADC clock @ F_CPU of 24 MHz (max is 1.4 MHz)
	ADC.PRESCALER = ADC_PRESCALER_DIV32_gc;
		
	// enable ADC input pins
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;
	
	// enable ADC channels as singled-ended inputs with no gain
	ADCA_CH0_CTRL = (ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc);
		
	// enable ADC
	ADC.CTRLA = ADC_ENABLE_bm;
}

void adc_enable(void)
{
	ADC.CTRLA |= ADC_ENABLE_bm;
}

void adc_disable(void)
{
	ADC.CTRLA &=~(ADC_ENABLE_bm);
}

void adc0_start(void)
{
	ADC.CTRLA |= ADC_CH0START_bm;
}

#if HALFNON
void ac_init(void)
{
	// Reference set to 1.8v using input+ pin 5, scaler on input-,
	// small hysteresis (may want to increase hysteresis to prevent 
	// threshing). Do not select high speed mode because of oscillation
	// around the trip point.  
	AC.CTRLB = VPA_REF_SCALER;
	AC.AC0MUXCTRL = (AC_MUXPOS_PIN5_gc | AC_MUXNEG_SCALER_gc);
	AC.AC0CTRL = (AC_INTMODE_BOTHEDGES_gc | AC_HYSMODE_SMALL_gc | 0x01);
	
	// NEW2 Turn on output pin PA7
	AC.CTRLA |= 0x01;
	
	// allow for comparator startup time
	_delay_us(100);
}

void ac_enable(void)
{
	AC.AC0CTRL |= 0x01;
	
	// allow for comparator startup time
	_delay_us(100);
}

void ac_disable(void)
{
	AC.AC0CTRL &=~(0x01);
}
#endif

void dac_init(void)
{
	//uint8_t gain_cal;
	//uint8_t offset_cal;
	
	// Retrieve DAC calibration data and apply  
	//gain_cal = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, DACB0GAINCAL)));
	//offset_cal = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, DACB0OFFCAL)));
	//DAC.CH0GAINCAL = gain_cal;
	//DAC.CH0OFFSETCAL = offset_cal;
	// This is hardcoded until the DAC cal is developed
	DAC.CH0GAINCAL = 0x06;
	DAC.CH0OFFSETCAL = 0xc5;
	
	//gain_cal = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, DACB1GAINCAL)));
	//offset_cal = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, DACB1OFFCAL)));
	//DAC.CH1GAINCAL = gain_cal;
	//DAC.CH1OFFSETCAL = offset_cal;
	// This is hardcoded until the DAC cal is developed
	DAC.CH1GAINCAL = 0x06;
	DAC.CH1OFFSETCAL = 0xc5;	
	
	DAC.CTRLA = (DAC_CH0EN_bm | DAC_CH1EN_bm | DAC_ENABLE_bm);  // adj VPA rail
	DAC.CTRLB = (DAC_CHSEL_DUAL_gc); // adj VPA rail
	DAC.CTRLC =  DAC_REFSEL_AVCC_gc | DAC_LEFTADJ_bm;  // use Analog insted of external voltage // DAC_REFSEL_AREFB_gc;
	
	gDACIndexLoaded = 0; // The Index is Zero for the initialization
	
	// Initializing the Pulse Count to zero.
/*
#ifdef DELAY_PULSE
	pulseNumber = 0;
#endif
*/
//#if 0
	// To count no of pulses so as to add 40 ms every 5th pulse in 144 mode
	pulseNumber = 0;
	// to indicate that there was a change in the frame rate so that it can be put back 
	frameRateChanged = 0;
//#endif
}

void dac_enable(void)
{
	DAC.CTRLA |= (DAC_ENABLE_bm);
}

void dac_disable(void)
{
	DAC.CTRLA &=~(DAC_ENABLE_bm);
}

// Change TX freq by writing new value into ADC
void dac_write_data(uint8_t enable)
{
	uint8_t freq_index = 0;
	
	// Macro defines select whether the freq is sequence (lowest to highest)
	// or interleaved as done for CP9
#if SEQ_FREQ

#if REV_FREQ
	uint8_t seq_freq_index[] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
#else
	uint8_t seq_freq_index[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
#endif

#else
	uint8_t intl_freq_index[] = {0,8,1,9,2,10,3,11,4,12,5,13,6,14,7,15};
#endif

	if(enable == 2)
	{
		if(gDACIndexLoaded > 0)
		{
			gDACIndexLoaded--;
		}
		else
		{
			gDACIndexLoaded = 15;
		}
	}

#if SEQ_FREQ	
	freq_index = seq_freq_index[gDACIndexLoaded];
#else
	freq_index = intl_freq_index[gDACIndexLoaded];
#endif
	
	// Sandeep
	// Load the DAC with new value
	do { } while ( !( DAC.STATUS & DAC_CH0) );
		
	if((enable == 1) || (enable == 2))
	{
		//load DAC with current TX freq 
		DAC.CH0DATA = gFrequencyTable[freq_index];
		
		// load next freq into DDS or DAC voltage
		if ( (NO_OF_FREQUENCY_TABLE_VALUES - 1)  == gDACIndexLoaded) 
		{
			gDACIndexLoaded = 0;
		} 
		else 
		{
			gDACIndexLoaded = gDACIndexLoaded + 1;
		}
	}
	else // disable VCO
	{
		DAC.CH0DATA = 0x0000;
	}
}

void dac_VPA_adj(uint16_t dac_value)
{
	// Wait until the last DAC is processed before writing the next
	do { } while ( !( DAC.STATUS & DAC_CH1) );
	
	DAC.CH1DATA = dac_value;
}
