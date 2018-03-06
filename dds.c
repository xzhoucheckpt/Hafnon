/*******************************************************************
 *
 * File name: dds.c
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
 * $History: dds.c $
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 2:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings
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
 * User: Galantij     Date: 6/03/13    Time: 1:55p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"
#include "dds.h"

#if USE_DDS

ad9833_settings_t ad_settings; ///<This is used to store all settings.
uint16_t dds_packet = 0; // Sandeep this acts as an buffer for the DDS


/**
 * Initializes the AD9833 and the relevant variables.
 * Also initializes the Timer1 peripheral that is used for modulation timing.
 */
void ad9833_init(void){

    //init FSYNC pin (aka Chip select)
    ad_settings.command_reg |= (1<<AD_B28);  // Two Write operation needed to load the complete word
    	
	dds_packet = (1<<AD_SLEEP12)|(1<<AD_RESET) ;   // // Power down the DAC and Reset it
	dds_send_data( dds_packet ); // Sandeep dds

    ad_settings.command_reg |= (1<<AD_SLEEP12); //  Power down the DAC , Disable the Reset

    //set some nice default values
    ad9833_set_frequency(0, 0);
    ad9833_set_frequency(1, 0);
    ad9833_set_phase(0, 0);
    ad9833_set_phase(1, 0);
    ad9833_set_freq_out(0);
    ad9833_set_phase_out(0);
	
	gDACIndexLoaded = 0; // The Index for Frequency is Zero for the initialization
}

/** 
 * Sets the ad9833 output waveform to the one given as a parameter.
 * \param mode possible values:
 *      - AD_OFF
 *      - AD_TRIANGLE
 *      - AD_SQUARE
 *      - AD_SINE
 */
void ad9833_set_mode(uint8_t mode){

    ad_settings.mode = mode;
    switch (mode){
        case AD_OFF:
            ad_settings.command_reg |= (1<<AD_SLEEP12);
            ad_settings.command_reg |= (1<<AD_SLEEP1);
            break;
        case AD_TRIANGLE:
            ad_settings.command_reg &= ~(1<<AD_OPBITEN);
            ad_settings.command_reg |=  (1<<AD_MODE);
            ad_settings.command_reg &= ~(1<<AD_SLEEP12);
            ad_settings.command_reg &= ~(1<<AD_SLEEP1);
            break;
        case AD_SQUARE:
            ad_settings.command_reg |=  (1<<AD_OPBITEN);
            ad_settings.command_reg &= ~(1<<AD_MODE);
            ad_settings.command_reg |=  (1<<AD_DIV2);
            ad_settings.command_reg &= ~(1<<AD_SLEEP12);
            ad_settings.command_reg &= ~(1<<AD_SLEEP1);
            break;
        case AD_SINE:
            ad_settings.command_reg &= ~(1<<AD_OPBITEN);
            ad_settings.command_reg &= ~(1<<AD_MODE);
            ad_settings.command_reg &= ~(1<<AD_SLEEP12);
            ad_settings.command_reg &= ~(1<<AD_SLEEP1);
            break;
    }

	dds_send_data( ad_settings.command_reg ); // Sandeep dds
}

/**
 * sets the desired ad9833 internal phase register to a value that
 * produces the desired phase.
 *
 * \param reg the desired phase register to be manipulated, either 0 or 1
 * \param phase the desired phase
 */
void ad9833_set_phase(uint8_t reg, double phase){

    uint16_t reg_reg; //probably should be renamed...

    if (reg==1)
        reg_reg = AD_PHASE1;
    else
        reg_reg = AD_PHASE0;

    ad_settings.phase[reg] = phase;

	dds_packet = ( reg_reg | AD_PHASE_CALC(ad_settings.phase[reg]) ) ;

	dds_send_data( dds_packet ); // Sandeep dds
}

/**
 * returns the phase of the selected register
 * \param reg the register of which value we want to get
 * \return the phase of the selected register
 */
double ad9833_get_phase(uint8_t reg){
    return ad_settings.phase[reg];
}

/**
 * Selects which frequency register is used to generate the output.
 * Also used to select FSK.
 * \param phase_out possible values:
 *      - 0 = use phase register 0
 *      - 1 = use phase register 1
 *      - 2 = PSK
 */
void    ad9833_set_freq_out(uint8_t freq_out){

    ad_settings.freq_out = freq_out;

    switch (freq_out){
        case 0:
            ad_settings.command_reg &= ~(1<<AD_FSELECT);
            break;
        case 1:
            ad_settings.command_reg |= (1<<AD_FSELECT);
            break;
        case 2:
            //TODO
            break;
    }

	dds_send_data( ad_settings.command_reg ); // Sandeep dds
}

/**
 * returns the previously set frequency output mode.
 * \return the previously set frequency out mode
 */
uint8_t ad9833_get_freq_out(void){
    return ad_settings.freq_out;
}

/**
 * Selects which phase register is used to generate the output
 * Also used to select PSK
 * \param phase_out possible values:
 *  - 0 = use phase register 0
 *  - 1 = use phase register 1
 *  - 2 = PSK
 */
void    ad9833_set_phase_out(uint8_t phase_out){

    ad_settings.phase_out = phase_out;

    switch (phase_out){
        case 0:
            ad_settings.command_reg &= ~(1<<AD_PSELECT);
            break;
        case 1:
            ad_settings.command_reg |= (1<<AD_PSELECT);
            break;
        case 2:
            //TODO
            break;
    }

	dds_send_data( ad_settings.command_reg ); // Sandeep dds
}

/**
 * returns the previously set phase output mode.
 * \return the previously set phase out mode
 */
uint8_t ad9833_get_phase_out(void){

    return ad_settings.phase_out;
}

/**
 * sets the desired ad9833 internal frequency register to a value that
 * produces the desired frequency.
 *
 * \param reg the desired frequency register to be manipulated, either 0 or 1
 * \param freq the desired frequency
 */
void ad9833_set_frequency(uint8_t reg, double freq){

    uint32_t freq_reg;
    uint16_t reg_reg; //probably should be renamed...

    freq_reg = AD_FREQ_CALC(freq);
    ad_settings.freq[reg] = freq;

    if (reg==1)
        reg_reg = AD_FREQ1;
    else
        reg_reg = AD_FREQ0;

	dds_packet = ((1<<AD_B28) | ad_settings.command_reg) ;
	dds_send_data( dds_packet ); // Sandeep dds

	// Sandeep dds data
	dds_packet =  reg_reg | (0x3FFF&(uint16_t)(freq_reg>>2 ));
	dds_send_data( dds_packet ); // Sandeep dds

	// Sandeep dds data
	dds_packet = (reg_reg | (0x3FFF&(uint16_t)(freq_reg>>16))) ;
	dds_send_data( dds_packet ); // Sandeep dds
}

/**
 * sets the desired ad9833 internal frequency register to a value that
 * produces the desired frequency in absolute terms (no conversion).
 *
 * \param reg the desired frequency register to be manipulated, either 0 or 1
 * \param freq the desired frequency as obtained from the eval tool
 */
void ad9833_set_frequency_abs(uint8_t reg, uint32_t freq){
   
    uint16_t reg_reg; 
	 
	if (reg==1)
        reg_reg = AD_FREQ1;
    else
        reg_reg = AD_FREQ0;

	// Seating the  Control Word see Table 9 of the Data Sheet AD9833
  	dds_packet = ((1<<AD_B28) ) ;
	dds_send_data( dds_packet ); // Sandeep dds

	// Sending first 14 bits of the frequency value see Table 9 of the Data Sheet AD9833
	dds_packet =  reg_reg | (0x3FFF&(uint16_t)(freq));
	dds_send_data( dds_packet ); // Sandeep dds
	
	// Sending next 14 bits of the frequency value see Table 9 of the Data Sheet AD9833
	dds_packet = (reg_reg | (0x3FFF&(freq >> 14))) ;
	dds_send_data( dds_packet ); // Sandeep dds
	
	// increment the Index to load next freq into DDS or DAC voltage
	if ( (NO_OF_FREQUENCY_TABLE_VALUES - 1)  == gDACIndexLoaded) {
		gDACIndexLoaded = 0;
	} else {
		gDACIndexLoaded = gDACIndexLoaded + 1;
	}
	
}


/**
 * returns the frequency of the selected register
 * \param reg the register of which value we want to get
 * \return the frequency of the selected register
 */
double ad9833_get_frequency(uint8_t reg){

    return ad_settings.freq[reg];
}

#endif