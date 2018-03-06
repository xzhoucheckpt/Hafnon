/*
 * crc.c
 *
 * Created: 6/3/2013 11:38:17 AM
 *  Author: dubes
 *
 * $History: crc.c $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 7/09/13    Time: 12:08p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Added files to support DMS tool
 * 
 *********************************************************************/

// This logic is take from the Evolve Code CRC.cpp base and integrated into Zircon code base
// to maintain seamless of communication between system


#include "stdio.h"
#include "globals.h"
#include "crc.h"

/* ********************************************************
   The lookup table based reflected CRC16 methods are below
   ******************************************************** */
static unsigned short crcTable[256];                       // Lookup table empty (can be pre-init const)
static bool bHasTable = false;	// need to generate table once

// ------------------------------------------------------------------------
// crcTableGen
//
// Method to Generate table entries for CRC16
//
// Parameters:	none
//
// Note: only support CRC16 with seed == 0, for now (Type not used)
// ------------------------------------------------------------------------
void crcTableGen(void)
{
	int i, j;
	unsigned short k;

	for (i = 0; i < 256; i++) {                     // loop through all table entries
	k = i;                                      // temp for crc calculation
	for (j = 8; j; j--) {                       // loop through bits
	if (k & 0x0001) {                       // shift or shift and xor with poly
	k = (k >> 1) ^ 0xA001;
} else {
	k >>= 1;
}
        }
        crcTable[i] =  k;                           // store entry
    }
    
    // print CRC table for validation
//	crcTablePrint();
}

// ------------------------------------------------------------------------
// CalculateCRC - returns the calculated CRC value for the record
//
// Method to Calculate CRC16 using the crcTable
//
// Parameters:
//		Type: CCITT (not supported) or CRC16
// 		*pData is a pointer to the data array
// 		len is the length of the data array
// 		crc is the initial value of the crc register
// 
// Note: only support CRC16 with seed == 0, for now (Type not used)
// ------------------------------------------------------------------------
unsigned short CalculateCRC(unsigned short Type,
	unsigned char *pData, unsigned short len, unsigned short crc)
{
    if (!bHasTable)
    {
	crcTableGen();			// Generate table entries
	bHasTable = true;
    }
    
    while (len--) {
        crc = crcTable[(crc ^ *pData++) & 0xFF] ^ (crc >> 8);
    }

    return crc;
}





