/*******************************************************************
 *
 * File name: analog.h
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
 * $History: autotune.h $
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 12/05/13   Time: 4:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the overvoltage signal strength threshold because of the change
 * for the ADC sample point on the ant sample port. 
 * 
 * *****************  Version 15  *****************
 * User: Dubes        Date: 11/26/13   Time: 12:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added defines for Types of Tuning The default is 0
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 11/20/13   Time: 5:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added macro define for overvoltage threshold which was mapped to 1850
 * signal strength from the ADC.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Change the startAutoTune() prototype for the removed input parameter,
 * added the called back function for the scheduled overvoltage test and
 * added the code to do both overvoltage testing at the beginning, during
 * normal operation and via the DMS tool.
 * 
 * *****************  Version 12  *****************
 * User: Dubes        Date: 10/10/13   Time: 6:31p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * // states of autotune_verify_flagadded definesAUTOTUNE_VERIFY_RESET
 * 0AUTOTUNE_VERIFY_EXECUTE				1AUTOTUNE_VERIFY_FREQ_COUNTING		2
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 9/27/13    Time: 11:09a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * code to support the DMS antenna tuning display. Still needs Sandeep's
 * code and the latest DMS to complete the feature
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 8/28/13    Time: 10:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Comment clean up
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:08p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Finished coding for the tuning verify feature 
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 8/09/13    Time: 8:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new file for a first time flag.
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 8/09/13    Time: 10:37a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added field for the eeprom stored structure for auto tune
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * "extern"'s in header file
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
 * Auto tuning structures and function prototypes
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:10a
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * initial
 * 
 *******************************************************************/


#ifndef AUTOTUNE_H_
#define AUTOTUNE_H_

#include "globals.h"
#include "timers.h"

////////////////////////////////////////////////////////////////////
// extern variables
///////////////////////////////////////////////////////////////////
extern volatile uint8_t gAutoState;
extern volatile uint8_t autotune_timing_flag;
extern volatile uint8_t autotune_verify_handler;
extern volatile uint8_t autotune_verify_flag;
extern volatile uint8_t autotune_verify_started;
extern volatile uint8_t autotune_overvoltmeas_flag;
extern volatile uint8_t autotune_overvolt_handler;

///////////////////////////////////////////////////////////////////
// Macro defines
//////////////////////////////////////////////////////////////////
#define AUTO_STATE_IDLE			0
#define AUTO_STATE_MEAS			1
#define AUTO_STATE_COMPARE		2
#define AUTO_STATE_ADJ			3
#define AUTO_STATE_COMP			4

#define SET_AUTO_STATE(x)		gAutoState = x
#define GET_AUTO_STATE(x)		gAutoState == x

#define MID_RANGE_FREQ			7
#define AUTO_SETTLE_TIME		20
#define AUTO_SAMPLE_TIME		10

#define NUM_RELAY_GPIO			5
#define NUM_RELAY_POSITIONS		32
#define RELAY_MASK				0x01

#define AUTO_SUCCESS			1
#define AUTO_FAIL				0

// states of autotune_verify_flag
#define AUTOTUNE_VERIFY_RESET				0
#define AUTOTUNE_VERIFY_EXECUTE				1
#define AUTOTUNE_VERIFY_FREQ_COUNTING		2

// Over voltage threshold level (400 Vp around primary TX)
// when sample point (ADC) is at 20 us
#define OV_THRESHOLD						2200//1850 //when sample point was at 60 us

// Types of Tuning The default is 0
#define TYPE_AUTO_TUNE_RESET				0
#define TYPE_MANUAL_TUNE_ONLY				1
#define TYPE_AUTO_TUNE_POWERUP				2

////////////////////////////////////////////////////////////////
// data structures
///////////////////////////////////////////////////////////////
// This structure is used during auto tuning and
// is stored in eeprom
typedef struct {
	uint8_t first_time_flag;
	uint16_t peak_value;
	uint16_t manual_value;
	uint8_t mistune_flag;
	uint8_t frame_rate;
	uint8_t vpa_setting;
	uint8_t peak_position;
	uint8_t relay_position;
	
} profileStructType;


/////////////////////////////////////////////////////////////////
// global function prototypes
////////////////////////////////////////////////////////////////
// call back function to set a flag after the tuning verification timer 
// expires.
void verifyTuning(void);

void verifyovervolt(void);

/*
** Function: startAutoTune
**
** Purpose : This is the entry point for auto/manual tuning and initializes
**			frame rate, VPA rail levels and transmit test frequency and 
**			provides clean up after the tuning process is complete. 
**
** Parameters:
**     Input :	autotune: indicate if auto/manual tuning from DMS
**				autotune_timing: indicate to the TX/RX timing feature
**								an auto tune session is active
**
**     Return: None
**
** Effected Var's:
**
** Effected IO/HW:
**
*/
// Macro defines for "autotune" parameter
#define MANUAL_TUNE		0
#define AUTO_TUNE		1
// Macro defines for "tuning_mode" parameter
#define NORMAL_MODE		0
#define DMS_MODE		1
#define OVERVOLT_MODE	2
#define DMS_OV_MODE		3
void startAutoTune(uint8_t autotune, uint8_t tuning_mode);


/*
** Function: measureAutoTune
**
** Purpose :	After one TX/RX cycle this function is immediately called to 
**				sample the antenna current (ADC) and store away to be averaged 
**				after ten samples are collected. This occurs until all 32 relay 
**				positions are tested. The peak is saved during the relay iterations
**				and the relay is set to the peak current found.
**				For manual tuning, the retrieved antenna positions is used to set 
**				the relays and a new current measurement is taken and stored in 
**				eeprom.		
**				This function should complete in one frame rate.	
**
** Parameters:
**     Input :	None
**
**     Return: None
**
** Effected Var's: autotune_meas_array[]: loads ant current samples for averaging
**					AUTO_STATE: This state could transitions from "AUTO_STATE_MEAS"
**								to "AUTO_STATE_COMPARE" when all 10 samples are taken
**
** Effected IO/HW: Reads antenna current HW using ADC
**
*/
void measureAutoTune(void);


#endif /* AUTOTUNE_H_ */