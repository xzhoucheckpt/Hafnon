/*******************************************************************
 *
 * File name: lowlevel.h
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
 * $History: lowlevel.h $
 * 
 * *****************  Version 21  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:17p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Commented the new test points (GPO)
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the prototypes for the new function which will return the active
 * state of the GPI features
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:08p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added protypes for the two new functions to support the GPIO features
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to make the same GPIO pins for the RX gate be the same.
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:09p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the GPO pins for Josh's alarm LEDs. Also added test pins for
 * debugging.
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed config function prototypes.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added test points for auto tuning
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:18p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * HAFNON flags installed
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "HAFNON define to comment out the VBAT function prototypes for
 * Thorite
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:08p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added pre-defines tto comment out code for Hafnon and added defines for
 * the GPI and GPO pin features
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/08/13    Time: 11:10a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added function to provide config values for a given input config
 * parameter
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:43a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the prototype for the read dip switches function and defined the
 * pins for the dip switches
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/01/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Clean up and comments and setup test GPIO for the relay outputs to
 * start testing before the HW is ready
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Setting the pins for the five relays and the ADC pins
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the DAC output pin for DAC1 and the output pin to set the Vcc on
 * the VPA rail from either 3.3 or 12 volts
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:31p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * sandeep added the pin define for freq counter and added the two new
 * clock setting prototypes for both internal and external clock
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * sandeep changed interlock timer from TCD1 to RTC to use timer for freq
 * counter
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:44p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 3  *****************
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

#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include "globals.h"

#if USE_FREQ_COUNT
#include "freq_cntr.h"
#endif

// interrupt vectors
#define INTERLOCK_INT_vect		PORTE_INT0_vect
#define VPA_MAX_INT_vect		PORTA_INT0_vect
#define PIN_N_vect				PORTD_INT0_vect

#define TC_PWM_vect				TCC0_CCA_vect
#define TX_CYCLE_vect			TCE0_CCA_vect
#define HOLD_CYCLE_vect			TCE0_CCB_vect
#define RX_CYCLE_vect			TCE0_CCC_vect
#define	TAG_CYCLE_vect			TCE0_CCD_vect
#define START_TAG_CYCLE_vect	TCE0_OVF_vect
#define TC_FRAME_vect			TCC1_OVF_vect
#define TC_INTERLOCK_vect		RTC_OVF_vect

#define ADC_CH0_vect			ADCA_CH0_vect
#define AC_CH0_vect				ACA_AC0_vect

#if HALFNON
#define HOST_SPI_vect			SPIC_INT_vect
#endif

// timers
#define FRAME_TIMER				TCC1
#define INTERLOCK_TIMER			RTC
#define PWM_TIMER				TCC0
#define CYCLE_TIMER				TCE0
#if USE_DDS
#define MCLK_TIMER				TCD0
#endif


// input pins
#define VPA_MAX_PORT			PORTA
#define VPA_MAX_PIN				PIN3_bm
#define VPA_MAX_PINCTRL			PIN3CTRL

#define INTERLOCK_PORT			PORTE
#define INTERLOCK_PIN			PIN2_bm
#define INTERLOCK_PINCTRL		PIN2CTRL

#define TAG_N_PORT				PORTD
#define TAG_N_PIN				PIN1_bm
#define TAG_N_PINCTRL			PIN1CTRL

#define ADC_REF_PORT			PORTA
#define ADC_REF_PIN				PIN0_bm
#define ADC_REF_PINCTRL			PIN0CTRL

#define FCC_CE_SW_PORT			PORTB
#define FCC_CE_SW_PIN			PIN4_bm
#define FCC_CE_SW_PINCTRL		PIN4CTRL

#define MODE_SEL0_SW_PORT		PORTB
#define MODE_SEL0_SW_PIN		PIN5_bm
#define MODE_SEL0_SW_PINCTRL	PIN5CTRL

#define MODE_SEL1_SW_PORT		PORTB
#define MODE_SEL1_SW_PIN		PIN6_bm
#define MODE_SEL1_SW_PINCTRL	PIN6CTRL

#define INTLK_EN_SW_PORT		PORTB
#define INTLK_EN_SW_PIN			PIN7_bm
#define INTLK_EN_SW_PINCTRL		PIN7CTRL


// output pins
#define CLKOUT_PORT				PORTC
#define CLKOUT_PIN				PIN7_bm // This pin is in use

// Select board type: high=CPiD, low=Thoralite
#define HW_TYPE_PORT			PORTC
#define HW_TYPE_PIN				PIN2_bm
#define HW_TYPE_PINCTRL			PIN2CTRL

//TP5: New test point after Thoralite
#define TEST_PORT				PORTC
#define TEST_PIN				PIN4_bm
//TP12: New test point after Thoralite
#define TEST2_PORT				PORTA
#define TEST2_PIN				PIN2_bm

#define PWM_PORT				PORTC
#define PWM_OUT					PIN0_bm
#define PWM_OUT_PINCTRL			PIN0CTRL

#define TX_ENABLE_N_PORT		PORTE
#define TX_ENABLE_N_PIN			PIN0_bm

#define RX_ENABLE_N_PORT		PORTE
#define RX_ENABLE_N_PIN			PIN1_bm

#if !HALFNON  // only used for Thorite HW
#define TX2_ENABLE_N_PORT		PORTD
#define TX2_ENABLE_N_PIN		PIN4_bm

#define RX2_ENABLE_N_PORT		PORTE
#define RX2_ENABLE_N_PIN		PIN1_bm

// This is for the original first spin HW before the receiver changes
//#define RX2_ENABLE_N_PORT		PORTD  // RJL
//#define RX2_ENABLE_N_PIN		PIN5_bm
#endif

//#define NON_DEACT_N_PORT		PORTA
//#define NON_DEACT_N_PIN			PIN4_bm //intervention??

#define MCLK_PORT				PORTD
#define MCLK_PIN				PIN3_bm

#if HALFNON
#define VPA_EN_PORT				PORTC
#define VPA_EN_PIN				PIN6_bm
#endif

#if HALFNON
#define RF_EN_PORT				PORTB
#define RF_EN_PIN				PIN1_bm
#endif

#if HALFNON
#define RX_EN_PORT				PORTC
#define RX_EN_PIN				PIN1_bm
#endif

#define DEACT_NOT_PORT			PORTC  // sets Vcc on VPA rail
#define DEACT_NOT_PIN			PIN5_bm

#if 1
// antenna tuning relays
#define TUNE_RELAY0_PORT		PORTF
#define TUNE_RELAY0_PIN			PIN0_bm
#define TUNE_RELAY1_PORT		PORTF
#define TUNE_RELAY1_PIN			PIN1_bm
#define TUNE_RELAY2_PORT		PORTF
#define TUNE_RELAY2_PIN			PIN2_bm
#define TUNE_RELAY3_PORT		PORTF
#define TUNE_RELAY3_PIN			PIN3_bm
#define TUNE_RELAY4_PORT		PORTF
#define TUNE_RELAY4_PIN			PIN4_bm
#endif

#if 0 // here to test on hafnon HW
#define TUNE_RELAY0_PORT		PORTA
#define TUNE_RELAY0_PIN			PIN2_bm
#define TUNE_RELAY1_PORT		PORTA
#define TUNE_RELAY1_PIN			PIN6_bm
#define TUNE_RELAY2_PORT		PORTD
#define TUNE_RELAY2_PIN			PIN2_bm
#define TUNE_RELAY3_PORT		PORTC
#define TUNE_RELAY3_PIN			PIN2_bm
#define TUNE_RELAY4_PORT		PORTE
#define TUNE_RELAY4_PIN			PIN3_bm
#endif

//Sandeep: PORT C PIN 3 is the input for freq counter.

#define FREQCOUNT_PORT			PORTC
#define FREQCOUNT_PIN			PIN3_bm

#if HALFNON
#define HOST_SPI				SPID
#define HOST_SPI_PORT			PORTD
#define HOST_NCS_PINCTRL		PIN4CTRL
#define HOST_NCS				PIN4_bm
#define HOST_MOSI				PIN5_bm
#define HOST_MISO				PIN6_bm
#define HOST_SCK				PIN7_bm
#endif

#define DDS_SPI					USARTC1
#define DDS_SPI_PORT			PORTC
#define DDS_NCS_PINCTRL			PIN4CTRL
#define DDS_NCS					PIN4_bm
#define DDS_SCK					PIN5_bm
#define DDS_MOSI				PIN7_bm 

#if HALFNON
#define AC						ACA
#define AC_PORT					PORTA
#define AC_POS					PIN5_bm
#define AC_POS_PINCTRL			PIN5CTRL
#endif

#define DAC						DACB
#define DAC_PORT				PORTB
#define DAC_OUTPUT				PIN2_bm  // used for frequency counter
#define DAC_OUTPUT_PINCTRL		PIN2CTRL // used for frequency counter	
#define DAC1_OUTPUT				PIN3_bm  // used for VPA rail adj
#define DAC1_OUTPUT_PINCTRL		PIN3CTRL // used for VPA rail adj

#define ADC						ADCA
#define ADC_PORT				PORTA
#define ADC_INPUT				PIN1_bm
#define ADC_INPUT_PINCTRL		PIN1CTRL			

// For the testing purpose this is set as E should be changed to F for new h/w
#define GPI_PORT				PORTF
//#define GPI_PORT				PORTE
#define GPI_PIN					PIN6_bm 
#define GPI_PINCTRL				PIN6CTRL
 
// For the testing purpose this is set as E should be changed to F for new h/w
#define GPO_PORT				PORTF
//#define GPO_PORT				PORTE  
#define GPO_PIN					PIN7_bm  
#define GP0_PINCTRL				PIN7CTRL


//josh alarm pins

#define LED_PORT				PORTA
#define LED_RED					PIN5_bm
#define LED_BLUE				PIN7_bm
#define LED_GREEN				PIN6_bm

#define SOUNDER_PORT			PORTD
#define SOUNDER_PIN				PIN2_bm


#define OUTPUT_PORT			PORTD
#define OUTPUT_PIN				PIN0_bm

#define DEVICE_ID			MCU

void lowlevel_init(void);
void clk_24MHZ_using_2MHZ_internal(void);
void clk_24MHZ_using_16MHZ_external(void);

// Thoralite: board type could be either CPID or Thoralite
#define CPID_HW							1
#define LITE_HW							0

uint8_t initGPIO(void);

// active state
#define GPO_CLEAR						0
#define GPO_SET							1
// Active HW States
#define GPI_ACTIVE_LOW_STATE			0
#define GPI_ACTIVE_HIGH_STATE			1
#define GPO_ACTIVE_OPEN					0
#define GPO_ACTIVE_CLOSE				1
// GPI applications
#define GPI_DISABLED_INPUT				0
#define GPI_DEACT_INPUT					1
#define GPI_SWITCH_INPUT				2
// GPO applications
#define GPO_PRI_SOUND_OUTPUT			0
#define GPO_PRI_NO_SOUND_OUTPUT			1
#define GPO_SEC_OUTPUT					2
#define GPO_ON_OFF_OUTPUT				3
#define GPO_ERROR_OUTPUT				4
void processGpoPin(uint8_t feature_select, uint8_t active_state);

// finding GPI active state
#define GPI_NONACTIVE					0
#define GPI_ACTIVE						1
uint8_t GPI_activeState(void);


#endif