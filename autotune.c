/*******************************************************************
 *
 * File name: autotune.c
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
 * Description: This is the interface file for auto and manual 
 *				antenna tuning.
 * 
 * Creator: Joe Galanti
 *
 * Date Created:
 *
 * $History: autotune.c $
 * 
 * *****************  Version 40  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 39  *****************
 * User: Galantij     Date: 5/13/15    Time: 1:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Installed a "ENABLE_WD_TICKLE" define macro around tickle.
 * 
 * *****************  Version 38  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 37  *****************
 * User: Galantij     Date: 3/27/14    Time: 1:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixes Defect #  (auto tune eepom gets corrupted when rapidly pressing
 * the reset button). The problem was the frame rate for auto tune in the
 * eeprom was corrupted. To fix the problem I hardcoded the frame rate for
 * auto tune since it will never change. I also found the manual current
 * does not have to be stored in eeprom or the VPA. 
 * 
 * *****************  Version 36  *****************
 * User: Galantij     Date: 3/21/14    Time: 2:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #104 (Overvoltage test could deactivate tags when unit is in
 * Verify Mode) Fixed a problem with the scheduled overvoltage test
 * possible being able to deactivate tags when in he verify mode. 
 * 
 * *****************  Version 35  *****************
 * User: Galantij     Date: 3/12/14    Time: 1:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This maybe a fix for Defect #100 (mistune occurs over a period of time,
 * (24-48 hours), when the unit is in 10 Hz, Mode 4 and using the SRRC tag
 * band). Although this may not fix the issue, it does fix a problem with
 * the postion of the ADC sampling of the ant sample port.
 * 
 * *****************  Version 34  *****************
 * User: Galantij     Date: 3/04/14    Time: 5:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new parameter for setVPA_Level() to indicate the frame rate for
 * the change to 10 Hz PWM charge rate.
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:26a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 32  *****************
 * User: Galantij     Date: 1/30/14    Time: 5:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Missed a timer when changing the tuning verification time from 10 hours
 * to 1 hour
 * 
 * *****************  Version 31  *****************
 * User: Galantij     Date: 1/28/14    Time: 8:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Used new dac_write_data() function.
 * 
 * *****************  Version 30  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added watchdog tickle in the main auto tune loop and added code to make
 * sure if either seq or interleave is selected the center freq will be
 * used during auto tune.
 * 
 * *****************  Version 28  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:12a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code added in the overvoltage detection code to support the new DMS
 * dual sliders to map the HI/LO switch
 * 
 * *****************  Version 27  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added test code to allow a 30 sec timer for tuning verify mode.
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 11/20/13   Time: 5:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the overvoltage threshold from working from the HW
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the second input parameter (autotune_timing) from from
 * startAutoTune() and added the code for the overvoltage test
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:47p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the code to flash the mistune LED (flashing red LED) for DMS
 * tuning session
 * 
 * *****************  Version 23  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:43p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * changed name of var from intlk_enable_ind to intlk_enable
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created macro defines to enable/disable the rail discharge code. For
 * this release this is disabled
 * 
 * *****************  Version 21  *****************
 * User: Dubes        Date: 10/10/13   Time: 6:31p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added AUTOTUNE_VERIFY_EXECUTE insted of 1
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 10/10/13   Time: 5:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to discharge the VPA rail after auto tuning.
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 9/27/13    Time: 11:09a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * code to support the DMS antenna tuning display. Still needs Sandeep's
 * code and the latest DMS to complete the feature
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 9/25/13    Time: 11:15a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support 10 Hz
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Imcreased ant_tune_relays to 2 Bytes
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:19p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to monitor the interlock pin state and if low start TX/RX
 * cycle during power up. When the pin goes high set interlock timer as
 * normal.
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 8/28/13    Time: 10:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Comment clean up
 * 
 * *****************  Version 14  *****************
 * User: Dubes        Date: 8/28/13    Time: 2:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Calculate CRC after writing to EEPROM
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Finished and tested code for tuning verify feature
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Started the verify tune mode for auto tune
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 8/15/13    Time: 3:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug in auto tune for manual mode. The TX/RX cycle would start
 * even if the interlock setting was enabled.
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 8/09/13    Time: 8:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * For the first time there is no data in thr eepom. This would make the
 * auto tune fail. For the first time create a default and store into
 * eeprom.
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 8/09/13    Time: 10:36a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the hooks into the config DB in auto tune
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added config include file
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changes done after HW integration
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added dip switch setting in place of hardcode
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Some cleanup for the auto tune code
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:38a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed auto tune bug which started the deactivation before the interlock
 * was selected
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 7/01/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Clean up and comments and setup test GPIO for the relay outputs to
 * start testing before the HW is ready
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:44p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added all functional for auto and manual tuning. This sets the relay
 * positions, retrives ant current and compares to find the highest
 * current for a given ant relay position. This stilll  needs to be test
 * using HW with a lot of unknowns at this point (HW current range,
 * different ranges for different loops, HW settling time, GPIO used for
 * relay setting, etc...)
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:10a
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * initial
 * 
 ********************************************************************/

#include "autotune.h"
#include "timers.h"
#include "analog.h"
#include "lowlevel.h"
#include "interface.h"
#include "nvm_eeprom.h"
#include "zircon_config.h"
#include "GTimer.h"
#include "alarm.h"
#include "watchdog.h"

// extern variables
volatile uint8_t gAutoState;
volatile uint8_t autotune_timing_flag = 0;
volatile uint8_t autotune_verify_handler = 0xff;
volatile uint8_t autotune_verify_flag = 0;
volatile uint8_t autotune_verify_started = 0;
volatile uint8_t autotune_overvoltmeas_flag = 0;
volatile uint8_t autotune_overvolt_handler = 0xff;

// static variables
static volatile uint16_t autotune_meas_array[10] = {0};
static volatile uint8_t autotune_flag = 0;
static volatile uint8_t autotune_dms_flag = 0;
static volatile uint8_t autotune_overvolt_flag = 0;
static volatile uint8_t autotune_dmsOV_flag = 0;
static profileStructType higher_peak;
static uint16_t manual_current = 0;

// static functions
static void compareAutoTune(void);
static uint8_t adj_AutoTune(uint8_t adj_results, uint8_t autotune_state);

extern volatile uint8_t start_intlk_timer;

// global function
void startAutoTune(uint8_t autotune, uint8_t tuning_mode)
{
	uint8_t return_status;
	uint16_t current_diff = 0;
	uint8_t intlk_signal_state = 0;
	uint8_t temp_frame_rate = 0;
#if RAIL_DISCHARGE
	uint8_t vpa_result = 0;
#endif

	// start TX/RX cycle to allow autotuning measurements
	// setup ADC and timers
	adc_init();
	adc_enable();
		
	// Read the first time byte for the auto tune structure, and if the 
	// first time used, set to default values and store in eeprom.
	return_status = nvm_eeprom_read_byte(EEPROM_ZIRCON_USER_DEF_AUTOTUNE);
	if(return_status != 0x01)
	{
		higher_peak.first_time_flag = 0x01;
		higher_peak.vpa_setting = 19;
		higher_peak.frame_rate = FRAME_144HZ;
		higher_peak.manual_value = 0;
		higher_peak.peak_value = 0;
		higher_peak.peak_position = 0;
		higher_peak.relay_position = 0x00;
		higher_peak.mistune_flag = 0x00;
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_USER_DEF_AUTOTUNE,
							&higher_peak, sizeof(profileStructType));
	}
	else // get stored auto tune structure
	{
		nvm_eeprom_read_buffer(EEPROM_ZIRCON_USER_DEF_AUTOTUNE,
								&higher_peak, sizeof(profileStructType));
	}
	
	temp_frame_rate = config_parameters.deact_frame_rate;
	setFrameRate(FRAME_144HZ);
	
	// This is the default mode for auto and manual tuning
	setDeactMode(DEACT_MODE6, TX2_DISABLE);
	
#if EVOLVESTORE
	// Only allow manual tuning after the reset when initially
	// enabling the nightsave feature.
	if(config_parameters.nightsave)
	{
		autotune_flag = 0;
	}
	else
	{
		autotune_flag = autotune;
	}
#else
	autotune_flag = autotune;
#endif

	autotune_dms_flag = 0;
	autotune_overvolt_flag = 0;
	autotune_dmsOV_flag = 0;
	
	switch(tuning_mode)
	{
		case NORMAL_MODE:
			return_status = setVPA_Level(19, FRAME_144HZ);
		break;
		
		case DMS_MODE:
			autotune_dms_flag = 1;
			return_status = setVPA_Level(19, FRAME_144HZ);
		break;
		
		case OVERVOLT_MODE:
			autotune_overvolt_flag = 1;
			if((config_parameters.mode_ind == DEACT_VERIFY) || (config_parameters.mode_ind == DEACT_MODE4))  //changed for sending deactivation message
			{
				return_status = setVPA_Level(config_parameters.config_detect_level, FRAME_144HZ);
			}
			else
			{
				return_status = setVPA_Level(config_parameters.tx_power, FRAME_144HZ);
			}
		break;
		
		case DMS_OV_MODE:
			autotune_dmsOV_flag = 1;
			if((config_parameters.mode_ind == DEACT_VERIFY) || (config_parameters.mode_ind == DEACT_MODE4))  //changed for sending deactivation message
			{
				return_status = setVPA_Level(config_parameters.config_detect_level, FRAME_144HZ);
			}
			else
			{
				return_status = setVPA_Level(config_parameters.tx_power, FRAME_144HZ);
			}
		break;
	}
		
	// setup auto tune frame rate (always 144 Hz) and use the parameter 
	// used for mode 6. Set the VPA to 19.
//	temp_frame_rate = config_parameters.deact_frame_rate;
//	setFrameRate(higher_peak.frame_rate);

#if SEQ_FREQ		
	gDACIndexLoaded = MID_RANGE_FREQ; // set for mid of tag band
#else
	gDACIndexLoaded = 14;
#endif
	
	// Enable TX/RX cycle measurement and set auto tune flag
	// to either autotune or manual tuning. This is recv by 
	// the caller (autotune).	
	autotune_timing_flag = 1;

	// For autotune, initialize the "higher_peak" to relay's lowest 
	// position and set peak_value and peak_position to zero.
	// For manual mode, get relay position from eeprom and set 
	// relay. Be sure to used the same VPA, TX PW and frame rate
	// used match a proper replacement for the stored ant current.
	if(autotune)
	{
		higher_peak.peak_value = 0;
		higher_peak.peak_position = 0;
		higher_peak.relay_position = 0x00;
		
		return_status = adj_AutoTune(higher_peak.relay_position, AUTO_STATE_MEAS);			
	}
	else // manual tuning override
	{
		return_status = adj_AutoTune(config_parameters.ant_tune_relays, AUTO_STATE_MEAS);
	}
		
	SET_AUTO_STATE(AUTO_STATE_MEAS);
		
#if USE_DDS
	ad9833_set_frequency_abs(0, gFrequencyTable[gDACIndexLoaded]);
#else
	dac_write_data(1);
#endif

#if SEQ_FREQ
	gDACIndexLoaded = MID_RANGE_FREQ; // set for mid of tag band
#else
	gDACIndexLoaded = 14;
#endif

	// start auto/manual tuning
	frame_timer_start();
		
	// after auto tuning is completed, start setting system back to operational 
	// state
	while(1)
	{
#if ENABLE_WD_TICKLE
		WDT_Reset();
#endif	
		if(GET_AUTO_STATE(AUTO_STATE_COMP))
		{
			adc_disable(); // only use during auto/manual tuning
			
#if RAIL_DISCHARGE
			// discharge code
			// There could be a condition when the interlock signals are coming in
			// at a fast pace where the VPA rail is charged higher than the
			// threshold voltage. In these cases TX/RX frame may not start.
			// To fixed this issue discharge the rail a little bit lower than
			// the deactivation normal VPA rail.
			if((config_parameters.mode_ind == DEACT_MODE6) || 
				(config_parameters.mode_ind == DEACT_MODE5))
			{
				setVPA_Level(config_parameters.tx_power, 
				             config_parameters.deact_frame_rate);
			}
			else // verify and 4 mode.
			{
				setVPA_Level(config_parameters.config_detect_level, 
				             config_parameters.deact_frame_rate);
			}
			vpa_result = PORTA.IN;
			if((vpa_result & (VPA_MAX_PIN)) == 0)
			{
				pwm_stop();
				TX_ENABLE_N_PORT.OUTSET = TX_ENABLE_N_PIN; /* Thoralite */
				while((vpa_result & (VPA_MAX_PIN)) == 0)
				{
					vpa_result = PORTA.IN;
				}
				TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN; /* Thoralite */
				gDACIndexLoaded = 0;
			}
			// end of discharge code /////////////////////////////// 
#endif
			config_parameters.deact_frame_rate = temp_frame_rate;
			if (DEACT_MODE4 ==config_parameters.mode_ind )  //change for sending deactivation message
			{
				setDeactMode(DEACT_VERIFY, config_parameters.enable_tx_2); 
			}
			else
			{
				setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
			}
			
			setFrameRate(config_parameters.deact_frame_rate);
				
			// if interlock is not enabled start TX/RX cycle (frame timer)
			if(!(config_parameters.intlk_enable))
			{
				frame_timer_start();
			}
			else // if autotune_verify_started == 0 then ???  // interlock enabled
			{
				// This should fix the issue with starting the frame when
				// the interlock signal is grounded during power up.
				// Take care of Soft InterLock also				
				intlk_signal_state = PORTE.IN;
				if(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
				(SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))
				{
					processInterlock();
					start_intlk_timer = 1;  // enable level monitoring in idle loop
					frame_timer_start();
				}
			}
				
			// stop further auto tune processing in timing loop
			autotune_timing_flag = 0; 
				
			if(autotune_verify_started)
			{
				// compare the ant tune current found during the initial auto tuning to
				// the value just computed (peak value) and if less find the different.
				// If the difference indicates a 50% reduction in antenna current, set 
				// the mistune LED, if not restart the timer for the  next verify 
				// session. 
				if((manual_current) < (higher_peak.peak_value))
				{
					current_diff =
						((higher_peak.peak_value)-(manual_current));
								
					if(current_diff > ((higher_peak.peak_value)/2))
					{
						// set mistune indication and LED
						config_parameters.ant_tune_mistune_ind = 1;
						buildStatusPayload(PAYLOAD_MISS_TUNED);
						misTuningBlinking();
					}
					else //current is lower than initial autotune, but within tolerate
					{
						// reset timer for next verify tuning session
						GTimer_Refresh(autotune_verify_handler, G_TIMER_1H);
						//GTimer_Refresh(autotune_verify_handler, G_TIMER_30S);
					}
				}
				else // current is either the same or greater
				{
					// auto tuning is good (no mistune) restart timer for next 
					// verify tuning session
					GTimer_Refresh(autotune_verify_handler, G_TIMER_1H);
					//GTimer_Refresh(autotune_verify_handler, G_TIMER_30S);
				}
					
				autotune_verify_started = 0;
			}
				
			break;
		}
	}			
}


// global function
void measureAutoTune(void)
{
	static uint8_t autotune_settle_counter = 0;
	static volatile uint8_t meas_array_index = 0;
	
	// During this state, ant current measurements and made and 
	// stored in an array
	// This test also locks out TX/RX cycles from being measured 
	// and stored while the previous 10 samples are being processed. 
	if(GET_AUTO_STATE(AUTO_STATE_MEAS))
	{
		autotune_settle_counter++;
		
		// Allow the new relay setting to settle for 20 TX/RX cycles
		// before taking samples
		if(autotune_settle_counter > AUTO_SETTLE_TIME)
		{
			// Take 10 ant current samples and store away
			if(meas_array_index < AUTO_SAMPLE_TIME)
			{
#if 0
				TEST_PORT.OUTTGL = TEST_PIN;
#endif
				adc0_start();
				
				do { } while ( !( ADC.INTFLAGS & ADC_CH0IF_bm) );	
				autotune_meas_array[meas_array_index++] = ADC.CH0RES;
				ADC.INTFLAGS |= ADC_CH0IF_bm;	
			}
			else // Send 10 samples to be averaged and compare to highest 
			     // peak found so far
			{
				SET_AUTO_STATE(AUTO_STATE_COMPARE);
				meas_array_index = 0;
				autotune_settle_counter = 0;
				compareAutoTune();
			}
		}
	}
}


// auto tune verification is activated from expired timer
// (call back function)
void verifyTuning(void)
{
	autotune_verify_flag = AUTOTUNE_VERIFY_EXECUTE;	
}

void verifyovervolt(void)
{
	autotune_overvoltmeas_flag = 1;
}


/*
** Function: compareAutoTune (private)
**
** Purpose :	Compare function averages ant current samples from TX/RX cycles
**				and compares to the highest peak found so far. If the new value
**				is higher than the stored peak, the new value will replace the
**				old peak and the relay position is stored to allow mapping to
**				the new peak. In any case the relay position is incremented by
**				one ready for a new measurement cycle. If all 32 positions are
**				tried, set relay to the highest peak found from the search.
**
** Parameters:
**     Input :	None
**
**     Return: None
**
** Effected Var's: AUTO_STATE: This transitions from "AUTO_STATE_COMPARE"
**								to "AUTO_STATE_ADJ" 
**				higher_peak:
**					peak_value-> ant current could be replaced with new value 
**								if higher
**					peak_position-> relay position could be replaced if new 
**								value is higher
**					relay_position-> This is increased when all 32 positions of 
**								the relay have not been tried yet.
**
** Effected IO/HW: eeprom updates with new ant current, VPA level and TX PW 
**					for manual mode
**
*/
static void compareAutoTune(void)
{
	uint8_t i, return_status;
	unsigned long auto_tune_sum;
	uint16_t calc_crc = 0;
	uint16_t overvolt_current = 0;

	// start process ant samples if compare state.	
	if(GET_AUTO_STATE(AUTO_STATE_COMPARE))
	{	
		auto_tune_sum = 0;
		SET_AUTO_STATE(AUTO_STATE_ADJ);
				
		for(i=0; i<AUTO_SAMPLE_TIME; i++)
		{
			auto_tune_sum += autotune_meas_array[i];
		}
		
		// if auto tune is selected, compared new value with old highest 
		// value and if higher, rewrite with new value.
		if(autotune_flag)
		{
			if((auto_tune_sum/AUTO_SAMPLE_TIME) > higher_peak.peak_value)
			{
				higher_peak.peak_value = auto_tune_sum/AUTO_SAMPLE_TIME;
				higher_peak.peak_position = higher_peak.relay_position;
			}
			
			++higher_peak.relay_position;
			
			// Still more relay positions to compare
			if(higher_peak.relay_position < NUM_RELAY_POSITIONS)
			{
				return_status = adj_AutoTune(higher_peak.relay_position, AUTO_STATE_ADJ);
			}
			else  // Completed all 32 positions, mark auto tuning for completion
			{
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_USER_DEF_AUTOTUNE, 
									&higher_peak, sizeof(profileStructType));

				config_parameters.ant_tune_current = higher_peak.peak_value;
				config_parameters.ant_tune_relays = higher_peak.peak_position;
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS, &config_parameters.ant_tune_relays, 2); // just copy the Data from EEPROM
				// calculate the new crc value
				calc_crc =  calculateCrcEeprom();
				// write it back
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2) ;// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2
				return_status = adj_AutoTune(higher_peak.peak_position, AUTO_STATE_COMP);
			}			
		}
		else  // manual tuning
		{
			// For this mode the results from the tuning are used to measure for a mistune
			// condition. This is done through the DMS tool via a 10 ten timer. If a 
			// mistune condition is detected, a flashing red LED will occur.
			if(autotune_dms_flag)
			{
				autotune_dms_flag = 0;
				
				config_parameters.ant_tune_current = auto_tune_sum/AUTO_SAMPLE_TIME;
				
				// If antenna signal strength fall to 50% of original value a mistune 
				// condition is reported using the red flashing LED.
				if((config_parameters.ant_tune_current) < ((higher_peak.peak_value)/2))
				{
					config_parameters.ant_tune_mistune_ind = 1;
					buildStatusPayload(PAYLOAD_MISS_TUNED);
					misTuningBlinking();
				}
				else
				{
					config_parameters.ant_tune_mistune_ind = 0;
					buildStatusPayload(PAYLOAD_TUNED);
					misTuningBlinkingOff();
				}
			}
			// This test for a overvoltage condition during normal operation after 
			// a given time period. If a overvoltage is detected a red flashing LED
			// indicates a overvoltage and the VPA level is reduce by one and the 
			// the overvoltage test iteration re-occurs 
			else if(autotune_overvolt_flag)
			{
				autotune_overvolt_flag = 0;
				
				overvolt_current = auto_tune_sum/AUTO_SAMPLE_TIME;
				
				// test for over voltage
				if(overvolt_current > OV_THRESHOLD) // need to find over voltage level in place of 3000
				{
					config_parameters.ant_fault = 1;
					buildStatusPayload(PAYLOAD_VOLTAGE_OVER);
					// turn on over voltage indication (LED) (keep on until reset)
					misTuningBlinking();
					
					// decrease VPA rail by 1, store in EEprom (check for default value?)
					// recal CRC for eeprom
					if(config_parameters.tx_power > 0)
					{
						--(config_parameters.tx_power);
					}
					
					// Make sure to set the MS-bit before storing value in eeprom if it's a default
					// value.
					if (config_parameters.hi_low_ind)
					{
						config_parameters.config_hi_power = config_parameters.tx_power;
						if (DEFAULT_TX_POWER_HI == config_parameters.tx_power )
						{
							Set_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);// Write 2 byte  data to EEPROM
							Clr_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
						}
						else
						{
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);
						}
					}
					else
					{
						config_parameters.config_lo_power = config_parameters.tx_power;
						if (DEFAULT_TX_POWER_LO == config_parameters.tx_power )
						{
							Set_bits(config_parameters.config_lo_power, DISPLAY_DEFAULT_DMS);
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);// Write 2 byte  data to EEPROM
							Clr_bits(config_parameters.tx_power, DISPLAY_DEFAULT_DMS);
						}
						else
						{
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);
						}
					}
					
					calc_crc =  calculateCrcEeprom();
					nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2) ;// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2
							
					// Start next measurement for overvoltage (set flag for main() )
					if(config_parameters.tx_power > 0)
					{
						autotune_overvoltmeas_flag = 1;
						
					}
				}
				else  // no overvoltage condition
				{
					config_parameters.ant_fault = 0;
					buildStatusPayload(PAYLOAD_VOLTAGE_NORMAL);
				}
				
			}
			// This is used to test for an overvoltage condition during a DMS session.
			else if(autotune_dmsOV_flag)
			{
				autotune_dmsOV_flag = 0;
				
				overvolt_current = auto_tune_sum/AUTO_SAMPLE_TIME;
								
				// test for over voltage
				if(overvolt_current > OV_THRESHOLD) // need to find over voltage level in place of 3000
				{
					config_parameters.ant_fault = 1;
					buildStatusPayload(PAYLOAD_VOLTAGE_OVER);
					misTuningBlinking();
				}
				else
				{
					config_parameters.ant_fault = 0;
					buildStatusPayload(PAYLOAD_VOLTAGE_NORMAL);
					misTuningBlinkingOff();
				}
				
			}
			else  // manual tuning setting 
			{
				// write new current value, TW PW, VPA and frame rate to reproduce
				// the conditions of the measurement.
				config_parameters.ant_tune_current = auto_tune_sum/AUTO_SAMPLE_TIME;
				manual_current = auto_tune_sum/AUTO_SAMPLE_TIME;
#if 0
				higher_peak.manual_value = auto_tune_sum/AUTO_SAMPLE_TIME;
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_USER_DEF_AUTOTUNE, 
											&higher_peak, sizeof(profileStructType));
#endif
			}
			
			return_status = adj_AutoTune(config_parameters.ant_tune_relays, AUTO_STATE_COMP);
			SET_AUTO_STATE(AUTO_STATE_COMP);
		}
	}		
}	


/*
** Function: adj_AutoTune (private)
**
** Purpose :	During auto tuning this function sets the antenna tuning relays to
**				The relay bit map value (1-5) sent in by the caller is decoded and 
**				either sets or clears the relay adding or subtracting shunt capacitance
**				in parallel with the loop antenna. The decision to increase the relay
**				position or finish the measurement process will be decided by the 
**				incoming state set by the caller.
**				When completed, the new antenna current, TX PW, VPA voltage setting
**				and frame rate will be stored in eeprom. 
**
** Parameters:
**     Input :	adj_results: This the bit mapped relay position between 1-5 and is 
**								used to set the relays
**				autotune_state: This parameter is used to make the next decision about 
**								which state to transition to.
**
**     Return: if adj_results is between 0-31 (within relay range) a one is sent back
**				to the caller indicating a correct input, if zero is returned back,
**				adj_results is out of range and the caller should resend with the 
**				proper range.
**
** Effected Var's:
**
** Effected IO/HW:
**
*/
static uint8_t adj_AutoTune(uint8_t adj_results, uint8_t autotune_state)
{
	uint8_t i;
	uint8_t return_status = AUTO_FAIL;
	
	// Make sure the incoming relay bit map is within range (0-31) + 1 for
	// final setting.
	if((adj_results >= 0) && (adj_results < NUM_RELAY_POSITIONS+1))
	{
		for(i=0; i<NUM_RELAY_GPIO; i++) // transverse all bit positions in bit map
		{
			// Shift each bit to LS positions and evaluate for set/clear condition 
			// for each relay position
			if((adj_results >> i) & RELAY_MASK) 
			{
				switch(i) // set the relay position
				{
					case 0: TUNE_RELAY0_PORT.OUTSET = TUNE_RELAY0_PIN; break;
			
					case 1: TUNE_RELAY1_PORT.OUTSET = TUNE_RELAY1_PIN; break;
			
					case 2: TUNE_RELAY2_PORT.OUTSET = TUNE_RELAY2_PIN; break;
			
					case 3: TUNE_RELAY3_PORT.OUTSET = TUNE_RELAY3_PIN; break;
			
					case 4: TUNE_RELAY4_PORT.OUTSET = TUNE_RELAY4_PIN; break;
			
					default:
					break;
				}
			}
			else
			{
				switch(i) // clear the relay position
				{
					case 0: TUNE_RELAY0_PORT.OUTCLR = TUNE_RELAY0_PIN; break;
				
					case 1: TUNE_RELAY1_PORT.OUTCLR = TUNE_RELAY1_PIN; break;
				
					case 2: TUNE_RELAY2_PORT.OUTCLR = TUNE_RELAY2_PIN; break;
				
					case 3: TUNE_RELAY3_PORT.OUTCLR = TUNE_RELAY3_PIN; break;
				
					case 4: TUNE_RELAY4_PORT.OUTCLR = TUNE_RELAY4_PIN; break;
				
					default:
					break;
				}
			}
		}
	
		if(autotune_state == AUTO_STATE_COMP)
		{
			pwm_stop(); 
			FRAME_TIMER.INTCTRLA = TC_OVFINTLVL_OFF_gc;
			FRAME_TIMER.INTFLAGS = 0xff;

			frame_timer_stop();
			autotune_timing_flag = 0;
		
			SET_AUTO_STATE(AUTO_STATE_COMP);
		}
		else
		{
			SET_AUTO_STATE(AUTO_STATE_MEAS);
		}
		
		return_status = AUTO_SUCCESS;
	}
	else
	{
		return_status = AUTO_FAIL;
	}
	
	return(return_status);	
}

