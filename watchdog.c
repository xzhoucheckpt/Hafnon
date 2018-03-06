/*******************************************************************
 *
 * File name: watchdog.c
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
 * $History: watchdog.c $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:17p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Supporting watchdog
 * Send-Checkout-Project:
 * 
 ****************************************************************************/

#include "watchdog.h"


/*! \brief Enable Watchdog and set prescaler.
 *
 *  This function enables the Watchdog and applies prescaler settings.
 *  The Watchdog will be reset automatically.
 *
 *  The function writes the correct signature to the Configuration
 *  Change Protection register before writing the CTRL register. Interrupts are
 *  automatically ignored during the change enable period. TThe function will
 *  wait for the watchdog to be synchronized to the other clock domains. before
 *  proceeding
 *
 *  \param  period  Watchdog Timer timeout period
 */
void WDT_EnableAndSetTimeout( WDT_PER_t period )
{
	uint8_t temp = WDT_ENABLE_bm | WDT_CEN_bm | period;
	CCP = CCP_IOREG_gc;
	WDT.CTRL = temp;

	/* Wait for WD to synchronize with new settings. */
	while(WDT_IsSyncBusy()){

	}
}



/*! \brief Disable Watchdog without changing prescaler settings.
 *
 *  This function disables the Watchdog without changing the prescaler settings.
 *  If it is enabled at a later time, the prescaler setting can be reused.
 *  Note that the Watchdog can only be disabled in Safety Level 1.
 *
 *  The function writes the correct signature to the Configuration
 *  Change Protection register before writing the CTRL register. Interrupts are
 *  automatically ignored during the change enable period. Disable functions
 *  operate asynchronously with immidiate effect.
 */
void WDT_Disable( void )
{
	uint8_t temp = (WDT.CTRL & ~WDT_ENABLE_bm) | WDT_CEN_bm;
	CCP = CCP_IOREG_gc;
	WDT.CTRL = temp;
}

