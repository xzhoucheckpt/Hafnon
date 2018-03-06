/*******************************************************************
 *
 * File name: zircon_config.c
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
 * $History: zircon_config.c $
 * 
 * *****************  Version 42  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 41  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 40  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 39  *****************
 * User: Galantij     Date: 3/27/14    Time: 5:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Took the setting of the auto tune eeprom byte to default because when
 * EEprom is erased the unit would never execute auto tune from the reset
 * button
 * 
 * *****************  Version 38  *****************
 * User: Galantij     Date: 2/25/14    Time: 11:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #80 (Verify mode kills 410 EP tags). Added code to change the
 * VPA's default value depending on the mode switch setting. Mode 4 will
 * remain VPA=2, while Verify Mode is VPA=0 with PWM disabled.
 * 
 * *****************  Version 37  *****************
 * User: Galantij     Date: 2/24/14    Time: 10:46a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments to define what the enum are for each auto tune mode.
 * 
 * *****************  Version 36  *****************
 * User: Galantij     Date: 2/20/14    Time: 5:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the default config settings and found if in Mode 6 and the LO
 * switch position is used, the hold off can be reduced for better
 * detection.
 * 
 * *****************  Version 35  *****************
 * User: Galantij     Date: 1/30/14    Time: 5:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Missed a CRC write in the begininng of the power cycle which still
 * allowed about a 17 mS window where the default config could occurs when
 * rapidly pressing the reset button.
 * 
 * *****************  Version 34  *****************
 * User: Galantij     Date: 1/30/14    Time: 11:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the writing to the eeprom at startup because of defect #69.
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the default for the interlock duration default from 500ms to 5
 * secs
 * 
 * *****************  Version 32  *****************
 * User: Dubes        Date: 12/06/13   Time: 11:36a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Setting the default bits for both HI and Low Powerfor DMS irrespective
 * of Hi Low Switch settings. 
 * Keep-Checked-Out:no
 * 
 * *****************  Version 31  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:19a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Sets the default and DB values for the two new pcodes for the dual DMS
 * TX rail voltage for the HI and LO position on the HI/LO switch.
 * 
 * *****************  Version 30  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed test code and old code supporting the GPIO features.
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed  the "gerConfigInfo()" function to handle the new GPIO config
 * DB
 * 
 * *****************  Version 28  *****************
 * User: Dubes        Date: 11/26/13   Time: 5:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Logic added for dip switch dependent settings , if they are default in
 * one mode they will be default in the other mode also if the dip
 * switches are changed. if they have a value other then default value
 * then that value will be preserved.the values are for grey pad
 * settings.As per Joe 11/26/2013 config_pri_hold_off will only be
 * dependent on mode_ind
 * 
 * *****************  Version 27  *****************
 * User: Dubes        Date: 11/26/13   Time: 1:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added functionality in case we set the default we will have to auto
 * tune again in case of Auto.
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:29a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new flag which tracks the default settings and is cleared if
 * any of the default parameters are changed by the DMS user.
 * 
 * *****************  Version 25  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:55p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support DMS switch to control Interlock 
 * 
 * *****************  Version 24  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added grey out logic and defines DISPLAY_DEFAULT_DMS |
 * DISPLAY_GREY_OUT_DMS)
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed getConfigInfo() to parse out the tag rate per mode selected.
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 9/25/13    Time: 5:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed an issues with the config storage feature
 * 
 * *****************  Version 21  *****************
 * User: Dubes        Date: 9/24/13    Time: 12:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added Default logic so if the user sets a parameter that is default he
 * will be warned by setting the bit next time he restarts.
 * Keep-Checked-Out:no
 * 
 * *****************  Version 20  *****************
 * User: Dubes        Date: 9/23/13    Time: 3:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added CONFIG_PRI_HOLDOFF CONFIG_SEC_HOLDOFF CONFIG_DET_TX_POWER
 * 
 * *****************  Version 19  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased all config_parameters to 2 bytesand some formatting changes.
 * ZIRCON_CONFIG_ANT_TUNE_OVERRIDE and ZIRCON_CONFIG_RX_LEVEL_IND,replaced
 * withZIRCON_CONFIG_ANT_FAULT and ZIRCON_CONFIG_SPARE_1,
 * 
 * *****************  Version 18  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:17a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Default Related Enhancement changes (Default ID 25)
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 9/11/13    Time: 5:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixes defect #13 (verify mode tag response should be med not short)
 * 
 * *****************  Version 16  *****************
 * User: Dubes        Date: 9/06/13    Time: 2:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * config_parameters.tx_power changed from 19 to 26
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 9/06/13    Time: 1:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created code to test if DMS has changed the VPA setting and if not set
 * for either FCC (vpa=10) or CE (vpa=19). This is selected by the dip
 * switch HIGH/LOW. 
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the default values for the new DMS settings, primary and
 * secondary holdoffs and detection VPA level. Also put a hardcode value
 * for the frame rate in case DMS selects the 10Hz frame rate.
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 12  *****************
 * User: Dubes        Date: 8/30/13    Time: 1:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * EEPROM was initialized with wrong pointer and hence wrong values.
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 8/28/13    Time: 3:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Set Joes Hard coded values in Default, and set ifdef to 0
 * 
 * *****************  Version 10  *****************
 * User: Dubes        Date: 8/28/13    Time: 2:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * test code for future use
 * 
 * *****************  Version 9  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:39p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * config_parameters.tag_rate = 0x8a; 
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the default value for the interlock duration from a byte to a
 * short
 * 
 * *****************  Version 7  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings, Changed The Tag Rate size
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:13p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Enabled auto tuning to test verify tuning feature
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed a bug in the getConfigInfo() functions and set the default for
 * manual tuning
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/18/13    Time: 4:55p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed a comment
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed an issue with the default settings. Initially I put the wrong
 * parameter in for the tag rate parameter.
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/09/13    Time: 10:41a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed issue with CRC failing during each power cycle even after the
 * default vaules are generated.
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:19p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Reducing resource needs by consoladating
 * 
 ******************************************************************/

#include "zircon_config.h"
#include "interface.h"
#include "nvm_eeprom.h"
#include "globals.h"
#include "GTimer.h"
#include "alarm.h"

EEPROM_Storage_Structure config_parameters = {0};
uint8_t default_config_flag = 1;
volatile uint8_t default_config_handler = 0xff;

//uint8_t write_config_eeprom = 0;

// Set the default vale for the config parameters
void setDefaultValues(void)
{

	// clear the memory of EEPROM with 0xFF since we want to re tune if we set every thing to default
	//nvm_eeprom_write_byte(EEPROM_ZIRCON_RESET_STORE, 0xFF);

	// As of now all default values are presumed to be zero except for the values below.
	// values below will be written to eeprom explicitly.
	memset(&config_parameters,0,sizeof(config_parameters));
	
	// the size of the data is EEPROM_ZIRCON_CONFIG_END
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &config_parameters, EEPROM_ZIRCON_CONFIG_END );
	
	// Read configuration from dip switches and/or EEprom
	readDipSwitch();

	// non-zero default values
	config_parameters.ant_tune_relays = DEFAULT_ANT_RELAYS;  // 0X19 set for first tag band and CP9 pad
	config_parameters.tag_rate = DEFAULT_TAG_RATE; // all modes have default tag rate of 16
	config_parameters.config_sec_hold_off = DEFAULT_SEC_HOLDOFF; // for detection
	config_parameters.intlk_duration = DEFAULT_INTLK_DURATION;
#if !INTERLOCK_CHOICE
	if(CPiD_HW_flag)  /* Thoralite */
	{
		config_parameters.intlk_enable = DEFAULT_INTERLOCK; // for InterLock
	}
	else
	{
		config_parameters.intlk_enable = 0;
	}
#endif
	// Set the Default Bits in the EEPROM Memory Uncomment when we are ready with support on DMS
	setDefaultBitAndValues();
	// Set the config based on Dip switches
	setDefaultBasedOnDipSwitches();
	// Calculate the new CRC and save
	//calculateCRCAndSave();
	
	// set default flag for LED indication
	default_config_flag = 0;
}

// This function sets the parameter after reading it from eeprom and dip switches
// it also checks if the crc value stored in the eeprom is good as a validity check
void set_parameters(void)
{
#if EVOLVESTORE
	uint8_t nightsave_status;
#endif
	
	// if eeprom got corrupted
	if (!verifyCRC())
	{
		// set the eprom values and reset the values to 0
		setDefaultValues();
	}
	else
	{
		// Will not change
		// Read configuration from dip switches and/or EEprom
		readDipSwitch();
		// Populate the config parameters from the EEPROM
		populateStructureWithSettingsBasedOnDefault();
		// Set the config based on dip switches
		setConfigBasedOnDipSwitchesAndDefault();
#if EVOLVESTORE
		// Check nightsave eeprom byte during powerup and see if the command was set
		// during last power cycle. If so, set local DB and clear eeprom byte for next
		// power cycle.
		// If not 0x01, disable nightsave feature.
		//nvm_eeprom_write_byte(EEPROM_ZIRCON_NIGHTSAVE, 0x01); test code
		nightsave_status = nvm_eeprom_read_byte(EEPROM_ZIRCON_NIGHTSAVE);
		if(nightsave_status == 0x01)
		{
			config_parameters.nightsave = 1;
			nvm_eeprom_write_byte(EEPROM_ZIRCON_NIGHTSAVE, 0xff);
		}
		else
		{
			config_parameters.nightsave = 0;
		}
#endif
		// Calculate the new CRC and save, since some setting may have changed because of changes in dip switch settings
		//calculateCRCAndSave();
	}
	
	
	if(CPiD_HW_flag == LITE_HW)  /* Thoralite */
	{
		config_parameters.enable_tx_2 = 0;
		config_parameters.intlk_enable = 0;
		config_parameters.config_gpi = 0;
		config_parameters.config_gpo = 0;
	}
	if(0 == config_parameters.enable_tx_2)
	{
		buildStatusPayload(PAYLOAD_TX3_DISABLED);
	} else
	{
		buildStatusPayload(PAYLOAD_TX3_ENABLED);
	}
	if(0 == config_parameters.intlk_enable)
	{
		buildStatusPayload(PAYLOAD_INTERLOCK_DISABLED);
	} else
	{
		buildStatusPayload(PAYLOAD_INTERLOCK_ENABLED);
	}	
}

// Global Function
void readDipSwitch(void)
{
	uint8_t dipswitch_results = PORTB.IN;
	uint8_t mode_temp = 0;
	
	// if HW pin is high, VPA is set for high power (CE). If HW pin is
	// low, VPA is set for low power (FCC).
	if((dipswitch_results & (FCC_CE_SW_PIN)) == FCC_CE_SW_PIN)
	{
		config_parameters.hi_low_ind = 1;
	}
	else
	{
		config_parameters.hi_low_ind = 0;
	}
	
	// Need to interpret both ModeSel_0 and ModeSel_1 to decode deactivation
	// mode. Save values of HW to temp and set to the appropriate mode
	if((dipswitch_results & (MODE_SEL0_SW_PIN)) == MODE_SEL0_SW_PIN)
	{
		mode_temp = 0x01;
	}
	else
	{
		mode_temp = 0x00;
	}
	
	if((dipswitch_results & (MODE_SEL1_SW_PIN)) == MODE_SEL1_SW_PIN)
	{
		mode_temp |= 0x02;
	}
	
	switch(mode_temp)
	{
		case 0x00:
			config_parameters.mode_ind = DEACT_MODE6;
			buildStatusPayload(PAYLOAD_MODE_6);
		break;
		
		case 0x01:
			config_parameters.mode_ind = DEACT_MODE4;
			buildStatusPayload(PAYLOAD_MODE_4);
		break;
		
		case 0x02:
			if(CPiD_HW_flag)
			{
				config_parameters.mode_ind = DEACT_VERIFY;
				buildStatusPayload(PAYLOAD_MODE_V);
			}
			else
			{
				config_parameters.mode_ind = DEACT_MODE4;
				buildStatusPayload(PAYLOAD_MODE_4);
			}
		break;
		
		case 0x03:
			config_parameters.mode_ind = DEACT_MODE5;
			buildStatusPayload(PAYLOAD_MODE_5);
		break;
		
		default:
		break;
	}

#if INTERLOCK_CHOICE
	// if HW pin is high, interlock is disabled. If HW pin is
	// low, interlock is enabled.
	if((dipswitch_results & (INTLK_EN_SW_PIN)) == INTLK_EN_SW_PIN)
	{
		config_parameters.intlk_enable = 0;
	}
	else
	{
		config_parameters.intlk_enable = 1;
	}
#endif
}

// Global Function
uint16_t getConfigInfo(uint16_t config_para)
{
	uint16_t return_config = 0xffff;
	
	switch(config_para)
	{
		case CONFIG_INTLK_DURATION:
		return_config = ((config_parameters.intlk_duration) & 0x00ff); break;
		
		case CONFIG_INTLK_RANGE:
		return_config = (((config_parameters.intlk_duration) >> 8) & 0x00ff); break;
		
		case CONFIG_TAGBAND:
		return_config = config_parameters.deact_tagband; break;
		
		case CONFIG_TX2_ENABLED:
		return_config = config_parameters.enable_tx_2; break;
		
		case CONFIG_ANT_RELAYS:
		return_config = config_parameters.ant_tune_relays; break;
		
		case CONFIG_TUNE_CURRENT:
		return_config = config_parameters.ant_tune_current; break;
		
		case CONFIG_ANT_FAULT:
		return_config = config_parameters.ant_fault; break;
		
		case CONFIG_TUNE_MISTUNE:
		return_config = config_parameters.ant_tune_mistune_ind; break;
		
		// AutoTune Modes
		// 0="AUTO TUNE"
		// 1="MANUAL TUNE"
		// 2="AUTO TUNE ON POWER UP"
		case CONFIG_TUNE_ONPOWERUP:
		return_config = config_parameters.ant_tune_onpowerup; break;
		
		case CONFIG_TAG_RATE:
		
			switch(config_parameters.mode_ind)
			{
				case DEACT_MODE4:
					return_config = (2<<(((config_parameters.tag_rate) >> 2) & 0x0003));
				break;
				
				case DEACT_MODE5:
					return_config = (2<<(((config_parameters.tag_rate) >> 4) & 0x0003));
				break;
				
				case DEACT_MODE6:
					return_config = (2<<(((config_parameters.tag_rate) >> 6) & 0x0003));
				break;
				
				case DEACT_VERIFY:
					return_config = (2<<((config_parameters.tag_rate) & 0x0003));
				break;
			}
		break;

		case CONFIG_FRAME_RATE:
		return_config = config_parameters.deact_frame_rate; break;
		
		case CONFIG_TX_POWER:
		return_config = config_parameters.tx_power; break;
		
		case CONFIG_INTLK_ENABLE:
		return_config = config_parameters.intlk_enable; break;
		
		case CONFIG_DEACT_MODE:
		return_config = config_parameters.mode_ind; break;
		
		case CONFIG_HILO_IND:
		return_config = config_parameters.hi_low_ind; break;
		
		case CONFIG_GPI_APP:
		return_config = ((config_parameters.config_gpi) & 0x00ff); break;
		
		case CONFIG_GPI_STATE:
		return_config = (((config_parameters.config_gpi) >> 8) & 0x00ff); break;
		
		case CONFIG_GPO_APP:
		return_config = ((config_parameters.config_gpo) & 0x00ff); break;
		
		case CONFIG_GPO_STATE:
		return_config = (((config_parameters.config_gpo) >> 8) & 0x00ff); break;
		break;
		
		case  CONFIG_PRI_HOLDOFF:
		return_config = config_parameters.config_pri_hold_off; break;
				
		case CONFIG_SEC_HOLDOFF:
		return_config = config_parameters.config_sec_hold_off; break;
						
		case CONFIG_DET_TX_POWER:
		return_config = config_parameters.config_detect_level; break;
		
		default:
		break;
	}
	
	return(return_config);
}

// For reseting using firmware
// this function is called ones we receive reset signal from DMS

void software_reset(void)
{
	// if the software reset has not being called
	// set the S/W reset bit
	// Clear the reset bit, only then we can reset it again
	RST.STATUS = RST_SRF_bm;
	//	if ( 0 == (RST.STATUS & RST_SRF_bm) )
	{
		// RST.CTRL = RST_SWRST_bm ;  // Software Reset bit mask, protected by Configuration Change Protection hence:
		ccp_write_io((void*)&RST.CTRL, RST_SWRST_bm);
		while (1) {
			/* Intentionally empty. */
		}
	}
}

// Set the MSB to 1 to indicate that these are default values
void setDefaultBitAndValues(void)
{
	// Set Non zero values and the default Bit
	// No indication of default for config_parameters.ant_tune_relays since it will change in auto tune function
	// Not to be shown as default value since it will get corrected by the Autotune function always
	/*
	Set_bits(config_parameters.ant_tune_relays, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS, &config_parameters.ant_tune_relays, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.ant_tune_relays, DISPLAY_DEFAULT_DMS);
	*/
	Set_bits(config_parameters.tag_rate, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAG_RATE, &config_parameters.tag_rate , 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.tag_rate, DISPLAY_DEFAULT_DMS);
	Set_bits(config_parameters.config_sec_hold_off, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF, &config_parameters.config_sec_hold_off, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.config_sec_hold_off, DISPLAY_DEFAULT_DMS);
	// For setting The interlock
#if !INTERLOCK_CHOICE
	Set_bits(config_parameters.intlk_enable, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTERLOCK, &config_parameters.intlk_enable, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.intlk_enable, DISPLAY_DEFAULT_DMS);
#endif

	Set_bits(config_parameters.intlk_duration, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration , 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.intlk_duration, DISPLAY_DEFAULT_DMS);
	
	//Will be set based on switch  see the function setConfigBasedOnDipSwitches
/*
	Set_bits(config_parameters.tx_power, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TX_POWER, &config_parameters.tx_power, 2);// Write 2 byte  data to EEPROM
	//Will be set based on switch
	Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
	//Will be set based on switch
	Set_bits(config_parameters.config_detect_level, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2);// Write 2 byte  data to EEPROM
*/		
	
	// Set the Bits for Parameters that are Zeros
//	Set_bits(config_parameters.intlk_duration, DISPLAY_DEFAULT_DMS);
//	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration, 2);// Write 2 byte  data to EEPROM
//	Clr_bits(config_parameters.intlk_duration, DISPLAY_DEFAULT_DMS);	
	Set_bits( config_parameters.deact_tagband, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAGBAND, & config_parameters.deact_tagband, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.deact_tagband, DISPLAY_DEFAULT_DMS);
	Set_bits(config_parameters.enable_tx_2, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.enable_tx_2, DISPLAY_DEFAULT_DMS);
	Set_bits(config_parameters.deact_frame_rate, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.deact_frame_rate, DISPLAY_DEFAULT_DMS);
	Set_bits(config_parameters.config_gpi, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPI, &config_parameters.config_gpi, 2); // just copy the Data from EEPROM
	Clr_bits(config_parameters.config_gpi, DISPLAY_DEFAULT_DMS);
	Set_bits(config_parameters.config_gpo, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2); // just copy the Data from EEPROM
	Clr_bits(config_parameters.config_gpo, DISPLAY_DEFAULT_DMS);

}

//  Set the Config values that are dependent on dip switches
//  Set the Config values that are dependent on dip switches
// This function is only for default flow

void setDefaultBasedOnDipSwitches(void)
{

	switch(config_parameters.mode_ind)
	{
		case DEACT_MODE6:
			if(config_parameters.hi_low_ind == 1)
			{
				config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE6;
			}
			else
			{
				config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE6_LO;
			}
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER;
		break;
		
		case DEACT_MODE4:  
			config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE4;
			//config_parameters.config_detect_level = DEFAULT_DET_TX_POWER;
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER_VERIFY;//changed for sending deactivation message
			
		break;
		
		case DEACT_VERIFY:
		//case DEACT_MODE4:
			config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_VERIFY;
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER_VERIFY;
			
			// Disable the 10Hz mode and Second transmitter selection in Verify Mode
			Set_bits(config_parameters.enable_tx_2, DISPLAY_GREY_OUT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);// Write 2 byte  data to EEPROM
			Clr_bits(config_parameters.enable_tx_2, DISPLAY_GREY_OUT_DMS);
			Set_bits(config_parameters.deact_frame_rate, DISPLAY_GREY_OUT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);// Write 2 byte  data to EEPROM
			Clr_bits(config_parameters.deact_frame_rate, DISPLAY_GREY_OUT_DMS);
		break;
		
		case DEACT_MODE5:
			config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE5;
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER;
		break;
		
		default:
			config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE6;
		break;
	}
	
	Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);

	config_parameters.config_hi_power = DEFAULT_TX_POWER_HI;
	Set_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
	
	config_parameters.config_lo_power = DEFAULT_TX_POWER_LO;
	Set_bits(config_parameters.config_lo_power, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.config_lo_power, DISPLAY_DEFAULT_DMS);
	
	// Copy the correct value to tx_power based on switch
	if (config_parameters.hi_low_ind)
	{
		config_parameters.tx_power = config_parameters.config_hi_power; // DEFAULT_TX_POWER_HI;
	}
	else
	{
		config_parameters.tx_power = config_parameters.config_lo_power; // DEFAULT_TX_POWER_LO;
	}

	//config_parameters.config_detect_level = DEFAULT_DET_TX_POWER;
	Set_bits(config_parameters.config_detect_level, DISPLAY_DEFAULT_DMS);
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2);// Write 2 byte  data to EEPROM
	Clr_bits(config_parameters.config_detect_level, DISPLAY_DEFAULT_DMS);
}

 //populate the structure with settings
// Populate Structure With Settings Based on Default values
void populateStructureWithSettingsBasedOnDefault(void){

	// populate the structure with the eeprom values
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration, 2);
	Clr_bits(config_parameters.intlk_duration,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_INTLK_DURATION != config_parameters.intlk_duration )
	{
		default_config_flag = 0;
	}
	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_TAGBAND, &config_parameters.deact_tagband, 2);
	Clr_bits(config_parameters.deact_tagband,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_TAGBAND != config_parameters.deact_tagband )
	{
		default_config_flag = 0;
	}

#if !INTERLOCK_CHOICE
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_INTERLOCK, &config_parameters.intlk_enable, 2);
	Clr_bits(config_parameters.intlk_enable,DISPLAY_DEFAULT_DMS);
	if (( DEFAULT_INTERLOCK != config_parameters.intlk_enable ) && (CPiD_HW_flag))  /* Thoralite */
	{
		default_config_flag = 0;
	}
#endif
/*	// Dependent on dip switches now
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);
	Clr_bits(config_parameters.enable_tx_2,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_TX2_ENABLED == config_parameters.enable_tx_2 )
	{
		Set_bits(config_parameters.enable_tx_2, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);
		Clr_bits(config_parameters.enable_tx_2,DISPLAY_DEFAULT_DMS);
	}
*/	
	// We dont have to show the default value since this will always get changed by Auto tune function
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS, &config_parameters.ant_tune_relays, 2);
	
	// This is a dynamic value to be filled by auto tune function, no need to read from EEPROM
	//nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_FAULT, &config_parameters.ant_fault, 2);
	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP, &config_parameters.ant_tune_onpowerup, 2);

/*	// Dependent on dip switches now
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);
	Clr_bits(config_parameters.deact_frame_rate,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_FRAME_RATE == config_parameters.deact_frame_rate )
	{
		Set_bits(config_parameters.deact_frame_rate, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);
		Clr_bits(config_parameters.deact_frame_rate,DISPLAY_DEFAULT_DMS);
	}
*/	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_TAG_RATE, &config_parameters.tag_rate, 2);
	Clr_bits(config_parameters.tag_rate,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_TAG_RATE != config_parameters.tag_rate )
	{
		default_config_flag = 0;
	}
	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF, &config_parameters.config_sec_hold_off, 2);
	Clr_bits(config_parameters.config_sec_hold_off,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_SEC_HOLDOFF != config_parameters.config_sec_hold_off )
	{
		default_config_flag = 0;
	}
	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_GPI, &config_parameters.config_gpi, 2);
	Clr_bits(config_parameters.config_gpi,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_GPI != config_parameters.config_gpi )
	{
		default_config_flag = 0;
	}
	
	// 2 bytes
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2);
	Clr_bits(config_parameters.config_gpo,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_GPO != config_parameters.config_gpo )
	{
		default_config_flag = 0;
	}

	// get the reset condition
	// get the reset condition
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);
	/*
	if ( RESET_SUPPRESS_AUTOTUNE == config_parameters.config_reset_condition )
	{
		config_parameters.config_reset_condition = RESET_NORMAL;
		// Reset it in EEPROM immediately
		//nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);// Write 2 byte  data to EEPROM
		//calculateCRCAndSave();
		//config_parameters.config_reset_condition = RESET_SUPPRESS_AUTOTUNE;		// Manual Tuning
	}
	else
	{
		config_parameters.config_reset_condition = RESET_NORMAL;
	}
	*/
	config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;	
}

// calculate the CRC and Save
inline void calculateCRCAndSave(void)
{
	uint16_t calc_crc = 0; //--> for test eeprom_crc = 0;

	// calculate the new crc value
	calc_crc =  calculateCrcEeprom();
	// write it back
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2) ;// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2

	// For Test --> nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2); // just copy the CRC
}


//  Set the Config values that are dependent on dip switches
void setConfigBasedOnDipSwitchesAndDefault(void)
{

	// As per Joe 11/26/2013 config_pri_hold_off will only be dependent on mode_ind
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2); // just copy the Data from EEPROM

	switch(config_parameters.mode_ind)
	{
		case DEACT_MODE6:
		
			if( (config_parameters.config_pri_hold_off & DISPLAY_DEFAULT_DMS) || (config_parameters.config_pri_hold_off & DISPLAY_GREY_OUT_DMS) )
			{
				if(config_parameters.hi_low_ind == 1)
				{
					config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE6;
				}
				else
				{
					config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE6_LO;
				}
			}

			if(config_parameters.hi_low_ind == 1)
			{		
				if (DEFAULT_PRI_HOLDOFF_MODE6 != config_parameters.config_pri_hold_off)
				{
					default_config_flag = 0;
				}
			}
			else
			{
				if (DEFAULT_PRI_HOLDOFF_MODE6_LO != config_parameters.config_pri_hold_off)
				{
					default_config_flag = 0;
				}				
			}
		
		break;
		case DEACT_MODE4:
		
			if( (config_parameters.config_pri_hold_off & DISPLAY_DEFAULT_DMS) || (config_parameters.config_pri_hold_off & DISPLAY_GREY_OUT_DMS) )
			{
				config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE4;
			}
					
			if (DEFAULT_PRI_HOLDOFF_MODE4 != config_parameters.config_pri_hold_off )
			{
				default_config_flag = 0;
			}

		break;
		case DEACT_VERIFY:

			if( (config_parameters.config_pri_hold_off & DISPLAY_DEFAULT_DMS) || (config_parameters.config_pri_hold_off & DISPLAY_GREY_OUT_DMS) )
			{
				config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_VERIFY;
			}
					
			if (DEFAULT_PRI_HOLDOFF_VERIFY != config_parameters.config_pri_hold_off )
			{
				default_config_flag = 0;
			}

		break;
		case DEACT_MODE5:

			if( (config_parameters.config_pri_hold_off & DISPLAY_DEFAULT_DMS) || (config_parameters.config_pri_hold_off & DISPLAY_GREY_OUT_DMS) )
			{
				config_parameters.config_pri_hold_off = DEFAULT_PRI_HOLDOFF_MODE5;
			}
			
			if (DEFAULT_PRI_HOLDOFF_MODE5 != config_parameters.config_pri_hold_off )
			{
				default_config_flag = 0;
			}

		break;
		default:

			if( (config_parameters.config_pri_hold_off & DISPLAY_DEFAULT_DMS) || (config_parameters.config_pri_hold_off & DISPLAY_GREY_OUT_DMS) )
			{
				config_parameters.config_pri_hold_off =  DEFAULT_PRI_HOLDOFF_MODE6;
			}
			
			if (DEFAULT_PRI_HOLDOFF_MODE6 != config_parameters.config_pri_hold_off )
			{
				default_config_flag = 0;
			}
		
		break;
	}
	// Clear all the Bits here
	Clr_bits(config_parameters.config_pri_hold_off, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	
	if( DEACT_VERIFY == config_parameters.mode_ind)
	{
		// Disable the 10Hz mode and Second transmitter selection in Verify Mode
		// Set the defaults and disable in case they are not already defaults
		config_parameters.enable_tx_2 = DEFAULT_TX2_ENABLED	;
		config_parameters.deact_frame_rate = DEFAULT_FRAME_RATE;
	}
	else
	{
		nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);

		if( (config_parameters.enable_tx_2 & DISPLAY_DEFAULT_DMS) || (config_parameters.enable_tx_2 & DISPLAY_GREY_OUT_DMS) )
		{
			config_parameters.enable_tx_2 = DEFAULT_TX2_ENABLED;
		}
		else
		{
			default_config_flag = 0;
		}
		
		nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);

		if( (config_parameters.deact_frame_rate & DISPLAY_DEFAULT_DMS) || (config_parameters.deact_frame_rate & DISPLAY_GREY_OUT_DMS) )
		{
			config_parameters.deact_frame_rate = DEFAULT_FRAME_RATE;

		}
		else
		{
			default_config_flag = 0;
		}
		
	}
	// Clear all the bits here
	Clr_bits(config_parameters.enable_tx_2, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	Clr_bits(config_parameters.deact_frame_rate, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

	// Hi Power
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2); // just copy the Data from EEPROM
	Clr_bits(config_parameters.config_hi_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	if (DEFAULT_TX_POWER_HI != config_parameters.config_hi_power )
	{
		default_config_flag = 0;
	}
	// Clear all the bits here
	Clr_bits(config_parameters.config_hi_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	
	// Low Power
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2); // just copy the Data from EEPROM
	Clr_bits(config_parameters.config_lo_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	if (DEFAULT_TX_POWER_LO != config_parameters.config_lo_power )
	{
		default_config_flag = 0;
	}
	// Clear all the bits here
	Clr_bits(config_parameters.config_lo_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	
	// Switch based on Hi Low switch
	if (config_parameters.hi_low_ind)
	{
		// Copy based on switch
		config_parameters.tx_power = config_parameters.config_hi_power;
	}
	else
	{
		// Copy based on switch
		config_parameters.tx_power = config_parameters.config_lo_power;
	}

	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2); // just copy the Data from EEPROM

	if( (config_parameters.config_detect_level & DISPLAY_DEFAULT_DMS) || (config_parameters.config_detect_level & DISPLAY_GREY_OUT_DMS) )
	{
		if((config_parameters.mode_ind == DEACT_VERIFY) || (config_parameters.mode_ind == DEACT_MODE4))
		{
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER_VERIFY;
		}
		else
		{
			config_parameters.config_detect_level = DEFAULT_DET_TX_POWER;
		}
	}
	else
	{
		default_config_flag = 0;
	}
	
	Clr_bits(config_parameters.config_detect_level,(DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
}

void disableConfigLED(void)
{
	uint8_t intlk_signal_state = 0;
	uint8_t interlock_led_on = 0;
	
	//default_config_flag = 1;
	if(config_parameters.intlk_enable)
	{
		intlk_signal_state = PORTE.IN;
		if(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
		(SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock))
		{
			interlock_led_on = 1;
		}
	}
	// sandeep The code to display the correct LED is in defaultConfigBlinkingOff 
	defaultConfigBlinkingOff(interlock_led_on);
	
	if(default_config_handler < G_TIMER_MAX_SLOT)
	{
		GTimer_unRegisterCB(default_config_handler);
	}
	
	// sandeep put your code here for the not tuned error
	//write_config_eeprom = 1;
}

 //populate the structure with settings
// Populate Structure With Settings Based on Default values
void writeConfigValuestForDMSToEEPROM(void){

	if ( DEFAULT_INTLK_DURATION == config_parameters.intlk_duration )
	{
		Set_bits(config_parameters.intlk_duration, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.intlk_duration,DISPLAY_DEFAULT_DMS);
	}
	
	if ( DEFAULT_TAGBAND == config_parameters.deact_tagband )
	{
		Set_bits(config_parameters.deact_tagband, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAGBAND, &config_parameters.deact_tagband, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.deact_tagband,DISPLAY_DEFAULT_DMS);
	}

#if !INTERLOCK_CHOICE

	if ( DEFAULT_INTERLOCK == config_parameters.intlk_enable )
	{
		Set_bits(config_parameters.intlk_enable, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTERLOCK, &config_parameters.intlk_enable, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.intlk_enable,DISPLAY_DEFAULT_DMS);
	}

#endif
	
	if ( DEFAULT_TAG_RATE == config_parameters.tag_rate )
	{
		Set_bits(config_parameters.tag_rate, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAG_RATE, &config_parameters.tag_rate, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.tag_rate,DISPLAY_DEFAULT_DMS);
	}

	
	if ( DEFAULT_SEC_HOLDOFF == config_parameters.config_sec_hold_off )
	{
		Set_bits(config_parameters.config_sec_hold_off, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF, &config_parameters.config_sec_hold_off, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.config_sec_hold_off,DISPLAY_DEFAULT_DMS);
	}


	if ( DEFAULT_GPI == config_parameters.config_gpi )
	{
		Set_bits(config_parameters.config_gpi, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPI, &config_parameters.config_gpi, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.config_gpi,DISPLAY_DEFAULT_DMS);
	}
	
	// 2 bytes
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2);
	Clr_bits(config_parameters.config_gpo,DISPLAY_DEFAULT_DMS);
	if ( DEFAULT_GPO == config_parameters.config_gpo )
	{
		Set_bits(config_parameters.config_gpo, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2);
		//calculateCRCAndSave();
		Clr_bits(config_parameters.config_gpo,DISPLAY_DEFAULT_DMS);
	}

/*
	// get the reset condition
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);
	if ( RESET_SUPPRESS_AUTOTUNE == config_parameters.config_reset_condition )
	{
		config_parameters.config_reset_condition = RESET_NORMAL;
		// Reset it in EEPROM immediately
		//nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);// Write 2 byte  data to EEPROM
		//calculateCRCAndSave();
		//config_parameters.config_reset_condition = RESET_SUPPRESS_AUTOTUNE;		// Manual Tuning
	}
	else
	{
		config_parameters.config_reset_condition = RESET_NORMAL;
	}
*/	

	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);// Write 2 byte  data to EEPROM
// Writing values based on dip switches


	switch(config_parameters.mode_ind)
	{
		case DEACT_MODE6:
		
			if(config_parameters.hi_low_ind == 1)
			{
				if (DEFAULT_PRI_HOLDOFF_MODE6 == config_parameters.config_pri_hold_off )
				{
					Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
					nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
				}
			}
			else
			{
				if (DEFAULT_PRI_HOLDOFF_MODE6_LO == config_parameters.config_pri_hold_off )
				{
					Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
					nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
				}				
			}
		
		break;
		case DEACT_MODE4:
		
			if (DEFAULT_PRI_HOLDOFF_MODE4 == config_parameters.config_pri_hold_off )
			{
				Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
			}
		break;
		
		case DEACT_VERIFY:

			if (DEFAULT_PRI_HOLDOFF_VERIFY == config_parameters.config_pri_hold_off )
			{
				Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
			}
		break;
		
		case DEACT_MODE5:

			if (DEFAULT_PRI_HOLDOFF_MODE5 == config_parameters.config_pri_hold_off )
			{
				Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
			}

		break;
		default:

			if (DEFAULT_PRI_HOLDOFF_MODE6 == config_parameters.config_pri_hold_off )
			{
				Set_bits(config_parameters.config_pri_hold_off, DISPLAY_DEFAULT_DMS);
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
			}
		
		break;
	}

	// Clear all the Bits here
	Clr_bits(config_parameters.config_pri_hold_off, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));	
	
	if( DEACT_VERIFY == config_parameters.mode_ind)
	{
		Set_bits(config_parameters.enable_tx_2, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);// Write 2 byte  data to EEPROM

		Set_bits(config_parameters.deact_frame_rate, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);// Write 2 byte  data to EEPROM

	}
	else
	{

		if( config_parameters.enable_tx_2 == DEFAULT_TX2_ENABLED )
		{
			Set_bits(config_parameters.enable_tx_2, DISPLAY_DEFAULT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);
		}
		
		if( config_parameters.deact_frame_rate == DEFAULT_FRAME_RATE )
		{
			Set_bits(config_parameters.deact_frame_rate, DISPLAY_DEFAULT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);
		}
		
	}
	// Clear all the bits here
	Clr_bits(config_parameters.enable_tx_2, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	Clr_bits(config_parameters.deact_frame_rate, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

	// Hi Power
	if (DEFAULT_TX_POWER_HI == config_parameters.config_hi_power )
	{
		Set_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);// Write 2 byte  data to EEPROM
		Clr_bits(config_parameters.config_hi_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	}
	
	// Low Power
	if (DEFAULT_TX_POWER_LO == config_parameters.config_lo_power )
	{
		Set_bits(config_parameters.config_lo_power, DISPLAY_DEFAULT_DMS);
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);// Write 2 byte  data to EEPROM
		Clr_bits(config_parameters.config_lo_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
	}

	// Clear all the bits here
	
	
	// Switch based on Hi Low switch
	if (config_parameters.hi_low_ind)
	{
		// Copy based on switch
		config_parameters.tx_power = config_parameters.config_hi_power;
	}
	else
	{
		// Copy based on switch
		config_parameters.tx_power = config_parameters.config_lo_power;
	}


	if(config_parameters.mode_ind == DEACT_VERIFY)
	{
		if( config_parameters.config_detect_level == DEFAULT_DET_TX_POWER_VERIFY )
		{
			Set_bits(config_parameters.config_detect_level, DISPLAY_DEFAULT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2);// Write 2 byte  data to EEPROM
			Clr_bits(config_parameters.config_detect_level,(DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
		}
	}
	else
	{
		if( config_parameters.config_detect_level == DEFAULT_DET_TX_POWER )
		{
			Set_bits(config_parameters.config_detect_level, DISPLAY_DEFAULT_DMS);
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2);// Write 2 byte  data to EEPROM
			Clr_bits(config_parameters.config_detect_level,(DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
		}
	}
	
	calculateCRCAndSave();
	
}



