/*******************************************************************
 *
 * File name: freq_tables.h
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
 * $History: freq_tables.h $
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 3/05/14    Time: 10:51a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new SRRC table from the measurements we made here. The transmit
 * gap is now 8.1 to 8.6 MHz and this will be the last tag band in DMS and
 * labeled "SRRC Tag Band"
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new frequency and count table for SRRC compliance (China). The
 * table could change after SRRC testing is completed.
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 2/13/14    Time: 4:24p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Had the first freq table counts backwards....
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 2/11/14    Time: 1:40p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Reversed the first table to comform with the other 7 freq tables and
 * changed the macro define from REV=1 to REV=0. This should  be low to
 * high for all freq tables
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:09a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Moved the counter values from freq_cntr.h to freq_tables.h, to get rid
 * of FrequencyCounPtr related Warnings and added new default value for
 * the frequency table to correspond to our new H/W
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Frequency table updated for index 0 to 7
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/15/13    Time: 3:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added freq table from Bob for the first tag band to be more accurate
 * for the new HW
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:19p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Reducing resource needs by consoladating
 * 
 ******************************************************************/


#ifndef FREQ_TABLES_H_
#define FREQ_TABLES_H_

#include "globals.h"

#if USE_DDS

// for 12.5 MHZ  clock
// All freq are in MHz
#define DDS_FREQ_8610				0xB055326
#define DDS_FREQ_8555				0xAF34D6A
#define DDS_FREQ_8500				0xAE147AE
#define DDS_FREQ_8446				0xACF95D5
#define DDS_FREQ_8391				0xABD9019
#define DDS_FREQ_8337				0xAABDE40
#define DDS_FREQ_8282				0xA99D884
#define DDS_FREQ_8227				0xA87D2C8
#define DDS_FREQ_8173				0xA7620EF
#define DDS_FREQ_8118				0xA641B33
#define DDS_FREQ_8063				0xA521577
#define DDS_FREQ_8009				0xA40639D
#define DDS_FREQ_7954				0xA2E5DE1
#define DDS_FREQ_7899				0xA1C5825
#define DDS_FREQ_7845				0xA0AA64C
#define DDS_FREQ_7790				0x9F505D1


// DDS table
static const uint32_t gFrequencyTable[NO_OF_FREQUENCY_TABLE_VALUES] = {
	
	DDS_FREQ_8610, DDS_FREQ_8555, DDS_FREQ_8500, DDS_FREQ_8446,
	DDS_FREQ_8391, DDS_FREQ_8337, DDS_FREQ_8282, DDS_FREQ_8227,
	DDS_FREQ_8173, DDS_FREQ_8118, DDS_FREQ_8063, DDS_FREQ_8009,
	DDS_FREQ_7954, DDS_FREQ_7899, DDS_FREQ_7845, DDS_FREQ_7790
};

#else  // using DAC

// Latest H/W 08/27/2013
#define FREQ_8610				0xA335
#define FREQ_8555				0xA0FC
#define FREQ_8500				0x9EA6
#define FREQ_8446				0x9C6B
#define FREQ_8391				0x9A46
#define FREQ_8337				0x9839
#define FREQ_8282				0x962A
#define FREQ_8227				0x941D
#define FREQ_8173				0x9231
#define FREQ_8118				0x9040
#define FREQ_8063				0x8E7A
#define FREQ_8009				0x8CA4
#define FREQ_7954				0x8AF6
#define FREQ_7899				0x8938
#define FREQ_7845				0x87AB
#define FREQ_7790				0x85F1

#if 0 // reversed this table to match the other tables
// default table 7.6 to 8.7 MHz (DMS index 0)
static uint16_t FreqTable76_87[] = {
	
	FREQ_8610, FREQ_8555, FREQ_8500, FREQ_8446,
	FREQ_8391, FREQ_8337, FREQ_8282, FREQ_8227,
	FREQ_8173, FREQ_8118, FREQ_8063, FREQ_8009,
	FREQ_7954, FREQ_7899, FREQ_7845, FREQ_7790

};
#endif

// default table 7.6 to 8.7 MHz (DMS index 0)
static uint16_t FreqTable76_87[] = {
	
	FREQ_7790, FREQ_7845, FREQ_7899, FREQ_7954,
	FREQ_8009, FREQ_8063, FREQ_8118, FREQ_8173,
	FREQ_8227, FREQ_8282, FREQ_8337, FREQ_8391,
	FREQ_8446, FREQ_8500, FREQ_8555, FREQ_8610

};

// Latest H/W 08/27/2013
#define FREQ_7400				0x7806
#define FREQ_7500				0x7B50
#define FREQ_7600				0x7E9E
#define FREQ_7700				0x81C1
#define FREQ_7800				0x85C2
#define FREQ_7900				0x88D8
#define FREQ_8000				0x8C60
#define FREQ_8100				0x8F67
#define FREQ_8200				0x92C5
#define FREQ_8300				0x96A0
#define FREQ_8400				0x9A52
#define FREQ_8600				0xA2A1
#define FREQ_8700				0xA6F4
#define FREQ_8800				0xAB8C
#define FREQ_8900				0xB03A

// 7.4 to 9.0 MHz (DMS index 1) FCC only
static uint16_t FreqTable74_90[] = {

	FREQ_7400, FREQ_7500, FREQ_7600, FREQ_7700,
	FREQ_7800, FREQ_7900, FREQ_8000, FREQ_8100,
	FREQ_8200, FREQ_8300, FREQ_8400, FREQ_8500,
	FREQ_8600, FREQ_8700, FREQ_8800, FREQ_8900

};


// Latest H/W 08/27/2013
#define FREQ_7490				0x7D96
#define FREQ_7580				0x8012
#define FREQ_7670				0x828C
#define FREQ_7760				0x8528
#define FREQ_7850				0x87C2
#define FREQ_7940				0x8A98
#define FREQ_8030				0x8D64
#define FREQ_8120				0x9066
#define FREQ_8390				0x9A3A
#define FREQ_8480				0x9DCC
#define FREQ_8570				0xA185
#define FREQ_8660				0xA57E
#define FREQ_8750				0xA971

// 7.4 to 8.8 MHz (DMS index 2)
static uint16_t FreqTable74_88[] = {

	FREQ_7400, FREQ_7490, FREQ_7580, FREQ_7670,
	FREQ_7760, FREQ_7850, FREQ_7940, FREQ_8030,
	FREQ_8120, FREQ_8200, FREQ_8300, FREQ_8390,
	FREQ_8480, FREQ_8570, FREQ_8660, FREQ_8750

};

// Latest H/W 08/27/2013
#define FREQ_9000				0xB52F
#define FREQ_9100				0xBA22
#define FREQ_9200				0xBF32
#define FREQ_9300				0xC483

// 7.8 to 9.4 MHz (DMS index 3) FCC only
static uint16_t FreqTable78_94[] = {

	FREQ_7800, FREQ_7900, FREQ_8000, FREQ_8100,
	FREQ_8200, FREQ_8300, FREQ_8400, FREQ_8500,
	FREQ_8600, FREQ_8700, FREQ_8800, FREQ_8900,
	FREQ_9000, FREQ_9100, FREQ_9200, FREQ_9300

};

// Latest H/W 08/27/2013
#define FREQ_8060				0x8E38
#define FREQ_8190				0x92A4
#define FREQ_8320				0x9775
#define FREQ_8450				0x9C8F
#define FREQ_8710				0xA794
#define FREQ_8840				0xAD81
#define FREQ_8970				0xB3A1
#define FREQ_9230				0xC0C2
#define FREQ_9360				0xC7BE
#define FREQ_9480				0xCE49
#define FREQ_9620				0xD62E
#define FREQ_9750				0xDDB6

// 7.8 to 9.8 MHz (DMS index 4) FCC only
static uint16_t FreqTable78_98[] = {

	FREQ_7800, FREQ_7940, FREQ_8060, FREQ_8190,
	FREQ_8320, FREQ_8450, FREQ_8570, FREQ_8710,
	FREQ_8840, FREQ_8970, FREQ_9100, FREQ_9230,
	FREQ_9360, FREQ_9480, FREQ_9620, FREQ_9750

};

// Latest H/W 08/27/2013
#define FREQ_7640				0x8112
#define FREQ_7710				0x8338
#define FREQ_8140				0x90E2
#define FREQ_8280				0x95F8
#define FREQ_8350				0x9890
#define FREQ_8420				0x9B60

// 7.5 to 8.6 MHz (DMS index 5)
static uint16_t FreqTable75_86[] = {

	FREQ_7500, FREQ_7580, FREQ_7640, FREQ_7710,
	FREQ_7790, FREQ_7850, FREQ_7940, FREQ_8000,
	FREQ_8060, FREQ_8140, FREQ_8200, FREQ_8280,
	FREQ_8350, FREQ_8420, FREQ_8480, FREQ_8570

};

// Latest H/W 08/27/2013
#define FREQ_7830				0x872C
#define FREQ_7970				0x8B73
#define FREQ_8250				0x951D
#define FREQ_8540				0xA050
#define FREQ_8680				0xA662

// 7.7 to 8.8 MHz (DMS index 6)
static uint16_t FreqTable77_88[] = {

	FREQ_7700, FREQ_7760, FREQ_7830, FREQ_7900,
	FREQ_7970, FREQ_8030, FREQ_8100, FREQ_8190,
	FREQ_8250, FREQ_8320, FREQ_8400, FREQ_8480,
	FREQ_8540, FREQ_8610, FREQ_8680, FREQ_8750

};


// Latest H/W 08/27/2013
#define FREQ_8920				0xB174
#define FREQ_9160				0xBD44
#define FREQ_9320				0xC5B2
#define FREQ_9400				0xCA07
//#define FREQ_9480				0xCE71
#define FREQ_9560				0xD30A
#define FREQ_9640				0xD784
#define FREQ_9720				0xDC30

// 8.5 to 9.8 MHz (DMS index 7) FCC only
static uint16_t FreqTable85_98[] = {

	FREQ_8500, FREQ_8600, FREQ_8680, FREQ_8750,
	FREQ_8840, FREQ_8920, FREQ_9000, FREQ_9100,
	FREQ_9160, FREQ_9230, FREQ_9320, FREQ_9400,
	FREQ_9480, FREQ_9560, FREQ_9640, FREQ_9720

};

#if 0
// 7.4 to 8.8 MHz (DMS index 8)  gap between 8.3 and 8.4 MHz
// SRRC (China compliance)
static uint16_t FreqTable_SRRC[] = {

	FREQ_7400, FREQ_7490, FREQ_7580, FREQ_7670,
	FREQ_7760, FREQ_7850, FREQ_7940, FREQ_8030,
	FREQ_8120, FREQ_8200, FREQ_8300, FREQ_8400,
	FREQ_8480, FREQ_8570, FREQ_8660, FREQ_8750

};
#endif

// 7.4 to 8.8 MHz (DMS index 8)  gap between 8.1 and 8.6 MHz
static uint16_t FreqTable_SRRC[] = {

	FREQ_7400, FREQ_7490, FREQ_7580, FREQ_7670,
	FREQ_7760, FREQ_7850, FREQ_7940, FREQ_8030,
	FREQ_8100, FREQ_8100, FREQ_8100, FREQ_8600,
	FREQ_8600, FREQ_8600, FREQ_8660, FREQ_8750

};

static uint16_t *FreqTablePtr[] = {
	
	FreqTable76_87, FreqTable74_90, FreqTable74_88, FreqTable78_94,
	FreqTable78_98, FreqTable75_86, FreqTable77_88, FreqTable85_98,
	FreqTable_SRRC
};

#endif // Not using DAC

// Moved the Tables here
//-----------------------
// Feed back Loops Defines

//Note: Count correspond to frequency Should be revised for different calculations

#if EXPAND_TO_32_BITS  // This is only used for the 32 bit mode and is not active at this time.

// count for 24.003 MHZ clock
#define COUNT_8610				47016
#define COUNT_8555				46716
#define COUNT_8500				46416
#define COUNT_8446				46121
#define COUNT_8391				45820
#define COUNT_8337				45526
#define COUNT_8282				45225
#define COUNT_8227				44925
#define COUNT_8173				44630
#define COUNT_8118				44330
#define COUNT_8063				44029
#define COUNT_8009				43734
#define COUNT_7954				43434
#define COUNT_7899				43134
#define COUNT_7845				42839
#define COUNT_7790				42539


// default table 7.6 to 8.7 MHz (DMS index 0)
static uint32_t FreqCount76_87[NO_OF_FREQUENCY_TABLE_VALUES] = {
	
	COUNT_8610, COUNT_8555, COUNT_8500, COUNT_8446,
	COUNT_8391, COUNT_8337, COUNT_8282, COUNT_8227,
	COUNT_8173, COUNT_8118, COUNT_8063, COUNT_8009,
	COUNT_7954, COUNT_7899, COUNT_7845, COUNT_7790

};

//----------- New Tables ---------------

// count for 24.003 MHZ clock

#define COUNT_7400		40409
#define COUNT_7500		40955
#define COUNT_7600		41501
#define COUNT_7700		42047
#define COUNT_7800		42593
#define COUNT_7900		43139
#define COUNT_8000		43685
#define COUNT_8100		44231
#define COUNT_8200		44777
#define COUNT_8300		45323
#define COUNT_8400		45870
#define COUNT_8600		46962
#define COUNT_8700		47508
#define COUNT_8800		48054
#define COUNT_8900		48600


// 7.4 to 9.0 MHz (DMS index 1) FCC only
static uint32_t FreqCount74_90[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7500, COUNT_7600, COUNT_7700,
	COUNT_7800, COUNT_7900, COUNT_8000, COUNT_8100,
	COUNT_8200, COUNT_8300, COUNT_8400, COUNT_8500,
	COUNT_8600, COUNT_8700, COUNT_8800, COUNT_8900

};

// count for 24.003 MHZ clock
#define COUNT_7490		40900
#define COUNT_7580		41392
#define COUNT_7670		41883
#define COUNT_7760		42375
#define COUNT_7850		42866
#define COUNT_7940		43356
#define COUNT_8030		43849
#define COUNT_8120		44341
#define COUNT_8390		45815
#define COUNT_8480		46306
#define COUNT_8570		46798
#define COUNT_8660		47289
#define COUNT_8750		47781

// 7.4 to 8.8 MHz (DMS index 2)
static uint32_t FreqCount74_88[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8120, COUNT_8200, COUNT_8300, COUNT_8390,
	COUNT_8480, COUNT_8570, COUNT_8660, COUNT_8750

};

// count for 24.003 MHZ clock
#define COUNT_9000		49145.85677
#define COUNT_9100		49691.92184
#define COUNT_9200		50237.98692
#define COUNT_9300		50784.05199

// 7.8 to 9.4 MHz (DMS index 3) FCC only
static uint32_t FreqCount78_94[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7800, COUNT_7900, COUNT_8000, COUNT_8100,
	COUNT_8200, COUNT_8300, COUNT_8400, COUNT_8500,
	COUNT_8600, COUNT_8700, COUNT_8800, COUNT_8900,
	COUNT_9000, COUNT_9100, COUNT_9200, COUNT_9300

};

// count for 24.003 MHZ clock
#define COUNT_8060		44013
#define COUNT_8190		44723
#define COUNT_8320		45436
#define COUNT_8450		46143
#define COUNT_8710		47562
#define COUNT_8840		48272
#define COUNT_8970		48982
#define COUNT_9230		50402
#define COUNT_9360		51112
#define COUNT_9480		51767
#define COUNT_9620		52532
#define COUNT_9750		53241

// 7.8 to 9.8 MHz (DMS index 4) FCC only
static uint32_t FreqCount78_98[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7800, COUNT_7940, COUNT_8060, COUNT_8190,
	COUNT_8320, COUNT_8450, COUNT_8570, COUNT_8710,
	COUNT_8840, COUNT_8970, COUNT_9100, COUNT_9230,
	COUNT_9360, COUNT_9480, COUNT_9620, COUNT_9750

};

// count for 24.003 MHZ clock
#define COUNT_7640		41719
#define COUNT_7710		42102
#define COUNT_8140		44450
#define COUNT_8280		45214
#define COUNT_8350		45596
#define COUNT_8420		45979

// 7.5 to 8.6 MHz (DMS index 5)
static uint32_t FreqCount75_86[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7500, COUNT_7580, COUNT_7640, COUNT_7710,
	COUNT_7790, COUNT_7850, COUNT_7940, COUNT_8000,
	COUNT_8060, COUNT_8140, COUNT_8200, COUNT_8280,
	COUNT_8350, COUNT_8420, COUNT_8480, COUNT_8570

};

// count for 24.003 MHZ clock
#define COUNT_7830		42757
#define COUNT_7970		43521
#define COUNT_8250		45050
#define COUNT_8540		46634
#define COUNT_8680		47399

// 7.7 to 8.8 MHz (DMS index 6)
static uint32_t FreqCount77_88[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7700, COUNT_7760, COUNT_7830, COUNT_7900,
	COUNT_7970, COUNT_8030, COUNT_8100, COUNT_8190,
	COUNT_8250, COUNT_8320, COUNT_8400, COUNT_8480,
	COUNT_8540, COUNT_8610, COUNT_8680, COUNT_8750

};

// count for 24.003 MHZ clock
#define COUNT_8920		48709
#define COUNT_9160		50020
#define COUNT_9320		50893
#define COUNT_9400		51330
#define COUNT_9480		51767
#define COUNT_9560		52204
#define COUNT_9640		52641
#define COUNT_9720		53078

// 8.5 to 9.8 MHz (DMS index 7) FCC only
static uint32_t FreqCount85_98[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_8500, COUNT_8600, COUNT_8680, COUNT_8750,
	COUNT_8840, COUNT_8920, COUNT_9000, COUNT_9100,
	COUNT_9160, COUNT_9230, COUNT_9320, COUNT_9400,
	COUNT_9480, COUNT_9560, COUNT_9640, COUNT_9720

};

#if 0
// SRRC table (DMS index 8)  gap between 8.3 and 8.4 MHz
// 7.4 to 8.75 MHz
static uint32_t FreqCount_SRRC[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8120, COUNT_8200, COUNT_8300, COUNT_8400,
	COUNT_8480, COUNT_8570, COUNT_8660, COUNT_8750
};
#endif

// SRRC table (DMS index 8)  gap between 8.1 and 8.6 MHz
static uint32_t FreqCount_SRRC[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8100, COUNT_8100, COUNT_8100, COUNT_8600,
	COUNT_8600, COUNT_8600, COUNT_8660, COUNT_8750

};


//-----------End Of New Tables-----------

static uint32_t *FrequencyCounPtr[] = {
	
	FreqCount76_87, FreqCount74_90, FreqCount74_88, FreqCount78_94,
	FreqCount78_98, FreqCount75_86, FreqCount77_88, FreqCount85_98,
	FreqCount_SRRC
};

#else  // This is what we are using for the freq counting feature

// count for 24.003 MHZ clock
#define COUNT_8610				47016
#define COUNT_8555				46716
#define COUNT_8500				46416
#define COUNT_8446				46121
#define COUNT_8391				45820
#define COUNT_8337				45526
#define COUNT_8282				45225
#define COUNT_8227				44925
#define COUNT_8173				44630
#define COUNT_8118				44330
#define COUNT_8063				44029
#define COUNT_8009				43734
#define COUNT_7954				43434
#define COUNT_7899				43134
#define COUNT_7845				42839
#define COUNT_7790				42539

// default table 7.6 to 8.7 MHz (DMS index 0)
static uint16_t FreqCount76_87[NO_OF_FREQUENCY_TABLE_VALUES] = {
	
	COUNT_7790, COUNT_7845, COUNT_7899, COUNT_7954,
	COUNT_8009, COUNT_8063, COUNT_8118, COUNT_8173,
	COUNT_8227, COUNT_8282, COUNT_8337, COUNT_8391,
	COUNT_8446, COUNT_8500, COUNT_8555, COUNT_8610

};

//----------- New Tables ---------------

// count for 24.003 MHZ clock
#define COUNT_7400		40409
#define COUNT_7500		40955
#define COUNT_7600		41501
#define COUNT_7700		42047
#define COUNT_7800		42593
#define COUNT_7900		43139
#define COUNT_8000		43685
#define COUNT_8100		44231
#define COUNT_8200		44777
#define COUNT_8300		45323
#define COUNT_8400		45870
#define COUNT_8600		46962
#define COUNT_8700		47508
#define COUNT_8800		48054
#define COUNT_8900		48600


// 7.4 to 9.0 MHz (DMS index 1) FCC only
static uint16_t FreqCount74_90[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7500, COUNT_7600, COUNT_7700,
	COUNT_7800, COUNT_7900, COUNT_8000, COUNT_8100,
	COUNT_8200, COUNT_8300, COUNT_8400, COUNT_8500,
	COUNT_8600, COUNT_8700, COUNT_8800, COUNT_8900

};

// count for 24.003 MHZ clock
#define COUNT_7490		40900
#define COUNT_7580		41392
#define COUNT_7670		41883
#define COUNT_7760		42375
#define COUNT_7850		42866
#define COUNT_7940		43356
#define COUNT_8030		43849
#define COUNT_8120		44341
#define COUNT_8390		45815
#define COUNT_8480		46306
#define COUNT_8570		46798
#define COUNT_8660		47289
#define COUNT_8750		47781

// 7.4 to 8.8 MHz (DMS index 2)
static uint16_t FreqCount74_88[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8120, COUNT_8200, COUNT_8300, COUNT_8390,
	COUNT_8480, COUNT_8570, COUNT_8660, COUNT_8750

};

// count for 24.003 MHZ clock
#define COUNT_9000		49145.85677
#define COUNT_9100		49691.92184
#define COUNT_9200		50237.98692
#define COUNT_9300		50784.05199

// 7.8 to 9.4 MHz (DMS index 3) FCC only
static uint16_t FreqCount78_94[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7800, COUNT_7900, COUNT_8000, COUNT_8100,
	COUNT_8200, COUNT_8300, COUNT_8400, COUNT_8500,
	COUNT_8600, COUNT_8700, COUNT_8800, COUNT_8900,
	COUNT_9000, COUNT_9100, COUNT_9200, COUNT_9300

};

// count for 24.003 MHZ clock
#define COUNT_8060		44013
#define COUNT_8190		44723
#define COUNT_8320		45436
#define COUNT_8450		46143
#define COUNT_8710		47562
#define COUNT_8840		48272
#define COUNT_8970		48982
#define COUNT_9230		50402
#define COUNT_9360		51112
#define COUNT_9480		51767
#define COUNT_9620		52532
#define COUNT_9750		53241

// 7.8 to 9.8 MHz (DMS index 4) FCC only
static uint16_t FreqCount78_98[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7800, COUNT_7940, COUNT_8060, COUNT_8190,
	COUNT_8320, COUNT_8450, COUNT_8570, COUNT_8710,
	COUNT_8840, COUNT_8970, COUNT_9100, COUNT_9230,
	COUNT_9360, COUNT_9480, COUNT_9620, COUNT_9750

};

// count for 24.003 MHZ clock
#define COUNT_7640		41719
#define COUNT_7710		42102
#define COUNT_8140		44450
#define COUNT_8280		45214
#define COUNT_8350		45596
#define COUNT_8420		45979

// 7.5 to 8.6 MHz (DMS index 5)
static uint16_t FreqCount75_86[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7500, COUNT_7580, COUNT_7640, COUNT_7710,
	COUNT_7790, COUNT_7850, COUNT_7940, COUNT_8000,
	COUNT_8060, COUNT_8140, COUNT_8200, COUNT_8280,
	COUNT_8350, COUNT_8420, COUNT_8480, COUNT_8570

};

// count for 24.003 MHZ clock
#define COUNT_7830		42757
#define COUNT_7970		43521
#define COUNT_8250		45050
#define COUNT_8540		46634
#define COUNT_8680		47399

// 7.7 to 8.8 MHz (DMS index 6)
static uint16_t FreqCount77_88[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7700, COUNT_7760, COUNT_7830, COUNT_7900,
	COUNT_7970, COUNT_8030, COUNT_8100, COUNT_8190,
	COUNT_8250, COUNT_8320, COUNT_8400, COUNT_8480,
	COUNT_8540, COUNT_8610, COUNT_8680, COUNT_8750

};

// count for 24.003 MHZ clock
#define COUNT_8920		48709
#define COUNT_9160		50020
#define COUNT_9320		50893
#define COUNT_9400		51330
#define COUNT_9480		51767
#define COUNT_9560		52204
#define COUNT_9640		52641
#define COUNT_9720		53078

// 8.5 to 9.8 MHz (DMS index 7) FCC only
static uint16_t FreqCount85_98[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_8500, COUNT_8600, COUNT_8680, COUNT_8750,
	COUNT_8840, COUNT_8920, COUNT_9000, COUNT_9100,
	COUNT_9160, COUNT_9230, COUNT_9320, COUNT_9400,
	COUNT_9480, COUNT_9560, COUNT_9640, COUNT_9720

};

#if 0
// SRRC table (DMS index 8)  gap between 8.3 and 8.4 MHz
// 7.4 to 8.75 MHz
static uint16_t FreqCount_SRRC[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8120, COUNT_8200, COUNT_8300, COUNT_8400,
	COUNT_8480, COUNT_8570, COUNT_8660, COUNT_8750
};
#endif

// SRRC table (DMS index 8)  gap between 8.1 and 8.6 MHz
static uint16_t FreqCount_SRRC[NO_OF_FREQUENCY_TABLE_VALUES] = {

	COUNT_7400, COUNT_7490, COUNT_7580, COUNT_7670,
	COUNT_7760, COUNT_7850, COUNT_7940, COUNT_8030,
	COUNT_8100, COUNT_8100, COUNT_8100, COUNT_8600,
	COUNT_8600, COUNT_8600, COUNT_8660, COUNT_8750

};


//-----------End Of New Tables-----------

static uint16_t *FrequencyCounPtr[] = {
	
	FreqCount76_87, FreqCount74_90, FreqCount74_88, FreqCount78_94,
	FreqCount78_98, FreqCount75_86, FreqCount77_88, FreqCount85_98,
	FreqCount_SRRC
};

#endif  // end of if def 32


//----------------------
// End of tables

#endif /* FREQ_TABLES_H_ */