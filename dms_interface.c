/*
 * dms_interface.c
 *
 * Created: 6/4/2013 5:03:35 PM
 *  Author: dubes
 *
 * $History: dms_interface.c $
 * 
 * *****************  Version 24  *****************
 * User: Dubes        Date: 11/18/15   Time: 1:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 1 minute problem reported by NCR left by mistake in 1.9R Fixed Release
 * 1.10R
 * 
 * *****************  Version 23  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 5/13/15    Time: 1:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Installed a "ENABLE_WD_TICKLE" define macro around tickle.
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 11/12/14   Time: 9:46a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Change the test for SET/GET commands. It was possibly the MSBit would
 * cause a GET command instead of the expected SET. Changed dest address
 * to interoperate with the Evolve reader (EvolveStore). Make sure the
 * format is alway big endian (EvolveStore). 
 * 
 * *****************  Version 20  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 3/27/14    Time: 5:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the setting of the auto tuning eeprom to default when the DMS
 * executes "Factory Default"
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 1/30/14    Time: 11:23a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Made calculateCrcEeprom() an inline function
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added watchdog tickles in the while loop during DMS firmware upgrade
 * and during the loop when first entering the DMS.
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:13a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support the lo and hi power adjustments in DMS
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed old code supporting the GPIO pins
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * commented out the older functions to handle GPIO features
 * 
 * *****************  Version 13  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:44p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support DMS switch to control Interlock 
 * 
 * *****************  Version 12  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:19p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug related with rtc timer not working properly when coming out
 * of DMS , hence functionality was not properly restored
 * 
 * *****************  Version 11  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * clear DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS bits is gets
 * 
 * *****************  Version 10  *****************
 * User: Dubes        Date: 9/23/13    Time: 2:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed memory corruption that we were seeing as a result of removing
 * single global var.
 * 
 * *****************  Version 9  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Increased all config_parameters to 2 bytesand some formatting changes
 * 
 * *****************  Version 8  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:05a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Default Related changes Code until DMS has the capability to process
 * the leading Bit will have top be reversed when DMS has the capability
 * to process MSB for default.
 * 
 * *****************  Version 7  *****************
 * User: Dubes        Date: 8/29/13    Time: 1:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_FIRMWARE_VERSION Pcode
 * 
 * *****************  Version 6  *****************
 * User: Dubes        Date: 8/28/13    Time: 2:13p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed unused var to get rid of DMS connection problem, looks like
 * stack is not sufficient.
 * 
 * *****************  Version 5  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * ZIRCON_CONFIG_PRI_HOLDOFF, ZIRCON_CONFIG_SEC_HOLDOFF,
 * ZIRCON_CONFIG_DET_TX_POWER added
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 8/23/13    Time: 5:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added ZIRCON_CONFIG_HOLD_OFF and ZIRCON_CONFIG_DETECT_VPA_LEVEL
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 1:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Old to remove warnings and tag rate change from two bytes to single.
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:31p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added config include file
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
 * Final Tested Code , This Code is Functionaly completewith 7 Test Cases
 * Should be used for Debug if we have problem
 * 
 * *****************  Version 1  *****************
 * User: Dubes        Date: 7/04/13    Time: 1:18p
 * Created in $/Zircon/Working_Thorite/Sandeep_Thorite/Hafnon
 * DMS interface code with the Test Code test cases are listed in main
 * while loop Cases 1 to 6
 */ 

#include "globals.h"
#include "dms_interface.h"
#include "rs232.h"
#include "crc.h"
#include "nvm_eeprom.h"
#include "timers.h"
#include "interface.h"
#include "zircon_config.h"
#include "watchdog.h"
#include "GTimer.h"

uint8_t alarm_ping_time = 0 ;
// Assumptions:
// 1. we are receiving  one msg at a time
// 2. second msg is not received unless the first msg is acked

DMSMessage *pOutMsg = (DMSMessage *)messageBufferOut;
DMSMessage *pInMsg = (DMSMessage *)messageBufferIn;

int iLen;

uint8_t		globalSequence = 0;  // For commands sent from CPiD
uint16_t	alarmCount = 0;  // For commands sent from CPiD
uint16_t	alarmCountNCR = 0;  // For commands sent from CPiD counts up to 15 only 
uint16_t	alarmRefreshCount = 0;  // For commands sent from CPiD Representative of duration for which the alarm is present in the field
uint32_t	alarmAccumulatedTime = 0;  // Time accumulated by doing various pulse

/********************************************************************
 *	FUNCTION: SerFEPTask()
 *
 *	PARAMETERS:	NONE
 *
 *	RETURNS:	Nothing.
 *
 *	DESCRIPTION:	This is the function that reads from  SerialIODevice
 *
 *	based on the function SerFEPTask in Evolve by J.S. Pawulack
 *	
 *******************************************************************/

uint8_t SerFEPTask()
{

	unsigned short BufCRC, CalCRC;
	int m_frameLen = 0;
	int i = 0, headerGood = 0; 
	// Test code var 
	//uint8_t messageBufferIn_Check[7];
	//uint8_t messageBufferIn_Check_Data[40], size_data = 0;		

// Reset the Buffer

	memset(&messageBufferIn[0],0, sizeof(messageBufferIn));

	// break this loop only when the process ends
	// Imp : We may have to adjust the timings for the DMS clock to increase the time out
	// using RTC_PRESCALER_DIV1024_gc for the slowest possible time out
	do
	{
		// Wait until RTC is not busy.
	} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
	rtc_interlock_timer_stop();
	do
	{
		// Wait until RTC is not busy.
	} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
	rtc_interlock_timer_init(DMS_PERIOD , RTC_PRESCALER_DIV1024_gc, DMS_RTC_USAGE);
	
	bAborted = DMS_DISCONNECT_INDICATION_DEFAULT;

	while (!bAborted)
	{
#if ENABLE_WD_TICKLE
		WDT_Reset();
#endif
		// collect all the 52 bytes and the process
		i = 0;
		do
		{
			// Wait until RTC is not busy.
		} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
		rtc_interlock_timer_start();

	    do
		{
			// Start the timer
			//rtc_interlock_timer_start(); // If things dont work
			messageBufferIn[i] = dms_rs232_getchar_block_timer(); // using time based blocking now
			//messageBufferIn[i] = dms_rs232_getchar(); // If things dont work
			// Stop the timer
			//rtc_interlock_timer_stop(); // If things dont work 
			
			// This indicates start of new packet
			if (  (0X7E == messageBufferIn[i])  && (0 == i) && ( !bAborted ) )
			{
						
				// collect the first eight bytes up to the Length
				// Attention Joe
				// From the Emereld Exerciser  I am seeing two 7E at the start that is the reason I am changing the
				// Index from 1 to 0 even though the first index has been read
				// See if we have to revert back ??? 
				
				for( i = 1; i < ( sizeof(MessageHeader) ); i++ )
				{
					//rtc_interlock_timer_start();  // If things dont work
					messageBufferIn[i] = dms_rs232_getchar_block_timer(); // using time based blocking now
					//messageBufferIn[i] = dms_rs232_getchar();// If things dont work
					//rtc_interlock_timer_stop();  // If things dont work
							
				}
						

				// Calculate the CRC of the header to see if it good enough
						
				if (pInMsg->HostEndianType == 0xFF)
				{
					// big Endian
					BufCRC =   Le16(pInMsg->HeaderCRC);    // These defines are not working so using Le16 ntohs(pInMsg->HeaderCRC);
					// mFrame length is the total no of bytes we should expect
					m_frameLen = Le16(pInMsg->Len)  + sizeof(MessageHeader);  // ntohs(pInMsg->Len) These defines are not working so using Le16
				}
				else
				{
					BufCRC = pInMsg->HeaderCRC;
					m_frameLen = pInMsg->Len + sizeof(MessageHeader);
				}
				//TestCode-->memcpy(&messageBufferIn_Check[0], ( (unsigned char *) pInMsg + 1) ,(sizeof(MessageHeader) - 3) );
				CalCRC = CalculateCRC(CRC16_WORD, (unsigned char *)pInMsg + 1, (sizeof(MessageHeader) - 3), 0x00);
						
				//check header CRC
				if (CalCRC != BufCRC)
				{
					// Not good header or msg
							
					i = 0;
					// NAK Emerald Message if data CRC mismatch
					// Send a generic NACK
					// this is the place we send ZIRCON_GENERIC_NACK
					// and break
					FormatAndSendSpecficCMD(ZIRCON_GENERIC_NACK);
							
				}
				else
				{
					// header CRC matches. Got a valid header. Remember target
					// we can proceed to next stage
					// break the loop.
					// Nothing to do here
					headerGood  = 1;

				}
						
			}
			else
			{
				// collect the remaining 52- size of header characters

				if (headerGood)
				{
					i = i + 1;
				}
				else
				{
					i = 0;	
				}
				 		
			}
						
		}while ( (i < 52) && (!bAborted) );
		
		//---> No Need rtc_interlock_timer_start();
		i = 0;  // get ready for the next msg
		headerGood  = 0;  // set the flag back to zero
		
		
		// Now map it to the structure for analysis
		// Header size is nine
		// Change the Endianness based on the Endian Byte

		//if we're here...the headers checked out
		if (pInMsg->HostEndianType == 0xFF) //if BigEndian
		{
			ChangeEmeraldEndian(messageBufferIn, 0x80); //change to internal Little Endian
		}
		
		// Since the size will be fixed it always pays to do quick check  it is 
		// as per the emerald data capture verified by Joe Extended header ((32 + 2 + 2) - 36 ) + Data Payload ((2 + 2 + 2) = 6) = 42
		
		if ( 42  == (pInMsg->Len) )
		{
			BufCRC = pInMsg->DataCRC;	
			//TestCode--> size_data = m_frameLen - sizeof(MessageHeader) - 2 ; 
			//TestCode--> memcpy(&messageBufferIn_Check_Data[0], ((unsigned char *)&(pInMsg->DataCRC)) + 2,size_data); 
			//TestCode-->CalCRC = CalculateCRC(CRC16_WORD, &messageBufferIn_Check_Data[0], size_data,0x00);

			CalCRC = CalculateCRC(CRC16_WORD, ((unsigned char *)&(pInMsg->DataCRC)) + 2, m_frameLen - sizeof(MessageHeader) - 2, 0x00);
			
			if ( CalCRC == BufCRC)
			{
				// Good packet
				// copy the data into out buffer since most of it is not changed
				memcpy(messageBufferOut, messageBufferIn, sizeof(DMSMessage));
				// data field will be changed in get functions , and other fields will be changed in ACK and nAK functions.
				
				// When testing the Ccode, mask out the MSBit. This will allow the evolve reader to send set ACKs
				// to the CPiD (this device). Evolve sets this bit for any return ACK messages.
				if ( ZIRCON_SET_SYSCONFIG == ((pInMsg->CCode) & 0x7fff)) 
				{
					// Set the parameters in the EEPROM
					// Get the parameters from the EEPROM
					ProcessSETPCODE();
				} 
				else
				{
					// GET is less a problem 
					// Get the parameters from the EEPROM
					ProcessGETPCODE();
				}
				
			// Calculate the CRC
			
			// Send Msg	
				
			} 
			else
			{
				// Bad Packet
				// Generic NAck
				FormatAndSendSpecficCMD(ZIRCON_GENERIC_NACK);
			}
			
		} 
		else
		{
			// It is a bad packet
			// generic NACK
			FormatAndSendSpecficCMD(ZIRCON_GENERIC_NACK);		
		}

		// Stop at this point
		do
		{
			// Wait until RTC is not busy.
		} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
		rtc_interlock_timer_stop();
		
	} // End do of while !bAborted

	return 0;

}

// ALL the Functions from  FEP.cc



/********************************************************************
 *  FUNCTION: FEP::fixEmeraldHeader()
 *
 *  DESCRIPTION:	helper utility to change endian-ness of MessageHeader
 *
 *  INPUT:	buf -- pointer to a buffer holding the message
 *   	   	newEndian -- the endian format to change to:
 *   			0x00 = to little endian
 *   			0x80 = to internal little endian
 *   			0xff = to big endian
 *
 *  RETURNS: 	0 if successful, -1 otherwise
 *
 *******************************************************************/
void fixEmeraldHeader(unsigned char* buf, unsigned char newEndian)
{
	unsigned short crcVal;
	//unsigned short oldEndian = reinterpret_cast<pMessageHeader>(buf)->HostEndianType;
	unsigned short oldEndian = ((pMessageHeader)(buf))->HostEndianType;
	
	if((oldEndian == 0xFF && (newEndian == 0x00 || newEndian == 0x80))//Big to Little
	   || ((oldEndian == 0x00 || oldEndian == 0x80) && newEndian == 0xFF)) //or Little to Big
	{
		((pMessageHeader)(buf))->HostEndianType = newEndian; //change HostEndianType
		((pMessageHeader)(buf))->Len
		= bswap16(((pMessageHeader)(buf))->Len); //swap the len
		
	}//end if
	else //Little to InternalLittle or InternalLittle to Little
	{
		((pMessageHeader)(buf))->HostEndianType = newEndian; //change HostEndianType
	}//end else

	crcVal = CalculateCRC(CRC16_WORD, buf + 1, (sizeof(MessageHeader) - 3), 0x00);
	((pMessageHeader)(buf))->HeaderCRC = (newEndian == 0xFF ? bswap16(crcVal) : crcVal);
}


/********************************************************************
 *  FUNCTION: FEP::fixEmeraldHeader()
 *
 *  DESCRIPTION:	helper utility to change endian-ness of Message
 *
 *  INPUT:	buf -- pointer to a buffer holding the message
 *
 *		   	newEndian -- the endian format to change to:
 *			0x00 = to little endian
 *			0x80 = to internal little endian
 *			0xff = to big endian
 *
 *			oldEndian -- The old Endian format
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/
void fixEmeraldMessage(unsigned char *buf, unsigned char newEndian, unsigned char oldEndian)
{
	unsigned short parameterCode;
	unsigned short typeCode;
	unsigned short swappedTypeCode;
	unsigned short swappedParameterCode;
	unsigned short swappedShortValue;
	int numBytesLeft, i;
	unsigned short extendedTCode;
	unsigned short lengthCode;
	unsigned short shortDataValue;
	unsigned long longDataValue;
	unsigned long swappedLongValue;
	//EVT_RECORD *pEvent;
	unsigned short elementLen;
	unsigned char* pData;
	unsigned short crcVal;
	unsigned short lenToCRC;
	//unsigned short payloadLen = reinterpret_cast<pMessageHeader>(buf)->Len;
	unsigned short payloadLen = ((pMessageHeader)(buf))->Len;
	
	//make payloadLen into Little Endian if Big
	payloadLen = ((pMessageHeader)(buf))->HostEndianType == 0xFF ? bswap16(payloadLen) : payloadLen;
	numBytesLeft = payloadLen - sizeof(EmeraldExtHeader);

	if((oldEndian == 0xFF && (newEndian == 0x00 || newEndian == 0x80))//Big to Little
	   || ((oldEndian == 0x00 || oldEndian == 0x80) && newEndian == 0xFF)) //or Little to Big
	{
		((pEmeraldMessage)buf)->extheader.CCode =
		bswap16(((pEmeraldMessage)(buf))->extheader.CCode); //so always swap
	}

	if((oldEndian == 0xFF && (newEndian == 0x00 || newEndian == 0x80))//Big to Little
	   || ((oldEndian == 0x00 || oldEndian == 0x80) && newEndian == 0xFF)) //or Little to Big
	{
		pData = buf + sizeof(EmeraldMessage); //point to first PCODE

		while(numBytesLeft > 0)	//crawl through the data
		{
			parameterCode = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;	//swap the PCODE
			swappedParameterCode = bswap16(*(unsigned short*)pData); //swap the PCODE
			memcpy(pData, (void*)&swappedParameterCode, sizeof(unsigned short)); //copy back to buf
			numBytesLeft -= sizeof(unsigned short);	//decrement data count
			pData += sizeof(unsigned short); //point to TCODE
/*
			if(parameterCode == SYS_CONFIG_EOR)	//is this an End Of Record???
			{
				//yes
				continue; //skip to top of loop
			}
*/
			typeCode = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;//make sure it's Little
			swappedTypeCode = bswap16(*(unsigned short*)pData);	//swap it
			memcpy(pData, (void*)&swappedTypeCode, sizeof(unsigned short));	//copy back to buf
			numBytesLeft -= sizeof(unsigned short);	//decrement data count
			pData += sizeof(unsigned short); // point to data value

			switch(typeCode)
			{
			
			case emerald_array:	//this is the # of elements
				swappedShortValue = bswap16(*(unsigned short*)pData);
				memcpy((void*)pData, (void*)&swappedShortValue, sizeof(unsigned short));//copy back
				numBytesLeft -= sizeof(unsigned short);	//decrement byte count
				pData += sizeof(unsigned short); //point to next PCODE
				break;

			case u16:
			case s16:
			case boolean:
				swappedShortValue = bswap16(*(unsigned short*)pData);
				memcpy((void*)pData, (void*)&swappedShortValue, sizeof(unsigned short));//copy back
				numBytesLeft -= sizeof(unsigned short);	//decrement byte count
				pData += sizeof(unsigned short); //point to next PCODE
				break;

			case u32:
			case s32:
			case dt:
				memcpy((void*)&longDataValue, (void*)pData, sizeof(unsigned long));	//do it this due to align issues
			        swappedLongValue = bswap32(longDataValue);
				memcpy((void*)pData, (void*)&swappedLongValue, sizeof(unsigned long));	//copy back
				numBytesLeft -= sizeof(unsigned long); //decrement byte count
				pData += sizeof(unsigned long);	//point to next PCODE
				break;

			case array:
				extendedTCode = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;	//extended TCODE
				swappedTypeCode = bswap16(*(unsigned short*)pData);	//swap extTCODE
				memcpy((void*)pData, (void*)&swappedTypeCode, sizeof(unsigned short));
				pData += sizeof(unsigned short); //point to extended lenCode
				numBytesLeft -= sizeof(unsigned short);	//decrement byte count

				elementLen = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;

				lengthCode = bswap16(*(unsigned short*)pData); //swap extlen code
				memcpy((void*)pData, (void*)&lengthCode, sizeof(unsigned short));
				pData += sizeof(unsigned short); //point to start of data
				numBytesLeft -= sizeof(unsigned short);	//decrement byte count

				if(extendedTCode == u8 || extendedTCode == s8 || extendedTCode == boolean) //if u8 or s8...just increment the pointer
				{
				    if (elementLen & 0x01)	// pad byte
					elementLen++;
				    
				    pData += elementLen; //go to next PCODE
				    numBytesLeft -= elementLen;	//decrement byte counter
				    break; //out of case array:
				}//e	nd if

				for (i=0; i<elementLen; i++)
				{
					switch(extendedTCode)
					{
					case u16:
					case s16:
					    memcpy((void*)&shortDataValue, (void*)pData, sizeof(unsigned short));
					    swappedShortValue = bswap16(shortDataValue);
					    memcpy((void*)pData, (void*)&swappedShortValue, sizeof(unsigned short));

					    pData += sizeof(unsigned short);
					    numBytesLeft -= sizeof(unsigned short);
					    break;

					case u32:
					case s32:
					case dt:
					    memcpy((void*)&longDataValue, (void*)pData, sizeof(unsigned long));
					    swappedLongValue = bswap32(longDataValue);
					    memcpy((void*)pData, (void*)&swappedLongValue, sizeof(unsigned long));

					    pData += sizeof(unsigned long);
					    numBytesLeft -= sizeof(unsigned long);
					    break;
/*
					case evtRec1:
					    //swap bytes for EVT_RECORD
					    pEvent = (EVT_RECORD *)pData;
//					    memcpy((void*)&longDataValue, (void*)&(pEvent->Timestamp), sizeof(unsigned long));
					    longDataValue = pEvent->Timestamp;
					    pEvent->Timestamp = bswap32(longDataValue);
//					    memcpy((void*)&(pEvent->Timestamp), (void*)&swappedLongValue, sizeof(unsigned long));
					    memcpy((void*)&shortDataValue, (void*)&(pEvent->iTag), sizeof(unsigned short));
					    swappedShortValue = bswap16(shortDataValue);
					    memcpy((void*)&(pEvent->iTag), (void*)&swappedShortValue, sizeof(unsigned short));
						
					    pData += sizeof(EVT_RECORD);
					    numBytesLeft -= sizeof(EVT_RECORD);
*/					    break;

					default:
						break;
						
					}//end switch(extendedTCode)
				}//end for
				break;

			case str: //don't need to swap string...just the extTCode, then increment pointer
				lengthCode = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;	//swap
				swappedShortValue = bswap16(lengthCode);
				memcpy((void*)pData, (void*)&swappedShortValue, sizeof(unsigned short)); //copy back
				pData += sizeof(unsigned short); //point to beginning of string
				numBytesLeft -= sizeof(unsigned short);	//decrement data count
				if (lengthCode & 0x01)	// pad byte
				    lengthCode++;
				
				pData += lengthCode; //increment pointer to end of string
				numBytesLeft -= lengthCode;
				break;

			case unicodestr:
				lengthCode = oldEndian == 0xFF ? bswap16(*(unsigned short*)pData) : *(unsigned short*)pData;
				numBytesLeft -= sizeof(unsigned short);	//decrement data count

				if(((lengthCode > 0) && (numBytesLeft > 0) && ((oldEndian == 0xFF) && (newEndian == 0x00 || newEndian == 0x80)))//Big to Little
				|| ((oldEndian == 0x00 || oldEndian == 0x80) && (newEndian == 0xFF))) //or Little to Big
				{
					swappedShortValue = bswap16(*(unsigned short*)pData);
					memcpy((void*)pData, (void*)&swappedShortValue, sizeof(unsigned short)); //copy back
					pData += sizeof(unsigned short); //point to beginning of string

				        elementLen = (lengthCode >> 1);	//number of Unicode chars == number of Unicode bytes / 2
					for (i=0; i<elementLen; i++)
					{
						shortDataValue = bswap16(*(unsigned short*)pData); //swap
						memcpy((void*)pData, (void*)&shortDataValue, sizeof(unsigned short)); //copy back
						pData += sizeof(unsigned short); //increment pointer
						numBytesLeft -= sizeof(unsigned short);	//decrement data count
					}//end for
				}//end if
				else //we're not swapping
				{
					pData += lengthCode; //just increment the pointer
					numBytesLeft -= lengthCode;
				}//end else
				break;
			}//end switch
		}//end while
	}//end if

	//if we're here...we swapped everything we needsd to swap find len of data to CRC
	lenToCRC = ((pMessageHeader)(buf))->HostEndianType == 0xFF 
			   ? bswap16(((pMessageHeader)(buf))->Len) - sizeof(unsigned short)
			   : ((pMessageHeader)(buf))->Len - sizeof(unsigned short);

	crcVal = CalculateCRC(CRC16_WORD,
						  (unsigned char*)(buf + sizeof(MessageHeader) + sizeof(unsigned short)),
						  lenToCRC, 0x00);

	((pEmeraldMessage)(buf))->extheader.DataCRC =  newEndian == 0xFF ? bswap16(crcVal) : crcVal; //make sure it's swapped if necessary
}

/********************************************************************
 *  FUNCTION: FEP::ChangeEmeraldEndian()
 *
 *  DESCRIPTION:	utility for changing the endianess of an Emerald message
 *					from one Endianess to another.
 *
 *  INPUT:	buf -- pointer to a buffer holding the message
			newEndian -- the endian format to change to:
				0x00 = to little endian
				0x80 = to internal little endian
				0xff = to big endian

 *  RETURNS: 	Nothing // Important Funtion Reused
 *
 *******************************************************************/
uint16_t ChangeEmeraldEndian(unsigned char* buf, unsigned char newEndian)
{
	unsigned short crcVal;
	//unsigned char oldEndian = reinterpret_cast<pMessageHeader>(buf)->HostEndianType;
	//unsigned short Len = reinterpret_cast<pMessageHeader>(buf)->Len;
	unsigned char oldEndian = ((pMessageHeader)(buf))->HostEndianType;
	unsigned short Len = ((pMessageHeader)(buf))->Len;


	if(oldEndian == newEndian) //are we sure we need to change?
	{
		//no change
		return 0;
	}//end if

	//if we're here...we want to change the endian-ness of the message
	fixEmeraldHeader(buf, newEndian);

	if((oldEndian == 0xFF && (newEndian == 0x00 || newEndian == 0x80))//Big to Little
	   || ((oldEndian == 0x00 || oldEndian == 0x80) && newEndian == 0xFF)) //or Little to Big
	{
		fixEmeraldMessage(buf, newEndian, oldEndian);
	}//end if
	else
	{//we're staying the same, but stuff could have changed in the data field. Calc new CRC
		Len = newEndian == 0xFF ? bswap16(Len) : Len;
		crcVal = CalculateCRC(CRC16_WORD,
							  (unsigned char*)(buf + sizeof(MessageHeader)) + sizeof(unsigned short),
							  Len - sizeof(unsigned short),
							  0x00);

		crcVal = newEndian == 0xFF ? bswap16(crcVal) : crcVal;
		memcpy((void*)&((pEmeraldMessage)(buf))->extheader.DataCRC, //copy back to extheader
			   (void*)&crcVal,
			   sizeof(unsigned short));
	}//end else

	return 0;
}


/********************************************************************
 *  FUNCTION: ProcessGETPCODE()
 *
 *  DESCRIPTION:	Process the GET Commands and sends NAck or ACK back
 *
 *  INPUT:	PCODE 
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/

void ProcessGETPCODE(void)
{
	//uint16_t iCCode = 0;
	uint16_t iPCode =  0;
#if SERIAL_NUM
	uint16_t temp = 0;
#endif

	memset(&(pOutMsg->DataValue), 0, sizeof(pOutMsg->DataValue));
	//iCCode = pOutMsg->CCode;
	iPCode =  pOutMsg->PCode;
		
	
	switch( iPCode )
	{
		case	ZIRCON_CONFIG_TECHID_LOW :
			
			NakMessage();		
		
		break;
		case	ZIRCON_CONFIG_TECHID_HIGH:
			
			NakMessage();
		
		break;
		case	ZIRCON_CONFIG_INTLK_DURATION:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.intlk_duration;
			ProcessACK();
			Clr_bits(config_parameters.intlk_duration, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_TAGBAND:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_TAGBAND, &config_parameters.deact_tagband, 2); // just copy the Data from EEPROM		
			pOutMsg->DataValue = config_parameters.deact_tagband;
			ProcessACK();
			Clr_bits(config_parameters.deact_tagband, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
		
		break;
		case	ZIRCON_CONFIG_ENABLE_TX2:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.enable_tx_2;
			ProcessACK();
			Clr_bits(config_parameters.enable_tx_2, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_RELAYS:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS, &config_parameters.ant_tune_relays, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.ant_tune_relays;
			ProcessACK();
			Clr_bits(config_parameters.ant_tune_relays, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_CURRENT:

			// This is not to be stored in EEPROM but obtained from Local variable
			// send this value
			pOutMsg->DataValue =  config_parameters.ant_tune_current ;
			ProcessACK();
		
		break;
		case	ZIRCON_CONFIG_ANT_FAULT:
		
			// This is a dynamic value so no need to write to eeprom
			//nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_FAULT, &config_parameters.ant_fault, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue =  config_parameters.ant_fault;
			ProcessACK();
		
		break;
		case	ZIRCON_CONFIG_ANT_TUNE_MISTUNE_IND:

			pOutMsg->DataValue = config_parameters.ant_tune_mistune_ind ; 
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP, &config_parameters.ant_tune_onpowerup, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.ant_tune_onpowerup;
			ProcessACK();
			Clr_bits(config_parameters.ant_tune_onpowerup, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));			

		break;
		case	ZIRCON_CONFIG_FRAME_RATE:
				
			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.deact_frame_rate;
			ProcessACK();
			Clr_bits(config_parameters.deact_frame_rate, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));		

		break;
		case	ZIRCON_CONFIG_HI_POWER:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.config_hi_power;
			ProcessACK();
			Clr_bits(config_parameters.config_hi_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_LO_POWER:

		nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2); // just copy the Data from EEPROM
		pOutMsg->DataValue = config_parameters.config_lo_power;
		ProcessACK();
		Clr_bits(config_parameters.config_lo_power, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_TAG_RATE:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_TAG_RATE, &config_parameters.tag_rate, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.tag_rate;
			ProcessACK();
			Clr_bits(config_parameters.tag_rate, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_RESET:
		
			// ERROR Reset is a set command
			NakMessage();
				
		break;
		case	ZIRCON_CONFIG_INTERLOCK:

#if INTERLOCK_CHOICE
			pOutMsg->DataValue = config_parameters.intlk_enable ;
			ProcessACK();
#else
			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_INTERLOCK, &config_parameters.intlk_enable, 2); // just copy the Data from EEPROM
			pOutMsg->DataValue = config_parameters.intlk_enable;			
			ProcessACK();
			Clr_bits(config_parameters.intlk_enable, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));
#endif

		break;
		case	ZIRCON_CONFIG_MODE_IND:

			pOutMsg->DataValue = config_parameters.mode_ind ;
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_HI_LO_IND:

			pOutMsg->DataValue = config_parameters.hi_low_ind;
			ProcessACK();

		break;
#if EVOLVESTORE
		// Read NightSave status and return one in the payload if the feature is enabled
		// and zero if disabled.
		case	ZIRCON_CONFIG_NIGHTSAVE:

			pOutMsg->DataValue = config_parameters.nightsave; // EvolveStore nightsave
			ProcessACK();

		break;
#endif
		case	ZIRCON_CONFIG_PING:
		
			// No parameters needed just a command
			// Send a ACK 
			ProcessACK( );
				
		break;
//		case	(uint16_t) ZIRCON_CONFIG_CONNECT:
			// Just a command no parameters needed
			// This is just a place holder no processing needed here
				//nvm_eeprom_read_byte();
//		break;
		case	ZIRCON_CONFIG_DEFAULT:
		
			// Error it is a set Commands
			NakMessage();
		break;
		case	ZIRCON_CONFIG_GPI:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_GPI, &config_parameters.config_gpi, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.config_gpi ;
			ProcessACK();
			Clr_bits(config_parameters.config_gpi, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_GPO:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2); // just copy the Data from EEPROM
			pOutMsg->DataValue = config_parameters.config_gpo;
			ProcessACK();
			Clr_bits(config_parameters.config_gpo, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_PRI_HOLDOFF:
		
			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.config_pri_hold_off;
			ProcessACK();
			Clr_bits(config_parameters.config_pri_hold_off, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_SEC_HOLDOFF:
		
			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF, &config_parameters.config_sec_hold_off, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.config_sec_hold_off;
			ProcessACK();
			Clr_bits(config_parameters.config_sec_hold_off, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;		
		case	ZIRCON_CONFIG_DET_TX_POWER:

			nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2); // just copy the Data from EEPROM			
			pOutMsg->DataValue = config_parameters.config_detect_level;		
			ProcessACK();
			Clr_bits(config_parameters.config_detect_level, (DISPLAY_DEFAULT_DMS | DISPLAY_GREY_OUT_DMS));

		break;
		case	ZIRCON_CONFIG_FIRMWARE_VERSION:

			pOutMsg->DataValue = FIRMWARE_VERSION;
			ProcessACK();

		break;
		case ZIRCON_CONFIG_BOARD_TYPE:  /* Thoralite */

			pOutMsg->DataValue = CPiD_HW_flag; // CPiD=1, Thoralite=0
			ProcessACK();

		break;
#if EVOLVESTORE
		// Return the 32 bit device serial number. There needs to be two calls
		// for HI and LO address because payload is only 16 bits.
		case ZIRCON_CONFIG_DEVICE_ID_LO:

			pOutMsg->DataValue = DEVICE_ID.DEVID2 | (DEVICE_ID.DEVID1 << 8);
			ProcessACK();

		break;
		
		case ZIRCON_CONFIG_DEVICE_ID_HI:

			pOutMsg->DataValue = DEVICE_ID.DEVID0;
			ProcessACK();

		break;
#if SERIAL_NUM
		case ZIRCON_CONFIG_SERIAL_NUM0:
			temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM1)));
			temp <<= 8;
			pOutMsg->DataValue = (nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM0)))) | temp;
			ProcessACK();
		break;
		
		case ZIRCON_CONFIG_SERIAL_NUM1:
			temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM3)));
			temp <<= 8;
			pOutMsg->DataValue = (nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM2)))) | temp;
			ProcessACK();
		break;
		
		case ZIRCON_CONFIG_SERIAL_NUM2:
			temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM5)));
			temp <<= 8;
			pOutMsg->DataValue = (nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, LOTNUM4)))) | temp;
			ProcessACK();
		break;
		
		case ZIRCON_CONFIG_SERIAL_NUM3:
			temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, COORDX0)));
			temp <<= 8;
			pOutMsg->DataValue = (nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, WAFNUM)))) | temp;
			ProcessACK();
		break;
		
		case ZIRCON_CONFIG_SERIAL_NUM4:
			temp = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, COORDY0)));
			temp <<= 8;
			pOutMsg->DataValue = (nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, COORDX1)))) | temp;
			ProcessACK();
		break;
		
		case ZIRCON_CONFIG_SERIAL_NUM5:
			pOutMsg->DataValue = nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, (offsetof(NVM_PROD_SIGNATURES_t, COORDY1)));
			ProcessACK();
		break;
#endif
#endif
		case	ZIRCON_CONFIG_STATUS:
		pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_STATUS);
		ProcessACK();
		break;

		case	ZIRCON_CONFIG_SOFT_INTERLOCK:
		// Error it is a set Commands
		NakMessage();
		break;

		case	ZIRCON_CONFIG_DISABLE_STATUS:
		// Error it is a set Commands
		NakMessage();
		break;

		case	ZIRCON_CONFIG_ALARM_PING:
		pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_ALARM_PING);
		ProcessACK();
		break;
		
		default:	
			// send a nack
			NakMessage();
	}
}

/********************************************************************
 *  FUNCTION: ProcessSETPCODE()
 *
 *  DESCRIPTION:	Process the SET Commands and sends NAck or ACK back
 *
 *  INPUT:		PCODE 
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/

void ProcessSETPCODE(void)
{
	uint16_t calc_crc = 0 ;
	//uint16_t iCCode = 0;
	uint16_t iPCode = 0;
	uint16_t counterValue = 0;

	//iCCode = pInMsg->CCode;
	iPCode = pInMsg->PCode;

	switch(iPCode)
	{
		case	ZIRCON_CONFIG_TECHID_LOW :
		
			// As of now this has no relevance
			//MAPPED_EEPROM_START
			config_parameters.techid_low =  pInMsg->DataValue ;// assignee the value from data pay lode
			ProcessACK();		
		
		break;
		case	ZIRCON_CONFIG_TECHID_HIGH:
		
			// As of now this has no relevance
			config_parameters.techid_high = pInMsg->DataValue  ;// assignee the value from data pay lode
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_INTLK_DURATION:

			// 2 bytes
			config_parameters.intlk_duration = pInMsg->DataValue;			
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &config_parameters.intlk_duration, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_TAGBAND:

			config_parameters.deact_tagband = pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAGBAND, &config_parameters.deact_tagband, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_ENABLE_TX2:

			config_parameters.enable_tx_2 =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ENABLE_TX2, &config_parameters.enable_tx_2, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_RELAYS:

			config_parameters.ant_tune_relays = pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_RELAYS, &config_parameters.ant_tune_relays, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_CURRENT:
			NakMessage();
		break;
		case	ZIRCON_CONFIG_ANT_FAULT:

			// Changed from ZIRCON_CONFIG_ANT_TUNE_OVERRIDE to ZIRCON_CONFIG_ANT_FAULT
			// Error
			NakMessage();

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_MISTUNE_IND:
			// Error
			NakMessage();

		break;
		case	ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP:

			config_parameters.ant_tune_onpowerup =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_ANT_TUNE_ONPOWERUP, &config_parameters.ant_tune_onpowerup, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_FRAME_RATE:

			config_parameters.deact_frame_rate = pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_FRAME_RATE, &config_parameters.deact_frame_rate, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_HI_POWER:

			config_parameters.config_hi_power =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_LO_POWER:

		config_parameters.config_lo_power =  pInMsg->DataValue;
		nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_TAG_RATE:
			
			config_parameters.tag_rate =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_TAG_RATE, &config_parameters.tag_rate, 2);// Write 2 byte  data to EEPROM
			ProcessACK();
			
		break;
		case	ZIRCON_CONFIG_RESET:

			config_parameters.config_reset_condition = pInMsg->DataValue;
			ProcessACK();
			
			if( RESET_SUPPRESS_AUTOTUNE == config_parameters.config_reset_condition )
			{
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_RESET_CONDITION, &config_parameters.config_reset_condition, 2);// Write 2 byte  data to EEPROM
				// calculate the new crc value
				calc_crc =  calculateCrcEeprom();
				// write it back
				nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2);// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2
				
			} else if( RESET_WITH_DELAY == config_parameters.config_reset_condition )
			{
				do
				{
					// Wait until RTC is not busy.
				} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
				rtc_interlock_timer_stop();
				do
				{
					// Wait until RTC is not busy.
				} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
				rtc_interlock_timer_init(DMS_PERIOD , RTC_PRESCALER_DIV1024_gc, DMS_RTC_USAGE);
				do
				{
					// Wait until RTC is not busy.
				} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
				rtc_interlock_timer_start();
				counterValue = 0;
				while ( counterValue < DMS_RESET_TIMEOUT )
				{
					counterValue = INTERLOCK_TIMER.CNT;
#if ENABLE_WD_TICKLE
					WDT_Reset();
#endif
				}
			}
			//ProcessACK();
			bAborted = DMS_DISCONNECT_INDICATION_RESET;
				
		break;
		case	ZIRCON_CONFIG_INTERLOCK:

#if INTERLOCK_CHOICE
			NakMessage();			
#else						
			config_parameters.intlk_enable =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_INTERLOCK, &config_parameters.intlk_enable, 2);// Write 2 byte  data to EEPROM
			ProcessACK();
#endif

		break;
		case	ZIRCON_CONFIG_MODE_IND:

			NakMessage();

		break;
		case	ZIRCON_CONFIG_HI_LO_IND:

			NakMessage();

		break;
#if EVOLVESTORE
		// SET the NightSave feature. This feature is volatile so after a
		// power cycle this feature becomes disabled. The first time this
		// set a flag is set in eeprom to allow the feature after the first
		// reset.
		case	ZIRCON_CONFIG_NIGHTSAVE:  // EvolveStore

			config_parameters.nightsave =  pInMsg->DataValue;
			if(config_parameters.nightsave)
			{
				nvm_eeprom_write_byte(EEPROM_ZIRCON_NIGHTSAVE, 0x01);
			}
			else
			{
				nvm_eeprom_write_byte(EEPROM_ZIRCON_NIGHTSAVE, 0xff);
			}

			ProcessACK();

		break;
#endif

		case	ZIRCON_CONFIG_PING:
		
			// No parameters needed just a command
			//Error
			NakMessage();

		break;
//		case	ZIRCON_CONFIG_CONNECT:
		// Just a command no parameters needed
		// This is just a place holder no processing needed here
			//nvm_eeprom_write_byte(, uint8_t value);
//		break;
		case	ZIRCON_CONFIG_DEFAULT:
		
			// Just a command no parameters needed
			nvm_eeprom_write_byte(EEPROM_ZIRCON_RESET_STORE, 0xFF);
			setDefaultValues();
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_GPI:

			config_parameters.config_gpi = pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPI, &config_parameters.config_gpi, 2);// Write 2 byte  data to EEPROM
			//bAborted = 1; // for testing GPI and GPO functionality could have a value of 3
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_GPO:

			config_parameters.config_gpo =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_GPO, &config_parameters.config_gpo, 2);// Write 2 byte  data to EEPROM
			//bAborted = 1; // for testing GPI and GPO functionality could have a value of 3
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_PRI_HOLDOFF:

			config_parameters.config_pri_hold_off =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_PRI_HOLDOFF, &config_parameters.config_pri_hold_off, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_SEC_HOLDOFF:

			config_parameters. config_sec_hold_off =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_SEC_HOLDOFF, &config_parameters. config_sec_hold_off, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
		case	ZIRCON_CONFIG_DET_TX_POWER:

			config_parameters.config_detect_level =  pInMsg->DataValue;
			nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_DET_TX_POWER, &config_parameters.config_detect_level, 2);// Write 2 byte  data to EEPROM
			ProcessACK();

		break;
//		case	ZIRCON_GENERIC_NACK:
		
		// Just a command no parameter needed
			//nvm_eeprom_write_byte(, uint8_t value);
//		break;
		case	ZIRCON_CONFIG_FIRMWARE_VERSION:
		
			// No parameters needed just a command
			//Error
			NakMessage();

		break;

		case	ZIRCON_CONFIG_STATUS:
			// Error it is a get Commands
			NakMessage();
		break;

		case	ZIRCON_CONFIG_SOFT_INTERLOCK:
		
			// There are two ways to enable and disable soft interlock 
			// a. The one used by NCR by using the 0X7F (Disable soft Interlock ) and 0X7A (Enable soft Interlock), This method was chosen
			// since the response time was needed to be around 200 ms, with this method it is approx 100 ms, (But we should claim it to be below 200 ms )
			// b. Using DMS interface (first send 0X7E to connect) and send ZIRCON_CONFIG_SOFT_INTERLOCK with different payload, 0 : Disable interlock
			// 1: Enable Interlock, 2: Enable Time based interlock.
			// This is one way
			config_parameters.config_soft_interlock =  pInMsg->DataValue;
			// This will send the pay load in the ack msg , only Disable interlock need to have a payload indicating the status of the CPiD
			if ( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock)
			{
				pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_STATUS);
			} else
			{
				pOutMsg->DataValue = config_parameters.config_soft_interlock;
			
			}
			ProcessACK();
		break;

		case	ZIRCON_CONFIG_DISABLE_STATUS:

			// Disable the Status Ping 
			GTimer_unRegisterCB(send_ping_handler);
			send_ping_handler = 0xff;
			// Indicate that CPiD has received the command
			// Review set this mask to 0X0100, set if you are using higher detection rate 
			// and want to sync the start and end of alarm msg to the sound of alarm. 
			if (0X0100 & pInMsg->DataValue)
			{
				flag_enable_hard_tag_indicator = 1;	
			}
			// Currently we are using 0 through 6 future we may use these bits
			// add to interface doc
			config_parameters.config_enable_alarm = (0x00FF & pInMsg->DataValue);
			// Register How often then we have to call it
			// only if the data value is non zero
			// alarm_ping_time duration after which the alarm ping has to be sent
			switch(config_parameters.config_enable_alarm)
			{
				case 1:
				alarm_ping_time = G_TIMER_15S;
				break;
				case 2:
				alarm_ping_time = G_TIMER_30S;
				break;
				case 3:
				alarm_ping_time = G_TIMER_1M;
				break;
				case 4:
				alarm_ping_time = G_TIMER_2M;
				break;
				case 5:
				alarm_ping_time = G_TIMER_15M;
				break;
				case 6:
				alarm_ping_time = G_TIMER_30M;
				break;
				default:
				alarm_ping_time = 0; // This is not  G_TIMER_1S which is defined as 0 but is this is set to zero then we will only send alarm
				break;
			}
			
			// Done for testing  1 minute problem reported by NCR left by mistake in 1.9R
			// alarm_ping_time = G_TIMER_1M;
			// This is for enabling the NCR behavior to start accepting the Soft interlock and Start and end of alarm
			flag_config_enable_alarm = 1;
		
			// Register the alarm ping as soon as you see the Msg
			if(send_alarm_ping_handler == 0xff)
			{
				send_alarm_ping_handler = GTimer_RegisterCB(&sendAlarmPing);
			}
		
			ProcessACK();
		break;

		case	ZIRCON_CONFIG_ALARM_PING:
			// Error it is a get Commands
			NakMessage();
		break;
		default:
		
			// Send a nack
			NakMessage();

		break;
		
	}
	// calculate the new crc value
	calc_crc =  calculateCrcEeprom();
	// write it back
	nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2);// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2

}




/********************************************************************
 *  FUNCTION: ProcessACK()
 *
 *  DESCRIPTION:	Formulate a proper ack and send it back
 *                  Since the code is single threaded
 *                  we are processing every thing in Sequence
 *                  so the ACK will always be for the iCode being processed
 *                  
 *  INPUT:		Nothing
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/

void ProcessACK(void)
{
	
// ACK is always of 52 bytes
	
	if ((pOutMsg->HostEndianType == 0xFF))
	{
		// Convert header to Little Endian message first (data will be ignored)
		pOutMsg->Len = htons(sizeof(ExtHeader) + sizeof(DataPayload));
		ChangeEmeraldEndian(messageBufferOut, 0x80);
	}
	else
	{
		// not an HostFEP or is in Little Endian
		pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));	//ignore data
	}
	
    pOutMsg->DestAddress = DMS_ADDRESS;
    pOutMsg->SourceAddress = THORITE_ADDRESS;
    pOutMsg->CCode |= BIT_CCODE_REPLY;		// it is a response
    pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK
    iLen = sizeof(DMSMessage); // the length of data that is to be sent
	
	// Calculate the CRC
	pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, (unsigned char *)(pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
	pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe	

	if (pOutMsg->HostEndianType == 0x80)	//did message come in as Big?
	{
		//yes
		ChangeEmeraldEndian(messageBufferOut, 0xFF); //change back to Big Endian
	}//end if

	// SendMessage(m_frameBufOut, returnMessageHeader.len);
	dms_rs232_send_data_length( iLen );

}


/********************************************************************
 *  FUNCTION: NakMessage()
 *
 *  PARAMETERS:
 *	
 *  RETURNS:
 *	Nothing.
 *
 *  DESCRIPTION:
 *	return an Nak message to originator
 *
 *******************************************************************/
void NakMessage(void)
{
    
    //build the response Frame (in Little Endian) from the partial Received Frame
    //Note: CCode may be invalid because extheader might have been corrupted
 
    memset(&(pOutMsg->DataCRC), 0,  sizeof(ExtHeader));
	pOutMsg->CCode = pInMsg->CCode;
	
    if ((pOutMsg->HostEndianType == 0xFF))
    {
		// Convert header to Little Endian message first (data will be ignored)
		pOutMsg->Len = htons(sizeof(ExtHeader));
		ChangeEmeraldEndian(messageBufferOut, 0x80);
    }
    else
    {
		// not an HostFEP or is in Little Endian
		pOutMsg->Len = sizeof(ExtHeader);	//ignore data
    }
    pOutMsg->DestAddress = DMS_ADDRESS;
    pOutMsg->SourceAddress = THORITE_ADDRESS;
    pOutMsg->CCode |= BIT_CCODE_REPLY;		// it is a response
    pOutMsg->Sequence &= ~BIT_SEQ_ACK;		// it is a NAK Imp Note Nak is a command in sequence 
    iLen = pOutMsg->Len + sizeof(MessageHeader);


    // calculate the CRC
	pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, (unsigned char *)(pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
	pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe
	// restore Endian
    if( pOutMsg->HostEndianType == 0x80 )	//did message come in as Big?
    {
		//restore to Big Endian for Host Message only
		ChangeEmeraldEndian(messageBufferOut, 0xFF); //change back to Big Endian
    }//end if
	
    // Send NAK message
   // SendMessage(m_frameBufOut, iLen);
    dms_rs232_send_data_length( iLen );
}



/********************************************************************
 *  FUNCTION: FormatAndSendSpecficCMD()
 *
 *  DESCRIPTION:	This function is for formating specific commands to be sent back to DMS 
 *                  like ZIRCON_GENERIC_NACK and Response to the connect Command
 *                  
 *  INPUT:	    Nothing
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/


void FormatAndSendSpecficCMD(uint16_t cmd)
{
	//TestCode-->uint8_t messageBufferIn_Check1[7];
	//TestCode-->uint8_t size_msghedder;
	
	
	switch(cmd)
	{
		case	ZIRCON_CONFIG_CONNECT :
		
			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// AN ACK to connect
			pOutMsg->StartFlag = 0x7E;		
			// at this point We dont know the Endianness we will have to figure that out
#if EVOLVESTORE
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS; // DMS_ADDRESS;
#else
			pOutMsg->DestAddress = DMS_ADDRESS;
#endif	
			//pOutMsg->DestAddress = DMS_ADDRESS;
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			globalSequence = 0; // Connect will zero the sequence no.
			pOutMsg->Sequence = globalSequence;
			pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK Sequence no is zero at this point
#if EVOLVESTORE
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
#else
			pOutMsg->Type = 0x0E; // Only one Type 0X0E
#endif
			pOutMsg->CCode = BIT_CCODE_REPLY | ZIRCON_SET_SYSCONFIG;		// it is a response
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
			pOutMsg->PCode = ZIRCON_CONFIG_CONNECT;
			pOutMsg->TCode = u16; //  always unsigned 16
#if EVOLVESTORE
			// build the bit mapped payload for EvolveStore
			pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_STATUS);
#else
			pOutMsg->DataValue = ZIRCON_CONFIG_CONNECT;
#endif
			
			iLen = sizeof(DMSMessage); // the length of data that is to be sent
			// Calculate the CRC
			//size_msghedder = (sizeof(MessageHeader) - 3);
			// This is Test Code
			//memcpy(&messageBufferIn_Check1[0], ((unsigned char *)  pOutMsg + 1) ,(sizeof(MessageHeader) - 3));
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, ((unsigned char *) pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe
				
		break;
		case	ZIRCON_GENERIC_NACK :
		
			// Assume that all the data may also be corrupt
			// A generic NACK is always in response to a command so we may be knowing some parameters
			// copy the data into out buffer since most of it is not changed
			// but this could arise in  case when the command received is corrupted

			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// at this point We don't know the Endianness we will have to figure that out
			pOutMsg->StartFlag = 0x7E;	
			pOutMsg->HostEndianType = 0x00;
			pOutMsg->PCode = ZIRCON_GENERIC_NACK;
			pOutMsg->CCode = BIT_CCODE_REPLY | ZIRCON_SET_SYSCONFIG;		// it is a response
			
			// Host Indian type could also be corrupted as in case of 7E 7E stream
			// so is the size 
			/*
			if ((pOutMsg->HostEndianType == 0xFF))
			{
				// Convert header to Little Endian message first (data will be ignored)
				pOutMsg->Len = htons(sizeof(ExtHeader));
				ChangeEmeraldEndian(messageBufferOut, 0x80);
			}
			else
			{
				// not an HostFEP or is in Little Endian
				pOutMsg->Len = sizeof(ExtHeader);	//ignore data
			}
			*/
			// Since the Payload will be corrupted
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
#if EVOLVESTORE
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS;
#else			
			pOutMsg->DestAddress = DMS_ADDRESS;
#endif
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			//pOutMsg->CCode |= BIT_CCODE_REPLY;		// it is a response
			pOutMsg->Sequence &= ~BIT_SEQ_ACK;		// it is a NAK Imp Note Nak is a command in sequence
			// sachin asked for this change to remove the NACK bit, DMS does not work properly with this change
			//pOutMsg->Sequence |= BIT_SEQ_ACK;  
#if EVOLVESTORE
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
#else
			pOutMsg->Type = 0x0E;
#endif
			// T Code is always u16
			pOutMsg->TCode = u16; //  always unsigned 16
			iLen = pOutMsg->Len + sizeof(MessageHeader);
			
			// calculate the CRC
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, (unsigned char *)(pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe
			// restore Endian
			
			// Host Endian type is corrupted
			/*
			if( pOutMsg->HostEndianType == 0x80 )	//did message come in as Big?
			{
				//restore to Big Endian for Host Message only
				ChangeEmeraldEndian(messageBufferOut, 0xFF); //change back to Big Endian
			}//end if
			*/
				
		break;
#if EVOLVESTORE
		// This is the status message sent to the Evolve reader every 15 seconds. The
		// payload of this message is a bit mapped status.
		case	ZIRCON_CONFIG_STATUS :

			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// AN ACK to connect
			pOutMsg->StartFlag = 0x7E;
			// at this point We dont know the Endianness we will have to figure that out
			pOutMsg->HostEndianType = 0x00;
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS; // THORITE_ADDRESS;  //DMS_ADDRESS;
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			pOutMsg->Sequence = 0; // Sequence no is zero at this point
			//pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK Sequence no is zero at this point
			//pOutMsg->Type = 0x0E; // Only one Type 0X0E
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
			pOutMsg->CCode = ZIRCON_GET_SYSCONFIG;		// it is a response
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
			pOutMsg->PCode = ZIRCON_CONFIG_STATUS;
			pOutMsg->TCode = u16; //  always unsigned 16
			// Test
			pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_STATUS);

			iLen = sizeof(DMSMessage); // the length of data that is to be sent
			// Calculate the CRC
			//size_msghedder = (sizeof(MessageHeader) - 3);
			// This is Test Code
			//memcpy(&messageBufferIn_Check1[0], ((unsigned char *)  pOutMsg + 1) ,(sizeof(MessageHeader) - 3));
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, ((unsigned char *) pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe

		break;
		case	ZIRCON_CONFIG_SOFT_INTERLOCK :

			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// AN ACK to connect
			pOutMsg->StartFlag = 0x7E;
			// at this point We dont know the Endianness we will have to figure that out
			pOutMsg->HostEndianType = 0x00;
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS; // THORITE_ADDRESS;  //DMS_ADDRESS;
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			pOutMsg->Sequence = globalSequence; // Sequence no is zero at this point
			pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK Sequence no is zero at this point
			//pOutMsg->Type = 0x0E; // Only one Type 0X0E
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
			pOutMsg->CCode = BIT_CCODE_REPLY | ZIRCON_SET_SYSCONFIG;		// it is a response
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
			pOutMsg->PCode = ZIRCON_CONFIG_SOFT_INTERLOCK;
			pOutMsg->TCode = u16; //  always unsigned 16
			// it will be SOFT_INTERLOCK_DISABLE if 0x7F is received and SOFT_INTERLOCK_ENABLE is received 0X7A
			if( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock)
			{
				pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_STATUS);
			}
			else
			{
				pOutMsg->DataValue = config_parameters.config_soft_interlock;
			}
		
			iLen = sizeof(DMSMessage); // the length of data that is to be sent
			// Calculate the CRC
			//size_msghedder = (sizeof(MessageHeader) - 3);
			// This is Test Code
			//memcpy(&messageBufferIn_Check1[0], ((unsigned char *)  pOutMsg + 1) ,(sizeof(MessageHeader) - 3));
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, ((unsigned char *) pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe

		break;
		case	ZIRCON_CONFIG_ALARM_PING :

			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// AN ACK to connect
			pOutMsg->StartFlag = 0x7E;
			// at this point We dont know the Endianness we will have to figure that out
			pOutMsg->HostEndianType = 0x00;
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS; // THORITE_ADDRESS;  //DMS_ADDRESS;
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			pOutMsg->Sequence = globalSequence; // Sequence no is zero at this point
			pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK Sequence no is zero at this point
			//pOutMsg->Type = 0x0E; // Only one Type 0X0E
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
			pOutMsg->CCode = ZIRCON_GET_SYSCONFIG;		// it is a response
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
			pOutMsg->PCode = ZIRCON_CONFIG_ALARM_PING;
			pOutMsg->TCode = u16; //  always unsigned 16
			// Test
			pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_ALARM_PING);

			iLen = sizeof(DMSMessage); // the length of data that is to be sent
			// Calculate the CRC
			//size_msghedder = (sizeof(MessageHeader) - 3);
			// This is Test Code
			//memcpy(&messageBufferIn_Check1[0], ((unsigned char *)  pOutMsg + 1) ,(sizeof(MessageHeader) - 3));
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, ((unsigned char *) pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe

		break;
		
		case ZIRCON_CONFIG_DEACT_EVENT: 
			memset(&messageBufferOut[0],0 ,sizeof(messageBufferOut));
			// AN ACK to connect
			pOutMsg->StartFlag = 0x7E;
			// at this point We dont know the Endianness we will have to figure that out
			pOutMsg->HostEndianType = 0x00;
			pOutMsg->DestAddress = EVOLVE_SELF_ADDRESS; // THORITE_ADDRESS;  //DMS_ADDRESS;
			pOutMsg->SourceAddress = THORITE_ADDRESS;
			pOutMsg->Sequence = globalSequence; // Sequence no is zero at this point
			pOutMsg->Sequence |= BIT_SEQ_ACK;	//it is a ACK Sequence no is zero at this point
			//pOutMsg->Type = 0x0E; // Only one Type 0X0E
			pOutMsg->Type = 0xE0; // Only one Type 0X0E
			pOutMsg->CCode = ZIRCON_GET_SYSCONFIG;		// it is a response
			pOutMsg->Len = (sizeof(ExtHeader) + sizeof(DataPayload));
			pOutMsg->PCode = ZIRCON_CONFIG_DEACT_EVENT;
			pOutMsg->TCode = u16; //  always unsigned 16
			// Test
			pOutMsg->DataValue = buildStatusPayload(PAYLOAD_GET_ALARM_PING);

			iLen = sizeof(DMSMessage); // the length of data that is to be sent
			// Calculate the CRC
			//size_msghedder = (sizeof(MessageHeader) - 3);
			// This is Test Code
			//memcpy(&messageBufferIn_Check1[0], ((unsigned char *)  pOutMsg + 1) ,(sizeof(MessageHeader) - 3));
			pOutMsg->HeaderCRC = CalculateCRC(CRC16_WORD, ((unsigned char *) pOutMsg + 1), (sizeof(MessageHeader) - 3), 0x00);  // Sandeep Confirm this from Joe
			pOutMsg->DataCRC = CalculateCRC(CRC16_WORD, (unsigned char *)&(pOutMsg->DataCRC) + 2, pOutMsg->Len - 2, 0x00); // Confirm this from Joe
			
		break;
#endif	
	} // End of switch command
	
	if( pOutMsg->HostEndianType == 0x00 )	//did message come in as Big?
	{
		//restore to Big Endian for Host Message only
		ChangeEmeraldEndian(messageBufferOut, 0xFF); //change back to Big Endian
	}//end if
	
	// Increment the sequence no. it should be mod 127
	if (globalSequence < 128)
	{
		globalSequence = globalSequence + 1;
	}else
	{
		globalSequence = 0;
	}
		
	// Send Out the msg
	dms_rs232_send_data_length( iLen );
}

/********************************************************************
 *  FUNCTION: verifyCRC()
 *
 *  DESCRIPTION:	Utility to verify the CRC
 * 
 *                  
 *  INPUT:	pointer to start of eeprom data
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/

uint8_t verifyCRC(void)
{
	uint8_t retValue = 0;
	uint16_t eeprom_crc = 0, calc_crc = 0;
	
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2); // just copy the CRC
	
	calc_crc =  calculateCrcEeprom();
	
	if (calc_crc == eeprom_crc )
	{
		retValue = 1;
	} 
	else
	{
		retValue = 0;
	}
	
	return retValue;
	
}

/********************************************************************
 *  FUNCTION: calculateCrcEeprom()
 *
 *  DESCRIPTION:	Utility to calculate CRC of stored EEPROM data
 * 
 *                  
 *  INPUT:	pointer to start of eeprom data
 *
 *  RETURNS: 	Nothing
 *
 *******************************************************************/

inline uint16_t calculateCrcEeprom(void)
{
	uint16_t eeprom_crc = 0;
	uint8_t eepromBuffer[EEPROM_ZIRCON_CONFIG_END - 2];
		
	nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_INTLK_DURATION, &eepromBuffer[0], (EEPROM_ZIRCON_CONFIG_END - 2)); // just copy the buffer
	// Prototypeeeprom_crc = CalculateCRC( unsigned short Type,unsigned char *pData, unsigned short Len, unsigned short CRC1 );
	eeprom_crc = CalculateCRC(CRC16_WORD, (unsigned char *)&eepromBuffer[0], sizeof(eepromBuffer), 0x00);
	
	return eeprom_crc;
}

/*
// This is for testing the Buffer write code 
// we can keep it for the time being 
// and remove it when the code is mature enough
// and we don't need any testing of this functionality.

void TestEepromBufferReadWrite(void)
{
	uint16_t i = 0, size = 0;
	uint16_t eeprom_crc_write = 0, eeprom_crc_read = 0;
	unsigned char eepromBuffer[ZIRCON_CONFIG_END - 2];
	
	size = sizeof(eepromBuffer);
	
	memset(&eepromBuffer, 0, size);
	
	for(i = 0; i< size ; i++)
	{
		eepromBuffer[i] = i + 10;
	}
	
	nvm_eeprom_erase_and_write_buffer(ZIRCON_CONFIG_INTLK_DURATION, &eepromBuffer, (ZIRCON_CONFIG_END - 2));// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2
	
	
	memset(&eepromBuffer, 0, size);
	
	nvm_eeprom_read_buffer(ZIRCON_CONFIG_INTLK_DURATION, &eepromBuffer, (ZIRCON_CONFIG_END - 2)); // just copy the buffer
	
		  eeprom_crc_write = 0;
		  
		  eeprom_crc_read = 0;

	// Prototypeeeprom_crc = CalculateCRC( unsigned short Type,unsigned char *pData, unsigned short Len, unsigned short CRC1 );
	  eeprom_crc_write = CalculateCRC(CRC16_WORD, (unsigned char *)&eepromBuffer, sizeof(eepromBuffer), 0x00);
	  
	  nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc_write, 2);// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2
	  
	  nvm_eeprom_read_buffer(EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc_read, 2); // just copy the buffer
	  
	  eeprom_crc_write = 0;
	  
	  eeprom_crc_read = 0;

}

*/