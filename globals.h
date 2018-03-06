/*******************************************************************
 *
 * File name: globals.h
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
 * $History: globals.h $
 * 
 * *****************  Version 61  *****************
 * User: Dubes        Date: 11/18/15   Time: 1:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 1 minute problem reported by NCR left by mistake in 1.9R Fixed Release
 * 1.10R
 * 
 * *****************  Version 60  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 59  *****************
 * User: Galantij     Date: 5/13/15    Time: 2:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed version number from 1.7R to 1.8R. Added two macro defines for
 * the WD enable and tickle. Removed the deceration for pulseNumber.
 * 
 * *****************  Version 58  *****************
 * User: Galantij     Date: 3/17/15    Time: 10:14a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased the version number from 1.6 to 1.7 for the EvolveStore
 * release
 * 
 * *****************  Version 57  *****************
 * User: Galantij     Date: 11/12/14   Time: 9:51a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the release version number from RC to R. This will be release
 * as "CPiD_1_7R_111214"
 * 
 * *****************  Version 56  *****************
 * User: Dubes        Date: 8/12/14    Time: 9:47a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * #define SERIAL_NUM changed to 1 for Evolve Storethis code is tested and
 * will work with latest DMS.
 * 
 * *****************  Version 55  *****************
 * User: Dubes        Date: 7/28/14    Time: 1:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * The Changes to address QC issue EAS.Zircon - Defect # 116 for Mode 4
 * and verification mode we are taking out the delay every 5 th pulse
 * 
 * *****************  Version 54  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 53  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 52  *****************
 * User: Galantij     Date: 6/09/14    Time: 10:12a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased the version number to 1.3R
 * 
 * *****************  Version 51  *****************
 * User: Galantij     Date: 5/29/14    Time: 2:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased release number to 1.2R
 * 
 * *****************  Version 50  *****************
 * User: Galantij     Date: 4/01/14    Time: 3:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased release to 1.1R
 * 
 * *****************  Version 49  *****************
 * User: Galantij     Date: 3/27/14    Time: 1:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed release to 1.0R
 * 
 * *****************  Version 48  *****************
 * User: Galantij     Date: 3/12/14    Time: 1:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increase release to 1.26R
 * 
 * *****************  Version 47  *****************
 * User: Galantij     Date: 3/06/14    Time: 7:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 46  *****************
 * User: Galantij     Date: 3/05/14    Time: 10:52a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed to the first production release 1.24R
 * 
 * *****************  Version 45  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed release version to 0.24RC
 * 
 * *****************  Version 44  *****************
 * User: Galantij     Date: 2/27/14    Time: 1:47p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed release to 0.23RC
 * 
 * *****************  Version 43  *****************
 * User: Galantij     Date: 2/26/14    Time: 12:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed release to 0.22RC
 * 
 * *****************  Version 42  *****************
 * User: Galantij     Date: 2/18/14    Time: 11:32a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased release to 0.21RC
 * 
 * *****************  Version 41  *****************
 * User: Galantij     Date: 2/13/14    Time: 4:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 40  *****************
 * User: Galantij     Date: 2/11/14    Time: 1:41p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Set the REV macro define REV back to zero after reversing the first
 * table 
 * 
 * *****************  Version 39  *****************
 * User: Galantij     Date: 2/05/14    Time: 4:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 38  *****************
 * User: Galantij     Date: 2/04/14    Time: 11:05a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Bumped up the release to 0.17 RC
 * 
 * *****************  Version 37  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Include a new macro define for the reversing of the transmit frequency
 * and set it for this mode. Also increased release to 0.16RC
 * 
 * *****************  Version 36  *****************
 * User: Galantij     Date: 1/16/14    Time: 5:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changing version number to 0.15RC
 * 
 * *****************  Version 35  *****************
 * User: Galantij     Date: 1/10/14    Time: 3:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Incremented the release version from 0.13RC to 0.14RC
 * 
 * *****************  Version 34  *****************
 * User: Galantij     Date: 1/07/14    Time: 4:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed firmware version to 0.13R for the next release
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the macro define for the choice between SEQ or INTERLEAVE TX
 * frequency "SEQ_FREQ"
 * 
 * *****************  Version 32  *****************
 * User: Dubes        Date: 11/26/13   Time: 5:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the build type just to show the diff
 * 
 * *****************  Version 31  *****************
 * User: Dubes        Date: 11/26/13   Time: 12:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added conditional compile parameter THREE_TYPE_TUNING
 * 
 * *****************  Version 30  *****************
 * User: Dubes        Date: 11/15/13   Time: 10:51a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Minor firmware version 11
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 11/13/13   Time: 4:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a macro define for the new feature which allows the VPA rail to
 * continue to charge during interlock
 * 
 * *****************  Version 28  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added define INTERLOCK_CHOICE to control iif the code support hard
 * switch or DMS based switch
 * 
 * *****************  Version 27  *****************
 * User: Galantij     Date: 11/04/13   Time: 5:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * change the version to 0.10 RC
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 10/25/13   Time: 4:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the release to 0.9 RC
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 10/25/13   Time: 4:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the mode processing back to the original method
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 10/25/13   Time: 11:22a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the macro define to allow the rail to discharge for the
 * original method.
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 10/24/13   Time: 9:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added macro define for the new method if mode operation. Also marked
 * this release as 0.8 T.
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:50p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added macro define for discharging the VPA rail voltage and changed the
 * release version to 0.8 RC
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 10/10/13   Time: 5:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the release type to RC from ENG
 * 
 * *****************  Version 20  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Firmware Version 0.7
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 10/02/13   Time: 1:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the release version to 0.6 RC
 * 
 * *****************  Version 18  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:10a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed Error related with Version No processing
 * 
 * *****************  Version 17  *****************
 * User: Dubes        Date: 9/11/13    Time: 2:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Updated the Firmware Version No. and added logic to contain information
 * if it is rc, R, T or Engg build
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 15  *****************
 * User: Dubes        Date: 8/29/13    Time: 1:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_FIRMWARE_VERSION Pcodeand define for
 * FIRMWARE_VERSION 
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:43p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Enabled the frequency counting feature
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 8/15/13    Time: 3:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Just enabled the single shot to allow the interlock to work properly 
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed freq tables from this file because the the frequency of
 * inclution into other files. It is how in a file called "freq_tables.h".
 * Also removed the configuration data and function prototypes
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added two macro defines, one for the HW changes for the change in
 * polarity for the PWM ad the other for the test ports for auto tuning.
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Converted HW selection to Thorite and enabled all tag bands
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added HAFNON define to discriminate between Hafnon and Thorite
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * function prototypes added to support NVM eeprom and service tool
 * features. Added HAFNON and LITTLE_ENDIAN flags. 
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:38a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the configuration DB. This is just a wrapper until Sandeep is
 * complete with his coding
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:45p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a state for auto tuning and fixed a warning for an implict type
 * cast for the tag band table.
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:11a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * implemented the tag band feature
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added data and defines for freq counter feature
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:30p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Enabled the interlock state from endless loop
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
 * User: Galantij     Date: 6/03/13    Time: 1:55p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <compat/ina90.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "utility/compiler.h"
#include "dms_interface.h"
#include "crc.h"

// Always update the version before the new release
// This a 2 byte value with upper byte representing
// major version and lower byte minor version
// For example if major version = 1 and  minor version = 1 then
// the value will be 0X0101, start version is 0X0001
// since the values of major and minor can go up to 99 only as per or release process
// we are going to use combination 1 bit of each byte of Major and Minor to indicate
// one of the following
// •Release (r) - FW has been unit tested, underwent in-house QA testing, and is ready to be deployed in the field. Scheduled release should be planned by the project team and signed off by the project Team lead.
// •Release Candidate (rc) - FW has been unit tested and is in the process of undergoing QA/System testing.  FW could be used for engineering testing, and should not be deployed to the field. rc version FW will eventually become release (r) when all QA/System validation is complete.  Since the FW has not gone through a complete QA cycle, the use of rc in the field should be avoided, and need to be approved by Product manager/ LOB.
// •Service Pack (sp) - the service pack aims at patching a regular release (r), or test release (t).  Patching can mean both new features and bug fixes.
// •Test (t) - FW has been unit-tested and could be used for engineering testing, or very specific deployment. Product manager/LOB/R&D will need to approve field use for this type of build.
// •Engineering (eng) - FW is circulated among engineering team for specific testing only. It is not to be used in deployment.
// of them we will never be producing Service Pack (sp) for this firmware so we can safely ignore that option. The 4 options will have the following bit settings
// The first bit represents the MSB of Major Byte and the Second Bit represents the MSB of minor version.
// 0 0 : Release Candidate (rc) (This just to be consistent since we have already released firmware with version as 0X0001, hence parsing that info will produce rc)
// 0 1 : Release (r)
// 1 0 : Test (t)
// 1 1 : Engineering (eng)
// Example's:
// Major version 1 Minor version 1 and Engineering build the value will be 0X99 : 1001 1001
// Major version 1 Minor version 2 and Release the value will be 0X1B : 0001 1011

// Note: Change These at the time of release to indicate the firmware version
#define MAJOR_FIRMWARE_VERSION	0X01
#define MINOR_FIRMWARE_VERSION	0X0A
// Release Type
// 00  rc
// 01  r
// 10  t
// 11  eng
#define RELEASE_TYPE 0X01

// Logic to set the FIRMWARE_VERSION based on Release Type
#if   RELEASE_TYPE == 0X01

#define FIRMWARE_VERSION	( (MAJOR_FIRMWARE_VERSION << 8 ) | ( MINOR_FIRMWARE_VERSION | 0X80 ) )

#elif RELEASE_TYPE == 0X10

#define FIRMWARE_VERSION	( ( ( MAJOR_FIRMWARE_VERSION | 0X80 ) << 8 ) | MINOR_FIRMWARE_VERSION )

#elif RELEASE_TYPE == 0X11

#define FIRMWARE_VERSION	( ( ( MAJOR_FIRMWARE_VERSION | 0X80 ) << 8 ) | ( MINOR_FIRMWARE_VERSION | 0X80 ) )

#else //RELEASE_TYPE == 0X00

#define FIRMWARE_VERSION	( (MAJOR_FIRMWARE_VERSION << 8 ) | MINOR_FIRMWARE_VERSION )

#endif // end of ifdef

#define CLKOUT				0		// allows output of system clock for testing
//#define USE_AC			0
//#define USE_ADC			0
#define USE_TP				0		// used for test purposes
#define USE_DDS				0 		// Sandeep Using DDS or Not
#define USE_FREQ_COUNT		1 		// Sandeep frequency counter
//#define TEST_HW			0
#define SINGLE_SHOT			1		// allows the system to free run
#define EXTERNAL_16			0
#define HALFNON				0		// flag for Hafnon HW
#define OLD_PWM_HW			0		// inverted PWM for switcher HW
#define TEST_AUTOTUNE		1
#define LITTLE_ENDIAN		1 
#define RAIL_DISCHARGE		1
// The next TBD defines are exclusive using the same TP
// only one at a time can be enabled.
#define LOCKOUT_TEST		0
#define MODE_PROCESS		1      // original method for processing alarms
// Chose between DMS and Hard Switch 0 DMS 1 Hard switch
#define INTERLOCK_CHOICE	0  // Sandeep  is use H/W switch 1 old way 0 is new way
#define PWM_DURING_INTER	1
// 3 type of tuning or two type of tuning
#define THREE_TYPE_TUNING	1 // Sandeep 0 is Old way 1 is new way
#define SEQ_FREQ			1
#define REV_FREQ			0
#define ENABLE_WD			1
#define ENABLE_WD_TICKLE	1

// Evolve Store macro defines
#define PING_ENABLE			1
#define EVOLVESTORE			1
#define SERIAL_NUM			1

//#define DELAY_PULSE			0

extern volatile uint8_t gState;
extern volatile uint32_t dac_test_values;

#define STATE_SLEEP		0
#define STATE_CHARGE	1
#define STATE_TX_CYCLE	2
#define STATE_HOLDOFF	3
#define STATE_RX_CYCLE	4
#define STATE_PROCESS	5
#define STATE_AUTOTUNE	6

#define SET_STATE(x)		gState = x
#define GET_STATE(x)		gState == x

extern volatile uint8_t gAppState;
#define APP_DETECT_STATE	0
#define APP_DEACT_STATE		1

#define SET_APP_STATE(x)	gAppState = x
#define GET_APP_STATE(x)	gAppState == x

#define NO_OF_FREQUENCY_TABLE_VALUES             16

// Sandeep
volatile uint8_t gDACIndexLoaded;
volatile uint16_t *gFrequencyTable;

//#if 0
// RJL Counting the No of Pulses after which we have to 
// have a delay of aprox 40 ms for the pulse pattern to 
// be same as Counter Point 9
volatile uint8_t pulseNumber;
volatile uint8_t frameRateChanged; // Flag to indicate if the frame rate was changed after 5th pulse
//#endif

// Status bit's for DAC
#define DAC_CH0    (1 << 0)                //!< DAC channel 0.
#define DAC_CH1    (1 << 1)                //!< DAC channel 1.

extern volatile uint8_t bAborted;

#if EVOLVESTORE
#define PAYLOAD_GET_STATUS					0
#define PAYLOAD_CLEAR_STATUS				1
#define PAYLOAD_ENABLE_NIGHTSAVE			2
#define PAYLOAD_DISABLE_NIGHTSAVE			3
#define PAYLOAD_KEYSWITCH_ENABLE			4
#define PAYLOAD_KEYSWITCH_DISABLE			5
#define PAYLOAD_MISS_TUNED					6
#define PAYLOAD_TUNED						7
#define PAYLOAD_VOLTAGE_OVER				8
#define PAYLOAD_VOLTAGE_NORMAL				9
#define PAYLOAD_INTERLOCK_ENABLED			10
#define PAYLOAD_INTERLOCK_DISABLED			11
#define PAYLOAD_TX3_ENABLED					12
#define PAYLOAD_TX3_DISABLED				13
#define PAYLOAD_MODE_4						14
#define PAYLOAD_MODE_5						15
#define PAYLOAD_MODE_6						16
#define PAYLOAD_MODE_V						17 // Verify
#define PAYLOAD_GET_ALARM_PING				18
uint16_t buildStatusPayload(uint8_t status);
#endif

// Finds whether the hardware is CPiD or Thoralite and returns
// Global flag:
// 1=CPiD; 0=Thoralite
extern volatile uint8_t CPiD_HW_flag;
// tag response value for the selected deactivation mode.
extern uint8_t tags_before_alarm;

#endif