/*******************************************************************
 *
 * File name: dds.h
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
 * $History: dds.h $
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 2:59p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings
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
 * User: Galantij     Date: 6/03/13    Time: 1:55p
 * Created in $/Zircon/Thorite/Thorite_Test/Hafnon
 * This is initial checkin
 * 
 ****************************************************************/

#ifndef DDS_H_
#define DDS_H_

#include "spi.h"

/** \name AD9833 waveform output modes
 * Parameters of \ref ad9833_set_mode()
 * @{
 */
#define AD_OFF      0
#define AD_TRIANGLE 1
#define AD_SQUARE   2
#define AD_SINE     3
/**@}*/

/** \name AD9833 command register bits
 * @{
 */
// Look at page 14 of the data sheet for the explanations
#define AD_B28     13
#define AD_HLB     12
#define AD_FSELECT 11
#define AD_PSELECT 10
#define AD_RESET   8
#define AD_SLEEP1  7
#define AD_SLEEP12 6
#define AD_OPBITEN 5
#define AD_DIV2    3
#define AD_MODE    1

/** @}*/

/** \name AD9833 register addresses
 * @{
 */
#define AD_FREQ0  (1<<14)
#define AD_FREQ1  (1<<15)
#define AD_PHASE0 (3<<14)
#define AD_PHASE1 ((3<<14)|(1<<13))

/** @}*/

/** \name AD9833 calculation macros
 * @{ */
#define AD_F_MCLK 25000000 ///<Clock speed of the ad9833 reference clock
#define AD_2POW28 268435456 ///<used in calculating output freq

/** Macro that calculates the value for a ad9833 frequency register from a frequency */
#define AD_FREQ_CALC(freq) (uint32_t)(((double)AD_2POW28/(double)AD_F_MCLK*freq)*4)

/** Macro that calculates the value for a ad9833 phase register from a phase in degrees */
#define AD_PHASE_CALC(phase_deg) (uint16_t)((512*phase_deg)/45)
/** @} */

#if USE_DDS

/** Struct that holds all the configuration it's initialized as a global variable
 * in the ad9833.c file */
typedef struct {
    float    freq[2]; ///<Holds the frequencies of the two registers
    float    phase[2];
    uint8_t  freq_out;
    uint8_t  phase_out;
    uint8_t  mode;
    uint16_t command_reg;
} ad9833_settings_t;


//some functions could be done more efficiently, maybe as inline functions...

void	ad9833_init(void);

void	ad9833_set_mode(uint8_t mode);

void    ad9833_set_frequency(uint8_t reg, double freq);
// Use ad9833_set_frequency_abs for seting the frequency
void	ad9833_set_frequency_abs(uint8_t reg, uint32_t freq);
double  ad9833_get_frequency(uint8_t reg);

void    ad9833_set_phase(uint8_t reg, double phase);
double  ad9833_get_phase(uint8_t reg);

void    ad9833_set_freq_out(uint8_t freq_out);
uint8_t ad9833_get_freq_out(void);

void    ad9833_set_phase_out(uint8_t phase_out);
uint8_t ad9833_get_phase_out(void);

#endif // If use DDS

#endif /* DDS_H_ */