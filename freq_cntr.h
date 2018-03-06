/*
 * freq_cntr.h
 * Taken for frequency counter example from Atmel look at
 * Atmel AVR1617: Frequency Measurement with Atmel AVR XMEGA Family Devices
 * Created: 3/7/2013 11:40:26 AM
 *  Author: dubes
 *
 * $History: freq_cntr.h $
 * 
 * *****************  Version 5  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:08a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Moved the counter values from freq_cntr.h to freq_tables.h, to get rid
 * of FrequencyCounPtr related Warnings.
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 8/27/13    Time: 6:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Count for table 1 to 7 added
 * 
 * *****************  Version 3  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:01p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warnings
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/19/13    Time: 12:33p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Preprocessed out the timer used for 32 bit freq counter so it does not
 * conflict with frame timer
 * 
 * *****************  Version 1  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:24p
 * Created in $/Zircon/Thorite/Thorite/Hafnon
 * used for freq counter when enabled
 * 
 * *****************  Version 4  *****************
 * User: Dubes        Date: 6/13/13    Time: 2:05p
 * Updated in $/Zircon/Hafnon/Halfnon_Sandeep/Hafnon
 * Added Important Note for TCCC TCC1 counter
 */ 


#ifndef FREQ_CNTR_H_
#define FREQ_CNTR_H_

 /*If this #define is set to '1',the 32 bit frequency counter option is enabled using TCCC.
 Otherwise the 16-bit result will be available using TCCB */

// Important NOTE: TCCC Overflow timer mapped to TCC1
// has conflict with the Frame timer FRAME_TIMER	TCC1
// Though it has no ISR associated with it , still if in future we want to
// use 32 bit counter we have to make sure this is take care.
// Do not set enable until conflict	is resolved between the frame timer and TCCC 
// Overflow counter (32 bit counter) 
#define EXPAND_TO_32_BITS	0 // 1
// #define CLK_SEL 5	//divide 32 MHz by 64
#define CLK_SEL 7	//divide 32 MHz by 1

/* If it is desired to change one or more of the the three timer/counter assignments (such
 * as changing TCD0 to another timer, the event channel assignments for clock and capture/
 * compare will have to be changed to this new timer/counter.
 */

// Re Mapping the timers for frequency counters

#define TCCA	TCD0	
#define TCCB	TCD1
#if EXPAND_TO_32_BITS
// Earlier TCE0
#define TCCC	TCC1  
#endif 

#define TCCA_INTFLAGS	TCD0_INTFLAGS
#define TCCB_INTFLAGS	TCD1_INTFLAGS
#if EXPAND_TO_32_BITS
// Earlier TCE0_INTFLAGS
#define TCCC_INTFLAGS	TCC1_INTFLAGS
#endif

#define	TCCA_OVFIF_bm	TC0_OVFIF_bm
#define TCCB_OVFIF_bm	TC1_OVFIF_bm
#if EXPAND_TO_32_BITS
// Earlier TC0_OVFIF_bm
#define TCCC_OVFIF_bm	TC1_OVFIF_bm
#endif

#define TCCA_OVF_vect 	TCD0_OVF_vect


/*  32 MHz is recommended although the application may use other frequencues if desired. If
*  no frequency is specified in  Project > Configuration Options, 32 MHz will be defined as follows:
*/
// For US F_CPU == 24000000UL Attention Joe 
/*
#if !defined(F_CPU)

#define F_CPU 32000000UL

#endif
*/

#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(64UL*8UL))
//#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(8UL*64UL))
//#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(2UL*256UL))
//#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(1UL*512UL))
//#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(1UL*375UL))
//#define TCCA_CNT_TO_OVF	 		(0xffffUL)-(F_CPU/(1UL*370UL))
#define TCCA_CNT_TO_OVF_L 		(TCCA_CNT_TO_OVF) & (0xff)
#define TCCA_CNT_TO_OVF_H 		(TCCA_CNT_TO_OVF) >>8

#define EVENT_SYSTEM_INPUT_PIN	EVSYS_CHMUX_PORTC_PIN3_gc; // changed to  Port C Pin 3 is the input  //  EVSYS_CHMUX_PORTD_PIN0_gc;  // Port D Pin 0 is the input
#define EVSYS_CHMUX_TCCA_OVF_gc	EVSYS_CHMUX_TCD0_OVF_gc   
#define EVSYS_CHMUX_TCCB_OVF_gc	EVSYS_CHMUX_TCD1_OVF_gc	  

#define TCA_EVAVT_gm	TC0_EVACT_gm
#define	TCA_EVACT0_bm	TC0_EVACT0_bm
#define	TCA_EVSEL_gm	TC0_EVSEL_gm
#define	TCA_EVSEL3_bm	TC0_EVSEL3_bm
#define	TCA_EVSEL0_bm	TC0_EVSEL0_bm

#define TCB_EVAVT_gm	TC1_EVACT_gm
#define	TCB_EVACT0_bm	TC1_EVACT0_bm
#define	TCB_EVSEL_gm	TC1_EVSEL_gm
#define	TCB_EVSEL3_bm	TC1_EVSEL3_bm
#define	TCB_EVSEL0_bm	TC1_EVSEL0_bm
#if EXPAND_TO_32_BITS
#define TCC_CCAEN_bm	TC0_CCAEN_bm;
#endif
#define	TCB_CCAEN_bm	TC1_CCAEN_bm


// Max retries allowed per frequency for correcting the frequency

#define	 MAX_ALLOWED 10 

// Count correspond to frequency Should be revised for different calculations
// This set is for 24 MHZ clock
// Change these values as these are are for 16 bit counter
//#define DELTA_MAX_COUNT			53
// 27 = .005 MHZ
// 55 = .010 MHZ
// 06 = .001 MHZ

#define DELTA_MAX_COUNT			2

// 1
#define COUNT_1_0				5461
// 0.1
#define COUNT_0_1				546
// .01
#define COUNT_0_0_1				55
// .005
#define COUNT_0_0_0_5			27
// .001
#define COUNT_0_0_0_1			6
// .0001 This is the minimum that can be accounted for.
#define COUNT_0_0_0_0_1			1

// minim change in voltage to change count by 1
#define MIN_VOLTAGE_CHANGE		2

#if EXPAND_TO_32_BITS

uint32_t result; // 32 bit long needed if 32 bit result is needed

extern uint32_t prev_difference;

volatile uint32_t *gFrequencyCount;

#else

uint16_t result;	// else 16 bit result

extern uint16_t prev_difference;

volatile uint16_t *gFrequencyCount;

#endif

// Feed back Loops Defines
/*
#if EXPAND_TO_32_BITS
//static uint32_t prev_difference = 0;
extern uint32_t prev_difference;
// Count correspond to frequency Should be revised for different calculations
// This set is for 24.96 MHZ clock used in experiment

#define DELTA_MAX_COUNT			52

#define COUNT_8610				45214
#define COUNT_8555				44925
#define COUNT_8500				44636
#define COUNT_8446				44352
#define COUNT_8391				44064
#define COUNT_8337				43780
#define COUNT_8282				43491
#define COUNT_8227				43202
#define COUNT_8173				42919
#define COUNT_8118				42630
#define COUNT_8063				42341
#define COUNT_8009				42058
#define COUNT_7954				41769
#define COUNT_7899				41480
#define COUNT_7845				41196
#define COUNT_7790				40908


//static const uint32_t gFrequencyCount[NO_OF_FREQUENCY_TABLE_VALUES] = {
//	
//	COUNT_8610, COUNT_8555, COUNT_8500, COUNT_8446,
//	COUNT_8391, COUNT_8337, COUNT_8282, COUNT_8227,
//	COUNT_8173, COUNT_8118, COUNT_8063, COUNT_8009,
//	COUNT_7954, COUNT_7899, COUNT_7845, COUNT_7790
//
//};


volatile uint32_t *gFrequencyCount;

// default table 7.6 to 8.7 MHz (DMS index 0)
//static const uint16_t FreqCount76_87[NO_OF_FREQUENCY_TABLE_VALUES] = {
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


//-----------End Of New Tables-----------


// minim change in voltage to change count by 1 
#define MIN_VOLTAGE_CHANGE		2	


static uint32_t *FrequencyCounPtr[] = {
	
	FreqCount76_87, FreqCount74_90, FreqCount74_88, FreqCount78_94,
	FreqCount78_98, FreqCount75_86, FreqCount77_88, FreqCount85_98
};

#else
 //#endif
 //#if !EXPAND_TO_32_BITS
 
//static uint16_t prev_difference = 0;
extern uint16_t prev_difference;
// Count correspond to frequency Should be revised for different calculations
// This set is for 24 MHZ clock
// Change these values as these are are for 16 bit counter
//#define DELTA_MAX_COUNT			53
// 27 = .005 MHZ
// 55 = .010 MHZ
// 06 = .001 MHZ

#define DELTA_MAX_COUNT			2

// 1
#define COUNT_1_0				5461
// 0.1
#define COUNT_0_1				546
// .01
#define COUNT_0_0_1				55
// .005
#define COUNT_0_0_0_5			27
// .001
#define COUNT_0_0_0_1			6
// .0001 This is the minimum that can be accounted for.
#define COUNT_0_0_0_0_1			1

// count for 24.0254 MHZ clock

//#define COUNT_8610				46972
//#define COUNT_8555				46672
//#define COUNT_8500				46372
//#define COUNT_8446				46078
//#define COUNT_8391				45778
//#define COUNT_8337				45483
//#define COUNT_8282				45183
//#define COUNT_8227				44883
//#define COUNT_8173				44588
//#define COUNT_8118				44288
//#define COUNT_8063				43988
//#define COUNT_8009				43694
//#define COUNT_7954				43394
//#define COUNT_7899				43094
//#define COUNT_7845				42799
//#define COUNT_7790				42499



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



// count for 24.00341 MHZ clock
//#define COUNT_8610				47015
//#define COUNT_8555				46715
//#define COUNT_8500				46414
//#define COUNT_8446				46120
//#define COUNT_8391				45820
//#define COUNT_8337				45525
//#define COUNT_8282				45224
//#define COUNT_8227				44924
//#define COUNT_8173				44629
//#define COUNT_8118				44329
//#define COUNT_8063				44029
//#define COUNT_8009				43734
//#define COUNT_7954				43433
//#define COUNT_7899				43133
//#define COUNT_7845				42838
//#define COUNT_7790				42538


// count for 24 MHZ clock
//#define COUNT_8610				47022
//#define COUNT_8555				46723
//#define COUNT_8500				46421
//#define COUNT_8446				46126
//#define COUNT_8391				45826
//#define COUNT_8337				45531
//#define COUNT_8282				45231
//#define COUNT_8227				44830
//#define COUNT_8173				44636
//#define COUNT_8118				44335
//#define COUNT_8063				44035
//#define COUNT_8009				43740
//#define COUNT_7954				43440
//#define COUNT_7899				43139
//#define COUNT_7845				42844
//#define COUNT_7790				42544

// old values see from where they have come
//#define COUNT_8610				45912
//#define COUNT_8555				44925
//#define COUNT_8500				44636
//#define COUNT_8446				44352
//#define COUNT_8391				44064
//#define COUNT_8337				43780
//#define COUNT_8282				43491
//#define COUNT_8227				43202
//#define COUNT_8173				42919
//#define COUNT_8118				42630
//#define COUNT_8063				42341
//#define COUNT_8009				42058
//#define COUNT_7954				41769
//#define COUNT_7899				41480
//#define COUNT_7845				41196
//#define COUNT_7790				40908



// Count for board 5 Sys clock clock of 24.53
//#define COUNT_8610				46006
//#define COUNT_8555				45712
//#define COUNT_8500				45418
//#define COUNT_8446				45130
//#define COUNT_8391				44836
//#define COUNT_8337				44547
//#define COUNT_8282				44254
//#define COUNT_8227				43960
//#define COUNT_8173				43671
//#define COUNT_8118				43377
//#define COUNT_8063				43083
//#define COUNT_8009				42795
//#define COUNT_7954				42501
//#define COUNT_7899				42207
//#define COUNT_7845				41919
//#define COUNT_7790				41625



// Count for board 5 Sys clock clock of 24.54
//#define COUNT_8610				45987
//#define COUNT_8555				45694
//#define COUNT_8500				45400
//#define COUNT_8446				45111
//#define COUNT_8391				44818
//#define COUNT_8337				44529
//#define COUNT_8282				44236
//#define COUNT_8227				43942
//#define COUNT_8173				43653
//#define COUNT_8118				43360
//#define COUNT_8063				43066
//#define COUNT_8009				42777
//#define COUNT_7954				42484
//#define COUNT_7899				42190
//#define COUNT_7845				41901
//#define COUNT_7790				41608



// Count for board 5 Sys clock clock of 24.573
//#define COUNT_8610				45926
//#define COUNT_8555				45632
//#define COUNT_8500				45339
//#define COUNT_8446				45051
//#define COUNT_8391				44758
//#define COUNT_8337				44469
//#define COUNT_8282				44176
//#define COUNT_8227				43883
//#define COUNT_8173				43595
//#define COUNT_8118				43301
//#define COUNT_8063				43007
//#define COUNT_8009				42720
//#define COUNT_7954				42427
//#define COUNT_7899				42133
//#define COUNT_7845				41845
//#define COUNT_7790				41552



//static const uint16_t gFrequencyCount[NO_OF_FREQUENCY_TABLE_VALUES] = {
//	
//	COUNT_8610, COUNT_8555, COUNT_8500, COUNT_8446,
//	COUNT_8391, COUNT_8337, COUNT_8282, COUNT_8227,
//	COUNT_8173, COUNT_8118, COUNT_8063, COUNT_8009,
//	COUNT_7954, COUNT_7899, COUNT_7845, COUNT_7790
//
//};

volatile uint16_t *gFrequencyCount;

// default table 7.6 to 8.7 MHz (DMS index 0)
//static const uint16_t FreqCount76_87[NO_OF_FREQUENCY_TABLE_VALUES] = {
static uint16_t FreqCount76_87[NO_OF_FREQUENCY_TABLE_VALUES] = {
	
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


//-----------End Of New Tables-----------

// minim change in voltage to change count by 1 
#define MIN_VOLTAGE_CHANGE		2	


static uint16_t *FrequencyCounPtr[] = {
	
	FreqCount76_87, FreqCount74_90, FreqCount74_88, FreqCount78_94,
	FreqCount78_98, FreqCount75_86, FreqCount77_88, FreqCount85_98
};

#endif
*/

/*! Prototypes */



/*!		/brief Initializtion of xmega counters and event system
 *
 *		The xmega peripherals such as Timers and the Event System must be
 *		initialized. This function executes the necessary instructions.
 *		Input: none
 *		Output: none
 */

void  xmega_freq_cntr_init(void);



/*!		/brief	Function to start the measure frequency via the Event System and TCCA and TCCB have been initialized
 *		After Event System and TCCA and TCCB have been initialized, this function pre-loads TCCA
 *		with .125 second (125 msec) of counts before OVF.
 *			
 *		At OVF, 125 msec has elapsed and thiss OVVF triggers and Event that clocks in TCCb's
 *		count into TCCA's Capture register CCA.
 *		Input: none
 *		Output: none
 */
void  xmega_freq_cntr_start_meas(void);
 

/*!		/brief	Function to return freq measurement results to the application code
* 
*		Input:none
*		if the #define 'EXPAND_TO_32_BITS = 0, then Output: 16-bit unsigned int for the frequency/4,
*		 due to the 125 msec (1/8 second) count interval
*		if the #define 'EXPAND_TO_32_BITS = 1, then Output: 32-bit unsigned int for the frequency/4,
*		 due to the 125 msec (1/8 second) count interval
*		Input: unsigned char clk_sel
*		Output: none
*		
*/
#if EXPAND_TO_32_BITS
	
uint32_t xmega_get_result(void); //long variable needed for 32 bit result

#endif

#if !EXPAND_TO_32_BITS

uint16_t xmega_get_result(void); // 16 bit variable for 16 bit result

#endif


/*!		/brief	Function to clear the result coming from the driver
* 
*		Input:none   Output:none
*		After the driver returns the frequency to the application, it is necessary to clear the results
*		in the driver to set it up for the next frequency measurement.
*		This is accomplished by the application code, by calling this function.
*		 due to the 125 msec (1/8 second) count interval*		
*/

void	xmega_freq_cntr_clr_result(void);



// compare the frequency value 

 uint8_t compare_frequency_and_set_new_voltage(uint8_t frequecy_index); 


// compare the frequency value

uint8_t calculate_min_voltage_change(void);


// Compare the frequency and set new voltages

void measure_and_correct_frequency( void );


// Compare single the frequency and set new voltages

void measure_and_correct_single_frequency( void );

#endif /* FREQ_CNTR_H_ */