/*******************************************************************
 *
 * File name: timers.h
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
 * $History: timers.h $
 * 
 * *****************  Version 14  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 2/26/14    Time: 11:47a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This fixes Defect#60 (seem to get more false alarms when second
 * transmitter is active near E3). Put new frame counters for each loop in
 * header file.
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a "extern" var to track when the deact mode is changes from
 * verify mode to mode 6 for the deactivation GPI feature
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 10/24/13   Time: 10:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the new variables for the new method of mode processing
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "extern" for both primary and secondary ant flags to allow
 * hafnon.c to have visiblity.
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a macro define for both 25% and 33% PWM duty cycle
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added flag to track the state of the frame cycle when the interlock is
 * enabled
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed an unused varaible
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:19p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * "extern"'s in header file
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed prototype for the RTC int function to support the timeout for
 * the DMS tool.
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Sandeep added the header file supporting freq counting
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * New Interlock timer protypes and counter value
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

#include "globals.h"

#ifndef __TIMERS_H__
#define __TIMERS_H__

#if USE_FREQ_COUNT
#include "freq_cntr.h"
#endif

/*
 * PWM frequency needs to be 500 KHz and a 75% duty cycle.  Be careful as there
 * is no sanity checking on these defines. 
 * (i.e F_CPU values that cannot produce positive non-zero PERIOD and CCA values.
*/
// JRG What does the comment above mean??
//#define PWM_PERIOD				(F_CPU / 500000) - 1;
//#define PWM_COMPARE_VALUE		((F_CPU / 500000) / 4) * 3  // 75% duty cycle.
// This changes the duty cycle to 25%. With this change and by 
#if 1
// 130KHz @ 25% duty cycle
#define PWM_PERIOD				(F_CPU / 130000) + 6
//#define PWM_COMPARE_VALUE		((F_CPU / 130000) / 4) + 2 // used for 8-26
#endif

#define PWM_COMPARE_VALUE		((F_CPU / 130000) / 3) + 2  // used this for VPA under 8 (33%)
//#define PWM_COMPARE_VALUE		((F_CPU / 130000) / 2) + 2  // 50% duty  //original HW/FW integration
//#define PWM_COMPARE_VALUE		((F_CPU / 130000) / 4) * 3  // 75% duty

// 260KHz @ 50%
//#define PWM_PERIOD				(F_CPU / 260000) + 6
//#define PWM_COMPARE_VALUE		((F_CPU / 260000) / 2) + 2  // 50% duty
//#define PWM_COMPARE_VALUE		((F_CPU / 260000) / 4) * 3  // 75% duty
//#define PWM_COMPARE_VALUE		((F_CPU / 260000) / 4) + 2  // 25% duty

// 520KHz @ 50%
//#define PWM_PERIOD				(F_CPU / 520000)
//#define PWM_COMPARE_VALUE		((F_CPU / 260000) / 2) + 2  // 50% duty
//#define PWM_COMPARE_VALUE		((F_CPU / 260000) / 4) * 3  // 75% duty
//#define PWM_COMPARE_VALUE		((F_CPU / 520000) / 4)  // 25% duty


// compare channel periods for cycle timer
#define CYCLE_TIMER_RX_RAIL		9600  //CCA
#define CYCLE_TIMER_TX			9760  //CCB  9725
#define CYCLE_TIMER_HOLDOFF		9850  //CCC  9800
#define CYCLE_TIMER_COMPLETE	10050  //overflow

// Sandeep RTC timer
#define INTRLOCK_TIMER_PER		16384 //1600

// JRG div by 4 (43260)
#define FRAME_TIMER_PER			43260 //6000 //1ms for test //43260 original 7ms
// NEW2
#define NON_DEACT_TIMER_PER		220

#define F_CPU_MHZ				(F_CPU/1000000)

#define DELAY_BETWEEN_PULSE		35000  // aprox 40 msecond

extern volatile uint8_t frame_counter;
extern volatile uint32_t frame_counter_flag;
extern volatile uint32_t pri_frame_counter_flag;
extern volatile uint32_t sec_frame_counter_flag;
extern volatile uint8_t TxRx_cycle_enable;
extern volatile uint8_t GPI_mode_change;

extern volatile uint8_t primary_ant_flag;
extern volatile uint8_t secondary_ant_flag;

#if MODE_PROCESS

#else
extern volatile uint8_t inhibit_flag;
extern volatile uint16_t alarm_count_down;
#endif

void frame_timer_init(uint16_t timer_value, uint8_t clock_div);
void frame_timer_start(void);
void frame_timer_stop(void);

void pwm_init(void);
void pwm_start(void);
void pwm_stop(void);

//Sandeep: Modified the rtc init function to get the usage type
// usage indicate if it is being used for Interlock or DMS timing
// both use different clock_div and timer values
// Imp : We may have to adjust the timings for the DMS clock to increase the time out
void rtc_interlock_timer_init(uint16_t timer_value, uint8_t clock_div,  uint8_t usage);
void rtc_interlock_timer_start(void);
void rtc_interlock_timer_stop(void);

#if USE_DDS
void DDS_mclk_timer_init(void);
void DDS_mclk_timer_start(void);
void DDS_mclk_timer_stop(void);
#endif

#endif