/*******************************************************************
 *
 * File name: spi.h
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
 * $History: spi.h $
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:29p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added pre-defines for commenting out cowde for Hafnon HW
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:49p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * File header added
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 2:03p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * This is initial checkin
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/03/13    Time: 1:56p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#include "lowlevel.h"

#define DDS_SPI_BAUD(x)		(F_CPU / (2 * x)) - 1

// Taken from usart.c as this is absent in the headers
/*
 * Fix XMEGA header files
 * USART.CTRLC  bit masks and bit positions
 */
#ifndef USART_UCPHA_bm
#  define USART_UCPHA_bm 0x02
#endif
#ifndef USART_DORD_bm
#  define USART_DORD_bm 0x04
#endif

// Defines taken from ioport.h
/** \name IOPORT Mode bit definitions */
/** @{ */
// #define IOPORT_MODE_TOTEM           (0x00 << 3) /*!< Totem-pole */ defined also in iox128a4u.h
#define IOPORT_MODE_INVERT_PIN      (0x01 << 6) /*!< Invert output and input */

#if HALFNON
void host_spi_init(void);
void host_spi_enable(void);
void host_spi_disable(void);
#endif

#if USE_DDS
void dds_spi_init(void);
void dds_spi_enable(void);
void dds_spi_disable(void);
//void dds_send_data(uint8_t *data, uint8_t len);
void dds_send_data( uint16_t data ); // Sandeep Changed 
void dds_send_data_freq( uint16_t data );
#endif

#endif