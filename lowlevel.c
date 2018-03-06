/*******************************************************************
 *
 * File name: lowlevel.c
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
 * $History: lowlevel.c $
 * 
 * *****************  Version 22  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 3/06/14    Time: 4:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed Defect #98 (When teal light is on there is the possibility that
 * the TX Gate signal could float high and cause one of the transmit fets
 * to short the VPA) This was fixed by using using a soft pull down on the
 * TX gate GPO pin. There should be a HW pull down on this line.
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a function to test for the active state for the GPI features.
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added functions to initialize the GPIO features and a fuctions to test
 * the active GPO features
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug where Interlock could be enabled using the interlock pin
 * even when Interlock is disabled  (by switch)
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 11/04/13   Time: 5:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:55p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Switched from using the internal VCO to using the external 16 MHz
 * oscillator. This is needed to mantain accurray for frequency counter
 * algorithm.
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed config code from this file and put in unique file.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put marcos in for both the auto tune test point and the change in the
 * polarity of the PWM
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:17p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put "HAFNON" flags to focus HW on Thorite
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:39p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "HAFNON define to comment out the VBAT function prototypes for
 * Thorite
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed system config DB name for reading both the dip switches and
 * providing the config value for a given config define input parameter.
 * Added a pre-define to comment out the host SPI for Hafnon
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/08/13    Time: 11:10a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added function to provide config values for a given input config
 * parameter
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:42a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the code for reading the dip switches and configurated the pins
 * for the dip switches
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/01/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Clean up and comments and setup test GPIO for the relay outputs to
 * start testing before the HW is ready
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new output pins for the five relay positions and the pin used for
 * the VREF for the ADC
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the DAC output pin for DAC1 and the output pin to set the Vcc on
 * the VPA rail from either 3.3 or 12 volts
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Sandeep added code for bring up both internal and external 24 MHz clock
 * and the input counter pin used to test freq during freq counting
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed RTC clock from 1.024KHz to 32 KHz
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:44p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 4  *****************
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

#include "lowlevel.h"
#include "interface.h"
#include "zircon_config.h"
#include "alarm.h"
#include "utility/util.h"

static uint8_t findHardwareType(void);

// This function creates the 24 MHz clock using the internal 2 MHz internal RC. At this 
// point we are not using this RC because of lack of frequency accuracy affecting
// the frequency counter feature.
void clk_24MHZ_using_2MHZ_internal(void)
{
	// configure the PLL using 2MHz internal RC with a mul of 12 for an F_CPU of 24 MHz
	OSC.PLLCTRL = (OSC_PLLSRC_RC2M_gc | ((12 & OSC_PLLFAC_gm) << OSC_PLLFAC_gp));
	OSC.CTRL |= OSC_PLLEN_bm;
	
	// set peripheral clock domains to F_CPU with no pre-scaling
	ccp_write_io((void*)&CLK.PSCTRL, (CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc));
	
	// wait until PLL is ready
	while ((OSC.STATUS & OSC_PLLRDY_bm) == 0);

	// change to PLL
	ccp_write_io((void*)&CLK_CTRL, ((CLK.CTRL & ~CLK_SCLKSEL_gm) | CLK_SCLKSEL_PLL_gc));
}

// This function creates the 24 MHz clock using an external 16 MHz OSC. This is more accurate
// then using the internal 2 MHz clock. This is what is currently being used.  
void clk_24MHZ_using_16MHZ_external(void)
{
	OSC.XOSCCTRL |= OSC_FRQRANGE_12TO16_gc |  OSC_XOSCSEL_XTAL_16KCLK_gc; //  OSC_XOSCSEL_EXTCLK_gc; //OSC_XOSCSEL_32KHz_gc;
	
	OSC.CTRL |= OSC_XOSCEN_bm;
	
	while ((OSC.STATUS & OSC_XOSCRDY_bm) == 0);
	
	OSC.PLLCTRL = (OSC_PLLSRC_XOSC_gc | OSC_PLLDIV_bm | (( 3 & OSC_PLLFAC_gm) << OSC_PLLFAC_gp));
	
	OSC.CTRL |= OSC_PLLEN_bm;
	
	// set peripheral clock domains to F_CPU with no pre-scaling
	//--->CLK.PSCTRL = CLK_PSADIV_1_gc | CLK_PSBCDIV_2_2_gc ;
	ccp_write_io((void*)&CLK.PSCTRL, (CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc));
	
	// wait until PLL is ready
	while ((OSC.STATUS & OSC_PLLRDY_bm) == 0);

	// change to PLL
	ccp_write_io((void*)&CLK_CTRL, ((CLK.CTRL & ~CLK_SCLKSEL_gm) | CLK_SCLKSEL_PLL_gc));
	
	
	// For testing to see if 16 MHZ clock is working
	//ccp_write_io((void*)&CLK_CTRL, ((CLK.CTRL & ~CLK_SCLKSEL_gm) |  CLK_SCLKSEL_XOSC_gc));
	
}

// Initializes the GPIO during power up.
uint8_t initGPIO(void)
{
	uint8_t io_enabled_flag = 0;
	
	if(CPiD_HW_flag) /* Thoralite */
	{
		// initialize GPO pin to active state
		switch(getConfigInfo(CONFIG_GPO_STATE))
		{
			case GPO_ACTIVE_OPEN:
				GPO_PORT.OUTCLR = GPO_PIN;
			break;
			
			case GPO_ACTIVE_CLOSE:
				GPO_PORT.OUTSET = GPO_PIN;
			break;
			
			default:
			break;
		}
		
		// Set direction for both GPI and GPO pins
		GPI_PORT.DIRCLR = GPI_PIN;
		GPO_PORT.DIRSET = GPO_PIN;
		
		// This determines if the sounder should be disabled/enabled.
		// This status id sent back to the caller and used during the
		// alarm initialization period.
		if(GPO_PRI_NO_SOUND_OUTPUT == getConfigInfo(CONFIG_GPO_APP))
		{
			io_enabled_flag = GPO_DISABLE_SOUNDER;
		}
		else if(GPO_SEC_OUTPUT == getConfigInfo(CONFIG_GPO_APP))
		{
			io_enabled_flag = GPO_DISABLE_IO;
		}
		
		return(io_enabled_flag);
	}
	else
	{
		return(GPO_DISABLE_IO);
	}
}

// This function decides which GPO feature is selected (only one can be selected
// at a given time) and sets/clears the active state from the selected feature
void processGpoPin(uint8_t feature_select, uint8_t active_state)
{
	if((feature_select == getConfigInfo(CONFIG_GPO_APP)) && (CPiD_HW_flag))
	{
		if(active_state)  // active state
		{
			if(GPO_ACTIVE_OPEN == getConfigInfo(CONFIG_GPO_STATE))
			{
				GPO_PORT.OUTSET = GPO_PIN;
			}
			else 
			{
				GPO_PORT.OUTCLR = GPO_PIN;
			}
		}
		else  // inactive state
		{
			if(GPO_ACTIVE_OPEN == getConfigInfo(CONFIG_GPO_STATE))
			{
				GPO_PORT.OUTCLR = GPO_PIN;
			}
			else 
			{
				GPO_PORT.OUTSET = GPO_PIN;
			}			
		}
	}
}

// This function detects the state of the input pin by physically checking
// the pin level and then decoding the active state of the input pin.
// This returns whether the input is active or not. 
uint8_t GPI_activeState(void)
{
	uint8_t GPI_pin_state = 0;
	uint8_t active_state = GPI_NONACTIVE;
	
	GPI_pin_state = PORTF.IN;

	if(GPI_ACTIVE_LOW_STATE == getConfigInfo(CONFIG_GPI_STATE))
	{
		if((GPI_pin_state & (GPI_PIN)) == 0)
		{
			active_state = GPI_ACTIVE;
		}
	}
	else if(GPI_ACTIVE_HIGH_STATE == getConfigInfo(CONFIG_GPI_STATE))
	{
		if((GPI_pin_state & (GPI_PIN)) == GPI_PIN)
		{
			active_state = GPI_ACTIVE;
		}
	}
	
	return(active_state);
}

static uint8_t findHardwareType(void)
{
	uint8_t hardware_type = PORTC.IN;
	
	if((hardware_type & (HW_TYPE_PIN)) == HW_TYPE_PIN)
	{
		return(CPID_HW);
	}
	else
	{
		return(LITE_HW);
	}
}

void lowlevel_init(void)
{
	// enable power saving features of EEPROM and Flash controler
	//ccp_write_io((void*)&NVM.CTRLB, (NVM_EPRM_bm | NVM_FPRM_bm));
	
	//clk_24MHZ_using_2MHZ_internal();
	clk_24MHZ_using_16MHZ_external();	
	
	// enable 32KHz RC	
	OSC.CTRL |= OSC_RC32KEN_bm;
	
	// wait for RC to stabilize
	while ((OSC.STATUS & OSC_RC32KRDY_bm) == 0);
	
	// enable the 32 KHz output of the 32KHz RC (as opposed to the 1.024 KHz output)
	CLK.RTCCTRL = (CLK_RTCSRC_RCOSC32_gc | CLK_RTCEN_bm);

	// Thoralite ////////////////////////////////////////////
	HW_TYPE_PORT.DIRCLR = HW_TYPE_PIN;
	HW_TYPE_PORT.HW_TYPE_PINCTRL = PORT_OPC_PULLUP_gc;
	
	CPiD_HW_flag = findHardwareType();
	/////////////////////////////////////////////////////////

#if USE_DDS
	// Setup MCLK for the DDS to output pin
	MCLK_PORT.DIRSET = MCLK_PIN;
#endif

	// Sandeep FREQ_COUNTERPORT
	FREQCOUNT_PORT.DIRCLR   = FREQCOUNT_PIN;
	
	if(CPiD_HW_flag)  /* Thoralite */
	{
		// setup input for interlock signal, pullup (active low) and turn on interrupt
		// for Interlock_n pin
		INTERLOCK_PORT.DIRCLR = INTERLOCK_PIN;
		INTERLOCK_PORT.INTERLOCK_PINCTRL = (PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc);
		INTERLOCK_PORT.INTCTRL = (PORT_INT0LVL_LO_gc);
	}
	
	// setup input for VPA max signal and turn on interrupt for VPA_MAX pin 
	// and pullup (active low)
	VPA_MAX_PORT.DIRCLR = VPA_MAX_PIN;
	VPA_MAX_PORT.VPA_MAX_PINCTRL = (PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc);
	// Change the prioity from HI to MED because it maybe effecting the timing of the cycle timer		
	VPA_MAX_PORT.INTCTRL = (PORT_INT0LVL_HI_gc);
	//VPA_MAX_PORT.INTCTRL = (PORT_INT0LVL_MED_gc);
	VPA_MAX_PORT.INT0MASK = VPA_MAX_PIN;
	
#if 1
	// NEW: This pin detects a tag from the receiver (active low)
	TAG_N_PORT.DIRCLR = TAG_N_PIN;
	TAG_N_PORT.TAG_N_PINCTRL = (PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc);
	TAG_N_PORT.INTCTRL = (PORT_INT0LVL_HI_gc);
	//TAG_N_PORT.INT0MASK = TAG_N_PIN;
#endif
	
	// setup outputs  (JRG VPA switcher), first invert, then set using a clear
#if OLD_PWM_HW
	PWM_PORT.PWM_OUT_PINCTRL = 0x40;
#endif
	PWM_PORT.OUTCLR = PWM_OUT;
	PWM_PORT.DIRSET = PWM_OUT;
	
	//DAC output for frequency counter
	DAC_PORT.DIRSET = DAC_OUTPUT;
	DAC_PORT.DAC_OUTPUT_PINCTRL = PORT_OPC_PULLDOWN_gc;
	
	// DAC output for VPA rail adj
	DAC_PORT.DIRSET = DAC1_OUTPUT;
	DAC_PORT.DAC1_OUTPUT_PINCTRL = PORT_OPC_PULLDOWN_gc;
	
	DDS_SPI_PORT.OUTSET = DDS_NCS;
	DDS_SPI_PORT.DIRSET = (DDS_MOSI | DDS_NCS | DDS_SCK);
	
#if HALFNON	
	HOST_SPI_PORT.DIRCLR = (HOST_MOSI | HOST_SCK | HOST_NCS);
	HOST_SPI_PORT.DIRSET = HOST_MISO;
#endif
	
	
	// JRG transmit enable gate signal changed to active high (6us)
	TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN;
	TX_ENABLE_N_PORT.PIN0CTRL = PORT_OPC_PULLDOWN_gc;
#if !HALFNON
	if(CPiD_HW_flag) /* Thoralite */
	{
		TX2_ENABLE_N_PORT.OUTCLR = TX2_ENABLE_N_PIN;
		TX2_ENABLE_N_PORT.DIRSET = TX2_ENABLE_N_PIN;
	}
#endif
	//TX_ENABLE_N_PORT.DIRSET = TX_ENABLE_N_PIN; //commented out for testing
	
#if HALFNON	
	// JRG active low receiver enable gate signal (10us)
	RX_ENABLE_N_PORT.OUTSET = RX_ENABLE_N_PIN;
	RX_ENABLE_N_PORT.DIRSET = RX_ENABLE_N_PIN;
#else  // Thorite HW
	// JRG active high receiver enable gate signal (10us)
	RX_ENABLE_N_PORT.OUTCLR = RX_ENABLE_N_PIN;
	RX_ENABLE_N_PORT.DIRSET = RX_ENABLE_N_PIN;
	if(CPiD_HW_flag) /* Thoralite */
	{
		RX2_ENABLE_N_PORT.OUTCLR = RX2_ENABLE_N_PIN;
		RX2_ENABLE_N_PORT.DIRSET = RX2_ENABLE_N_PIN;
	}
#endif

#if HALFNON	
	// Enables VPA power is active high
	// Enable now and keep enabled during sleep.
	VPA_EN_PORT.OUTSET = VPA_EN_PIN;
	VPA_EN_PORT.DIRSET = VPA_EN_PIN;
#endif

#if HALFNON	
	// Enable RF power rail is active high
	// Enable now and keep enabled during sleep. 
	RF_EN_PORT.OUTSET = RF_EN_PIN; // commented out for testing JRG_TEST
	//RF_EN_PORT.OUTCLR = RF_EN_PIN; // uncomment for test pin
	RF_EN_PORT.DIRSET = RF_EN_PIN;
#endif
	
#if HALFNON	
	// Enable RX power rail only after VPA monitor signal and until 
	// the end of the receive cycle. Give at least 400us to charge up
	// this rail.
	RX_EN_PORT.OUTCLR = RX_EN_PIN;
	RX_EN_PORT.DIRSET = RX_EN_PIN;
#endif
	
	// This active low pin adjusts the Vcc applied to the VPA rail.
	// When high the Vcc is 3.3v, when low the Vcc is 12v
	DEACT_NOT_PORT.OUTSET = DEACT_NOT_PIN;
	DEACT_NOT_PORT.DIRSET = DEACT_NOT_PIN;
	
#if 1
	// Set relay default value to close only the LS relay 
	TUNE_RELAY0_PORT.OUTCLR = TUNE_RELAY0_PIN;
	TUNE_RELAY0_PORT.DIRSET = TUNE_RELAY0_PIN;
	
	TUNE_RELAY1_PORT.OUTCLR = TUNE_RELAY1_PIN;
	TUNE_RELAY1_PORT.DIRSET = TUNE_RELAY1_PIN;
	
	TUNE_RELAY2_PORT.OUTCLR = TUNE_RELAY2_PIN;
	TUNE_RELAY2_PORT.DIRSET = TUNE_RELAY2_PIN;
	
	TUNE_RELAY3_PORT.OUTCLR = TUNE_RELAY3_PIN;
	TUNE_RELAY3_PORT.DIRSET = TUNE_RELAY3_PIN;
	
	TUNE_RELAY4_PORT.OUTCLR = TUNE_RELAY4_PIN;
	TUNE_RELAY4_PORT.DIRSET = TUNE_RELAY4_PIN;
#endif	

	ADC_REF_PORT.DIRCLR = ADC_REF_PIN;
	
	FCC_CE_SW_PORT.DIRCLR = FCC_CE_SW_PIN;
	MODE_SEL0_SW_PORT.DIRCLR = MODE_SEL0_SW_PIN;
	MODE_SEL1_SW_PORT.DIRCLR = MODE_SEL1_SW_PIN;
	INTLK_EN_SW_PORT.DIRCLR = INTLK_EN_SW_PIN;

	TEST_PORT.OUTCLR = TEST_PIN;
	TEST_PORT.DIRSET = TEST_PIN;
	TEST2_PORT.OUTCLR = TEST2_PIN;
	TEST2_PORT.DIRSET = TEST2_PIN;
	

// Shifting this here since they have to over write the DDS and HOST pin allotment
/*
 * The following code can be used to output the main clock on a pin 
 * (PC7 in this case) and the RTC clock output on PC6 - refer to the datasheet for other pins
*/
#if CLKOUT	
	// set clock out pin as output.
	CLKOUT_PORT.DIRSET = CLKOUT_PIN;
	
	// enable clock output
	//PORTCFG.CLKEVOUT = (PORTCFG_CLKOUT_PC7_gc | PORTCFG_RTCOUT_bm);
	// Sandeep: For test since 3/25 H/W does not have C7 coming out
	PORTCFG.CLKEVOUT = (PORTCFG_CLKOUT_PD7_gc | PORTCFG_RTCOUT_bm);
#endif

#if HALFNON
	AC_PORT.DIRCLR = (AC_POS);

	AC_PORT.AC_POS_PINCTRL = PORT_ISC_INPUT_DISABLE_gc;
#endif

	// enable all interrupt levels in the PMIC
	PMIC.CTRL |= (PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm);

	//SET_STATE(STATE_SLEEP);
}
