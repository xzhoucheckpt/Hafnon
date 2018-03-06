/*******************************************************************
 *
 * File name: watchdog.h
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
 * $History: watchdog.h $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:17p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Supporting watchdog
 * Send-Checkout-Project:
 * 
 ************************************************************************/


#ifndef WATCHDOG_H_
#define WATCHDOG_H_

//#include "avr_compiler.h"
#include "utility/compiler.h"
//#include "wdt.h"


/* Definition of macros */

/*! \brief Check if Synchronization busy flag is set. */
#define WDT_IsSyncBusy() (WDT.STATUS & WDT_SYNCBUSY_bm)

/*! \brief This macro resets the Watchdog Timer. */
#define WDT_Reset()	asm("wdr") //( watchdog_reset( ) )

#define wdt_enable(value) \
__asm__ __volatile__ ( \
"in __tmp_reg__, %0"  "\n\t" \
"out %1, %3"          "\n\t" \
"sts %2, %4"          "\n\t" \
"wdr"                 "\n\t" \
"out %0, __tmp_reg__" "\n\t" \
: \
: "M" (_SFR_MEM_ADDR(RAMPD)), \
"M" (_SFR_MEM_ADDR(CCP)), \
"M" (_SFR_MEM_ADDR(WDT_CTRL)), \
"r" ((uint8_t)0xD8), \
"r" ((uint8_t)(WDT_CEN_bm | WDT_ENABLE_bm | value)) \
: "r0" \
)


/* Prototypes of funtions. */

//void WDT_Enable(void);
void WDT_EnableAndSetTimeout(WDT_PER_t period);
void WDT_Disable(void);


#endif /* WATCHDOG_H_ */