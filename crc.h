/*
 * crc.h
 *
 * Created: 6/3/2013 11:38:17 AM
 *  Author: dubes
 *
 * $History: crc.h $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:08p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Added files to support DMS tool
 * 
 *********************************************************************/

// This logic is take from the Evolve Code CRC.h base and integrated into Zircon code base
// to maintain seamless of communication between system
// pragma once is commented out since we are using include guards

// #pragma once

#ifndef CRC_H_
#define CRC_H_


/** include files **/
// This function does not exists in the Evolve code
// unsigned short crc16(unsigned char *ptr, unsigned short count);

// --- CRC related definitions...
#define CRC16_WORD          0xA001
#define CRC_CCITT_WORD      0x8408
#define INI_CRC16_WORD      0x0

unsigned short CalculateCRC( unsigned short Type,unsigned char *pData, unsigned short Len, unsigned short CRC1 );

//uint16_t CalculateCRC( uint16_t Type, uint8_t *pData, uint16_t Len, uint16_t CRC );


#endif /* CRC_H_ */