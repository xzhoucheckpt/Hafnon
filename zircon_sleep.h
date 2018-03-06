/*******************************************************************
 *
 * File name: zircon_sleep.h
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
 * $History: zircon_sleep.h $
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:19p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * Reducing resource needs by consoladating
 *
 *****************************************************************/


#ifndef ZIRCON_SLEEP_H_
#define ZIRCON_SLEEP_H_

#if HALFNON
void prepare_for_sleep(void);
void restore_from_sleep(void);
void enter_sleep(void);
#endif


#endif /* ZIRCON_SLEEP_H_ */
