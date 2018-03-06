/*******************************************************************
 *
 * File name: GTimer.h
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
 * Creator: Stanley Ren
 *
 * Date Created:
 *
 * $History: GTimer.h $
 * 
 * *****************  Version 13  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 3/17/15    Time: 10:11a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a macro define for the two second timer and increased the number
 * of timers to 14
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * New macro define for the one hour timer value
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:27a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the new macro define for the new 5 second timer for the new
 * default config indication.
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new timer value macro defines for overvoltage feature
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two function prototypes to stop and start the timer for alarming
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 10/08/13   Time: 4:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the 200 ms timer macro define
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 9/30/13    Time: 3:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new macro defines for new timer values for alarming
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:09p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added macro define for the 2 min timer
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the macro define for the 10 hour timer
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new macro define for new timer value
 * 
 *****************************************************************/

#ifndef _GTIMER_H
#define _GTIMER_H


#include "globals.h"

typedef void (*GTimerCB)(void );

#define G_TIMER_1S			0	
#define G_TIMER_500mS		1
#define G_TIMER_100mS		2
#define G_TIMER_1500mS		3
#define G_TIMER_10H			4
#define G_TIMER_2M			5
#define G_TIMER_1M			6
#define G_TIMER_600mS		7
#define G_TIMER_200mS		8
#define G_TIMER_30M			9
#define G_TIMER_30S			10
#define G_TIMER_5S			11
#define G_TIMER_1H			12
#if EVOLVESTORE
#define G_TIMER_15S			13
#define G_TIMER_2S			14
#endif
#define G_TIMER_15M			15

#if EVOLVESTORE
#define G_TIMER_MAX_SLOT	16
#else
#define G_TIMER_MAX_SLOT	11
#endif

extern	void GTimer_Initial(void);
extern	uint8_t GTimer_RegisterCB(GTimerCB FunCB);
extern	void GTimer_unRegisterCB(uint8_t TimeSlot);
extern	void GTimer_Refresh(uint8_t TimeSlot, uint8_t TimeExpire);
extern	void GTimer_Stop(uint8_t TimeSlot);
void GTimerStopCounter(void);
void GTimerStartCounter(void);

// For send Alarm Ping Msg
extern	void sendAlarmPing(void); 
// Timer handles for the 15 second status message and the
// inhibit timer after EvolveStore sends 0x7f connect message
// for connect ACK with status payload.
extern volatile uint8_t send_ping_handler;
extern volatile uint8_t status_inhibit_handler;
extern volatile uint8_t send_alarm_ping_handler;

// Flags to control the sending of Msg from main See the comments where it is defined
	// This change was taken out because there was communication failure in sending the ping for evolve
	// from inside the main while loop 10/23/2015 NCR changes
//extern volatile uint8_t flag_send_ping_handler;
extern volatile uint8_t flag_send_alarm_ping_handler;
extern volatile uint8_t flag_status_inhibit_handler;
extern volatile uint8_t flag_send_end_alarm;
extern volatile uint8_t flag_config_enable_alarm;
extern volatile uint8_t flag_enable_hard_tag_indicator;
extern volatile uint8_t primary_tag_counter_without_tag;
extern volatile uint8_t secondary_tag_counter_without_tag;
#endif
