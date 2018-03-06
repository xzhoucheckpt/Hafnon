/*
 * dms_interface.h
 *
 * Created: 6/4/2013 5:03:14 PM
 *  Author: dubes
 *
 * $History: dms_interface.h $
 * 
 * *****************  Version 20  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 11/12/14   Time: 9:48a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new Pcode (ZIRCON_REQ_INPROGRESS) to handle a delay between the
 * Evolve reader and the EvolveStore network (EvolveStore). This Pcode is
 * not used by the CPiD
 * 
 * *****************  Version 18  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:05p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Just commented the Pcode table to be able to index more easy.
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:14a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the new pcodes to support the dual sliders for the HI and LO
 * power adjustment.
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed old prototype functions used to support the GPIO features
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * commented out prototypes for the old GPOI feature functions
 * 
 * *****************  Version 13  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:51p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * changed ZIRCON_CONFIG_INTLK_ENABLE_INDto
 * ZIRCON_CONFIG_INTLK_ENABLEadded EEPROM_ZIRCON_CONFIG_INTERLOCK place
 * holder for EEPROM
 * 
 * *****************  Version 12  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added DMS DISCONNECT INDICATION for bAborted
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * added EEPROM_ZIRCON_CONFIG_RESET_CONDITION to store reset on startup
 * 
 * *****************  Version 10  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * ZIRCON_CONFIG_ANT_TUNE_OVERRIDE and ZIRCON_CONFIG_RX_LEVEL_IND,replaced
 * withZIRCON_CONFIG_ANT_FAULT and ZIRCON_CONFIG_SPARE_1,
 * 
 * *****************  Version 9  *****************
 * User: Dubes        Date: 8/29/13    Time: 1:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_FIRMWARE_VERSION Pcode
 * 
 * *****************  Version 8  *****************
 * User: Dubes        Date: 8/28/13    Time: 2:14p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Set the ZIRCON_CONFIG_END to new boundary
 * 
 * *****************  Version 7  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * ZIRCON_CONFIG_PRI_HOLDOFF, ZIRCON_CONFIG_SEC_HOLDOFF,
 * ZIRCON_CONFIG_DET_TX_POWER added
 * 
 * *****************  Version 6  *****************
 * User: Dubes        Date: 8/23/13    Time: 5:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_HOLD_OFF and ZIRCON_CONFIG_DETECT_VPA_LEVEL
 * 
 * *****************  Version 5  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings, Changed The Tag Rate size
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:31p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed config DB and place in config new header file
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Set a area after the configuration in the eeprom to store data for
 * autotuning.
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed buffer size from 55 to 52 because of excess bytes being sent.
 * The packet size is fixed to 52 bytes
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:08p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Added files to support DMS tool
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 7/07/13    Time: 6:44p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * 1.The functionality related with DMS interface and GPIO is     unit
 * tested and checked in2.Test Code Commented out
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 7/05/13    Time: 4:37p
 * Updated in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * Final Tested Code , This Code is Functionally complete with 7 Test Cases
 * Should be used for Debug if we have problem
 * 
 * *****************  Version 1  *****************
 * User: Dubes        Date: 7/04/13    Time: 1:18p
 * Created in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * DMS interface code with the Test Code test cases are listed in main
 * while loop Cases 1 to 6
 */ 

#include "lowlevel.h"
#include "autotune.h"

#ifndef DMS_INTERFACE_H_
#define DMS_INTERFACE_H_


#define bswap16(x) ((x)>>8 | ((x)&255)<<8) 

#define bswap32(x) ((bswap16((x)>>16)&65535)|(bswap16((x)&65535)<<16))


// Only the Zircon related PCODES and CCODES are taken from codes.h
// the size is 55 since to flush all the 52 bytes we need 
//#define  COM_BUF_SIZE 55  JRG_HW
#define  COM_BUF_SIZE 52

#define TECHID_LEN 32

// Enumerations not working in case statement so changed to defines
//Parameter Codes
typedef enum
{

//*************************************
// Start Zircon pcodes  JRG_DEACT
//*************************************
	ZIRCON_CONFIG_START = 0X3D00,
	ZIRCON_CONFIG_TECHID_LOW = ZIRCON_CONFIG_START,
	ZIRCON_CONFIG_TECHID_HIGH,
	ZIRCON_CONFIG_INTLK_DURATION,
	ZIRCON_CONFIG_TAGBAND,
	ZIRCON_CONFIG_ENABLE_TX2,
	ZIRCON_CONFIG_ANT_TUNE_RELAYS,
	ZIRCON_CONFIG_ANT_TUNE_CURRENT,
	ZIRCON_CONFIG_ANT_FAULT,
	ZIRCON_CONFIG_ANT_TUNE_MISTUNE_IND,
	ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP,  //0x3d09
	ZIRCON_CONFIG_FRAME_RATE,
	ZIRCON_CONFIG_HI_POWER,
	ZIRCON_CONFIG_TAG_RATE,
	ZIRCON_CONFIG_RESET,
	ZIRCON_CONFIG_INTERLOCK,
	ZIRCON_CONFIG_MODE_IND,
	ZIRCON_CONFIG_HI_LO_IND,  //0x3d10
	ZIRCON_CONFIG_NIGHTSAVE,
	ZIRCON_CONFIG_PING,
	ZIRCON_CONFIG_CONNECT,
	ZIRCON_CONFIG_DEFAULT,
	ZIRCON_CONFIG_GPI,
	ZIRCON_CONFIG_GPO,
	ZIRCON_GENERIC_NACK,
	ZIRCON_CONFIG_PRI_HOLDOFF,
	ZIRCON_CONFIG_SEC_HOLDOFF,
	ZIRCON_CONFIG_DET_TX_POWER,
	ZIRCON_CONFIG_FIRMWARE_VERSION,
	ZIRCON_CONFIG_LO_POWER ,  //0x3d1c
	ZIRCON_CONFIG_DEVICE_ID_LO,
	ZIRCON_CONFIG_DEVICE_ID_HI,
	ZIRCON_CONFIG_STATUS,
	ZIRCON_CONFIG_SERIAL_NUM0, //0x3d20
	ZIRCON_CONFIG_SERIAL_NUM1,
	ZIRCON_CONFIG_SERIAL_NUM2,
	ZIRCON_CONFIG_SERIAL_NUM3,
	ZIRCON_CONFIG_SERIAL_NUM4,
	ZIRCON_CONFIG_SERIAL_NUM5,
	ZIRCON_CONFIG_BOARD_TYPE,  //0x3d26  Thoralite	
	ZIRCON_REQ_INPROGRESS,
	ZIRCON_CONFIG_SOFT_INTERLOCK,
	ZIRCON_CONFIG_DISABLE_STATUS,
	ZIRCON_CONFIG_ALARM_PING,
	ZIRCON_CONFIG_DEACT_EVENT,
  ZIRCON_CONFIG_END


//**********************************
//End of PCODE information
//**********************************
//	LAST_PCODE = 0x5FFF
}PCODE;


//Command Codes
typedef enum
{
//*********************************************
// Start of Zircon CCODES   JRG_DEACT
//*********************************************
	ZIRCON_CCODE_START = 0X0600,
	ZIRCON_SET_SYSCONFIG = ZIRCON_CCODE_START,
	ZIRCON_GET_SYSCONFIG,
   ZIRCON_CCODE_END

}CCODE;

//*************************************
// Start Zircon ADDRESS for parametersspcodes  JRG_DEACT
//*************************************
  // Start address MAPPED_EEPROM_START
  // All have 1 byte Index after that. 

// CRC is stored at the start that way we can always
// do parameter updates even though new parameters are added in the code 
// since new defines are added at the end

// All Changed to 2 Bytes values
#define		EEPROM_ZIRCON_CONFIG_CRC				0	// Should always be the last byte
#define		EEPROM_ZIRCON_CONFIG_INTLK_DURATION		2   
#define		EEPROM_ZIRCON_CONFIG_TAGBAND			4
#define		EEPROM_ZIRCON_CONFIG_ENABLE_TX2			6
#define		EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS	8
#define		EEPROM_ZIRCON_CONFIG_ANT_FAULT			10
#define		EEPROM_ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP	12
#define		EEPROM_ZIRCON_CONFIG_FRAME_RATE			14
#define		EEPROM_ZIRCON_CONFIG_HI_POWER			16
#define		EEPROM_ZIRCON_CONFIG_TAG_RATE			18  
#define		EEPROM_ZIRCON_CONFIG_GPI				20
#define		EEPROM_ZIRCON_CONFIG_GPO				22
#define		EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF        24
#define		EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF        26
#define		EEPROM_ZIRCON_CONFIG_DET_TX_POWER		28
#define		EEPROM_ZIRCON_CONFIG_RESET_CONDITION	30
#define		EEPROM_ZIRCON_CONFIG_INTERLOCK			32
#define		EEPROM_ZIRCON_CONFIG_LO_POWER			34

#define		EEPROM_ZIRCON_CONFIG_END				36  // Always update this address, This + 1 will  also represents the size including the CRC

#define EEPROM_ZIRCON_USER_DEF_START				EEPROM_ZIRCON_CONFIG_END+2
#define EEPROM_ZIRCON_USER_DEF_AUTOTUNE				EEPROM_ZIRCON_USER_DEF_START
#define EEPROM_ZIRCON_USER_DEF_END					EEPROM_ZIRCON_USER_DEF_AUTOTUNE+sizeof(profileStructType)

// EEPROM defines for reset functionality only one Byte is used as of now
#define EEPROM_ZIRCON_RESET_START				EEPROM_ZIRCON_USER_DEF_END+2
#define EEPROM_ZIRCON_RESET_STORE				EEPROM_ZIRCON_RESET_START
#define EEPROM_ZIRCON_RESET_END					EEPROM_ZIRCON_RESET_STORE+1

// Store the nightsave condition for next reset from EvolveStore command
#define EEPROM_ZIRCON_NIGHTSAVE_START				EEPROM_ZIRCON_RESET_END+1
#define EEPROM_ZIRCON_NIGHTSAVE						EEPROM_ZIRCON_NIGHTSAVE_START
#define EEPROM_ZIRCON_NIGHTSAVE_END					EEPROM_ZIRCON_NIGHTSAVE+1

// DMS DISCONNECT INDICATION for bAborted
#define DMS_DISCONNECT_INDICATION_DEFAULT				0
#define DMS_DISCONNECT_INDICATION_RESET					1
#define DMS_DISCONNECT_INDICATION_NOCOM					2

#define BIT_CCODE_REPLY		0x8000	/* mark Emerald Message as a reply */
#define BIT_SEQ_ACK		0x80	/* mark Emerald Message as an ACK */

#define THORITE_ADDRESS		0x00		/*0X00 address used by thorite   */
#define DMS_ADDRESS			0xFF	/* address used by DMS */

#define EVOLVE_SELF_ADDRESS	 0x0F	/*0X0F self address used by evolve   */



//Type Codes
typedef enum
{
	boolean,	// unsigned 16-bit value, 0x00 = False; 0x01 = True
	spare_01,
	u16,
	u32,
	spare_04,
	s16,
	s32,
	spare_07,
	spare_08,
	spare_09,
	dt_02,	// date-time in Month/WeekOfMonth/DayOfWeek format
	dt,		// date-time in UTC format

	// This section defines types that needs dynamic memory allocation
	dynamic_cfgTCode,
	str = dynamic_cfgTCode, 	//8-bit NULL terminated ASCII string data
	unicodestr, 		//Unicode strings terminated with double NULL characters
	end_dynamic_cfgTCode = unicodestr,

	// This section defines types that are not stored (directly) in Cfg,
	// but are used in Emerald format messages
	emerald_array, //An array of Emerald Formatted elements
	array,

	array_extTCode,	// ext Tcode enum that is only allow when TCode is array
	evtRec1 = array_extTCode,	//Event Record revision 1 - defined in EVT_RECORD structure
	u8, 	//only allowed in arrays
	s8, 	//only allowed in arrays
	end_array_extTCode
}TCODE;

// These defines take from Messages.hpp and EmeraldMessages.h of Evolve Project
// The variables have the same name so that changes are easy in both code base.

typedef enum	{
	NO_FRAME,	// can't find frame header Start-bytes. Waiting for Start-bytes
	HEADER_FRAME,	// Got header frame Start-bytes. Waiting for header bytes
	DATA_FRAME, 	// Got complete header. Waiting for data
	COMPLETE_FRAME,	// Complete frame with header and data. Need to process frame
	BAD_FRAME, 	// complete frame with bad CRC. Need to NACK
	
	ZMODEM_RECEIVE_FRAME //the Host is trying to initiate a Zmodem transfer
}FrameType;

//uint8_t m_frameState = NO_FRAME;

//#pragma pack(2)

// Since we are already using -fpack-struct
//#pragma pack()

typedef struct DMSMessage_tag
{
	uint8_t		StartFlag;
	uint8_t		HostEndianType;
	uint8_t		DestAddress;
	uint8_t		SourceAddress;
	uint8_t		Sequence;
	uint8_t		Type;
	uint16_t	Len;			// 16-bit data Must be on even address
	uint16_t	HeaderCRC;		// 16-bit data Must be on even address
// Start of Emerald Extended Header 	
	uint16_t DataCRC;
	char extData[TECHID_LEN];
	uint16_t CCode;
// Data Payload	
	uint16_t PCode;
	uint16_t TCode;
	uint16_t DataValue;
} DMSMessage, *pDMSMessage;

typedef struct MessageHeader_tag
{
	uint8_t		StartFlag;
	uint8_t		HostEndianType;
	uint8_t		DestAddress;
	uint8_t		SourceAddress;
	uint8_t		Sequence;
	uint8_t		Type;
	uint16_t	Len;			// 16-bit data Must be on even address
	uint16_t	HeaderCRC;		// 16-bit data Must be on even address
} MessageHeader, *pMessageHeader;


//  Evolve unsigned short - > uint16_t 
typedef struct
{
	uint16_t DataCRC;
	char extData[TECHID_LEN];
	uint16_t CCode;
} ExtHeader, *pExtHeader;

// Data Payload
typedef struct
{
uint16_t PCode;
uint16_t TCode;
uint16_t DataValue;
} DataPayload ;

// redefine them later

typedef struct
{
	unsigned short DataCRC;
	char extData[TECHID_LEN];
	unsigned short CCode;
} EmeraldExtHeader, *pEmeraldExtHeader;

typedef struct	EmeraldMessage_tag
{
	MessageHeader header;
	EmeraldExtHeader   extheader;
}EmeraldMessage, *pEmeraldMessage;

/*
#pragma pack()

typedef struct FinderMessage_tag
{
	uint16_t Fccode;
	uint16_t Len;
}FinderMessage, *pFinderMessage;
*/
// In Evolve the buffer is part of the Queue
// Queue<unsigned char> messageQue(COM_BUF_SIZE);
// We are not using a Queue since we have to process one msg at a time 
// the same buffer will be used for recieveing and sendg the msg

//static unsigned char messageBufferIn[COM_BUF_SIZE];
//static unsigned char messageBufferOut[COM_BUF_SIZE];

//static uint8_t messageBufferIn[COM_BUF_SIZE];
uint8_t messageBufferIn[COM_BUF_SIZE];
//static uint8_t  messageBufferOut[COM_BUF_SIZE];
uint8_t  messageBufferOut[COM_BUF_SIZE];

// Declarations of functions

extern DMSMessage *pOutMsg ;
extern DMSMessage *pInMsg ;
extern uint8_t	  globalSequence;  // For commands sent from CPiD
extern uint16_t	  alarmCount;  // For commands sent from CPiD
extern uint16_t	  alarmCountNCR;  // For commands sent from CPiD counts up to 15 only 
extern uint16_t	  alarmRefreshCount;  // For commands sent from CPiD Representative of duration for which the alarm is present in the field
extern uint32_t	  alarmAccumulatedTime ;  // Time accumulated by doing various pulse

extern uint8_t alarm_ping_time;



// End of storage structure

uint8_t SerFEPTask( void );

// Protected functions from FEP.h
//	void FixHeader(unsigned char *msg);
//	bool IsMsgTR4024Type(unsigned  char *msg);
void fixEmeraldHeader(unsigned char* buf, unsigned char newEndian);
void fixEmeraldMessage(unsigned char *buf, unsigned char newEndian, unsigned char oldEndian);
//	bool isEmeraldMessageGood(unsigned char *buf);
uint16_t ChangeEmeraldEndian(unsigned char* buf, unsigned char newEndian);

void NakMessage(void);	// NAK an Emerald message (Data CRC mismatch or timeout waiting on data)
void ProcessACK(void);
void ProcessGETPCODE(void);
void ProcessSETPCODE(void);
void FormatAndSendSpecficCMD(uint16_t cmd);
uint8_t verifyCRC(void);
uint16_t calculateCrcEeprom(void);

// Test code 
//void TestEepromBufferReadWrite(void);

#endif /* DMS_INTERFACE_H_ */


