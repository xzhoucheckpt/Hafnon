/*******************************************************************
 *
 * File name: interface.h
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
 * $History: interface.h $
 * 
 * *****************  Version 29  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 28  *****************
 * User: Galantij     Date: 6/09/14    Time: 10:16a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a new macro define for the reduced RX PW.
 * 
 * *****************  Version 27  *****************
 * User: Galantij     Date: 3/04/14    Time: 5:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new parameter for setVPA_Level() to indicate the frame rate for
 * the change to 10 Hz PWM charge rate. Added new prototype.
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two new macro defines to indicate the first tag band and the
 * amount of tag bands available.
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 2/27/14    Time: 1:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (In verify mode, 410 tags can be deactivated) . Changed
 * macro define for reduced TX PW
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:24a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80: defining the variable used to track VPA and shut down PWM
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 1/28/14    Time: 8:00p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Set "10 Hz power limt" macro defne to 26 until a new limit is found.
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 1/20/14    Time: 11:31a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Updated the macro define for the 10 Hz limit which was derived from the
 * HW team and is VPA=13
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 1/07/14    Time: 4:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created new macro's for the new 10 Hz frame rate.
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:17a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the macro define for the limited VPA voltage for 10 Hz. As of now
 * the level is set to the max VPA setting until HW provides the limit
 * 
 * *****************  Version 19  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * reduced DMS_TIMEOUT
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 10/24/13   Time: 10:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the two new supporting prototypes for the new method of mode
 * processing.
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed prototype for setAlarm() function for new parameter for looped
 * alarmed.
 * 
 * *****************  Version 16  *****************
 * User: Dubes        Date: 9/23/13    Time: 2:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * changed the prototype setFrameRate(uint16_t frame_rate) 
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * varaible for setting the PWM duty cycle 
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a macro define for the max number of VPA settings
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added structures for the 2nd TX and added changed prototype for
 * createJitter()
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:00p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased DMS timeout
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a tag counter
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:07p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two new macro defines for the changes for the detect/deact modes.
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Place "extern"'s in header file
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added predefines for RTC timer used for service tool feature.
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:11a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * implemented the tag band feature
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the high level VPA rail adj function prototype to allow a
 * return value. Added the two potential returned values
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two new prototypes for the interlock processing for high level
 * code and added a new alarm state for the state of deactivation
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added macro defines
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

#include "globals.h"

#ifndef INTERFACE_H_
#define INTERFACE_H_

//****************************************************************
// Macro Defines
//****************************************************************
// Deactivation Modes
#define DEACT_MODE4					0
#define DEACT_MODE5					1
#define DEACT_MODE6					2
#define DEACT_VERIFY				3

// deactivation/detection mode states
#define DEACT_STATE					0
#define DETECT_STATE				1
#define VERIFY_STATE				2

//TX2 control
#define TX2_ENABLE					1
#define TX2_DISABLE					0

// Tag Bands
#define FIRST_BAND					0
#define NUM_BANDS					9
#define TAGBAND_72					0
#define TAGBAND_82					1
#define TAGBAND_95					2

//Frame Rates	
#define FRAME_144HZ_TICKS			(uint16_t)(((F_CPU * .25) / 144) + 1594)
#define FRAME_10HZ_TICKS			(uint16_t)((F_CPU * (1/64)) / 10)
#define FRAME_40MS_DELAY_TICKS		(uint16_t)((F_CPU * (1/64)) * (1/100) * (40))
#define FRAME_144HZ					0
#define FRAME_10HZ					1
#define FRAME_DELAY_40MS			2
#define LIMIT_VPA_10HZ				8 // HW needs to set the MAX 10 Hz rail voltage

//Interlock Control
#define INTERLOCK_USAGE			0
#define DMS_RTC_USAGE			1	
#define DMS_PERIOD				65535  // with current setting this is 2 seconds if 16384 = 500ms , Change If needed
#define DMS_TIMEOUT				5000    //50000  // for comparing with current setting this is 2 seconds if 16384 = 500ms , Change from 30000 to 50000 If needed
#define DMS_RESET_TIMEOUT		250	

#define INTERLOCK_500MS				16384
#define INTERLOCK_5SECS				30000  //need to verify timing
#define INTERLOCK_ENABLE			1
#define INTERLOCK_DISABLE			0
#define INTERLOCK_RS232				0
#define INTERLOCK_HARDWIRE			1
#define INTERLOCK_SHORT_TIME		0
#define INTERLOCK_LONG_TIME			1

// Timing settings for different mode and modes of operation.
#define DETECT_HI_PWM_PER			13000	// charge up period and TX/RX cycle delay
#define MODE4_DET_TX_PW_10HZ		4
#define MODE4_DEACT_TX_PW_10HZ		7
#define MODE4_DET_TX_PW				60
#define VERIFY_TX_PW				2 //4
#define MODE4_DEACT_TX_PW			240
#define DEACT_TX_PW					151		// 6us TX PW for deactivation
#define DEACT_TX_PW_10HZ			5
#define COMMON_RX_PW				700		// RX switch closed for 40 us
#define COMMON_RX_PW_10HZ			40
#define DETECT_HOLDOFF_PER			1		// 300 ns holdoff for verify and mode 4
#define MODE4_DET_HOLDOFF_PER		2
#define DEACT_HOLDOFF_PER			10		// 4us holdoff for deactivation
#define COMMON_ISR_ENABLE			200		// RX ISR enabled 12 us after RX switch is closed
#define VERIFY_COMMON_ISR_ENABLE	40
#define COMMON_RX_PW_IMMUNITY		70

// VPA return status
#define VPA_ADJ_SUCCESS				1
#define VPA_ADJ_FAILED				0
#define MAX_VPA_SETTING				27

// initial setting during power up cycle for a given mode
typedef struct
{
	unsigned short tx_delay;			// charge time of the VPA for both channels (us)
	unsigned short tx_pw;				// transmit gate time (us)
	unsigned short rx_pw;				// receiver enable time
	unsigned short rx_holdoff_time;		// 2nd loop holdoff delay
	unsigned short rx_isr_delay_time;	// isr delay period
	unsigned short vpa_volt_level;		// vpa rail voltage
	unsigned short tx2_pw;				// 2nd loop transmit gate time (us)
	unsigned short rx2_pw;				// 2nd loop receiver enable time
	unsigned short rx2_holdoff_time;	// 2nd loop holdoff delay
	unsigned short rx2_isr_delay_time;	// 2nd isr delay period
	unsigned short vpa2_volt_level;		// 2nd loop vpa rail voltage
	
	unsigned short jitter;
	
} ModeStructType;

//extern volatile uint8_t TX2_enable_flag;
extern ModeStructType ModeParaStruct;
extern volatile uint8_t intertag_counter;
extern uint16_t pwm_duty_value;
extern uint8_t VPA_value;


//////////////////////////////////////////////////////////////////////// 
// Global Function Protocols
////////////////////////////////////////////////////////////////////////

// Functions call at start up
void setDeactMode(uint8_t mode, uint8_t TX2_enable);
uint8_t setTagBand(uint8_t tag_band);
void setFrameRate(uint16_t frame_rate);
void configInterlock(uint16_t duration, uint16_t short_long_time,
						uint8_t source, uint8_t enable);

// Functions called during normal operation
void setTXGate(uint16_t TX_gate_ticks);
void setHoldOff(uint16_t holdoff_ticks);
void setRXGate(uint16_t RX_gate_ticks);
void setRX_ISR(uint16_t rx_isr_ticks);
void createJitter(uint8_t disable_jitter);
uint8_t setVPA_Level(uint16_t VPA_volt_level, uint16_t frame_rate);

#if MODE_PROCESS
void setAlarms(uint8_t deact_mode, uint8_t deact_state, uint8_t loop);
#else
void setMode4_HiPower(void);
void setMode4_LoPower(void);
#endif

void processInterlock(void);
void closeInterlock(void);



#endif /* INTERFACE_H_ */