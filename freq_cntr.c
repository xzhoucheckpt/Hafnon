/*******************************************************************
 *
 * File name: freq_cntr.c
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
 * Creator: Dubes
 *
 * Date Created:
 *
 * $History: freq_cntr.c $
 * 
 * *****************  Version 5  *****************
 * User: Dubes        Date: 10/10/13   Time: 5:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * corrected correctly 
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 9/20/13    Time: 1:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Formating Changes
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * removed a comment in a comment which caused a warning
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:24p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * used for freq counter when enabled
 *
*******************************************************************/

#include <stdint.h>
#include "globals.h"
#include "lowlevel.h"
#include "freq_cntr.h"
#include <avr/interrupt.h>

#if EXPAND_TO_32_BITS
uint32_t ic_result = 0;
uint32_t prev_difference = 0;
#else
uint16_t ic_result = 0;
uint16_t prev_difference = 0;
#endif

uint8_t clk_sel = 0;

/*
void xmega_tcca_clk_freq_sel(uint8_t select){
	
	clk_sel = select;
}
*/ 
void  xmega_freq_cntr_init(void){


// 1. Connect Event Chan to the input pin EVENT_SYSTEM_INPUT PIN to TCCA's clock input pin.

	
    EVSYS.CH0MUX = EVENT_SYSTEM_INPUT_PIN; 
	
	// Test Counter A Over flow will be the event to the TCCB
	//--> EVSYS.CH0MUX = EVSYS_CHMUX_TCD0_OVF_gc;
	

//2. Set Event Chan 1 to trigger on CNTRA OVF causing an Input Capture on CNTB  
	
	EVSYS.CH1MUX = EVSYS_CHMUX_TCCA_OVF_gc; 

//3. Select event channel 0 as clock source for TCCB  Sandeep: The Input see Section 1

	TCCB.CTRLA = TC_CLKSEL_EVCH0_gc; //  TC_CLKSEL_DIV1024_gc;//TC_CLKSEL_DIV64_gc; //TC_CLKSEL_EVCH0_gc; 

//4. Select Event Action 0001 => Input Capture, and Event Source select = 0b1001 => 

	TCCB.CTRLD = (TC1_EVACT_gm & TCB_EVACT0_bm) | (TCB_EVSEL_gm & (TCB_EVSEL3_bm | TCB_EVSEL0_bm));

	 // TCCB.CTRLD |= TC_EVSEL_CH0_gc;     //event channel 0 as event source for TCC0
	 // TCCB.CTRLD |= TC_EVACT_CAPT_gc;   //input capture as event action.

	
#if EXPAND_TO_32_BITS
	//5.
	TCCC.CTRLA = TC_CLKSEL_EVCH2_gc; 
	TCCC.CTRLD = (TCA_EVAVT_gm & TCA_EVACT0_bm) | (TCA_EVSEL_gm & (TCA_EVSEL3_bm | TCA_EVSEL0_bm));
	TCCC.CTRLB =  TCC_CCAEN_bm; // Capture enable
	EVSYS.CH2MUX = EVSYS_CHMUX_TCCB_OVF_gc; 

#endif

//6. Select Event Chan1 as TCCB Input Capture enable to Capt Channel A

	TCCB.CTRLB = TCB_CCAEN_bm; // Capture enable
} 

void  xmega_freq_cntr_start_meas(void){ 

/*1.	Clear input signal counter CCCB (Timer B) */
	TCCB.CNTL =	0;
	TCCB.CNTH =	0;
	ic_result = 0;
	TCCB_INTFLAGS |= TCCB_OVFIF_bm;
	//-->TCCB.INTFLAGS |= TCCB_OVFIF_bm;
	
/* This code resets the TCC counter not part of the original code 
#if EXPAND_TO_32_BITS
		TCCC.CCABUFL = 0;
		TCCC.CCA = 0;
		TCCC.CNTL =	0;
		TCCC.CNTH =	0;
	//TCCC.CTRLA = TC_CLKSEL_DIV1_gc; 

#endif
#if EXPAND_TO_32_BITS
	//5.
	TCCC.CTRLA = TC_CLKSEL_EVCH2_gc; 
	TCCC.CTRLD = (TCA_EVAVT_gm & TCA_EVACT0_bm) | (TCA_EVSEL_gm & (TCA_EVSEL3_bm | TCA_EVSEL0_bm));
	TCCC.CTRLB =  TCC_CCAEN_bm; // Capture enable
	EVSYS.CH2MUX = EVSYS_CHMUX_TCCB_OVF_gc; 

#endif
*/
	
/*2.	Clear TCCA OVF Flag 
 *	This flag is used to signal to the application code that input capture
 *	results are ready.
 *
 */
// -->TCCA.CTRLFSET = 0x0C;   // Reset timer added code from website not part of the original code
	

	TCCA_INTFLAGS |= TCCA_OVFIF_bm;
	//-->TCCA.INTFLAGS |= TCCA_OVFIF_bm;

/*3.	Load CCCA (timer A) with gate count to OVF value (nominally  125 msec)*/

	//-->TCCA.CNTL = TCCA_CNT_TO_OVF_L;  // Original code
	//-->TCCA.CNTH = TCCA_CNT_TO_OVF_H;  // Original code
	// Set the period register
	 
	 // Changed we are now counting from 0000 to FFFF to get the max time interval for the duration of count
	 // Time of Measurement = 65536 / (System Clock in MHz)
	 // This gives us a measuring time of .00262 Seconds for 24.97 MHz system clock or 24.00341 it is .00273 seconds
	 // We can adjust the count to get different time period.
	 TCCA.CNT = 0;
	 
	 
/*4.  Set TCCA interrupt priority level to Medium */

	TCCA.INTCTRLA = TC_OVFINTLVL_MED_gc; // Experimented with various priority level's // TC_OVFINTLVL_HI_gc; // TC_OVFINTLVL_LO_gc; // TC_OVFINTLVL_MED_gc;

/*5.  Set Prog Interrupt Ctrlr to mid-level Ints enabled for TCCA */
	
	// The below code is not needed as the int are already enable in lowlevel_init in lowlevel.c .
	//PMIC.CTRL = PMIC_MEDLVLEN_bm;  
	//asm("sei");

//6. TimerA set clock input based on divider to clk_sel.

	TCCA.CTRLA =  TC_CLKSEL_DIV1_gc;   //With slower clock you can increase the duration  // TC_CLKSEL_DIV64_gc;  // TC_CLKSEL_DIV2_gc; //(clk_sel & TC0_CLKSEL_gm);
	
	//-->while(TCCA.CNTL==0); // Sync with common prescaler Code from website, not part of the original code 

}

#if EXPAND_TO_32_BITS

uint32_t xmega_get_result(void){ 
	
	return	ic_result;
}
#endif

#if !EXPAND_TO_32_BITS

uint16_t xmega_get_result(void){ 
	
	return	ic_result;
}
#endif


void	xmega_freq_cntr_clr_result(void){

		ic_result = 0;
}

/*!  The following ISR is executed when TCCA overflows.  This will stop the clock to TCCA 
 *  and combine the upper and lower 8 bits of the TCCB capture register into ic_result
 */


ISR(TCCA_OVF_vect){
		/* Stop TCCA timer */
		TCCA.CTRLA = ( TCCA.CTRLA & ~TC0_CLKSEL_gm ) | TC_CLKSEL_OFF_gc;

#if !EXPAND_TO_32_BITS
		if((TCCB_INTFLAGS & 0x01) != 0)
		{
			ic_result = 0xffff; //return TCCB OVF via 0xffff
		}
		else
		{ 	

			ic_result = TCCB.CNTL + (TCCB.CNTH<<8);
		
		}			
	
#endif


#if EXPAND_TO_32_BITS
		{
			/* Stop TCCC timer Not part of the original code */
			//TCCC.CTRLA = ( TCCC.CTRLA & ~TC_CLKSEL_EVCH2_gc ) | TC_CLKSEL_OFF_gc;
			
			/* Combine two 16-bit Capture Compare register contents into one result */
			ic_result= (TCCC.CCABUF*65536) + (0xffff&(uint32_t)(TCCB.CCABUFL + (TCCB.CCABUFH<<8)));			
						
		}

#endif

}



// compare the frequency value

 uint8_t compare_frequency_and_set_new_voltage(uint8_t frequecy_index)
{
	uint8_t step_multiplier = 0; // step multiplier
	int16_t difference = 0;
//--> For testing	uint16_t abs_difference  = 0;
	uint16_t temp_changed_value = 0;
//--> For testing	uint16_t frequency_measured = 0;
//--> for testing	uint16_t frequency_voltage = 0;  // for testing
	uint8_t return_done = 1;
	
	
//--> For testing	frequency_measured = gFrequencyCount[frequecy_index] ;
//--> For testing	frequency_voltage = gFrequencyTable[frequecy_index] ;
	// use ic_result directly
	difference =  ( gFrequencyCount[frequecy_index]- ic_result );
	//difference =  (ic_result - gFrequencyCount[frequecy_index]);
	
//--> For testing	abs_difference =  abs(difference) ; // for testing
	
	// assumption is that the range for the value is between 0 and 15 index i.e gFrequencyCount[0] - gFrequencyCount[16] = 10336
	// for the calibration that we have
	// the corresponding count which is equivalent to freq for us is 47022 - 42544 = 4178
	// so we have a problem we can not fine tune even though we have the capability since we can not measure with that 
	// precision.
	// to change count by one i.e voltage by .0001 we need to change the voltage by 2.5 in integer terms 2 to 3 so we will pick 2
	// i.e we will have to change the v by to 2 to get a change in count by 1     
	
	if ( abs(difference) > DELTA_MAX_COUNT)
	{
		// find out which decimal place the difference is 
		// and then try incrementing the value from one below
		// this will take care of all the values
		// replace 2 with the value returned from calculate_min_voltage_change
		// If we are are stuck in local minima or maxima then there should be a way to get out of it 
		// the way to do is tho reduce the multiplication factor by 1 i.e if it is 2 the reduce it to 1
		// that will reduce the step size
		// the way we will see it is the alternate values will be same i.e if x1 x2 and x3 are consecutive values
		// then x1 and x3 will be same or the two consecutive errors having different signs will be same, 
		// i.e x1 and x2 are equidistant from the point of convergence, and subsequent values are going to 
		// alternate between the two values.
		 
		// convergence logic
		if ( prev_difference == abs(difference) ||  ( abs(difference) < COUNT_0_0_0_1 ) )
		{
			step_multiplier = 1;
	
		} else 
		{
			step_multiplier = MIN_VOLTAGE_CHANGE;	// evaluated as ( gFrequencyTable[0] - gFrequencyTable[15] ) / ( gFrequencyCount[0] - gFrequencyCount[15] ) 
		}
		temp_changed_value = gFrequencyTable[frequecy_index] + step_multiplier * difference ; // Load the initial Value	
		gFrequencyTable[frequecy_index] = temp_changed_value;	
		 prev_difference = abs(difference);
			
		return_done = 0; // if it did not match 			

	}
	else
	{
		// Else do nothing
		return_done = 1;  // done for this frequency start measuring for the next one
	}	
	
	return return_done;

}	



uint8_t calculate_min_voltage_change(void)
{
	uint8_t return_value = 0;
	
	// gFrequencyTable contains the voltage value for the  
	
	return_value =  ( gFrequencyTable[0] - gFrequencyTable[15] ) / ( gFrequencyCount[0] - gFrequencyCount[15] ) ;
	
	
	return return_value;
}


// Compare the frequency and set new voltages

void measure_and_correct_frequency( void )
{

	uint8_t i = 0;
	int8_t done = 0;
	
	// Initializes XMEGA timer/counters and Event System
	
	xmega_freq_cntr_init();				
	
	// for each frequency measure and set the value correctly 
	// for the time being there are 16 of them
	
	for (i = 0; i < NO_OF_FREQUENCY_TABLE_VALUES ; i++ )
	{
		
		done = 0;
		while( done < MAX_ALLOWED  )
		{
		
			// Sandeep
			// Load the DAC with new value
			do { } while ( !( DAC.STATUS & DAC_CH0) );
			DAC.CH0DATA = gFrequencyTable[i]; // Load the initial Value


			xmega_freq_cntr_start_meas();	// take a frequency measurement

			// More User Application code		
			while( 0 == ic_result ){
				//More User Application code here, if desired

			}

		
			// At this point in the application code ,'result' is the sum of both positive and negative edges
			// being counted. This makes the result double the actual frequency.  However, since the counting
			// time interval is 1/8 second (125 milliseconds),  * the result must be both multiplied by 8 and
			// divided by two, for a resulting multiplication factor  of four.  The 'result', above, is 1/4 of the
			// actual frequency.  Thus a 16 bit result(2^16 -1) will allow frequencies up to 262143 (2^18 -1)
			// to be measured.
		
		
			// Now correct it after measuring if it has deviated
		
			if ( !compare_frequency_and_set_new_voltage(i) ) {
				
				done = done + 1;
			
			} else {
				
				done = MAX_ALLOWED; // get out of the loop since the value matched within tolerance.
			}
			
		
			ic_result = 0;
				

		} // end of While 1
	
	}	
	
	// Set frequency Index back to zero
	gDACIndexLoaded = 0;
}	


// Compare single the frequency and set new voltages

void measure_and_correct_single_frequency( void )
{
	int8_t done = 0;
	
	// for each frequency measure and set the value correctly
	// for the time being there are 16 of them
			
	done = 0;


	while( done < MAX_ALLOWED  )
	{
			
		// Sandeep
		// Load the DAC with new value
		do { } while ( !( DAC.STATUS & DAC_CH0) );
		DAC.CH0DATA = gFrequencyTable[gDACIndexLoaded]; // Load the initial Value
		// Test for frequency counter testing
		
		// User Application code
		
		xmega_freq_cntr_start_meas();	// take a frequency measurement

		
		// More User Application code
		
		while( 0 == ic_result ){
			//More User Application code here, if desired

		}

		// no wrappers use ic_result directely result = xmega_get_result(); // result available here
			
			
		// At this point in the application code ,'result' is the sum of both positive and negative edges
		// being counted. This makes the result double the actual frequency.  However, since the counting
		// time interval is 1/8 second (125 milliseconds),  * the result must be both multiplied by 8 and
		// divided by two, for a resulting multiplication factor  of four.  The 'result', above, is 1/4 of the
		// actual frequency.  Thus a 16 bit result(2^16 -1) will allow frequencies up to 262143 (2^18 -1)
		// to be measured.
			
			
		// Now correct it after measuring if it has deviated
			
		if ( !compare_frequency_and_set_new_voltage( gDACIndexLoaded ) ) {
				
			done = done + 1;
				
		} else {
				
			done = MAX_ALLOWED; // get out of the loop since the value matched within tolerance.
		}
			
			ic_result = 0;
			
	} // end of While 1
		
}