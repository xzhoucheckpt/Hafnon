/*******************************************************************
 *
 * File name: interface.c
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
 * $History: interface.c $
 * 
 * *****************  Version 46  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 45  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 44  *****************
 * User: Galantij     Date: 6/09/14    Time: 10:15a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Decreased the RX PW from 40 uS to 12.5 uS for immunity  issues with a
 * scanner. This was done for all deactivation modes and verification
 * mode. This also covers the 2nd TX functionality.
 * 
 * *****************  Version 43  *****************
 * User: Galantij     Date: 3/04/14    Time: 5:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new parameter for setVPA_Level() to indicate the frame rate for
 * the change to 10 Hz PWM charge rate. The new function only allows the
 * 3.3 volt Vcc to charge up the 10 Hz rail. Only 33% duty cycle is used
 * for 10 Hz.
 * 
 * *****************  Version 42  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:13p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased the range of the tag bands from 8 to 9 to make room for the
 * new SRRC tag band. This is the last band in DMS.
 * 
 * *****************  Version 41  *****************
 * User: Galantij     Date: 2/27/14    Time: 1:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (In verify mode, 410 tags can be deactivated) Changed TX PW
 * from 166ns to 80ns
 * 
 * *****************  Version 40  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:22a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (Verify mode deactivates tags). Created a variable to hold
 * the VPA setting to indicate when set to zero which shuts down the PWM
 * 
 * *****************  Version 39  *****************
 * User: Galantij     Date: 2/18/14    Time: 11:34a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed jitter function to increase the jitter for 10 Hz from 400us to
 * 2ms. This was because of immunity issues found when testing Thorite
 * units close together.
 * 
 * *****************  Version 38  *****************
 * User: Galantij     Date: 2/05/14    Time: 4:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Needed to reduce the TX PW for the 2nd loop for mode 6. It was 8.5us
 * needed to reduce to 6us
 * 
 * *****************  Version 37  *****************
 * User: Galantij     Date: 1/28/14    Time: 7:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Enable the VCO, shunt VPA rail and then disable VCO. This is only need
 * for mode 4.
 * 
 * *****************  Version 36  *****************
 * User: Galantij     Date: 1/16/14    Time: 3:39p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Only allow freq locking during Mode 4 detection, for deactivation
 * unlock. This fixes an issue where we had loss of detection/deactvation
 * for the 144 Hz Mode 4. This change is for all Mode 4 selection (both
 * FCC and CE).
 * 
 * *****************  Version 35  *****************
 * User: Galantij     Date: 1/07/14    Time: 4:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put all hardcoded values into macro's which are used for the TX/RX
 * cycle. Some of the values needed to be changed because of the new
 * method of doing 10 Hz frame rate.
 * 
 * *****************  Version 34  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the test point for this file. It is now being used for the
 * overvoltage monitor feature.
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed defect #26 (interlock 10 sec selection was only 1 sec). We now
 * have a 10 sec interlock timer
 * 
 * *****************  Version 32  *****************
 * User: Galantij     Date: 11/04/13   Time: 5:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed algorithms for new HW
 * 
 * *****************  Version 31  *****************
 * User: Galantij     Date: 10/25/13   Time: 4:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support Mode 5
 * 
 * *****************  Version 30  *****************
 * User: Galantij     Date: 10/24/13   Time: 10:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Marco define the latest mode operation code into the older method.
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Made changes to support the new mode 4 which now reaches the max rail
 * VPA. Also created macro defines to enable/disable the rail discharge
 * code. For this release this is disabled
 * 
 * *****************  Version 28  *****************
 * User: Galantij     Date: 10/08/13   Time: 4:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased the mode 4 high power mode TX PW from 6us to 10 us.
 * 
 * *****************  Version 27  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the setalarm() function to support the discrimunation between
 * the 1st and 2nd TX
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 9/30/13    Time: 3:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added logic to support the reduce alarm LED/sounder/IO
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 9/25/13    Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Implemented 10 Hz code
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 9/25/13    Time: 11:13a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code for 10 Hz support
 * 
 * *****************  Version 23  *****************
 * User: Dubes        Date: 9/23/13    Time: 2:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * changed the prototype setFrameRate(uint16_t frame_rate) 
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed "setVPA_Level()" funtion to change the duty cycle for the PWM
 * from 50% to 33% from a vpa setting of 0-7 and 25% for the range of 8-26
 * to reduce current draw.
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 9/05/13    Time: 12:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Allow the transmit frequency to unlock during deactivation  for mode 4.
 * It's already implemented for mode 6
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added hooks for the DMS config for both holdoff and VPA level and
 * increase the range in setVPA_Level() from 0-19 to 0-26.
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 8/28/13    Time: 6:45p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added freq lock flag for mode 6 and added DB to some of the hardcoded
 * values
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * setTagBand , Frequency Counter logic added for that band
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added second TX, interlock and alarm code
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Made some changes to the VPA level of the verify mode to protect the
 * tag from being deactivated and also coded the consecutive tag feature
 * to stop false alarms 
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the timer value for both verify and mode 4. This was done to
 * allow the new receiver's sensitivity to be used. An inhibit was created
 * for Mode 4 to allow the system to settle after a high TX PW and VPA
 * voltage needed for deactivation.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to provide the functionality for the detect/deact modes.
 * This is only temp until the new receiver is completed.
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added new include files
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the config check for Hi/LO power setting. This can not be
 * implemented until complianve testing is completed
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the VPA rail setting for Mode 6 from 19 (MAX) to 7 until HW is
 * fixed for overcurrent issues. Added dip switch settings in place of
 * hardcodes
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a parameter for the "configInterlock" function to support the
 * timer for the DMS timeout.
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:40a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the high level state mchine called for Stanleys development
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:47p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Missed a return for the tag band function
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:11a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * implemented the tag band feature
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the header files need for VAP rail adj feature and created the
 * high level function to map a DMS index for a VPA voltage to an actual
 * VPA voltage
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two new functions to allow tracking of the interlock for high
 * level code
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added macro defines and comments for hooks into low level timing
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:44p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
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

#include "interface.h"
#include "analog.h"
#include "freq_tables.h"
#include "freq_cntr.h"
#include "zircon_config.h"
#include "alarm.h"
#include "GTimer.h"

ModeStructType ModeParaStruct = {0};
volatile uint8_t gAppState;
volatile uint8_t intertag_counter = 0;
uint16_t pwm_duty_value = ((F_CPU / 130000) / 3) + 2;  // duty cycle 33%
uint8_t VPA_value = 0;
extern uint8_t flag_ready_to_send_deact_event;

#if MODE_PROCESS
static uint8_t mode4_timer_handler = 0xff;
static uint8_t mode4_lockout_handler = 0xff;
static uint8_t mode6_lockout_handler = 0xff;
static uint8_t mode4_lockout = 0; 

static void setDetectionMode4(void);
static void setLockoutMode4(void);
static void setLockoutMode6(void);
#endif

// Global Function
void setDeactMode(uint8_t mode, uint8_t TX2_enable)
{
	if(CPiD_HW_flag == LITE_HW)  /* Thoralite */
	{
		TX2_enable = 0;
	}
	switch (mode)
	{
		case DEACT_MODE4:
			if(!TX2_enable)
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = MODE4_DET_TX_PW;
					ModeParaStruct.rx_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
				}
				else // 10 Hz
				{
					ModeParaStruct.tx_pw = MODE4_DET_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;
			}
			else if(CPiD_HW_flag)  // 2nd TX enabled  Thoralite
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = MODE4_DET_TX_PW;
					ModeParaStruct.rx_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
					ModeParaStruct.tx2_pw = MODE4_DET_TX_PW;//50;
					ModeParaStruct.rx2_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
				}
				else // 10 Hz
				{
					ModeParaStruct.tx_pw = MODE4_DET_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
					ModeParaStruct.tx2_pw = MODE4_DET_TX_PW_10HZ;
					ModeParaStruct.rx2_pw = COMMON_RX_PW_10HZ;					
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;
				
				ModeParaStruct.rx2_holdoff_time = config_parameters.config_sec_hold_off;
			}
					
			setVPA_Level(config_parameters.config_detect_level, 
			             config_parameters.deact_frame_rate);
			
		break;
		
		case DEACT_VERIFY:
			if(!TX2_enable)
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = VERIFY_TX_PW;
					ModeParaStruct.rx_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
					setVPA_Level(config_parameters.config_detect_level, 
					             config_parameters.deact_frame_rate);
				}
				else  // this is disabled for 10 Hz frame rate
				{
					ModeParaStruct.tx_pw = VERIFY_TX_PW;
					ModeParaStruct.rx_pw = COMMON_RX_PW;
					setVPA_Level(config_parameters.config_detect_level, 
					             config_parameters.deact_frame_rate);
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
				ModeParaStruct.rx_isr_delay_time = VERIFY_COMMON_ISR_ENABLE;
			}
			
		break;
		
		case DEACT_MODE5:
		
			if(!TX2_enable)
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW; // 6us TX gate (deactivation)
					ModeParaStruct.rx_pw = COMMON_RX_PW;
				}
				else  // 10 Hz frame rate
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
				}
				
				ModeParaStruct.rx_holdoff_time = 12;
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;
				
				setVPA_Level(config_parameters.tx_power, 
				             config_parameters.deact_frame_rate);
			}
			else if(CPiD_HW_flag)  // 2nd TX enabled  Thoralite
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW;
					ModeParaStruct.rx_pw = COMMON_RX_PW;
					ModeParaStruct.tx2_pw = DEACT_TX_PW;
					ModeParaStruct.rx2_pw = COMMON_RX_PW;
				}
				else  // 10 Hz frame rate
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
					ModeParaStruct.tx2_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx2_pw = COMMON_RX_PW_10HZ;
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;;
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;
				
				ModeParaStruct.rx2_holdoff_time = config_parameters.config_sec_hold_off;
				
				setVPA_Level(config_parameters.tx_power, 
				             config_parameters.deact_frame_rate);
			}
		break;
			
		case DEACT_MODE6:

			if(!TX2_enable)
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW; // 6us TX gate (deactivation)
					ModeParaStruct.rx_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
				}
				else  // 10 Hz frame rate
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off; 
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;		
			
				setVPA_Level(config_parameters.tx_power, 
				             config_parameters.deact_frame_rate);
			}
			else if(CPiD_HW_flag)  // 2nd TX enabled  Thoralite
			{
				ModeParaStruct.tx_delay = DETECT_HI_PWM_PER;
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW;//151;
					ModeParaStruct.rx_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
					ModeParaStruct.tx2_pw = 70; //DEACT_TX_PW; //151
					ModeParaStruct.rx2_pw = COMMON_RX_PW_IMMUNITY; //COMMON_RX_PW;
				}
				else  // 10 Hz frame rate
				{
					ModeParaStruct.tx_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx_pw = COMMON_RX_PW_10HZ;
					ModeParaStruct.tx2_pw = DEACT_TX_PW_10HZ;
					ModeParaStruct.rx2_pw = COMMON_RX_PW_10HZ;
				}
				
				ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
				ModeParaStruct.rx_isr_delay_time = COMMON_ISR_ENABLE;
				
				ModeParaStruct.rx2_holdoff_time = config_parameters.config_sec_hold_off;
			
				setVPA_Level(config_parameters.tx_power, 
				             config_parameters.deact_frame_rate);
			}
		break;
		
		default:
		break;
	}
} // end deact_mode function


uint8_t setTagBand(uint8_t tag_band)
{
	uint8_t return_status;
	
	// Only 8 tags band (0-7) can be selected by DMS and a 9th for 
	// SRRC compliance
	if((tag_band >= FIRST_BAND) && (tag_band < NUM_BANDS))
	{
		gFrequencyTable = FreqTablePtr[tag_band];
		// Sandeep Frequency Counting
		gFrequencyCount = FrequencyCounPtr[tag_band];
		return_status = 1;
	}
	else  // error in tag band selection, use default band
	{
		// load the default freq range if out of range 
		// tag band is received
		gFrequencyTable = FreqTable76_87;
		// Sandeep Frequency Counting
		gFrequencyCount = FreqCount76_87;		
		return_status = 0;
	}
	
	return(return_status);
}


void setFrameRate(uint16_t frame_rate)
{
	
	// frame rate is selected by the DMS
	if(frame_rate == FRAME_144HZ)
	{
		frame_timer_init(FRAME_144HZ_TICKS, TC_CLKSEL_DIV4_gc);
		config_parameters.deact_frame_rate = FRAME_144HZ;
	}
	else if ( FRAME_10HZ == frame_rate) // 10Hz frame rate
	{
		// here temp until 10Hz is coded
		frame_timer_init(37500, TC_CLKSEL_DIV64_gc);
		config_parameters.deact_frame_rate = FRAME_10HZ;
		//frame_timer_init(37500, TC_CLKSEL_DIV64_gc);
	} else
	{  // This is to cause a delay of 40 ms every 5th pulse
		// FRAME_40MS_DELAY_TICKS 15000 corresponds to 47.3 , 7.3 corresponds to 2315 
		// so the count should be 12685 corresponds to 41.07
		//frame_timer_init(15000, TC_CLKSEL_DIV64_gc);
		frame_timer_init(12376, TC_CLKSEL_DIV64_gc);
		config_parameters.deact_frame_rate = FRAME_144HZ;
	}
		/*
		// frame rate is selected by the DMS
		if(frame_rate == FRAME_144HZ)
		{
			frame_timer_init(FRAME_144HZ_TICKS, TC_CLKSEL_DIV4_gc);
			config_parameters.deact_frame_rate = FRAME_144HZ;
		}
		else // 10Hz frame rate
		{
			// here temp until 10Hz is coded
			frame_timer_init(37500, TC_CLKSEL_DIV64_gc);
			config_parameters.deact_frame_rate = FRAME_10HZ;
			//frame_timer_init(37500, TC_CLKSEL_DIV64_gc);
		}
		*/
}


void configInterlock(uint16_t duration, uint16_t short_long_time,
						uint8_t source, uint8_t enable)
{
	uint16_t duration_step;

	if(CPiD_HW_flag)
	{
		if (short_long_time)
		{
			//As the duration from 0-19, for high time range(30s to 10mins), every step is 30 sec
			// 10mins/20= 30 sec
			// enable the 32 KHz output of the 32KHz RC (as opposed to the 1.024 KHz output)
			//30.5 us *prescaler 1024 = 0.03125 s per tick
			// 30s = 960 ticks
			duration_step=960;
			rtc_interlock_timer_init((duration+2)* duration_step, RTC_PRESCALER_DIV1024_gc, INTERLOCK_USAGE);
		}
		else
		{
			//As the duration from 0-19, for low time range(500ms to 10sec), every step is 500ms
			// 10 secs/20= 500 ms
			// enable the 32 KHz output of the 32KHz RC (as opposed to the 1.024 KHz output)
			//30.5 us *prescaler 64 = 1952 us per tick
			// 500 ms /1952 us = 256
			//256 ticks per 500ms
			duration_step=256;
			rtc_interlock_timer_init((duration+1)*duration_step, RTC_PRESCALER_DIV64_gc, INTERLOCK_USAGE);
		}
	}
}

void setTXGate(uint16_t TX_gate_ticks)
{
	//ModeParaStruct.tx_pw = TX_gate_ticks;
}

void setHoldOff(uint16_t holdoff_ticks)
{
	//ModeParaStruct.rx_holdoff_time = holdoff_ticks;
}

void setRXGate(uint16_t RX_gate_ticks)
{
	//ModeParaStruct.rx_pw = RX_gate_ticks;
}

void setRX_ISR(uint16_t rx_isr_ticks)
{
	//ModeParaStruct.rx_isr_delay_time = rx_isr_ticks;
}

void createJitter(uint8_t disable_jitter)
{
	uint16_t  myrand;
	
	// auto tuning can not have jitter active during session
	if(disable_jitter)
	{
		ModeParaStruct.jitter = 0;
	}
	else
	{	
		if(config_parameters.deact_frame_rate == FRAME_144HZ)
		{
			// Josh, do some random number calculation and set jitter variable
			// this frame jitter range is 100-400 us.
			// the jitter is used in rx_rail_chargeup()'s cycle timer.
			// in cycle timer:  100 us  = 300 ticks , 
			// range =100-400 us = 300 - 1200 ticks
			// srand(300);      
			myrand=0;
			myrand=rand()%900; 	
			myrand+=300;
			ModeParaStruct.jitter = myrand;
		}
		else  // 10 Hz frame rate
		{
			myrand=0;
			myrand=rand()%12000; //12000;
			myrand+=300;
			ModeParaStruct.jitter = myrand;
		}
	}
}

uint8_t setVPA_Level(uint16_t VPA_volt_level, uint16_t frame_rate)
{
	uint8_t return_status;

	if((VPA_volt_level >= 0) && (VPA_volt_level < MAX_VPA_SETTING))
	{
		if(frame_rate == FRAME_144HZ)
		{
			// if the range is 0-7, the VPA Vcc is set for 3.3 volts and the 
			// PWM freq@duty cycle is 130KHz@33%. If the VPA range is 8-26, 
			// VPA Vcc is set to 12 volts and PWM freq@duty is 130KHz@25%
			// This is important to maintain a Vcc current draw during VPA rail 
			// charge up under 500ma and still have a reasonable changeup time.
			if(VPA_volt_level > 7)
			{
				// Clear deact pin to allow a 12v Vcc on VPA rail and
				// PWM duty cycle is set to 25% to reduce supply current draw
				DEACT_NOT_PORT.OUTCLR = DEACT_NOT_PIN;
				pwm_duty_value = ((F_CPU / 130000) / 4) + 2;
			}
			else
			{
				// Set deact pin to allow a 3.3v Vcc on VPA rail and
				// PWM duty cycle is set to 33% to reduce supply current draw
				DEACT_NOT_PORT.OUTSET = DEACT_NOT_PIN;
				pwm_duty_value = ((F_CPU / 130000) / 3) + 2;
			}
		}
		else // 10 Hz frame rate
		{
			// PWM duty cycle is set to 33% to reduce supply current draw
			// and the charging voltage is 3.3 V for all 10 Hz settings
			// For 10 Hz we have about 95 mS to charge the rail.
			// Charge it slow to reduce the Vcc draw.
			DEACT_NOT_PORT.OUTSET = DEACT_NOT_PIN;
			pwm_duty_value = ((F_CPU / 130000) / 3) + 2;
		}
		
		VPA_value = VPA_volt_level;
		
		dac_VPA_adj(gVPA_Adj_CE[VPA_volt_level]);
		
		return_status = VPA_ADJ_SUCCESS;
	}
	else
	{
		return_status = VPA_ADJ_FAILED;
	}
	
	return(return_status);
}

#if MODE_PROCESS
void setAlarms(uint8_t deact_mode, uint8_t deact_state, uint8_t loop)
{
	switch(deact_mode)
	{
		case DEACT_MODE4:
			
			if(!mode4_lockout)
			{	
				startAlarm(loop);
				
				enable_freq_lock = 0;
				
				if(config_parameters.deact_frame_rate == FRAME_144HZ)
				{
#if 1  // taken out for better performance for mode 4 (144Hz) 2nd TX enabled.
					if(config_parameters.enable_tx_2)
					{
						enable_freq_lock = 0;	
					}
#endif					
					ModeParaStruct.rx_holdoff_time = DEACT_HOLDOFF_PER+5;
					ModeParaStruct.tx_pw = MODE4_DEACT_TX_PW;
				}
				else
				{
					ModeParaStruct.rx_holdoff_time = DEACT_HOLDOFF_PER+2;
					ModeParaStruct.tx_pw = MODE4_DEACT_TX_PW_10HZ;
				}
								
				setVPA_Level(config_parameters.tx_power, 
				            config_parameters.deact_frame_rate);
							 
			
				
				if(mode4_timer_handler == 0xff)
				{
					// callback function to return back to detection state
					mode4_timer_handler = GTimer_RegisterCB(&setDetectionMode4);
				}
				
				if(mode4_timer_handler < G_TIMER_MAX_SLOT)
				{
					if(config_parameters.deact_frame_rate == FRAME_144HZ)
					{
						if(!(config_parameters.enable_tx_2))
						{
						GTimer_Refresh(mode4_timer_handler, G_TIMER_200mS);
						//GTimer_Refresh(mode4_timer_handler, G_TIMER_500mS);
						}
						else
						{
						GTimer_Refresh(mode4_timer_handler, G_TIMER_500mS);
						//GTimer_Refresh(mode4_timer_handler, G_TIMER_1S);
						}
					}
					else
					{
						if(!(config_parameters.enable_tx_2))
						{
							GTimer_Refresh(mode4_timer_handler, G_TIMER_200mS);
						}
						else
						{
							GTimer_Refresh(mode4_timer_handler, G_TIMER_500mS);
						}
					}
				}
			}
			break;
			
		case DEACT_VERIFY:
			startAlarm(loop);	
			break;	
			
		case DEACT_MODE5:
			//startAlarm();	// no tag response in mode 5 means no sounder/Led alarm 
			break;
	
		case DEACT_MODE6:
			startAlarm(loop);
			
			// disable the frequency locking for a more effective deactivation.
			// return back to frequency locking after the LED alarm is over
			enable_freq_lock = 0;

			// set a timer to allow 500 ms of deactivation time before setting
			// back to detection state
			if(mode6_lockout_handler == 0xff)
			{
				// callback function to return back to detection state
				mode6_lockout_handler = GTimer_RegisterCB(&setLockoutMode6);
			}
			if(mode6_lockout_handler < G_TIMER_MAX_SLOT)
			{
				GTimer_Refresh(mode6_lockout_handler, G_TIMER_500mS);  // 500 ms
			}
				
			break;
	}

}
#endif

void processInterlock(void)
{
	interlockLEDOff();
}

void closeInterlock(void)
{
	interlockLEDOn();
	if (DEACT_MODE4 ==config_parameters.mode_ind )  //change for sending deactivation message
	{
		setDeactMode(DEACT_VERIFY, config_parameters.enable_tx_2);
	}
	else
	{
		setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
	}
	//setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
}

#if MODE_PROCESS
// detection state callback function 
static void setDetectionMode4(void)
{
	setDeactMode(DEACT_VERIFY,0);
	//
//#if RAIL_DISCHARGE
	uint8_t vpa_result = 0;
//#endif
	
	// return system back to detection TX PW, holdoff delay and VPA rail 
	// voltage
	mode4_lockout = 1;
	
//#if 0
	//TEST_PORT.OUTSET = TEST_PIN;
//#endif

	//setVPA_Level(config_parameters.config_detect_level, 
	             //config_parameters.deact_frame_rate);
	//
	//if(config_parameters.deact_frame_rate == FRAME_144HZ)
	//{
		//ModeParaStruct.tx_pw = MODE4_DET_TX_PW;
	//}
	//else
	//{
		//ModeParaStruct.tx_pw = MODE4_DET_TX_PW_10HZ;
		//ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
	//}
	
	intertag_counter = 0;
	GTimer_unRegisterCB(mode4_timer_handler);
	mode4_timer_handler = 0xff;
	
	dac_write_data(2);
	
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
//		setVPA_Level(config_parameters.config_detect_level, 
//                   config_parameters.deact_frame_rate);
	}
	
	vpa_result = PORTA.IN;
	if((vpa_result & (VPA_MAX_PIN)) == 0)
	{
#if 0
		TEST_PORT.OUTSET = TEST_PIN;
#endif
		pwm_stop();
		TX_ENABLE_N_PORT.OUTSET = TX_ENABLE_N_PIN; /* Thoralite */
		while((vpa_result & (VPA_MAX_PIN)) == 0)
		{
			vpa_result = PORTA.IN;
		}
		TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN; /* Thoralite */
#if 0
		TEST_PORT.OUTCLR = TEST_PIN;
#endif
		//gDACIndexLoaded = 0;
	}
	// end of discharge code ///////////////////////////////
#endif

	dac_write_data(0);

	// set detect/deact cycle lock out for one sec because of potential 
	// oscillation and unlock using call back function. 
	//mode4_lockout = 1;
	
	if(mode4_lockout_handler == 0xff)
	{
		mode4_lockout_handler = GTimer_RegisterCB(&setLockoutMode4);
		flag_ready_to_send_deact_event = true;
	}
	if(mode4_lockout_handler < G_TIMER_MAX_SLOT)
	{
		GTimer_Refresh(mode4_lockout_handler, G_TIMER_100mS);
	}
	
}

static void setLockoutMode4(void)
{
	// unlock detect/deact inhibit
	ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
	//mode4_lockout = 0;
	GTimer_unRegisterCB(mode4_lockout_handler);
	mode4_lockout_handler = 0xff;
	mode4_lockout = 0;
	if (flag_ready_to_send_deact_event)
	{
		GTimer_Refresh(send_ping_handler, G_TIMER_2S);
		FormatAndSendSpecficCMD(ZIRCON_CONFIG_DEACT_EVENT);
	}
	
#if 0
	TEST_PORT.OUTCLR = TEST_PIN;
#endif

}

static void setLockoutMode6(void)
{
	enable_freq_lock = 1;
	GTimer_unRegisterCB(mode6_lockout_handler);
	mode6_lockout_handler = 0xff;
}

#else

void setMode4_HiPower(void)
{
	if(config_parameters.deact_frame_rate == FRAME_144HZ)
	{
		// set TX PW, holdoff and VPA rail to deactivation state
		ModeParaStruct.rx_holdoff_time = DEACT_HOLDOFF_PER+4;
		ModeParaStruct.tx_pw = MODE4_DEACT_TX_PW;
	}
	else
	{
		ModeParaStruct.rx_holdoff_time = DEACT_HOLDOFF_PER;
		ModeParaStruct.tx_pw = MODE4_DEACT_TX_PW_10HZ;
	}
	
	setVPA_Level(config_parameters.tx_power, 
	             config_parameters.deact_frame_rate);
}

void setMode4_LoPower(void)
{
	uint8_t vpa_result = 0;
	
	setVPA_Level(config_parameters.config_detect_level, 
	             config_parameters.deact_frame_rate);

	// discharge code
	// There could be a condition when the interlock signals are coming in
	// at a fast pace where the VPA rail is charged higher than the
	// threshold voltage. In these cases TX/RX frame may not start.
	// To fixed this issue discharge the rail a little bit lower than
	// the deactivation normal VPA rail.
	setVPA_Level(((config_parameters.config_detect_level)-1), 
	               config_parameters.deact_frame_rate);
	
	vpa_result = PORTA.IN;
	if((vpa_result & (VPA_MAX_PIN)) == 0)
	{
#if 0
		TEST_PORT.OUTSET = TEST_PIN;
#endif
		pwm_stop();
		TX_ENABLE_N_PORT.OUTSET = TX_ENABLE_N_PIN; /* Thoralite */
		while((vpa_result & (VPA_MAX_PIN)) == 0)
		{
			vpa_result = PORTA.IN;
		}
		TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN; /* Thoralite */
#if 0
		TEST_PORT.OUTCLR = TEST_PIN;
#endif
		//gDACIndexLoaded = 0;
	}
	// end of discharge code ///////////////////////////////
	
	if(config_parameters.deact_frame_rate == FRAME_144HZ)
	{
		ModeParaStruct.tx_pw = MODE4_DET_TX_PW;
		ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
	}
	else
	{
		ModeParaStruct.tx_pw = MODE4_DET_TX_PW_10HZ;
		ModeParaStruct.rx_holdoff_time = config_parameters.config_pri_hold_off;
	}
	
	setVPA_Level(config_parameters.config_detect_level, 
	             config_parameters.deact_frame_rate);
	
}
#endif
