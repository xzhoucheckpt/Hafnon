/*******************************************************************
 *
 * File name: zircon_config.h
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
 * Creator: Joe Galanti
 *
 * Date Created:
 *
 * $History: zircon_config.h $
 * 
 * *****************  Version 27  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 26  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 5/29/14    Time: 2:45p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed all Detection Rate defaults to 16 tags (extra long)
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 4/01/14    Time: 3:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed holdoff for Mode 6 from 10 to 15 for Lothar and Greg Plizak.
 * This was done because of certain antenna with more ringing.
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 2/27/14    Time: 1:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (In verify mode, 410 tags can be deactivated) . Changed
 * default detection power level for verify mode from 0 to 1. This was
 * suggested by Nimish even though this could deact tags. 
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:29a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (Verify mode kills 410 EP tags). Added a macro define for
 * the new VPA default value for Verify Mode.
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 2/20/14    Time: 5:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the default config setting for new output transformer.
 * 
 * *****************  Version 20  *****************
 * User: Galantij     Date: 1/30/14    Time: 11:29a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new prototype for function now used to write to eeprom right
 * before a DMS session.
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 1/20/14    Time: 11:32a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Updated the macro defines for the default config settings for new HW
 * using the handwound center tap transformer
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:41p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the macro defines to support the new interlock default and TX
 * low power default.
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:20a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the two new DB fields for the new DMS dual TX level controls for
 * the HI/LO switch mapping
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:13p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the new macro defines for the changes to the getConfigInfo()
 * function to support the new GPIO features
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:32a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the default for mode 6 holdoff  from 8 to 10 to stop the false
 * alarming. Added the new flags for the new default config indication.
 * 
 * *****************  Version 14  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:55p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support DMS switch to control Interlock 
 * 
 * *****************  Version 13  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added RESET_WITH_DELAY for the 5 reset condition 
 * Keep-Checked-Out:no
 * 
 * *****************  Version 12  *****************
 * User: Dubes        Date: 10/10/13   Time: 6:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * changed default as per Joeand changed the name to RESET_INDICATOR 
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added defines DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS)and defines
 * for reset condition
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new macro define for tag rate parsing for getConfigInfo()
 * 
 * *****************  Version 9  *****************
 * User: Dubes        Date: 9/24/13    Time: 12:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added Default logic so if the user sets a parameter that is default he
 * will be warned by setting the bit next time he restarts, and added
 * default values.
 * 
 * *****************  Version 8  *****************
 * User: Dubes        Date: 9/23/13    Time: 3:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added CONFIG_PRI_HOLDOFF CONFIG_SEC_HOLDOFF CONFIG_DET_TX_POWER
 * 
 * *****************  Version 7  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased all config_parameters to 2 bytesand some formatting changes.
 * ZIRCON_CONFIG_ANT_TUNE_OVERRIDE and ZIRCON_CONFIG_RX_LEVEL_IND,replaced
 * withZIRCON_CONFIG_ANT_FAULT and ZIRCON_CONFIG_SPARE_1,
 * 
 * *****************  Version 6  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:16a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Default Related Enhancement changes (Default ID 25)
 * 
 * *****************  Version 5  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * ZIRCON_CONFIG_PRI_HOLDOFF,ZIRCON_CONFIG_SEC_HOLDOFF,ZIRCON_CONFIG_DET_T
 * X_POWER added
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 8/23/13    Time: 5:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_HOLD_OFF and ZIRCON_CONFIG_DETECT_VPA_LEVEL
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings, Changed The Tag Rate size
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the ant_tune_current field from 8 bits to 16 bits
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:19p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Reducing resource needs by consoladating
 *
 *****************************************************************/


#ifndef ZIRCON_CONFIG_H_
#define ZIRCON_CONFIG_H_

#include "globals.h"

//Bit Values to Display Values On DMS screen
//Indicates that this is a default value as indicated by firmware
#define DISPLAY_DEFAULT_DMS					0X8000
//Indicates that this is a default value as indicated by firmware
#define DISPLAY_GREY_OUT_DMS				0X4000

// Default Values for the Config Parameters
// Based on switch
#define DEFAULT_PRI_HOLDOFF_MODE6				15 //10  // 7.19 uS
#define DEFAULT_PRI_HOLDOFF_MODE6_LO			15 // 8  // 4.9 uS
//#define DEFAULT_PRI_HOLDOFF_MODE4				5        // 5.09 uS
#define DEFAULT_PRI_HOLDOFF_MODE5				15 //10  // 7.19 uS
#define DEFAULT_PRI_HOLDOFF_VERIFY				3   // 5.14 uS
#define DEFAULT_PRI_HOLDOFF_MODE4				DEFAULT_PRI_HOLDOFF_VERIFY //changed for sending deactivation message

#define DEFAULT_TX_POWER_HI						22  // 35 volts
#define DEFAULT_TX_POWER_LO						8   // 15 volts
#define DEFAULT_DET_TX_POWER					2   // 7 volts
#define DEFAULT_DET_TX_POWER_VERIFY				1
// Hard codded in Firmware
#define DEFAULT_INTLK_DURATION					9   // default 5 secs //0
#define DEFAULT_TAGBAND							0	// 1st transmit table
#define DEFAULT_TX2_ENABLED						0	// disabled
#define DEFAULT_ANT_RELAYS						0X19
#define DEFAULT_FRAME_RATE						0	// 144 Hz
#define DEFAULT_TAG_RATE						0Xff // Detection rate for all modes is 16 tags (extra long)
#define DEFAULT_GPI								0	// input pin disabled
#define DEFAULT_GPO								0	// primary alarm w/sounder
#define DEFAULT_SEC_HOLDOFF						10
#define DEFAULT_INTERLOCK						1	// enabled
// Reset Values
#define RESET_NORMAL							0
#define RESET_SUPPRESS_AUTOTUNE					1
#define NO_RESET_EXIT_DMS_MODE					2
#define RESET_INDICATOR							3
#define RESET_WITH_DELAY						4
// Values for Soft Reset ZIRCON_CONFIG_SOFT_INTERLOCK
#define SOFT_INTERLOCK_DISABLE					0  // this will be the default in all cases
#define SOFT_INTERLOCK_ENABLE					1
#define SOFT_INTERLOCK_ENABLE_TIMED				2

// Storage Structure for the parameters
// Start of storage structure
// database variables

typedef struct EEPROM_Storage
{
	uint16_t techid_low;				// ZIRCON_CONFIG_TECHID_LOW
	uint16_t techid_high;				// ZIRCON_CONFIG_TECHID_HIGH
	uint16_t intlk_duration;			// y ZIRCON_CONFIG_INTLK_DURATION InterLock Duration in the document changed from interlock_per
	uint16_t deact_tagband;				// y ZIRCON_CONFIG_TAGBAND  changed from deact_tag_band
	uint16_t enable_tx_2;				// y ZIRCON_CONFIG_ENABLE_TX2
	uint16_t ant_tune_relays;			// n ZIRCON_CONFIG_ANT_TUNE_RELAYS
	uint16_t ant_tune_current;			// n ZIRCON_CONFIG_ANT_TUNE_CURRENT,  Only Get
	uint16_t ant_fault;					// n ZIRCON_CONFIG_ANT_FAULT
	uint16_t ant_tune_mistune_ind;		// n ZIRCON_CONFIG_ANT_TUNE_MISTUNE_IND
	uint16_t ant_tune_onpowerup;		// n ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP
	uint16_t deact_frame_rate;			// y ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP
	uint16_t tx_power;					// y ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP
	uint16_t tag_rate;					// y ZIRCON_CONFIG_TAG_RATE
	uint16_t intlk_enable;				// y ZIRCON_CONFIG_INTLK_ENABLE changed from  interlock_enable_ind
	uint16_t mode_ind;					// n ZIRCON_CONFIG_MODE_IND
	uint16_t hi_low_ind;				// n ZIRCON_CONFIG_HI_LO_IND
#if EVOLVESTORE
	uint16_t nightsave;					// y ZIRCON_CONFIG_NIGHTSAVE
#else
	uint16_t spare_1;					// y ZIRCON_CONFIG_SPARE_1
#endif
	uint16_t config_gpi;				// y ZIRCON_CONFIG_GPI // Pay attention changed from 8 to 16
	uint16_t config_gpo;				// y ZIRCON_CONFIG_GPO // Pay attention changed from 8 to 16
	uint16_t config_pri_hold_off;		// y ZIRCON_CONFIG_PRI_HOLDOFF
	uint16_t config_sec_hold_off;		// y ZIRCON_CONFIG_SEC_HOLDOFF
	uint16_t config_detect_level;		// y ZIRCON_CONFIG_DET_TX_POWER
	uint16_t config_reset_condition;	// n ZIRCON_CONFIG_RESET
	uint16_t config_hi_power;			// y ZIRCON_CONFIG_HI_POWER 
	uint16_t config_lo_power;			// n ZIRCON_CONFIG_LO_POWER
	uint16_t config_soft_interlock;		// n ZIRCON_CONFIG_SOFT_INTERLOCK
	uint16_t config_enable_alarm;		// n ZIRCON_CONFIG_DISABLE_STATUS

} EEPROM_Storage_Structure ;

extern EEPROM_Storage_Structure config_parameters;
extern uint8_t default_config_flag;
extern volatile uint8_t default_config_handler;

//extern uint8_t write_config_eeprom;

// Sandeep DMS Related functions
/*
** Function: set_parameters
**
** Purpose : This function sets the parameter after reading it from eeprom and dip switches
**			 it also checks if the crc value stored in the eeprom is good as a validity check
**
** Parameters:
**     Input : None
**
**     Return: None
**
**
** Effected IO/HW:	None
**
*/

void set_parameters(void);

/*
** Function:setDefaultValues
**
** Purpose : // Set the default vale for the config parameters
**
** Parameters:
**     Input : None
**
**     Return: None
**
**
** Effected IO/HW:	None
**
*/
void setDefaultValues(void);

/*
** Function: software_reset
**
** Purpose : S/W Reset Related functionality For reseting using firmware
**			 this function is called ones we receive reset signal from DMS
**
** Parameters:
**     Input : None
**
**     Return: None
**
**
** Effected IO/HW:	None
**
*/

void software_reset(void);

/*
** Function: readDipSwitch
**
** Purpose : Reads dip switch for system configuration and sets the
**			configuration DB for the detected values.
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters.hi_low_ind: CE of FCC mode
**					config_parameters.mode_ind: Sets the deactivation Mode
**					config_parameters.intlk_enable: enables/disables interlock
**
** Effected IO/HW:	None
**
*/
void readDipSwitch(void);


/*
** Function: getConfigInfo
**
** Purpose : Retrieves the system configuration data in unsigned shorts using a
**				macro define indicating the config parameter t return.
**
** Parameters:
**     Input : config_para: Macro define indicating which config parameter to return
**							from the system DB.
**
**     Return: The value of the config from the input macro define
**
** Effected Var's:
**
** Effected IO/HW:	None
**
*/
// config DB input parameters (config_para)
#define CONFIG_INTLK_DURATION					0
#define CONFIG_INTLK_RANGE						1
#define CONFIG_TAGBAND							2
#define CONFIG_TX2_ENABLED						3
#define CONFIG_ANT_RELAYS						4
#define CONFIG_TUNE_CURRENT						5
#define CONFIG_ANT_FAULT						6
#define CONFIG_TUNE_MISTUNE						7
#define CONFIG_TUNE_ONPOWERUP					8
#define CONFIG_FRAME_RATE						9
#define CONFIG_TX_POWER							10
#define CONFIG_VERIFY_TAG_RATE					11
#define CONFIG_MODE4_TAG_RATE					12
#define CONFIG_MODE5_TAG_RATE					13
#define CONFIG_MODE6_TAG_RATE					14
#define CONFIG_INTLK_ENABLE						15
#define CONFIG_DEACT_MODE						16
#define CONFIG_HILO_IND							17
#define CONFIG_GPI_APP							18
#define CONFIG_GPI_STATE						19
#define CONFIG_GPO_APP							20
#define CONFIG_GPO_STATE						21
#define CONFIG_PRI_HOLDOFF						22
#define CONFIG_SEC_HOLDOFF						23
#define CONFIG_DET_TX_POWER						24
#define CONFIG_TAG_RATE							25

uint16_t getConfigInfo(uint16_t config_para);


/*
** Function: setDefaultBitAndValues
**
** Purpose : // Set the MSB to 1 to indicate that these are default values
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_paramete's
**
** Effected IO/HW:	None
**
*/
void setDefaultBitAndValues(void);


/*
** Function: setConfigBasedOnDipSwitches
**
** Purpose :	Set the Config values that are dependent on dip switches
**				Set the Config values that are dependent on dip switches
**				This function is only for default flow
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters.tx_power : CE of FCC mode
**					config_parameters.config_detect_level: CE of FCC mode
**					config_parameters.config_pri_hold_off: CE of FCC mode
**
** Effected IO/HW:	None
**
*/
void setDefaultBasedOnDipSwitches(void);

/*
** Function: populateStructureWithSettingsBasedOnDefault
**
** Purpose : // Populate Structure With Settings Based on Default values
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters
**
** Effected IO/HW:	None
**
*/
void populateStructureWithSettingsBasedOnDefault(void);

/*
** Function: calculateCRCAndSave
**
** Purpose : // calculate the CRC and Save
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters
**
** Effected IO/HW:	None
**
*/
void calculateCRCAndSave(void);

/*
** Function: setConfigBasedOnDipSwitchesAndDefault
**
** Purpose : Set the Config values that are dependent on dip switches
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters
**
** Effected IO/HW:	None
**
*/
void setConfigBasedOnDipSwitchesAndDefault(void);

// disables the blue flashing LED if all the config parameters are
// set to default values.
void disableConfigLED(void);

/*
** Function: writeConfigValuestForDMSToEEPROM
**
** Purpose : Write the config values to EEProm for DMS
**
** Parameters:
**     Input : None
**
**     Return: None
**
** Effected Var's:	config_parameters
**
** Effected IO/HW:	None
**
*/
void writeConfigValuestForDMSToEEPROM(void);

#endif /* ZIRCON_CONFIG_H_ */