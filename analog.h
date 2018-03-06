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
 * $History: analog.h $
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 1/28/14    Time: 7:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * New proto type for dac_write_data()
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 9/04/13    Time: 3:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new VPA rail voltage table with extended rail voltage (from:0-31
 * to 0-41) and removed the array structure from this file and placed it
 * in the .c file to reduce warnings
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Just a space
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "HAFNON define to comment out the VBAT function prototypes for
 * Thorite
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:39p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added prototypes for new functions for ADC ant current drivers
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:18p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created the DAC word table to map 0-19 index with a VPA voltage and
 * created the array mapping the DMS value. Created the prototype for the
 * VPA rail adj driver
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:48p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * File header
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
#ifndef __ADC_H__
#define __ADC_H__

#if HALFNON
#define VPA_REF_SCALER		34
#endif

#define VPA_4V				0x1740  //DMS=0: 320mv (4v)
#define VPA_5V				0x1c70  //DMS=1: 386mv (5v)
#define VPA_7V				0x2810  //DMS=2: 533mv (7v)
#define VPA_8V				0x2e80  //DMS=3: 614mv (8v)
#define VPA_10V				0x3a10  //DMS=4: 760mv (10v)
#define VPA_11V				0x40b0  //DMS=5: 844mv (11v)
#define VPA_12V				0x4670  //DMS=6: 917mv (12v)
#define VPA_14V				0x51f0  //DMS=7: 1.063v (14v)
#define VPA_15V				0x57c0  //DMS=8: 1.136v	(15)
#define VPA_17V				0x64b0  //DMS=9: 1.299v (17)
#define VPA_18V				0x69d0  //DMS=10: 1.364v (18)
#define VPA_20V				0x7600  //DMS=11: 1.518v (20)
#define VPA_21V				0x7bc0  //DMS=12: 1.59v (21)
#define VPA_22V				0x8190  //DMS=13: 1.664v (22)
#define VPA_24V				0x8de0  //DMS=14: 1.82v (24)
#define VPA_25V				0x9440  //DMS=15: 1.901v (25)
#define VPA_27V				0x9fe0  //DMS=16: 2.048v (27)
#define VPA_28V				0xa660  //DMS=17: 2.13v (28)
#define VPA_30V				0xb1e0  //DMS=18: 2.275v (30)
#define VPA_31V				0xb860  //DMS=19: 2.357v (31)
#define VPA_32V				0xbe30  //DMS=20: 2.43v (32)
#define VPA_34V				0xca80  //DMS=21: 2.586v (34)
#define VPA_35V				0xd050  //DMS=22: 2.66v (35)
#define VPA_37V				0xdc80  //DMS=23: 2.813v (37)
#define VPA_38V				0xe250  //DMS=24: 2.887v (38)
#define VPA_40V				0xede0  //DMS=25: 3.033v (40)
#define VPA_41V				0xf450  //DMS=26: 3.115v (41)

#if 0
// Defines for DMS values to MAX CE VPA voltage rail
#define VPA_4V				0x0990  //DMS=0: 300mv (4v)
#define VPA_5V				0x12e0  //DMS=1: 409mv (5v)
#define VPA_7V				0x1b00  //DMS=2: 502mv (7v)
#define VPA_8V				0x2390  //DMS=3: 599mv (8v)
#define VPA_10V				0x2c20  //DMS=4: 696mv (10v)
#define VPA_11V				0x3500  //DMS=5: 796mv (11v)
#define VPA_12V				0x3df0  //DMS=6: 898mv (12v)
#define VPA_14V				0x46f0  //DMS=7: 999mv (14v)
#define VPA_15V				0x4ff0  //DMS=8: 1.1v
#define VPA_17V				0x58f0  //DMS=9: 1.204v
#define VPA_18V				0x61f0  //DMS=10: 1.306v
#define VPA_20V				0x6af0  //DMS=11: 1.408v
#define VPA_21V				0x72f0  //DMS=12: 1.499v
#define VPA_22V				0x7bf0  //DMS=13: 1.601v
#define VPA_24V				0x84f0  //DMS=14: 1.704v
#define VPA_25V				0x8df0  //DMS=15: 1.806v
#define VPA_27V				0x95f0  //DMS=16: 1.898v
#define VPA_28V				0x9ef0  //DMS=17: 2v
#define VPA_30V				0xb0f0  //DMS=18: 2.204v
#define VPA_31V				0xb9f0  //DMS=19: 2.306v
#endif

extern uint16_t gVPA_Adj_CE[];

#if HALFNON
void ac_init(void);
void ac_enable(void);
void ac_disable(void);
#endif

void dac_enable(void);
void dac_init(void);
void dac_disable(void);
//void dac_write_data(void);
void dac_write_data(uint8_t enable);
void dac_VPA_adj(uint16_t dac_value);

void adc_init(void);
void adc_enable(void);
void adc_disable(void);
void adc0_start(void);


#endif