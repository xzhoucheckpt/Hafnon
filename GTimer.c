/*******************************************************************
 *
 * File name: GTimer.c
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
 * $History: GTimer.c $
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 5/13/15    Time: 2:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the priortiy from high to low for the 100 mS timer. This drives
 * the timers for scheduling, alarm LED duration and non-solicited status
 * messages. 
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 3/17/15    Time: 10:12a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the two second timer for evolvestore to allow the evolve reader
 * to have a faster response between the CPiD and evolve reader
 * 
 * *****************  Version 14  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a new timer value of 1 hour for the tuning verification
 * feature. This was changed from 10 hours.
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a test around GTimer_unRegisterCB() to range check the handle
 * being put back into the timer structure.
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:25a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a 5 second timer for the new default config indication.
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added to new timer values to support the overvoltage feature
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two function to stop and start the timer for alarming
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 10/08/13   Time: 4:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a 200 ms timer case in the timer switch
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 9/30/13    Time: 3:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a 600 ms timer for the alarm for all modes except mode 4
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the value of one of the timers
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:08p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timer for  2 seconds to test the verify tuning feature
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased the timer range to allow a 32 bit counter time and created a
 * 10 hour timer for the verify tune feature
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the new timer value to the timer refresh function.
 * 
 ******************************************************************/

#include "timers.h"
#include "lowlevel.h"
#include "interface.h"
#include "GTimer.h"

// For transmitter and LO frequency generation/accuracy either the 
// DDS is used or VCO. The VCO method may need to be validated via
// counter algorithms. 
#if USE_DDS
#include "dds.h"
#else
#include "analog.h"
#endif 

#define GTIMER_EMPTY	0
#define GTIMER_STOP		1
#define GTIMER_RUN		2

#define GTIMER 			TCF0
#define GTIMER_ISR_VECT	TCF0_OVF_vect

// NULL callback function used for a non-initialized timer. 
static void Gtimer_Idle(void)
{
}

static GTimerCB	TimerCB[G_TIMER_MAX_SLOT];
//static uint8_t	TimerCnt[G_TIMER_MAX_SLOT];
static uint32_t	TimerCnt[G_TIMER_MAX_SLOT];
static uint8_t	TimerState[G_TIMER_MAX_SLOT];
//static uint8_t	TimerExpired[G_TIMER_MAX_SLOT];
static uint32_t	TimerExpired[G_TIMER_MAX_SLOT];
	

void GTimer_Initial(void)
{
	uint8_t i;

	// Setup overflow timer for 100ms
	GTIMER.CTRLA = TC_CLKSEL_OFF_gc;
	GTIMER.PER = 2343;  // for 100ms 
	GTIMER.CNT = 0x00;
	//GTIMER.INTCTRLA = TC_OVFINTLVL_HI_gc;
	GTIMER.INTCTRLA = TC_OVFINTLVL_LO_gc;
	GTIMER.CTRLB = (TC_WGMODE_NORMAL_gc);

	// Initialize all timer slots to empty
	for(i=0;i<G_TIMER_MAX_SLOT;i++)
	{
		TimerCB[i] = Gtimer_Idle;
		TimerCnt[i] = 0;
		TimerState[i]= GTIMER_EMPTY;
		TimerExpired[i] = 0;
	}
	
	// Turn on timer.
	GTIMER.CTRLA = TC_CLKSEL_DIV1024_gc;
	return;
}


void GTimerStopCounter(void)
{
	GTIMER.CTRLA = TC_CLKSEL_OFF_gc;
}

void GTimerStartCounter(void)
{
	GTIMER.CTRLA = TC_CLKSEL_DIV1024_gc;
}


// Initialize the general timer, and register the callback function, 
// that function will be called when time interrupt occurs
uint8_t GTimer_RegisterCB(GTimerCB FunCB)
{
	uint8_t i;
	
	// Find empty slot and register callback function
	for(i=0;i<G_TIMER_MAX_SLOT;i++)
	{
		if(TimerState[i] == GTIMER_EMPTY)
		{
			TimerCB[i] = FunCB;
			TimerState[i] = GTIMER_STOP;
			return i;
		}
	}
		
	// Can not find an empty slot for register, so return the 
	// 0xff for failure register	
	return 0xFF;	
}


void GTimer_unRegisterCB(uint8_t TimeSlot)
{
	if(TimeSlot < G_TIMER_MAX_SLOT)
	{
		TimerState[TimeSlot] = GTIMER_EMPTY;
		TimerCB[TimeSlot] = Gtimer_Idle;
	}
}

// refresh the timer, update the new interrupt time, and start the timer
void GTimer_Refresh(uint8_t TimeSlot, uint8_t TimeExpire)
{
	switch(TimeExpire){
		
		case G_TIMER_10H:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 360000;	//100ms*360000 = 10 hours
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
		
		case G_TIMER_1H:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 36000;	//100ms*36000 = 1 hours
			TimerState[TimeSlot] = GTIMER_RUN;
		break;		
		
		case G_TIMER_30M:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 18000;	//100ms*18000 = 30 mins
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
		
		case G_TIMER_2M:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 1200;	//100ms*1200 = 2m
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
		
		case G_TIMER_1M:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 600 ;//600;	//100ms*600 = 1m
			TimerState[TimeSlot] = GTIMER_RUN;		
		break;
		
		case G_TIMER_1500mS:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 15;	//100ms*20 = 2s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;				
		
		case G_TIMER_1S:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 10;	//100ms*10 = 1s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
		
		case G_TIMER_2S:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 20;	//100ms*10 = 1s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
		
		case G_TIMER_5S:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 50;	//100ms*50 = 5s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;		
			
		case G_TIMER_30S:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 300;	//100ms*300 = 30s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
			
		case G_TIMER_600mS:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 6;	//100ms*10 = 1s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
			
		case G_TIMER_500mS:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 5;		//100ms*5 = 500ms
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
			
		case G_TIMER_200mS:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 2;		//100ms*1 = 100ms
			TimerState[TimeSlot] = GTIMER_RUN;
		break;			
			
		case G_TIMER_100mS:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 1;		//100ms*1 = 100ms
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
#if EVOLVESTORE
		case G_TIMER_15S:
			TimerState[TimeSlot] = GTIMER_STOP;
			TimerCnt[TimeSlot] = 0;
			TimerExpired[TimeSlot] = 150;	//100ms*150 = 15s
			TimerState[TimeSlot] = GTIMER_RUN;
		break;
#endif
		case G_TIMER_15M:
		TimerState[TimeSlot] = GTIMER_STOP;
		TimerCnt[TimeSlot] = 0;
		TimerExpired[TimeSlot] = 9000;	//100ms*9000 = 15 mins
		TimerState[TimeSlot] = GTIMER_RUN;
		break;
					
		}
		
	return;
}

//stop the timer 
void GTimer_Stop(uint8_t TimeSlot)
{
	TimerState[TimeSlot] = GTIMER_STOP;
	return;
}


//time interrupt, the registered callback function will be called
ISR(GTIMER_ISR_VECT)  // CCA
{	
	uint8_t i;
	
	GTIMER.CTRLA = TC_CLKSEL_OFF_gc;
	GTIMER.CNT = 0x00; // reset the counter
	
	for(i=0;i<G_TIMER_MAX_SLOT;i++)
	{
		if(TimerState[i] == GTIMER_RUN)
		{
			TimerCnt[i]++;
			if(TimerCnt[i]>=TimerExpired[i])
			{
				TimerState[i] = GTIMER_STOP;
				TimerCB[i]();
			}
		}
	}
	
	GTIMER.CTRLA = TC_CLKSEL_DIV1024_gc;
}


