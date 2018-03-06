/*******************************************************************
 *
 * File name: timers.c
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
 * $History: timers.c $
 * 
 * *****************  Version 39  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 38  *****************
 * User: Galantij     Date: 5/13/15    Time: 2:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the 40 mS TX/RX delay from the TX interrupt and the section
 * where the pulseNumber is incremented. Added macro defines around the WD
 * tickles.
 * 
 * *****************  Version 37  *****************
 * User: Dubes        Date: 7/28/14    Time: 1:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * The Changes to address QC issue EAS.Zircon - Defect # 116 for Mode 4
 * and verification mode we are taking out the delay every 5 th pulse
 * 
 * *****************  Version 36  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 35  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 34  *****************
 * User: Galantij     Date: 3/12/14    Time: 1:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a test in a section of code for 10 Hz to include a test for the
 * auto tuning flag.
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 2/26/14    Time: 11:47a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This fixes Defect#60 (seem to get more false alarms when second
 * transmitter is active near E3). Increment new timers for each frame.
 * Now there is a dedicated frame counter for each loop when the 2nd TX is
 * enabled.
 * 
 * *****************  Version 32  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:26a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (Verify mode kills 410 EP tags). Added logic function
 * pwm_start() to not enable the PWM if VPA is set to zero
 * 
 * *****************  Version 31  *****************
 * User: Galantij     Date: 2/20/14    Time: 5:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed Defect #85 (when the 2nd TX is enabled the auto tune signal
 * strength is only half of what it should be). This was fixed by testing
 * in the toggle function.
 * 
 * *****************  Version 30  *****************
 * User: Galantij     Date: 2/18/14    Time: 11:36a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added jitter parameter to the 10 Hz and moved the setting of the 10 Hz
 * burst rate into the actual ISR
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 2/04/14    Time: 11:08a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added watchdog tickle to the frame ISR and when frames are initially
 * started
 * 
 * *****************  Version 28  *****************
 * User: Galantij     Date: 1/28/14    Time: 8:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Enabling the VCO about 4 uS before the TX PW and disabling the VCO
 * right after receiver gate is closed. This helps compliance.
 * 
 * *****************  Version 27  *****************
 * User: Galantij     Date: 1/16/14    Time: 3:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a comment to the area where the ant port is being sampled via ADC
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 1/07/14    Time: 4:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * New timing was created for the new 10 Hz frame rate for both primary
 * and secondary antenna.
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support the different TX freq transmit methods;
 * seq/interleaved
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 12/05/13   Time: 4:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Moved ADC sample point from after the IRS delay to after the RX gate PW
 * is completed. This reduces the ADC sample point from 60us to 20us.
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed a problem of not turning the blue LED back on after the system is
 * no interlocked and the forced deactivation was selected for the GPI
 * feature.
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code in the interlock ISR to handle the forced deactions feature
 * for the GPI features set. Also added the sync test for the RTC timer
 * before writing to an registers
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 10/24/13   Time: 10:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleared flags in the interlock ISR for the new method of mode
 * processing.
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increase the 10 Hz blast rate from 210us to 410us to protect against FA
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 10/10/13   Time: 5:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Shut down all alarm indications (LED, sounder and IO) and disable tag
 * ISR when the interlock expirers.
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 9/27/13    Time: 11:12a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increaed jitter for 10 Hz frame rate
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 9/25/13    Time: 11:14a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code for 10 Hz support
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the adjustable PWM duty cycle in "pwm_start()"
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support the 2nd TX and the interlock feature.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug which would not allow the state of PROCESS when RX/TX cycle
 * was active
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:47p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Implemented a frame counter for the consecutive tag feature
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Moved the tag ISR to the beginning of the RX gate enable to allow
 * better detection. 
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the auto tuning TX PW from 166ns to 6us
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:18p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code for 2nd TX
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "HAFNON define to comment the active RX from low to high between
 * Hafnon and Thorite.
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changes to the Interlock initialization to allow the RTC to be used for
 * the DMS timeout.
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:44a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added some changes for auto tuning
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Inserted the auto tune flag to control the TX/RX cycle
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:32p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added interlock control and function to change freq after each TX/RX
 * cycle iteration.
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Function body for interlock config interface into low level
 * timingSandeep added RTC functions 
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:44p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 5  *****************
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

#include "timers.h"
#include "autotune.h"
#include "lowlevel.h"
#include "interface.h"
#include "zircon_config.h"
#include "alarm.h"
#include "watchdog.h"
#include "GTimer.h"
#include "rs232.h"

// For transmitter and LO frequency generation/accuracy either the 
// DDS is used or VCO. The VCO method may need to be validated via
// counter algorithms. 
#if USE_DDS
#include "dds.h"
#else
#include "analog.h"
#endif 

static void rx_rail_chargeup(void);
static void toggleLoops(void);
static void clearCycleTimer(void);

static uint8_t frame_timer_div = TC_CLKSEL_DIV4_gc;
static uint8_t interlock_timer_div = RTC_PRESCALER_DIV1_gc;

// Keep track on the number of tag detection to verify tag deactivation.
volatile uint8_t frame_counter = 0;
volatile uint8_t primary_ant_flag = 0;
volatile uint8_t secondary_ant_flag = 0;
volatile uint32_t frame_counter_flag = 0;
volatile uint32_t pri_frame_counter_flag = 0;
volatile uint32_t sec_frame_counter_flag = 0;
volatile uint8_t TxRx_cycle_enable = 0;
volatile uint8_t GPI_mode_change = 0;
//volatile uint8_t pwm_lockout_flag = 0;

#if MODE_PROCESS

#else
volatile uint8_t inhibit_flag = 0;
volatile uint16_t alarm_count_down = 0;
#endif

/*
** Function: (ISR) frame timer overflow signal
**
** Purpose : Maintains a 7ms frame rate which could provide a 
**				TX/RX cycle. There is also an algorithm to 
**				ensure the PWM charge is not on for longer than 14ms
**
** Parameters:
**     Input : source from internal frame timer expiring
**
**     Return: None
**
** Effected Var's:	frame_counter: used to ensure the PWM is on no longer
**									than 14ms to protect HW
**
** Effected IO/HW: VPA rail charging PWM is enabled if continuous charging
**					is under 14ms (HW protection)
**
*/
ISR(TC_FRAME_vect)
{
	uint8_t vpa_result = 0;

	if((config_parameters.deact_frame_rate == FRAME_10HZ) && (!autotune_timing_flag))
	{
		// set the first frequency before executing 16 TX/RX blasts
		gDACIndexLoaded = 0;
	}

//	if(config_parameters.deact_frame_rate == FRAME_144HZ)
//	{
//		dac_write_data(1);
//	}

	if(!autotune_timing_flag)
	{
		createJitter(0);
		TAG_N_PORT.INT0MASK &= (~TAG_N_PIN);

		// Start next frame, charge VPA rail and set state to charge
		SET_STATE(STATE_CHARGE);
	}
	else
	{
		// disable jitter during auto tuning
		createJitter(1);
		SET_STATE(STATE_AUTOTUNE);
	}	
	// If the PWM is not active start charging the VPA rail, else if 
	// the frame counter is greater than zero (been charging for two 
	// frames 14ms) stop PWM
	// If both conditions are not met, the PWM has been active for 7ms
	if(PWM_TIMER.CTRLA == TC_CLKSEL_OFF_gc)
	{
		vpa_result = PORTA.IN;
		
		// If the VPA monitor signal is low do not start the PWM VPA
		// charging output. There could be an issue with the TX circuit
		// not allowing the VPA to drain off.
		if((vpa_result & (VPA_MAX_PIN)) == VPA_MAX_PIN)
		{
			pwm_start();
		}
		else
		{
			pwm_stop();
		}
	}
	else if(frame_counter > 0)
	{
		pwm_stop();
		frame_counter = 0;
	}
	else
	{
		frame_counter++;
	}

#if HALFNON
	//RX_EN_PORT.OUTSET = RX_EN_PIN;  // blue trace test signal
	//RF_EN_PORT.OUTCLR = RF_EN_PIN; // green trace
	
	if(!autotune_timing_flag)
	{
		RX_EN_PORT.OUTSET = RX_EN_PIN; // enable RX rail voltage
	}
#endif

#if ENABLE_WD_TICKLE
	WDT_Reset();
#endif
	// if the frame timer has started and the dms is not restarted restart it here
	// this will also help us to DMS start quickly as we just need to delay the by less then 5 ms
	// to eat up all the 52 bytes. and this timer is 7 ms timer
	if(1 == flag_status_inhibit_handler)
	{
		dms_rs232_init();
		flag_status_inhibit_handler = 0;
	}
	toggleLoops();
	clearCycleTimer();
	rx_rail_chargeup();
}

// This function decides which transmitter is active at a certain 
// time frame. This is important when the 2nd TX is enabled to allow
// an interleaving between both transmitters. When the 2nd TX is 
// disabled only the primary loop is selected.
static void toggleLoops(void)
{
	static uint8_t toggle_flag = 1;
	
	// 2nd TX is enabled, find the active transmitter for this 
	// frame.
	if((config_parameters.enable_tx_2) && (!autotune_timing_flag) &&
		(CPiD_HW_flag))
	{
		// The primary transmitter is selected
		if(toggle_flag)
		{
			secondary_ant_flag = 0;
			primary_ant_flag = 1;
			
			// This counter is used to track consecutive alarms
			// to help prevent false alarms from environment
			if(++pri_frame_counter_flag == 0xffffffff)
			{
				pri_frame_counter_flag = 0;
			}
			
			toggle_flag = 0;
			// See if the Alarm is on and then put it off
			
			
		}
		else // Secondary transmitter is selected
		{
			primary_ant_flag = 0;
			secondary_ant_flag = 1;
			
			// This counter is used to track consecutive alarms
			// to help prevent false alarms from environment			
			if(++sec_frame_counter_flag == 0xffffffff)
			{
				sec_frame_counter_flag = 0;
			}			
			
			toggle_flag = 1;
		}
	}
	else // Only primary transmitter is used
	{
		primary_ant_flag = 0;
		secondary_ant_flag = 0;
		
#if 0		
		// Only increment the frame counter flag if we are not going 
		// have a delay
		// We dont want to add delay after 5th pulses in Mode 4 and verification
		if ( (5 != pulseNumber) || (DEACT_MODE4 == config_parameters.mode_ind)
		|| (DEACT_VERIFY == config_parameters.mode_ind))
		{
			// This counter is used to track consecutive alarms
			// to help prevent false alarms from environment
			if(++frame_counter_flag == 0xffffffff)
			{
				frame_counter_flag = 0;
			}
		
			toggle_flag = 1;
		}
		else
		{
			frame_counter_flag--;
		}
		pulseNumber++;
		pulseNumber = pulseNumber % 6;
#else
		// This counter is used to track consecutive alarms
		// to help prevent false alarms from environment
		if(++frame_counter_flag == 0xffffffff)
		{
			frame_counter_flag = 0;
		}
		
		toggle_flag = 1;

#endif
	}
//  Only for Mode 6 we should have this 
	
	if((DEACT_MODE6 == config_parameters.mode_ind) && (!autotune_timing_flag) && (FRAME_10HZ != config_parameters.deact_frame_rate) )
	{
		// We have to add 40 ms delay only when we are in Primary
		// toggel_flag is set to 1 only when the primary antenna is being used
		if (1 == toggle_flag)
		{		
			pulseNumber++;
			pulseNumber = pulseNumber % 6;
			
			if (5 == pulseNumber)
			{
				setFrameRate(FRAME_DELAY_40MS);
				frame_timer_start();
				frameRateChanged = 1;
				// To accumulate time elapsed
				if (0 != flag_send_end_alarm)
				{
					alarmAccumulatedTime = alarmAccumulatedTime + 40; // Add 40 ms each time				
				}
				 
			} else
			{   
				// Reset the frame rate to 144 after the frame rate was changed 
				if (frameRateChanged)
				{
					setFrameRate(FRAME_144HZ);
					frame_timer_start();
					frameRateChanged = 0;
				}
				// To accumulate time elapsed
				if (0 != flag_send_end_alarm)
				{
					alarmAccumulatedTime = alarmAccumulatedTime + 7; // Add 7 ms each time
				}		
							
			}
		} else
		{
				// Reset the frame rate to 144 after the frame rate was changed
				if (frameRateChanged)
				{
					setFrameRate(FRAME_144HZ);
					frame_timer_start();
					frameRateChanged = 0;
				}
				// To accumulate time elapsed
				if (0 != flag_send_end_alarm)
				{
					alarmAccumulatedTime = alarmAccumulatedTime + 7; // Add 7 ms each time
				}	
		}
		
		// Only in the case of Tag rate of 16 we have to do this since the duration to see TAG  16 time exceeds the alarm duration 500 ms
		// In all other cases it is good 
		if ((1 == flag_enable_hard_tag_indicator) && (16 == tags_before_alarm))
		{
			if (1 == flag_send_end_alarm) // Indicates Primary alarm
			{
				// Count the no of frames seen without the TAG being present in the field so as to disable 
				// The alarm, Only done when alarm time is long
				primary_tag_counter_without_tag = primary_tag_counter_without_tag + 1; // Add 7 ms each time			
				if ( primary_tag_counter_without_tag >  (2 * tags_before_alarm))
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);		
				}	
						
			} else if(2 == flag_send_end_alarm) // Indicates secondary alarm
			{
				// Count the no of frames seen without the TAG being present in the field so as to disable
				//The alarm, Only done when alarm time is long
				secondary_tag_counter_without_tag = secondary_tag_counter_without_tag + 1; // Add 7 ms each time
				if ( secondary_tag_counter_without_tag >  (2 * tags_before_alarm))
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);		
				}
			} else{
						
				primary_tag_counter_without_tag = 0;
				secondary_tag_counter_without_tag = 0;
			}
		} else
		{
				primary_tag_counter_without_tag = 0;
				secondary_tag_counter_without_tag = 0;	
		}
		
   } else if((DEACT_MODE6 != config_parameters.mode_ind) && (!autotune_timing_flag) && (FRAME_10HZ != config_parameters.deact_frame_rate) ) // End of mode 6
   {
		// Counting for all other mode
		frameRateChanged = 0;
		pulseNumber = 0;
		//Counting Time 
		if (0 != flag_send_end_alarm)
		{
			// To accumulate time elapsed
			alarmAccumulatedTime = alarmAccumulatedTime + 7; // Add 7 ms each time
		}
		if ((1 == flag_enable_hard_tag_indicator) && (16 == tags_before_alarm) && (DEACT_MODE4 == config_parameters.mode_ind))
		{
			if (1 == flag_send_end_alarm) // Indicates Primary alarm
			{
				// Count the no of frames seen without the TAG being present in the field so as to disable
				// The alarm, Only done when alarm time is long
				primary_tag_counter_without_tag = primary_tag_counter_without_tag + 1; // Add 7/14 ms each time
				if ( primary_tag_counter_without_tag >  (3 * tags_before_alarm))
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);
				}
					
			} else if(2 == flag_send_end_alarm) // Indicates secondary alarm
			{
				// Count the no of frames seen without the TAG being present in the field so as to disable
				// The alarm, Only done when alarm time is long
				secondary_tag_counter_without_tag = secondary_tag_counter_without_tag + 1; // Add 7/14 ms each time
				if ( secondary_tag_counter_without_tag >  (3 * tags_before_alarm))
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);
				}
				} else{
					
				primary_tag_counter_without_tag = 0;
				secondary_tag_counter_without_tag = 0;
			}
		} else
		{
			primary_tag_counter_without_tag = 0;
			secondary_tag_counter_without_tag = 0;
		}			
	

   } else if( (!autotune_timing_flag) && (FRAME_10HZ == config_parameters.deact_frame_rate) ) // End of mode 6
   {
		pulseNumber = 0;
		frameRateChanged = 0;
		// To accumulate time elapsed
		if(0 != flag_send_end_alarm)
		{
			alarmAccumulatedTime = alarmAccumulatedTime + 100; // Add 100 ms each time
			
			// Only if Hard tag indicator is on
			if (1 == flag_enable_hard_tag_indicator)
			{
				if ( (( 8 == tags_before_alarm) && (!config_parameters.enable_tx_2)) ||
				     (( 4 == tags_before_alarm) && (config_parameters.enable_tx_2))  ||
				     (( 16 == tags_before_alarm) && (!config_parameters.enable_tx_2))||
				     (( 8 == tags_before_alarm) && (config_parameters.enable_tx_2)) || 
				     (( 16 == tags_before_alarm) && (config_parameters.enable_tx_2)) || 
				     (( 2 == tags_before_alarm) && (config_parameters.enable_tx_2)) )
				{
					if (1 == flag_send_end_alarm)
					{
						// Count the no of frames seen without the TAG being present in the field so as to disable
						// The alarm, Only done when alarm time is long						
						primary_tag_counter_without_tag = primary_tag_counter_without_tag + 1; // Add 100/200 ms each time
						if ( primary_tag_counter_without_tag >  (2 * tags_before_alarm))
						{
							GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);
						}
					} else if(2 == flag_send_end_alarm)
					{
						// Count the no of frames seen without the TAG being present in the field so as to disable
						// The alarm, Only done when alarm time is long						
						secondary_tag_counter_without_tag = secondary_tag_counter_without_tag + 1; // Add 100/200 ms each time
						if ( secondary_tag_counter_without_tag >  (2 * tags_before_alarm))
						{
							GTimer_Refresh(alarmHandle_solt, G_TIMER_100mS);
						}
					}
				}
					
			} else
			{
				primary_tag_counter_without_tag = 0;
				secondary_tag_counter_without_tag = 0;
			}		
		} else  // end of if(0 != flag_send_end_alarm)
		{
			
			primary_tag_counter_without_tag = 0;
			secondary_tag_counter_without_tag = 0;			
		}
   } 
   

}

// This function allows a delay after the frame timer is started to
// allow jitter to be added to the TX burst and the rail to settle
// before the TX burst occurs.
static void rx_rail_chargeup(void)
{
#if HALFNON
	//RF_EN_PORT.OUTTGL = RF_EN_PIN; // pink test trace
#endif

	// Zeroize the timer counter and set the timer mode.
	CYCLE_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
	CYCLE_TIMER.CNT = 0x00;
	CYCLE_TIMER.CTRLB = (TC_WGMODE_NORMAL_gc);
	
	// If the 10 Hz frame rate is selected set the compare value
	// to the TX burst rate of each freq, set the ISR priority,
	// stop the charging of the VPA rail and start the timer.
	if(config_parameters.deact_frame_rate == FRAME_10HZ)
//	if((config_parameters.deact_frame_rate == FRAME_10HZ) && (!autotune_timing_flag))
	{
		TX_ENABLE_N_PORT.DIRSET = TX_ENABLE_N_PIN;
		CYCLE_TIMER.CCD = (ModeParaStruct.jitter); //1000;/*4000;*/ // 210us burst
		CYCLE_TIMER.INTCTRLB = TC_CCDINTLVL_HI_gc;
		pwm_stop();
		CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;
	}
	else  // 144 Hz frame rate
	{	
		// Zero timer count value
		if(!autotune_timing_flag)
		{
			CYCLE_TIMER.PER =
				(ModeParaStruct.tx_delay) + (ModeParaStruct.jitter); //1000; //12000;
		}
		else  // auto tune
		{
			CYCLE_TIMER.PER = ModeParaStruct.tx_delay; //1000; //12000;		
		}
			
		CYCLE_TIMER.INTCTRLA = TC_OVFINTLVL_HI_gc;
		CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV8_gc;
	}
}

// This is called from the overflow ISR if 144 Hz frame rate is selected and 
// is used to enable the RX switch allowing the receive signal to be processed
// by the receiver. This handler sets the time when the RX switch is to stay closed
// by setting up an ISR to close the switch after a given amount of time. 
ISR(TX_CYCLE_vect)  // CCA
{
	uint8_t i;
	
	CYCLE_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
	
	if(!secondary_ant_flag)  // primary ant
	{
		clearCycleTimer();
		CYCLE_TIMER.CCB = ModeParaStruct.rx_pw;
	}
	else //secondary ant only
	{
		TX2_ENABLE_N_PORT.OUTCLR = TX2_ENABLE_N_PIN;
		for(i=0; i<ModeParaStruct.rx2_holdoff_time; i++);  // holdoff
		RX2_ENABLE_N_PORT.OUTSET = RX2_ENABLE_N_PIN;
		for(i=0; i<1; i++);  // delay to allow the RX gate edge to settle before enable ISR
		TAG_N_PORT.INT0MASK |= TAG_N_PIN;
		clearCycleTimer();
		CYCLE_TIMER.CCB = ModeParaStruct.rx2_pw;  // RX gate duration timer
	}
	
#if 0
	// This sets the ADC sample point at 6us after TX PW
	if(autotune_timing_flag)
	{
		measureAutoTune();
	}
#endif

	// setup the next ISR
	CYCLE_TIMER.CNT = 0x00;
	CYCLE_TIMER.CTRLB = (TC_WGMODE_NORMAL_gc | TC0_CCBEN_bm);
	CYCLE_TIMER.INTCTRLB = TC_CCBINTLVL_HI_gc;
	CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;
}


// For the primary/secondary transmitter the RX switch is opened disconnecting 
// the receiver from active loop. If auto tune is active, the ADC is read for 
// tuning and overvoltage status. 
ISR(HOLD_CYCLE_vect) // CCB  
{	
	if(!autotune_timing_flag)
	{
		if(!secondary_ant_flag)
		{
#if HALFNON
			RX_ENABLE_N_PORT.OUTSET = RX_ENABLE_N_PIN;
#else
			RX_ENABLE_N_PORT.OUTCLR = RX_ENABLE_N_PIN;			
			dac_write_data(0);
#endif
		}
		else // enable RX gate secondary only
		{
#if HALFNON
			RX2_ENABLE_N_PORT.OUTCLR = RX2_ENABLE_N_PIN;
#else
			RX2_ENABLE_N_PORT.OUTCLR = RX2_ENABLE_N_PIN;			
			dac_write_data(0);
#endif
		}
	}
	
#if 1  // This is the sample point for the release code
	else //auto tuning is in session
	{
		// This sets the ADC sample point at 20us after TX PW
		measureAutoTune();
	}
#endif
		
	clearCycleTimer();
	
	// Allows some delay after the receiver is disabled to allow 
	// settling.
	if(!secondary_ant_flag)
	{
		CYCLE_TIMER.CCC = ModeParaStruct.rx_isr_delay_time;
	
	}
	else // secondary only
	{
		CYCLE_TIMER.CCC = ModeParaStruct.rx_isr_delay_time;
	}
	
	// Disable receiver ISR
	TAG_N_PORT.INT0MASK &= (~TAG_N_PIN);
	
	// setup for next ISR
	CYCLE_TIMER.CNT = 0x00;
	CYCLE_TIMER.CTRLB = (TC_WGMODE_NORMAL_gc | TC0_CCCEN_bm);
	CYCLE_TIMER.INTCTRLB = (TC_CCCINTLVL_HI_gc);

	CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;	
}

// TX/RX frame cycle is completed. Turn on the VPA rail PWM to start charging the 
// rail if needed, set to new TX freq and set state to PROCESS allowing host functions
// to execute.
ISR(RX_CYCLE_vect) // CCC
{
	uint8_t vpa_result = 0;
	
	clearCycleTimer();
	
	// Alway set the TX freq to center of band when auto tuning 
	// is active.
	if(autotune_timing_flag)
	{
#if SEQ_FREQ
		gDACIndexLoaded = MID_RANGE_FREQ;
#else
		gDACIndexLoaded = 14;
#endif
	}
	
	// set new TX frequency 
#if USE_DDS
	ad9833_set_frequency_abs(0, gFrequencyTable[gDACIndexLoaded]);
#else
	//dac_write_data(1);
#endif

	// Keep the TX freq the same until both primary and secondary transmitters
	// had a chance to transmit. This only occurs when 2nd loop is enabled. 
	if(primary_ant_flag)	
	{
		// If secondary transmitter is enabled, load the same TX frequency
		// for the secondary antenna the next time through the timer.
		if(gDACIndexLoaded > 0)
		{
			--gDACIndexLoaded;
		}
	}
	
	vpa_result = PORTA.IN;
			
	// If the VPA monitor signal is low do not start the PWM VPA
	// charging output. There could be an issue with the TX circuit
	// not allowing the VPA to drain off.
	if((vpa_result & (VPA_MAX_PIN)) == VPA_MAX_PIN)
	{
		pwm_start();
	}
	else
	{
		pwm_stop();
	}
#if 0
	// This set the ADC sample point to 60us after the TX PW
	if(autotune_timing_flag)
	{
		measureAutoTune();	
	}	
#endif	
	// Allow host functions to execute. 
	SET_STATE(STATE_PROCESS);	
}

// This function provides the TX blast PW for the primary transmitter and enables
// the secondary TX gate. The primary TX gate must be able to get as low as 170ns
// for the Verify Mode so hardware was used to get around the ISR latency. For 
// the primary transmitter this allows the holdoff time. 
ISR(START_TAG_CYCLE_vect) // Overflow
{
	uint16_t i;
	
	if(config_parameters.deact_frame_rate == FRAME_144HZ)
	{
		dac_write_data(1);
	}
	
	pwm_stop();
	
	if(config_parameters.deact_frame_rate == FRAME_144HZ)
	{
		CYCLE_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
		CYCLE_TIMER.INTCTRLA = (CYCLE_TIMER.INTCTRLA) & (~TC_OVFINTLVL_HI_gc);
	
		// Set the TX PW according to the deactivation mode. Auto tuning uses
		// the same TX PW for all modes.
		if(!autotune_timing_flag)
		{
#if 0
			// If it is the fifth pulse add a delay
			// We dont want to add delay after 5th pulses in Mode 4 and verification
			if ( (5 == pulseNumber) && (config_parameters.mode_ind != DEACT_MODE4) 
			&& (config_parameters.mode_ind != DEACT_VERIFY))
			{
				// create delay of aprox 40 ms _delay_ms(30) is near about 37 ms
				// we are not using delay_ms because of compiler warning 
				for(i=0; i<DELAY_BETWEEN_PULSE; i++); // this is near about 40 ms
			}
#endif
			CYCLE_TIMER.CCA = ModeParaStruct.tx_pw;
		}
		else // auto tune
		{
			CYCLE_TIMER.CCA = 151;
		}
		
		// For primary loop setup the hardware to allow direct access to the GPI
		// pin used for the TX gate and start timer. For the secondary loop
		// set the TX gate to start transmission and start timer.
		if(!secondary_ant_flag)
		{
			CYCLE_TIMER.CNT = 0x00;
			CYCLE_TIMER.CTRLB = (TC_WGMODE_SINGLESLOPE_gc | TC1_CCAEN_bm);
			TX_ENABLE_N_PORT.DIRSET = TX_ENABLE_N_PIN;
			CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;
			CYCLE_TIMER.INTCTRLB = TC_CCAINTLVL_HI_gc;
		}
		else // secondary antenna only
		{
			TX2_ENABLE_N_PORT.OUTSET = TX2_ENABLE_N_PIN;
			CYCLE_TIMER.CCA = ModeParaStruct.tx2_pw;
			CYCLE_TIMER.CNT = 0x00;
			CYCLE_TIMER.CTRLB = (TC_WGMODE_NORMAL_gc | TC0_CCAEN_bm);
			CYCLE_TIMER.INTCTRLB = TC_CCAINTLVL_HI_gc;
			CYCLE_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;	
		}
	
		// Set the holdoff time for the primary loop after the TX blast is completed.
		// After holdoff is completed close receiver switch and enable RX ISR and start 
		// processing tag responses.
		if(!secondary_ant_flag)
		{
			if(!autotune_timing_flag)
			{
				for(i=0; i<(ModeParaStruct.rx_holdoff_time/*21*/); i++);
#if HALFNON
				RX_ENABLE_N_PORT.OUTCLR = RX_ENABLE_N_PIN; // added for different holdoff times
#else
				RX_ENABLE_N_PORT.OUTSET = RX_ENABLE_N_PIN; // added for different holdoff times
				TAG_N_PORT.INT0MASK |= TAG_N_PIN; // Enable RX ISR
#endif 
			}
		}
	}
}

// This function is used to process the 10 Hz frame TX/RX cycle. Because of the low TX/RX cycle
// blast rate the processing for the complete cycle must be done in the contexts of one 
// ISR handler. This was needed to conform to the issues with the Alpha tags.
ISR(TAG_CYCLE_vect)  // CCD
{
	uint16_t i;
	uint8_t vpa_result = 0;	
	
	CYCLE_TIMER.CNT = 0x00;
	CYCLE_TIMER.CCD = 1000;
	
	dac_write_data(1);
	
			if(!secondary_ant_flag)
			{
				TX_ENABLE_N_PORT.OUTSET = TX_ENABLE_N_PIN;
				for(i=0; i<ModeParaStruct.tx_pw; i++);  // sets TX PW  (mode6:10)
				TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN;
				for(i=0; i<ModeParaStruct.rx_holdoff_time/*5*/; i++); // holdoff delay before RX (mode6:18)
				RX_ENABLE_N_PORT.OUTSET = RX_ENABLE_N_PIN;
				TAG_N_PORT.INT0MASK |= TAG_N_PIN;  // enable RX isr
				for(i=0; i<10/*ModeParaStruct.rx_pw*/; i++);  // sets RX PW (mode6:40)
				RX_ENABLE_N_PORT.OUTCLR = RX_ENABLE_N_PIN;
				TAG_N_PORT.INT0MASK &= (~TAG_N_PIN); // disable RX isr
			}
			else  // secondary loop
			{
				TX2_ENABLE_N_PORT.OUTSET = TX2_ENABLE_N_PIN;
				for(i=0; i<ModeParaStruct.tx2_pw; i++);  // sets TX PW
				TX2_ENABLE_N_PORT.OUTCLR = TX2_ENABLE_N_PIN;
				for(i=0; i<ModeParaStruct.rx2_holdoff_time/*5*/; i++); // holdoff delay before RX
				RX2_ENABLE_N_PORT.OUTSET = RX2_ENABLE_N_PIN;
				TAG_N_PORT.INT0MASK |= TAG_N_PIN;  // enable RX isr
				for(i=0; i<10/*ModeParaStruct.rx2_pw*/; i++);  // sets RX PW
				RX2_ENABLE_N_PORT.OUTCLR = RX2_ENABLE_N_PIN;
				TAG_N_PORT.INT0MASK &= (~TAG_N_PIN); // disable RX isr			
			}
			
			dac_write_data(0);

#if 0 		
#if USE_DDS
			ad9833_set_frequency_abs(0, gFrequencyTable[gDACIndexLoaded]);
#else
			dac_write_data(1);
#endif
#endif 

			if(gDACIndexLoaded == 0)
			{
				CYCLE_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
			
				vpa_result = PORTA.IN;
				
				// If the VPA monitor signal is low do not start the PWM VPA
				// charging output. There could be an issue with the TX circuit
				// not allowing the VPA to drain off.
				if((vpa_result & (VPA_MAX_PIN)) == VPA_MAX_PIN)
				{
					pwm_start();
				}
				else
				{
					pwm_stop();
				}
			}		
		
		SET_STATE(STATE_PROCESS);
}


// Clear timer registers for next ISR
static void clearCycleTimer(void)
{
	CYCLE_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
	CYCLE_TIMER.CTRLB = 0;
	CYCLE_TIMER.INTCTRLA = 0;
	CYCLE_TIMER.INTCTRLB = 0;
	CYCLE_TIMER.INTFLAGS = 0xff;
	CYCLE_TIMER.CCA = 0xffff;
	
	//CYCLE_TIMER.CCB = 0xffff; //installed for test
	//CYCLE_TIMER.CCC = 0xffff;
	
	CYCLE_TIMER.CNT = 0x00;
}


/*
** Function: (ISR) interlock timer signal
**
** Purpose : To only allow a restricted amount of time for deact.
**			For the handheld this will be fixed to 500ms.
**
** Parameters:
**     Input : Source: Interlock timer over flow.
**
**     Return: None
**
** Effected Var's: None
**
** Effected IO/HW: None
**
*/
ISR(TC_INTERLOCK_vect)
{
	uint8_t intlk_signal_state = 0;
	
	ledOff();
	sounderOff();
	outputOff();	
	
	// Clear the GPO output for next condition
	processGpoPin(GPO_PRI_SOUND_OUTPUT, GPO_CLEAR);
	processGpoPin(GPO_PRI_NO_SOUND_OUTPUT, GPO_CLEAR);
	processGpoPin(GPO_SEC_OUTPUT, GPO_CLEAR);
	
	TAG_N_PORT.INT0MASK &= (~TAG_N_PIN);
		
	// Both timers below are stopped when going into sleep
	if(!GPI_mode_change)
	{
		TxRx_cycle_enable = 0;
		frame_timer_stop();
		closeInterlock();
	}
	
	// Disable RX ISR and stop interlock timer
	TAG_N_PORT.INT0MASK &= (~TAG_N_PIN);
	rtc_interlock_timer_stop();
	// Reset the Soft Interlock Parameter in case it is timed based
	if(SOFT_INTERLOCK_ENABLE_TIMED == config_parameters.config_soft_interlock)
	{
		config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;
	}

	// For the forced deactivation feature if the Deactivation Mode is either Verify
	// or Mode 4, the mode was changed to allow the high power needed to deactivate
	// a tag. This set the mode back to the intended mode.
	if(GPI_mode_change)
	{
		GPI_mode_change = 0;
		if (DEACT_MODE4 ==config_parameters.mode_ind )  //change for sending deactivation message
		{
			setDeactMode(DEACT_VERIFY, config_parameters.enable_tx_2);
		}
		else
		{
			setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
		}
		//setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
		
		// need to turn on the blue LED for the condition of verify mode
		// interlock enabled and interlock pin grounded. 
		// veriify mode should be runnin after this condition.
		if(config_parameters.mode_ind == DEACT_VERIFY)
		{
			ledBlueOn();
		}
		
		// Check to see if the interlock is enabled and the pin is in non-active
		// state (pin high). If this is the case stop the disable TX/RX cycles
		// and close interlock indication.
		intlk_signal_state = PORTE.IN;
		if((config_parameters.intlk_enable) &&
		(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
		( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock) ))
		{
			frame_timer_stop();
			closeInterlock();
		}
	}

	frame_counter_flag = 0;
	pri_frame_counter_flag = 0;
	sec_frame_counter_flag = 0;
	
#if MODE_PROCESS

#else
	inhibit_flag = 0;
	alarm_count_down = 0;
#endif

#if HALFNON
	SET_STATE(STATE_SLEEP); 
#else
	SET_STATE(STATE_PROCESS);
#endif
}

// Initialize the frame timer for either 144 or 10 Hz frame rate. This is determined 
// by the DMS user.
void frame_timer_init(uint16_t timer_value, uint8_t clock_div)
{
	frame_timer_div = clock_div;
	
	// set FRAME_TIMER period to 43260 --> (1/2400000) * 4 * 41667 = 6.9445 msec (~ 144 Hz)
	FRAME_TIMER.PER = timer_value;
	
	// zero the count value
	FRAME_TIMER.CNT = 0x00;
	
	// set to normal counter mode
	FRAME_TIMER.CTRLB = (TC_WGMODE_NORMAL_gc);
	
	// enable the overflow interrupt with HI priority
	FRAME_TIMER.INTCTRLA = TC_OVFINTLVL_HI_gc;
	// Changed during testing because it maybe effecting the cycle timer
	//FRAME_TIMER.INTCTRLA = TC_OVFINTLVL_LO_gc;
}

// Start TX/RX cycles
void frame_timer_start(void)
{
#if ENABLE_WD_TICKLE
	WDT_Reset();
#endif
	// start FRAME_TIMER by enabling the prescaler
	FRAME_TIMER.CTRLA = frame_timer_div;
	//FRAME_TIMER.CTRLA = TC_CLKSEL_DIV64_gc; //for testing 10 Hz frame rate
}

// Stop TX/RX cycles
void frame_timer_stop(void)
{
	// stop FRAME_TIMER by disabling the clock
	FRAME_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
	
	// zero the count value
	FRAME_TIMER.CNT = 0x00;
}

// Setup the frequency and duty cycle for the PWM used to charge the VPA rail voltage.
void pwm_init(void)
{
	// set PWM timer period for 500 KHz SS PWM --> (1/F_CPU) * PRESCALER * ((F_CPU / 500000) - 1 = PWM_PERIOD
	PWM_TIMER.PER = PWM_PERIOD;
	
	// zero the count
	PWM_TIMER.CNT = 0x0000;
	
	// set PWM_TIMER for single-slop PWM mode and enable compare channel A
	PWM_TIMER.CTRLB = (TC_WGMODE_SS_gc | TC0_CCAEN_bm);
}

// Start the PWM used to charge the VPA rail voltage. The duty cycle is selected 
// according to the level of the VPA voltage set by the DMS user.
void pwm_start(void)
{
	// If VPA setting is not zero start the PWM and start charging rail, if zero
	// may sure the PWM never turn on
	if(VPA_value != 0)
	{		
		// duty cycle changes with different VPA settings, set PWM pin as output
		// and start PWM_TIMER by enabling the clock prescaler
		PWM_TIMER.CCA = pwm_duty_value;
		PWM_PORT.DIRSET = PWM_OUT;
		PWM_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;
	}
	else  // VPA setting is zero
	{
		pwm_stop();
	}
}

// Stop charging the VPA rail
void pwm_stop(void)
{
	// stop PWM_TIMER by disabling the clock
	PWM_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
	
	// set PWM pin low
	PWM_PORT.DIRCLR = PWM_OUT;
	
	// zero the count value
	PWM_TIMER.CNT = 0x00;
	
}

// Sandeep Modified the rtc init function to get the usage type
// usage indicate if it is being used for Interlock or DMS timing
// both use different clock_div and timer values
// Imp : We may have to adjust the timings for the DMS clock to increase the time out
void rtc_interlock_timer_init(uint16_t timer_value, uint8_t clock_div, uint8_t usage)
{
	interlock_timer_div = clock_div;
	INTERLOCK_TIMER.PER = timer_value;
	
	// zero the count value
	INTERLOCK_TIMER.CNT = 0x00;
	if ( INTERLOCK_USAGE == usage)
	{
	
#if SINGLE_SHOT
		// enable the overflow interrupt with LO priority
		INTERLOCK_TIMER.INTCTRL = RTC_OVFINTLVL_HI_gc;
#endif

	}
	else
	{
		// disable the overflow interrupt with LO priority
		INTERLOCK_TIMER.INTCTRL = RTC_OVFINTLVL_OFF_gc;
	}
}

// Sandeep
// Start the RTC timer after the interlock signal reverts back to the 
// non-active state. Care must be taken when setting the RTC registers
// so a check is needed.
void rtc_interlock_timer_start(void)
{
	do
	{
		// Wait until RTC is not busy.
	} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
	
	// start FRAME_TIMER by enabling the prescaler
	INTERLOCK_TIMER.CTRL =  interlock_timer_div;
}

// Sandeep
// Stop the RTC timer.
void rtc_interlock_timer_stop(void)
{
	do
	{
		// Wait until RTC is not busy.
	} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
	
	// stop CYCLE_TIMER by disabling the clock
	INTERLOCK_TIMER.CTRL = RTC_PRESCALER_OFF_gc;
	
	// zero the count value
	INTERLOCK_TIMER.CNT = 0x00;
}

#if USE_DDS
void DDS_mclk_timer_init(void)
{
	MCLK_TIMER.CCD = 0;
	MCLK_TIMER.CTRLB = (TC_WGMODE_FRQ_gc | TC0_CCDEN_bm);
}

void DDS_mclk_timer_start(void)
{
	MCLK_TIMER.CTRLA = TC_CLKSEL_DIV1_gc;
}

void DDS_mclk_timer_stop(void)
{
	MCLK_TIMER.CTRLA = TC_CLKSEL_OFF_gc;
}
#endif

