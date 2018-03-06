/*******************************************************************
 *
 * File name: alarm.c
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
 * Creator: Josh Zhao
 *
 * Date Created:
 *
 * $History: alarm.c $
 * 
 * *****************  Version 18  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 1/29/14    Time: 9:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a function for a new LED color (purple)
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 11/27/13   Time: 3:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to mark both the areas for the GPO application features of
 * primary and seconary alarm features. Added a function to clear the
 * relay output to a non-active mode
 * 
 * *****************  Version 13  *****************
 * User: Dubes        Date: 11/26/13   Time: 12:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added ledBlueGreenOn and added code in defaultConfigBlinkingOff to have
 * tile color on if the system  has not been auto tuned.
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:24a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to allow the blue LED to flash for 1/2 second and code to
 * enable and disable the blue LED flashing. Disabled the turning on of
 * the interlock and verify mode LEDs until after the default indication
 * is completed.
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:44p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added function to disable the mistune LED (flashing red LED) and
 * mistune condition is cleared
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Decreased the alarm indication tme from 600ms to 500ms
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 10/08/13   Time: 4:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Reduced the alarm indication time from 1000ms to 600ms for mode 4.
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:19p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new parameter to "startAlarm() to indicate whether the 1st or 2nd
 * TX caused the alarm.
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 9/30/13    Time: 3:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Reduced the LED/sounder/IO timer from 1500ms to 1000ms for mode 4 and
 * 600ms for all other modes.
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Reversed the logic for the alarm IO per Bob Langer.
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 8/28/13    Time: 10:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Comment clean up
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/28/13    Time: 6:42p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a flag to unlock freqs during deactivation (when the alarm
 * light is enables)
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changes to the code to integrate the alarm LED/sounder and IO feature.
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed LED timer for alarm from one to two seconds. This was done to
 * allow the inhibit to take affect and not allow a flashing of the alarm
 * LED
 * 
 ******************************************************************/

#include "interface.h"
#include "lowlevel.h"
#include "gtimer.h"
#include "alarm.h"
#include "nvm_eeprom.h"
#include "dms_interface.h"
#include "zircon_config.h"


// enables and disables frequency locking
uint8_t enable_freq_lock = 1;

//alarm timer handler
//static uint8_t  alarmHandle_solt;
uint8_t  alarmHandle_solt = 0;
//ping alarm timer handler
//static uint8_t  pingAlarmHandle_solt;
//blink led alarm timer handler
static uint8_t  blinkingHandle_solt;
// blink blue LED to indicate default config parameters
static uint8_t defaultBlinkingHandle;
//used for restoring led when interlock timer expired
static uint8_t  current_mode ;
static uint8_t interlock_state;
// indicates whether alarm is from 1st or 2nd TX
static uint8_t loop_alarm = 0;
static uint8_t sounder_enabled = 1;
static uint8_t IO_enabled = 1;


void  ledYellowOn(void)
{
	LED_PORT.OUTCLR = LED_RED;
	LED_PORT.OUTSET = LED_BLUE;
	LED_PORT.OUTCLR = LED_GREEN;
}


void  ledBlueOn(void)
{
	LED_PORT.OUTSET = LED_RED;
	LED_PORT.OUTCLR = LED_BLUE;
	LED_PORT.OUTSET = LED_GREEN;
}


void  ledRedOn(void)
{
	LED_PORT.OUTCLR = LED_RED;
	LED_PORT.OUTSET = LED_BLUE;
	LED_PORT.OUTSET = LED_GREEN;
}

void  ledBlueGreenOn(void)
{
	LED_PORT.OUTSET = LED_RED;
	LED_PORT.OUTCLR = LED_BLUE;
	LED_PORT.OUTCLR = LED_GREEN;
}

void ledBlueRedOn(void)
{
	LED_PORT.OUTCLR = LED_RED;
	LED_PORT.OUTCLR = LED_BLUE;
	LED_PORT.OUTSET = LED_GREEN;	
}

void ledOff(void)
{
	LED_PORT.OUTSET = LED_RED;
	LED_PORT.OUTSET = LED_BLUE;
	LED_PORT.OUTSET = LED_GREEN;
}

//PD2
void sounderOn(void)
{
	SOUNDER_PORT.OUTSET = SOUNDER_PIN;
}

void sounderOff(void)
{
	SOUNDER_PORT.OUTCLR = SOUNDER_PIN;
}

//PD0
void outputOn(void)
{
	if(CPiD_HW_flag) /* Thoralite */
	{
		OUTPUT_PORT.OUTSET = OUTPUT_PIN;
	}
}

void outputOff(void)
{
	if(CPiD_HW_flag) /* Thoralite */
	{
		OUTPUT_PORT.OUTCLR = OUTPUT_PIN;
	}
}

// Sets relay to it's default value
void GPOoutputOff(uint8_t active_state)
{
	if(CPiD_HW_flag) /* Thoralite */
	{
		// normally open relay
		if(GPO_ACTIVE_OPEN == active_state)
		{
			GPO_PORT.OUTCLR = GPO_PIN;
		}
		else  // normally closed relay
		{
			GPO_PORT.OUTSET = GPO_PIN;
		}
	}
}

// this function is called when alarm duration is expired.
void alarmExpired(void)
{
	// enables frequency locking during mode 6 detection
	enable_freq_lock = 1;
	
	// One of these GPO feature could be selected so clear the 
	// value if so.
	processGpoPin(GPO_PRI_SOUND_OUTPUT, GPO_CLEAR);
	processGpoPin(GPO_PRI_NO_SOUND_OUTPUT, GPO_CLEAR);
	processGpoPin(GPO_SEC_OUTPUT, GPO_CLEAR);

	ledOff();
	sounderOff();
	outputOff();

	if(current_mode == DEACT_VERIFY)
	{
		ledBlueOn();
	}
	
	
		// Send the Alarm msg , this will also result in suppressing of ping msg as timer is refreshed.
		// Send only if the it has been enabled
		
	if (alarmCount < 255)
	{
		alarmCount = alarmCount + 1;
	}
	else
	{
		alarmCount = 0;
	}
	
	/*
	if (alarmCountNCR < 15)
	{
		alarmCountNCR = alarmCountNCR + 1;
	}
	else
	{
		alarmCountNCR = 0;
	}
	*/	
	// This is to send Soft Allarm
	// NCR mode enabled
	if( 1 == flag_config_enable_alarm)
	{
		// To take care of Back to Back Alarm Ping msg
		GTimer_Stop(send_alarm_ping_handler);
		flag_send_alarm_ping_handler = 3;
		//flag_send_end_alarm = 0;
		// No need to send the Alarm Ping if the Alarm is being sent
		if (0 != alarm_ping_time)
		{
			GTimer_Refresh(send_alarm_ping_handler, alarm_ping_time);
		}			
	
	}
		
}


// this function is called when mis-tuning occurs
void BlinkingExpired(void)
{
	static uint8_t  flag = 0;
	
	if (flag)
	{
		ledOff();
		flag=0;
	}
	else
	{
		ledRedOn();
		flag=1;
	}

	GTimer_Refresh(blinkingHandle_solt,G_TIMER_500mS);
}

// This is used to toggle the blue LED used to indicate the unit
// is using default configuration settings
void DefaultBlinkingExpired(void)
{
	static uint8_t  flag = 0;
	
	if (flag)
	{
		ledOff();
		flag=0;
	}
	else
	{
		ledBlueOn();
		flag=1;
	}

	GTimer_Refresh(defaultBlinkingHandle,G_TIMER_500mS);
}

// initialize sounder, led and output gpios
void alarmInit(uint8_t deact_mode, uint8_t enable, uint8_t IO)
{
	// disable sounder led, alarm output 
	SOUNDER_PORT.OUTCLR = SOUNDER_PIN;
	SOUNDER_PORT.DIRSET = SOUNDER_PIN;
	
	if(CPiD_HW_flag) /* Thoralite */
	{
		OUTPUT_PORT.OUTCLR = OUTPUT_PIN;
		OUTPUT_PORT.DIRSET = OUTPUT_PIN;
	}

	LED_PORT.OUTSET = LED_RED;
	LED_PORT.DIRSET = LED_RED;

	LED_PORT.OUTSET = LED_BLUE;
	LED_PORT.DIRSET = LED_BLUE;

	LED_PORT.OUTSET = LED_GREEN;
	LED_PORT.DIRSET = LED_GREEN;
#if 0
	// Yellow light has priority over blue verify mode LED
	if(enable)
	{
		ledYellowOn();
	}
	else if(DEACT_VERIFY == deact_mode)
	{
		ledBlueOn();
	}
#endif

	// set handlers for all flashing indications
	alarmHandle_solt = GTimer_RegisterCB(&alarmExpired);
	blinkingHandle_solt = GTimer_RegisterCB(&BlinkingExpired);
	defaultBlinkingHandle = GTimer_RegisterCB(&DefaultBlinkingExpired);

	current_mode=deact_mode;
	interlock_state = enable;
			
	// Initialize the GPO feature selected		
	if(IO == GPO_DISABLE_SOUNDER)
	{
		sounder_enabled = 0;
		IO_enabled = 1;
	}
	else if(IO == GPO_DISABLE_IO)
	{
		sounder_enabled = 1;
		IO_enabled = 0;		
	}
	else // enable both sounder and IO
	{
		sounder_enabled = 1;
		IO_enabled = 1;		
	}
}

// start to alarm when detecting a tag
// loop also indicate the weather the alarm is from secondary or primary antenna
// loop = 0 indicate primary loop = 1 indicate secondary
void startAlarm(uint8_t loop)
{
	loop_alarm = loop;
	
	if(loop == 0)
	{
		ledRedOn();
		processGpoPin(GPO_PRI_SOUND_OUTPUT, GPO_SET);
		processGpoPin(GPO_PRI_NO_SOUND_OUTPUT, GPO_SET);
	}
	else
	{
#if 0 // keep for testing purposes to indicate the secondary loop
		LED_PORT.OUTCLR = LED_GREEN;
#endif
		ledRedOn();
		// put code here for 2nd TX alarm for GPO feature
		processGpoPin(GPO_SEC_OUTPUT, GPO_SET);
	}
	
	if(sounder_enabled)
	{
		sounderOn();
	}
	
	if((loop == 0) || (IO_enabled))
	{
		outputOn();
	}
	
	// In case of higher tag rates the 500 ms alarm expiration is too short, in order that the alarm should expire when the tag is removed from the field
	// we need longer alarm duration.
	// 500 ms duration was chosen so that the precipitation of hight deference between Alarm Detect and Deactivation in mode 6 is less
	// but in case of hard tag the the 500 ms alarm will expire before in case of higher detection rate before the start of next detection cycle. 
	// All this when this flag is enabled: Indicates the higher Tag rate is enabled
	if (1 == flag_enable_hard_tag_indicator)
	{ // Have different timing here dependent on TAG rate and Mode 
	  // the conditions are not combined just for the sake of readability	
		if(config_parameters.deact_frame_rate == FRAME_144HZ)
		{
			// Only for Mode 6 and Tag alarm rate the code is changed
			if ((16 == tags_before_alarm) && (DEACT_MODE6 == config_parameters.mode_ind))
			{
				if (config_parameters.enable_tx_2)
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_2S);
					// 1500 does not works
					//GTimer_Refresh(alarmHandle_solt, G_TIMER_1500mS);
				} else
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_1S);
				}
				
			} else 
			{
				if(current_mode == DEACT_MODE4)
				{
					if ( 16 ==  tags_before_alarm)
					{
						if (config_parameters.enable_tx_2)
						{
							//GTimer_Refresh(alarmHandle_solt, G_TIMER_1500mS);
							GTimer_Refresh(alarmHandle_solt, G_TIMER_2S);				
						} else
						{
							//GTimer_Refresh(alarmHandle_solt, G_TIMER_1S);
							GTimer_Refresh(alarmHandle_solt, G_TIMER_1500mS);						
						}
						
					} else
					{
					  GTimer_Refresh(alarmHandle_solt, G_TIMER_500mS);
					}					
					
				}
				else  // all other mode 1/2 second alarm period
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_600mS);
				}
			}		
		} else
		{  // 10 Hz Tag rate	
			
			if (( 16 == tags_before_alarm) && (config_parameters.enable_tx_2))
			{
				GTimer_Refresh(alarmHandle_solt, G_TIMER_5S);
			} else if ((( 16 == tags_before_alarm) && (!config_parameters.enable_tx_2) )|| (( 8 == tags_before_alarm) && (config_parameters.enable_tx_2) ))
			{
				GTimer_Refresh(alarmHandle_solt, G_TIMER_2S);
			} else if ((( 8 == tags_before_alarm) && (!config_parameters.enable_tx_2) )|| (( 4 == tags_before_alarm) && (config_parameters.enable_tx_2) ))
			{
				GTimer_Refresh(alarmHandle_solt, G_TIMER_1500mS);
			}else if (( 2 == tags_before_alarm) && (config_parameters.enable_tx_2) )
			{
				GTimer_Refresh(alarmHandle_solt, G_TIMER_1S);
			} else
			{
				if(current_mode == DEACT_MODE4)
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_500mS);
				}
				else  // all other mode 1/2 second alarm period
				{
					GTimer_Refresh(alarmHandle_solt, G_TIMER_600mS);
				}
			}		
		} 
	
	} else  // All have Same Alarm timing if we have not enabled Hard tag indicator Flag
	{
		//GTimer_Refresh(alarmHandle_solt, G_TIMER_1500mS);
		if(current_mode == DEACT_MODE4)
		{
			GTimer_Refresh(alarmHandle_solt, G_TIMER_500mS);
			//GTimer_Refresh(alarmHandle_solt, G_TIMER_600mS);
		}
		else  // all other mode 1/2 second alarm period
		{
			GTimer_Refresh(alarmHandle_solt, G_TIMER_600mS);
			//GTimer_Refresh(alarmHandle_solt, G_TIMER_1S);
		}

	}
	
	// This is to send Soft Allarm only if this is enabled by sending the NCR mode enabled ZIRCON_CONFIG_DISABLE_STATUS by NCR
	if( 1 == flag_config_enable_alarm)
	{
		if(0 == flag_send_end_alarm)
		{
			// NCR wants the alarm count to increment at the start alarm 08/05/2015
			if (alarmCountNCR < 15)
			{
				alarmCountNCR = alarmCountNCR + 1;
			}
			else
			{
				alarmCountNCR = 0;
			}
			
			// 1 will indicate alarm caused by Primary flag and 2 will indicate alarm caused by secondary flag
			// We can send this information also up in future
			if (0 == loop_alarm)
			{
				flag_send_end_alarm = 1;	
			} else
			{
				flag_send_end_alarm = 2;				
			}
			
			alarmRefreshCount = 0; // one it has send this it should reset to zero, since it indicates the duration of last tag seen

			alarmAccumulatedTime = 0;
			// To take care of Back to Back Alarm Ping msg
			GTimer_Stop(send_alarm_ping_handler);
			flag_send_alarm_ping_handler = 2; // Will indicate start of alarm 3 will indicate alarm stop
			// No need to send the Alarm Ping if the Alarm is being sent
			if (0 != alarm_ping_time)
			{
				GTimer_Refresh(send_alarm_ping_handler, alarm_ping_time);
			}			
		} else
		{
			IncrementAlarmRate();
		}		
	}

}

//turn on led when interlock timer expired
void interlockLEDOn(void)
{
	//make sure the alarm timer is stopped when interlock timer expired 
	GTimer_Stop(alarmHandle_solt);
	// Ping Alarm Handel stop
	//GTimer_Stop(pingAlarmHandle_solt);
	ledOff();
	ledYellowOn();
}


// turn off the led when interlock is active
void interlockLEDOff(void)
{
	ledOff();

	if(current_mode == DEACT_VERIFY)
	{
		ledBlueOn();
	}
}


void misTuningBlinking(void)
{
	GTimer_Refresh(blinkingHandle_solt,G_TIMER_500mS);
}

void misTuningBlinkingOff(void)
{
	GTimer_Stop(blinkingHandle_solt);
	ledOff();
	
	if(interlock_state)
	{
		ledYellowOn();
	}
	else if(DEACT_VERIFY == current_mode)
	{
		ledBlueOn();
	}
}

void defaultConfigBlinking(void)
{
	GTimer_Refresh(defaultBlinkingHandle,G_TIMER_500mS);
}

void defaultConfigBlinkingOff(uint8_t interlock_status)
{
	GTimer_Stop(defaultBlinkingHandle);
	ledOff();
	
#if THREE_TYPE_TUNING
	// If this is the case then probably it has to be Auto tuned
	if ( (0Xff == nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) && (TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) ) )
	{
		ledBlueGreenOn();
	}
	else
	{
		if(/*interlock_state*/interlock_status)
		{
			ledYellowOn();
		}
		else if(DEACT_VERIFY == current_mode)
		{
			ledBlueOn();
		}
	}

#else	
	if(/*interlock_state*/interlock_status)
	{
		ledYellowOn();
	}
	else if(DEACT_VERIFY == current_mode)
	{
		ledBlueOn();
	}
#endif	
	GTimer_unRegisterCB(defaultBlinkingHandle);
}

// Increment Alarm Refresh Count in a normalized way
// the idea is that this no should indicate as to how much time duration it has seen the last tag in the field
// it is more representative of interval of time rather then duration e.g 1 may indicate any thing between 0 to .5 second
// 2 .5 to 1 second , 3 1 to 1 seconds etc.
// The no denotes range based on Time accumulated during each Frame 
void IncrementAlarmRate(void)
{

		if (  (100 <= alarmAccumulatedTime) && ( 500 >= alarmAccumulatedTime) )
		{
			alarmRefreshCount = 1;
		}else if ((500 < alarmAccumulatedTime) && ( 1000 >= alarmAccumulatedTime) )
		{
			alarmRefreshCount = 2;
		}else if ((1000 < alarmAccumulatedTime) && ( 2000 >= alarmAccumulatedTime) )
		{
			alarmRefreshCount = 3;
		}else if ( (2000 < alarmAccumulatedTime) && ( 3000 >= alarmAccumulatedTime) )
		{
			alarmRefreshCount = 4;
		}else if ( (3000 < alarmAccumulatedTime) && ( 4000 >= alarmAccumulatedTime)  )
		{
			alarmRefreshCount = 5;
		}else if ( (4000 < alarmAccumulatedTime) && ( 5000 >= alarmAccumulatedTime)  )
		{
			alarmRefreshCount = 6;
		}else if ( (5000 < alarmAccumulatedTime) && ( 6000 >= alarmAccumulatedTime) )
		{
			alarmRefreshCount = 7;
		}else if ( (6000 < alarmAccumulatedTime) && ( 7000 >= alarmAccumulatedTime)  )
		{
			alarmRefreshCount = 8;
		}else if ( (7000 < alarmAccumulatedTime) && ( 8000 >= alarmAccumulatedTime)  )
		{
			alarmRefreshCount = 9;
		}else if ( (8000 < alarmAccumulatedTime) && ( 9000 >= alarmAccumulatedTime)  )  // up to 9 second 
		{
			alarmRefreshCount = 10; //A 
		}else if ((9000 < alarmAccumulatedTime) && ( 10000 >= alarmAccumulatedTime)  )  // up to 10 seconds 
		{
			alarmRefreshCount = 11; //B
		} else if ( (10000 < alarmAccumulatedTime) && ( 30000 >= alarmAccumulatedTime)  ) //up to 30 second  
		{
			alarmRefreshCount = 12; //C
		}else if ( (30000 < alarmAccumulatedTime) && ( 60000 >= alarmAccumulatedTime)  )  //up to  1 minute 
		{
			alarmRefreshCount = 13; //D
		}else if ( (60000 < alarmAccumulatedTime) && ( 300000 >= alarmAccumulatedTime)  ) // up to 5 minute    
		{
			alarmRefreshCount = 14; //E
		}else  if (300000 < alarmAccumulatedTime)     // greater then 5 minute 
		{
			alarmRefreshCount = 15;
		}
	
}