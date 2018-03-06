/*******************************************************************
 *
 * File name: Hafnon.c
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
 * $History: Hafnon.c $
 * 
 * *****************  Version 78  *****************
 * User: Dubes        Date: 10/26/15   Time: 5:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * NCR Soft Inter Lock Changes and Reintroduced  the 40mS TX/RX delay for
 * immunity against interfering devices and to make the pulse pattern
 * closer to the CP9 (This was taken out in 1.8R)
 * 
 * *****************  Version 77  *****************
 * User: Galantij     Date: 5/13/15    Time: 2:21p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the 40 mS TX/RX delay code in the tag interrupt to keep track
 * of the tag coming in for the detection rate measurement. Installed
 * macro defines for the WD enable and tickles
 * 
 * *****************  Version 76  *****************
 * User: Galantij     Date: 3/17/15    Time: 10:10a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Decreased the interval for the status ping message from 5 seconds to 2
 * seconds to allow the evolve reader to respond faster.
 * 
 * *****************  Version 75  *****************
 * User: Galantij     Date: 11/12/14   Time: 9:55a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug #60 "CPiD does not show up in node tree until reboot". The
 * status ping would become disabled when connecting the Evolve reader to
 * the CPiD via the modem port. Reduced the status message interval from
 * every 15 seconds to 5 seconds. (EvolveStore).
 * 
 * *****************  Version 74  *****************
 * User: Dubes        Date: 7/28/14    Time: 1:56p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * The Changes to address QC issue EAS.Zircon - Defect # 116 for Mode 4
 * and verification mode we are taking out the delay every 5 th pulse
 * 
 * *****************  Version 73  *****************
 * User: Dubes        Date: 7/17/14    Time: 9:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Code with aprox 40 ms delay after the 5 th pulse, to make the pulsing
 * smiler to CP9 
 * 
 * *****************  Version 72  *****************
 * User: Dubes        Date: 7/11/14    Time: 3:53p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This is the merged code Thoralite + Evolve  + 1.3R Base Code (Immunity
 * changes, narrow receive window)
 * 
 * *****************  Version 71  *****************
 * User: Galantij     Date: 4/01/14    Time: 9:54a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put a test around the initialization of the overvoltage test and if in
 * verify mode do not enable. This fixes Defect #104 (Overvoltage test
 * while in Verify Mode could deactivate tags)
 * 
 * *****************  Version 70  *****************
 * User: Galantij     Date: 3/21/14    Time: 2:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Defect #103 (Tuning verification and overvoltage test could happen
 * while the unit is in interlock). This was fixed by testing when the
 * system is in interlock and the jumper is removed. This was done for
 * both tuning verification and overvoltage testing.
 * 
 * *****************  Version 69  *****************
 * User: Galantij     Date: 3/04/14    Time: 5:27p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a new parameter for setVPA_Level() to indicate the frame rate for
 * the change to 10 Hz PWM charge rate.
 * 
 * *****************  Version 68  *****************
 * User: Galantij     Date: 3/04/14    Time: 2:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed the 10 Hz power limit from code. DMS is handling the limiting
 * for the 10 Hz frame rate.
 * 
 * *****************  Version 67  *****************
 * User: Galantij     Date: 2/26/14    Time: 11:45a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Re-coded the Tag ISR for the 2nd TX to allow totally independent
 * structures for each loop and isolated from the 2nd disabled condition.
 * This fixes Defect#60 (seem to get more false alarms when second
 * transmitter is active near E3)
 * 
 * *****************  Version 66  *****************
 * User: Galantij     Date: 2/24/14    Time: 10:46a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added a test for the auto tune mode for processing interlock ISR. This
 * is a fixed for defect #84 (interlock does not work when in Auto Tune On
 * Power Up.
 * 
 * *****************  Version 65  *****************
 * User: Galantij     Date: 2/11/14    Time: 5:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This fixes defect #83 where after the scheduled freq counting occurs
 * the system would be struck in the freq counter loop and would not allow
 * the DMS to connect. This is because we never go back to the main loop.
 * The problem was we were shutting down the VCO during the freq counting
 * process. There was also an issue with not counting the right freq
 * because of the frame processing occurring
 * 
 * *****************  Version 64  *****************
 * User: Galantij     Date: 2/11/14    Time: 1:42p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed a test pin
 * 
 * *****************  Version 63  *****************
 * User: Galantij     Date: 2/04/14    Time: 11:07a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Placed a watchdog tickle outsite of the process state in the main loop
 * 
 * *****************  Version 62  *****************
 * User: Galantij     Date: 1/30/14    Time: 5:04p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Missed a timer when changing the tuning verification time from 10 hours
 * to 1 hour
 * 
 * *****************  Version 61  *****************
 * User: Galantij     Date: 1/30/14    Time: 11:27a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Move writes to eeprom right before starting a DMS session. This fixes
 * Defect #69 (unit is set back to default config when the reset button is
 * rapidly pressed)
 * 
 * *****************  Version 60  *****************
 * User: Galantij     Date: 1/29/14    Time: 9:32p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Replaced the new purple LED for the auto tune reset window which was
 * blue
 * 
 * *****************  Version 59  *****************
 * User: Galantij     Date: 1/28/14    Time: 7:57p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new dac_write_data() in existing places and before the main loop
 * to disable VCO in case of interlock
 * 
 * *****************  Version 58  *****************
 * User: Galantij     Date: 1/26/14    Time: 6:15p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Changed the timer value for the tuning verfication feature from 10
 * hours to 1 hour
 * 
 * *****************  Version 57  *****************
 * User: Galantij     Date: 1/20/14    Time: 10:23a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * This fixes defect #71. This defect was created because when in the Auto
 * Tune mode and the unit TX/RX cycles are disabled because of lack of
 * auto tuning, TX/RX cycles start when the overvoltage test is executed.
 * There were also issues with the interlock doing the same thing.
 * 
 * *****************  Version 56  *****************
 * User: Galantij     Date: 1/16/14    Time: 3:37p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Re-worked the tag ISR to not shut down the alarm indications allowing
 * the 500ms timer to expirer. This fixes an issue where we had loss of
 * detection/deactvation for the 144 Hz Mode 4. This change is for all
 * Mode 4 selection (both FCC and CE).
 * 
 * *****************  Version 55  *****************
 * User: Galantij     Date: 1/13/14    Time: 2:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added comments before code review
 * 
 * *****************  Version 54  *****************
 * User: Galantij     Date: 1/10/14    Time: 3:36p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to fix defect with the auto tune blue LED window not
 * appearing when interlock is enabled. Also fixed an issue with the VPA
 * charging occurring when during 10 Hz TX blast.
 * 
 * *****************  Version 53  *****************
 * User: Galantij     Date: 12/11/13   Time: 2:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added watchdog enable and tickles in the main loop 
 * 
 * *****************  Version 52  *****************
 * User: Galantij     Date: 12/04/13   Time: 11:16a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to limit the VPA rail voltage for the 10 Hz frame rate. At
 * this point the limit has not been decided by HW
 * 
 * *****************  Version 51  *****************
 * User: Galantij     Date: 12/02/13   Time: 2:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Needed to add the feature to allow the GPI to have a active high state.
 * 
 * *****************  Version 50  *****************
 * User: Galantij     Date: 11/27/13   Time: 4:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code for the asGPOI features in the main loop to do the following
 * 
 * *****************  Version 49  *****************
 * User: Dubes        Date: 11/26/13   Time: 1:00p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to support 3 type of Tuning Auto , Manual and Auto Tun ing
 * on power upin Auto the tuning will be executed by press of reset button
 * twice, if it has not been tuned ever then tiel colored light will be
 * on. 
 * 
 * *****************  Version 48  *****************
 * User: Galantij     Date: 11/22/13   Time: 10:28a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the code to start the 5 second timer and blinking blue LED if any
 * of the default config was change by the DMS user
 * 
 * *****************  Version 47  *****************
 * User: Galantij     Date: 11/21/13   Time: 12:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to start frame timer if the interlock pin is grounded and
 * the interlock is enabled. Added code to not start the frame timer when
 * performing verification if the interlock is enabled and interlock pin
 * is high ( no interlock signal). Added code to auto verifiy when in
 * manual tuning mode. 
 * 
 * *****************  Version 46  *****************
 * User: Galantij     Date: 11/18/13   Time: 5:06p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code in beginning of main to start timer for scheduled
 * overvoltage test, prrovide the call in the main loop and provide a call
 * for DMS overvoltage tuning.
 * 
 * *****************  Version 45  *****************
 * User: Galantij     Date: 11/14/13   Time: 3:45p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Just added a comment at where the DMS tuning code starts
 * 
 * *****************  Version 44  *****************
 * User: Galantij     Date: 11/13/13   Time: 4:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to allow the VPA rail to continue to charge during interlock
 * 
 * *****************  Version 43  *****************
 * User: Dubes        Date: 11/08/13   Time: 3:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug where Interlock could be enabled using the interlock pin
 * even when Interlock is disabled  (by switch)
 * 
 * *****************  Version 42  *****************
 * User: Galantij     Date: 11/04/13   Time: 5:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added test pin to measure inhibit
 * 
 * *****************  Version 41  *****************
 * User: Dubes        Date: 10/31/13   Time: 7:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed bug related with rtc timer not working properly when coming out
 * of DMS , hence functionality was not properly restored
 * 
 * *****************  Version 40  *****************
 * User: Galantij     Date: 10/25/13   Time: 4:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Fixed issues with Mode 5 and alarming during autotuning
 * 
 * *****************  Version 39  *****************
 * User: Galantij     Date: 10/24/13   Time: 10:00p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added new code to the tag ISR to allow a more sync operation between
 * TX/RX frames for alarming and detection and deactivation.Macro defined
 * the older version to allow a comparison.
 * 
 * *****************  Version 38  *****************
 * User: Galantij     Date: 10/21/13   Time: 5:49p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created a macro define for the rail discharge code and added code for
 * the new Mode 4
 * 
 * *****************  Version 37  *****************
 * User: Dubes        Date: 10/15/13   Time: 4:17p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * stopped rtc timer rtc_interlock_timer_stop(); fixed error reported by
 * Joe Occasionally Thorite was going into inter lock enable mode after
 * connecting with DMS even when interlock was disabled.
 *
 * *****************  Version 36  *****************
 * User: Dubes        Date: 10/10/13   Time: 6:35p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 1. moved frequency counting code before auto tuning as it was
 * interfering with the frequency correction since the frame timer was
 * changing the index on the run.2.added the logic to run frequency
 * correction when ever auto tuning is run ever 10 hrs3. changed the name
 * of define RESET_INDICATOR 
 * 
 * *****************  Version 35  *****************
 * User: Galantij     Date: 10/10/13   Time: 5:09p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code to discharge the VPA rail before excuting the interlock.
 * 
 * *****************  Version 34  *****************
 * User: Dubes        Date: 10/04/13   Time: 5:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * removed deact_frame_rate and logic for different reset conditions
 * 
 * *****************  Version 33  *****************
 * User: Galantij     Date: 10/02/13   Time: 12:22p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Created independent tag rate for both 1st and 2nd TX and increase
 * immunity for the 2nd TX 
 * 
 * *****************  Version 32  *****************
 * User: Galantij     Date: 9/30/13    Time: 3:23p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * 
 * *****************  Version 31  *****************
 * User: Galantij     Date: 9/27/13    Time: 11:09a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * code to support the DMS antenna tuning display. Still needs Sandeep's
 * code and the latest DMS to complete the feature
 * 
 * *****************  Version 30  *****************
 * User: Galantij     Date: 9/25/13    Time: 5:34p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Took out the "setFrameRate()" in interlock ISR
 * 
 * *****************  Version 29  *****************
 * User: Galantij     Date: 9/25/13    Time: 11:12a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added support for 10 Hz
 * 
 * *****************  Version 28  *****************
 * User: Dubes        Date: 9/23/13    Time: 2:58p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * removed deact_frame_rate (the single var that was causing the prog not
 * to fail)
 * 
 * *****************  Version 27  *****************
 * User: Dubes        Date: 9/16/13    Time: 11:16a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Default Related Enhancement changes (Default ID 25)
 * 
 * *****************  Version 26  *****************
 * User: Galantij     Date: 9/11/13    Time: 2:20p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added visiblity to the flag which monitors the interlock pin state.
 * 
 * *****************  Version 25  *****************
 * User: Galantij     Date: 9/05/13    Time: 5:28p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Disabled PWM before starting a DMS session
 * 
 * *****************  Version 24  *****************
 * User: Galantij     Date: 9/05/13    Time: 2:39p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Disabled alarms (sounder/LED/IO) before entering a DMS session. There
 * was an issue with the alarms being struck on when entering a DMS
 * session
 * 
 * *****************  Version 23  *****************
 * User: Galantij     Date: 9/02/13    Time: 8:54p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Cleaned up comments for code review
 * 
 * *****************  Version 22  *****************
 * User: Galantij     Date: 8/28/13    Time: 6:44p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added freq lock/unlock logic in tag ISR
 * 
 * *****************  Version 21  *****************
 * User: Galantij     Date: 8/27/13    Time: 4:16p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added code for the interlock function. There was an issue with the
 * interlock not stopping the TX/RX cycle. Also needed to not set the
 * interlock timer when the interlock signal is held low. Added the code
 * for consecetive frames for the 2nd TX
 * 
 * *****************  Version 20  *****************
 * User: Dubes        Date: 8/23/13    Time: 3:00p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed warningsInitialize variables
 * 
 * *****************  Version 19  *****************
 * User: Galantij     Date: 8/22/13    Time: 9:11p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put the rest of the code in for the verify tuning feature and fixed a
 * bug not allowing a state change to PROCESS when TX/RX cycle was active 
 * 
 * *****************  Version 18  *****************
 * User: Galantij     Date: 8/20/13    Time: 8:44p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Implemented the consecutive tag code to reduce false alarms. This was
 * very effective.
 * 
 * *****************  Version 17  *****************
 * User: Galantij     Date: 8/15/13    Time: 4:03p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added the code for Josh's new timer and alarm code. Added the config
 * data from the eeprom for the functions parameters. Added the setAlarm()
 * code in the tag ISR.
 * 
 * *****************  Version 16  *****************
 * User: Galantij     Date: 8/09/13    Time: 10:38a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added hooks for the config DB
 * 
 * *****************  Version 15  *****************
 * User: Galantij     Date: 8/07/13    Time: 4:25p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Removed sleep and configuration code and place in unique file
 * 
 * *****************  Version 14  *****************
 * User: Galantij     Date: 7/31/13    Time: 4:48p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * auto tuning changes
 * 
 * *****************  Version 13  *****************
 * User: Galantij     Date: 7/16/13    Time: 10:12p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Blocked off Hafnon HW and used dip switch values instead of hard code
 * 
 * *****************  Version 12  *****************
 * User: Galantij     Date: 7/09/13    Time: 4:38p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added "HAFNON define to comment out HW functionality  for Thorite.
 * Cleaned up code
 * 
 * *****************  Version 11  *****************
 * User: Galantij     Date: 7/09/13    Time: 1:02p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added header files to support both config mgmt (eeprom) and DMS tool.
 * Added functions for retrieing config and to set default config if
 * needed. Added code to the main loop to process DMS commands
 * 
 * *****************  Version 10  *****************
 * User: Galantij     Date: 7/08/13    Time: 11:10a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added function to provide config values for a given input config
 * parameter
 * 
 * *****************  Version 9  *****************
 * User: Galantij     Date: 7/05/13    Time: 11:39a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added call for reading the dip switches and fixed a bug in auto tune
 * 
 * *****************  Version 8  *****************
 * User: Galantij     Date: 7/01/13    Time: 4:10p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Clean up and comments and setup test GPIO for the relay outputs to
 * start testing before the HW is ready
 * 
 * *****************  Version 7  *****************
 * User: Galantij     Date: 6/30/13    Time: 8:46p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Put new auto tune call in the main and added test code for testing the
 * ADC
 * 
 * *****************  Version 6  *****************
 * User: Galantij     Date: 6/26/13    Time: 11:11a
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * implemented the tag band feature
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/19/13    Time: 8:19p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Asserted the first call to the VPA rail adj in main(). Cleaned  code to
 * make more readable.
 * 
 * *****************  Version 4  *****************
 * User: Galantij     Date: 6/18/13    Time: 12:26p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * sandeep added counter for single and all 16 freqs during main().
 * Cleaned code
 * 
 * *****************  Version 3  *****************
 * User: Galantij     Date: 6/15/13    Time: 7:32p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Sandeep added calls to use RTC for interlock timerAdded hook into
 * interlock control
 * 
 * *****************  Version 2  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:52p
 * Updated in $/Zircon/Thorite/Thorite/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 5  *****************
 * User: Galantij     Date: 6/12/13    Time: 2:44p
 * Updated in $/Zircon/Hafnon/Hafnon/Hafnon
 * Added timing for verfication mode and charged TX/RX cycle to be async
 * to the VPA threshold indication.Added more inferface for shanghia
 * development
 * 
 * *****************  Version 4  *****************
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

#include "globals.h"
#include "timers.h"
#include "spi.h"
#include "analog.h"
#include "interface.h"
#include "nvm_eeprom.h"
#include "rs232.h"
#include "dms_interface.h"
#include "utility/util.h"
#include "autotune.h"
#include "zircon_config.h"
#include "alarm.h"
#include "GTimer.h"
#include "watchdog.h"
#if HALFNON
#include "zircon_sleep.h"
#endif
#if USE_DDS
#include "dds.h"
#endif
#if USE_FREQ_COUNT
#include "freq_cntr.h"
#endif
#include "GTimer.h"

// Flag defines HW type; CPiD or Thoralite
volatile uint8_t CPiD_HW_flag = 1;

// For the DMS
volatile uint8_t bAborted = DMS_DISCONNECT_INDICATION_DEFAULT;
volatile uint8_t gState;

// tracks when the interlock low edge is detected and when the level
// returns high, then indicates to start the interlock timers
volatile uint8_t start_intlk_timer = 0;

#if EVOLVESTORE
// Timer handles for the 15 second status message and the
// inhibit timer after EvolveStore sends 0x7f connect message
// for connect ACK with status payload.
volatile uint8_t send_ping_handler = 0xff;
volatile uint8_t status_inhibit_handler = 0xff;
#endif

volatile uint8_t send_alarm_ping_handler = 0xff;  // Handler for sending the Alarm Pin
	// This change was taken out because there was communication failure in sending the ping for evolve
	// from inside the main while loop 10/23/2015 NCR changes
//volatile uint8_t flag_send_ping_handler = 0; // Flag to indicate that we have to send Status Ping command
volatile uint8_t flag_send_alarm_ping_handler = 0; // Flag to indicate that we have to send Alarm Ping command, 0 will indicate nothing to send, 1 will indicate alarm Ping, 2 will indicate start of alarm 3 will indicate alarm stop
volatile uint8_t flag_status_inhibit_handler = 0; // Flag to Indicate to Restart the DMS again 
volatile uint8_t flag_send_end_alarm = 0; // Flag to indicate the send End of Alarm
volatile uint8_t flag_config_enable_alarm = 0; // Flag to indicate NCR mode and hence sending Alarm is enabled
volatile uint8_t flag_enable_hard_tag_indicator = 0; // Flag to indicate NCR mode i.e hence sending Alarm and soft interlock  is enabled
volatile uint8_t primary_tag_counter_without_tag = 0;  // Counters to find out no of primary cycles that the system sees without the TAG being present in the field 
volatile uint8_t secondary_tag_counter_without_tag = 0; // Counters to find out no of secondary cycles that the system sees without the TAG being present in the field
// tag response value for the selected deactivation mode.
uint8_t tags_before_alarm = 0;

//reset timer handler
static uint8_t  resetHandle_slot = 0Xff;
static uint8_t  previorResetValue = 0;

// Semaphore for blue auto tune LED window after reset 
uint8_t reset_led_on = 0;

// binary semaphore for scheduled freq counter 
uint8_t freq_counter_enabled = 0;
volatile uint8_t flag_ready_to_send_deact_event = false;

#if EVOLVESTORE
// Callback functions for sending 15 second status ping and
// inhibiting the receipt of a other connect flags.
void sendPing(void);
void statusInhibit(void);
#endif

/*
** Function: (ISR) VPA monitor signal
**
** Purpose : After the VPA rail is charged to the threshold voltage, a 
**			GPO is cleared which signals this ISR. At this point the PWM
**			is disabled and if the last TX/RX cycle occurred greater the
**			7ms, a new TX/RX cycle starts.
**			if a new cycle is started, clear the active low TX gate for 
**			6us.
**
** Parameters:
**     Input : source from VPA rail monitor (comparator)
**
**     Return: None
**
** Effected Var's:	frame_counter: used to ensure the PWM is on no longer
**									than 14ms to protect HW
**					
**
** Effected IO/HW: GPO connected to the TX and RX gates are exercised (TX/RX cycles)
**					and PWM used for the DC/DC boost is disabled. 
**
*/
ISR(VPA_MAX_INT_vect)
{
	// Stop charging VPA rail and set frame counter used to ensure over 
	// charging does not occur.
	pwm_stop();
	
	// Don't start the frame timer (TX/RX cycles) if auto tuning is active
	// and only if interlock is received or disabled. 
	// Also do not start the frame if the freq counter function is active.
#if EVOLVESTORE
	if((!autotune_timing_flag) && (TxRx_cycle_enable) &&
		(!freq_counter_enabled) && (!(config_parameters.nightsave)))
#else
	if((!autotune_timing_flag) && (TxRx_cycle_enable) && (!freq_counter_enabled))
#endif
	{
		frame_timer_start(); // added for new charge up changes		
	}

	frame_counter = 0;	
}


/*
** Function: (ISR) interlock signal
**
** Purpose : The interlock is used to enable deactivation for a given period of time
**				and exit the sleep mode. If Halfnon all GPIO are re-initialized, all 
**				peripherals are re-enabled. For all cases the 7ms frame timer starts 
**				and PWM starts to charge the VPA rail. 
**
** Parameters:
**     Input : Source from external device
**
**     Return: None
**
** Effected Var's: All input/output pins are re-initialized after coming 
**					out of the sleep mode for Hafnon.
**
** Effected IO/HW: PWM starts charging the VPA rail until the feedback from 
**					the VPA monitor is received and rail is discharged if VPA rail
**					is larger then the new setting.
**
*/
ISR(INTERLOCK_INT_vect)
{
	uint8_t vpa_result = 0;

#if EVOLVESTORE
	// if nightsave is enabled do not allow a interlock signal to restart the frames.
	if(!(config_parameters.nightsave))
	{
#endif
	// If the eeprom reset value was never cleared (0xff) (Auto tune was never done)
	// and auto tune mode is "AUTO TUNE" (enum=0) do not process interlock ISR. 
	// This would start TX/RX cycles when the system should be disabled.
	if((nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) != 0xff) || 
	   (config_parameters.ant_tune_onpowerup))
	{
#if 0
		TEST_PORT.OUTSET = TEST_PIN;
#endif
	
#if PWM_DURING_INTER
		SET_STATE(STATE_PROCESS);
		pwm_stop();
#endif
		// make sure all alarms are off before processing the interlock 
		// signal.
		ledOff();
		sounderOff();
		outputOff();
	
		// initialize the GPO feature and active state selected by the 
		// DMS user. Only one of these features can be active at one time.
		processGpoPin(GPO_PRI_SOUND_OUTPUT, GPO_CLEAR);
		processGpoPin(GPO_PRI_NO_SOUND_OUTPUT, GPO_CLEAR);
		processGpoPin(GPO_SEC_OUTPUT, GPO_CLEAR);
		
		dac_write_data(2);
	
#if RAIL_DISCHARGE
		// discharge code
		// There could be a condition when the interlock signals are coming in 
		// at a fast pace where the VPA rail is charged higher than the 
		// threshold voltage. In these cases TX/RX frame may not start.
		// To fixed this issue discharge the rail a little bit lower than 
		// the deactivation mode's normal VPA rail.
		if((config_parameters.mode_ind == DEACT_MODE6) ||
		   (config_parameters.mode_ind == DEACT_MODE5))
		{
			setVPA_Level(config_parameters.tx_power, 
			             config_parameters.deact_frame_rate);
		}
		else // verify and 4 mode.
		{
			setVPA_Level(config_parameters.config_detect_level, 
			             config_parameters.deact_frame_rate);
		}
	
		vpa_result = PORTA.IN;
		if((vpa_result & (VPA_MAX_PIN)) == 0)
		{
			pwm_stop();
			TX_ENABLE_N_PORT.OUTSET = TX_ENABLE_N_PIN; /* Thoralite */
			while((vpa_result & (VPA_MAX_PIN)) == 0)
			{
				vpa_result = PORTA.IN;
			}
			TX_ENABLE_N_PORT.OUTCLR = TX_ENABLE_N_PIN; /* Thoralite */
			gDACIndexLoaded = 0;
		}
		// end of discharge code ///////////////////////////////
#endif
	
		// Enable TX/RX cycle and start looking for the release of the
		// active low interlock signal before starting the interlock timer.
		TxRx_cycle_enable = 1;
		start_intlk_timer = 1;
	
		// Process interlock indication.
		processInterlock();

#if HALFNON	
		// Wakeup from deep sleep and set IO pins to start 
		// deactivation
		if(GET_STATE(STATE_SLEEP))
		{
			restore_from_sleep();
			lowlevel_init();	
		}
#endif

#if USE_DDS
		DDS_mclk_timer_start();
#endif
		vpa_result = PORTA.IN;
		
		// If the VPA monitor signal is low do not start the PWM VPA
		// charging output. There could be an issue with the TX circuit
		// not allowing the VPA to drain off.
		if((vpa_result & (VPA_MAX_PIN)) == VPA_MAX_PIN)
		{
			pwm_start();
		}
		else
		{
			pwm_stop();
		}
#if 0
		TEST_PORT.OUTCLR = TEST_PIN;
#endif
	}
#if EVOLVESTORE
	}
#endif	
}

/*
** Function: (ISR) Tag_n signal
**
** Purpose : This signal comes from a pin connected to the dual 
**			comps which detects a tag from the receiver. Only a 
**			small window for this signal to be received is maintained.
**			Contains logic to lock onto a frequency during detection 
**			and then release the lock for deactivation. Also uses a 
**			consecutive tag rate counter to reduce false alarming.  
**
** Parameters:
**     Input : Receiver output via interrupt 
**
**     Return: None
**
** Effected Var's:	1) tag_counter: counts consecutive tags
**					2) frame_counter_flag: counts frames
**					3) last_alarm_count: last frame a tag was detected
**
** Effected IO: 1) Disables receiver ISR for the rest of the frame
**				2) locks transmit freq during detection
**				3) counts consecutive frames at user selected rate
**					before issuing an alarm. 
**
*/
ISR(PIN_N_vect)
{
	static uint32_t last_alarm_count = 0;
	static uint32_t pri_last_alarm_count = 0;
	static uint32_t sec_last_alarm_count = 0;
	static uint8_t pri_tag_counter = 0;
	static uint8_t sec_tag_counter = 0;
	//static uint8_t alarm_ind_counter = 0;
	//uint8_t alarm_loop = 0;
		
	// Disable the receiver ISR and gate to RF switch
	TAG_N_PORT.INT0MASK &= (~TAG_N_PIN);
	
	// No need to process a tag if in deactivation Mode 5
	if((!(config_parameters.mode_ind == DEACT_MODE5)) && (!autotune_timing_flag))
	{
#if MODE_PROCESS	
		if(config_parameters.deact_frame_rate == FRAME_144HZ)
		{	
			// Lock in a frequency only during detection	
			if((gDACIndexLoaded > 0) && (enable_freq_lock))
			{
				gDACIndexLoaded--;
			}
		}
#else
		// This is outside of the tag response test below, this means every tag
		// detected will reset the counter to 5. It will be up to the main loop
		// (every 7 ms) bring this down to zero.
		if((alarm_count_down != 0) && /*(config_parameters.mode_ind == DEACT_MODE4) &&*/
		   (!inhibit_flag))
		{
			if((config_parameters.mode_ind == DEACT_MODE4) && (config_parameters.deact_frame_rate == FRAME_10HZ))
			{
				if(config_parameters.enable_tx_2)
				{
					alarm_count_down = 40000;
				}
				else
				{
					alarm_count_down = 25000;
				}
				//alarm_count_down = 25000;
			}
			else
			{
				alarm_count_down = 5000;
			}
	
			// refresh the alarm
			startAlarm(0);
		}
	
		if(config_parameters.deact_frame_rate == FRAME_144HZ)
		{
			// Lock in a frequency only during detection
			if((gDACIndexLoaded > 0) && (enable_freq_lock))
			{
				gDACIndexLoaded--;
			}
		}
#endif
		// Count consecutive tags and alarm only if the user defined number of tags have
		// been detected before issuing an alarm
		// This branch of code is used when the 2nd transmitter is disabled.
		if((!primary_ant_flag) && (!secondary_ant_flag))
		{
#if 0
			// execute this only when we dont have to have a delay between
			// We dont want to add delay after 5th pulses in Mode 4 and verification
			if ((5 != pulseNumber) || (DEACT_MODE4 == config_parameters.mode_ind)
			 || (DEACT_VERIFY == config_parameters.mode_ind))
			{	
#endif		
				// Keep track of consecutive frames and create a starting point.
				if((last_alarm_count == 0) || ((last_alarm_count+1) == frame_counter_flag) ||
					(last_alarm_count == frame_counter_flag))
				{
					last_alarm_count = frame_counter_flag;
					
					// each time this gets enabled the count get set to 0 since we are trying to count frames without seeing the tag
					primary_tag_counter_without_tag = 0;
					// Count consecutive tags detected on the primary loop, if the number 
					// exceeds the DMS tag response duration an alarm occurred.
					if((++pri_tag_counter) > (tags_before_alarm))
					{
						pri_tag_counter = 0;
						last_alarm_count = 0;
						frame_counter_flag = 0;
						flag_ready_to_send_deact_event = 0;
						 GTimer_Refresh(send_ping_handler, G_TIMER_2S);
#if MODE_PROCESS
						setAlarms(config_parameters.mode_ind, DEACT_STATE, 0);
#else
						if((alarm_count_down == 0) && /*(config_parameters.mode_ind == DEACT_MODE4) &&*/
						   (!inhibit_flag))
						{
							startAlarm(0);
					
							if((config_parameters.mode_ind == DEACT_MODE4) && (config_parameters.deact_frame_rate == FRAME_10HZ))
							{
								alarm_count_down = 25000;
							}
							else
							{
								alarm_count_down = 5000;
							}
					
							//alarm_count_down = 5000;
#if 0
							TEST_PORT.OUTSET = TEST_PIN;
#endif
							if(config_parameters.mode_ind == DEACT_MODE4)
							{
								// enable high power mode
								setMode4_HiPower();
							}
						}
#endif
					}
				}
				else
				{
#if MODE_PROCESS
#if 0
					if(config_parameters.mode_ind == DEACT_MODE4)
					{
						ledOff();
						sounderOff();
						outputOff();
					}
#endif
#endif		
					pri_tag_counter = 0;
					last_alarm_count = 0;
				}
#if 0
			} // If !Pulse No 
#endif
		}
		else  // 2nd TX enabled
		{
			if(primary_ant_flag)
			{
				if((pri_last_alarm_count == 0) || ((pri_last_alarm_count+1) == pri_frame_counter_flag) ||
					(pri_last_alarm_count == pri_frame_counter_flag))
				{
					pri_last_alarm_count = pri_frame_counter_flag;
					// each time this gets enabled the count get set to 0 since we are trying to count frames without seeing the tag
					primary_tag_counter_without_tag = 0;
					// Count tags on primary loop
					if((++pri_tag_counter) > (tags_before_alarm))
					{
						pri_tag_counter = 0;
						pri_last_alarm_count = 0;
						pri_frame_counter_flag = 0;
#if MODE_PROCESS
						setAlarms(config_parameters.mode_ind, DEACT_STATE, 0);
#else
						if((alarm_count_down == 0) && /*(config_parameters.mode_ind == DEACT_MODE4) &&*/
						(!inhibit_flag))
						{
							startAlarm(0);
							if(/*(config_parameters.mode_ind == DEACT_MODE6) &&*/ (config_parameters.enable_tx_2))
							{
								enable_freq_lock = 0;
							}
						
							if((config_parameters.mode_ind == DEACT_MODE4) && (config_parameters.deact_frame_rate == FRAME_10HZ))
							{
								//alarm_count_down = 25000;
								alarm_count_down = 40000;
							}
							else
							{
								alarm_count_down = 5000;
							}
						
							//alarm_count_down = 5000;
#if 0
							TEST_PORT.OUTSET = TEST_PIN;
#endif
							if(config_parameters.mode_ind == DEACT_MODE4)
							{
								// enable high power mode
								setMode4_HiPower();
							}
						}
#endif
					}
				}
				else
				{
#if MODE_PROCESS
#if 0
					if(config_parameters.mode_ind == DEACT_MODE4)
					{
						ledOff();
						sounderOff();
						outputOff();
					}
#endif
#endif
					pri_tag_counter = 0;
					pri_last_alarm_count = 0;
				}
			}
			else  // secondary_ant_flag
			{
				if((sec_last_alarm_count == 0) || ((sec_last_alarm_count+1) == sec_frame_counter_flag) ||
					(sec_last_alarm_count == sec_frame_counter_flag))
				{
					sec_last_alarm_count = sec_frame_counter_flag;
					// each time this gets enabled the count get set to 0 since we are trying to count frames without seeing the tag
					primary_tag_counter_without_tag = 0;
					// Count tags on the secondary loop
					if((++sec_tag_counter) > (tags_before_alarm))
					{
						sec_tag_counter = 0;
						sec_last_alarm_count = 0;
						sec_frame_counter_flag = 0;
#if MODE_PROCESS
						setAlarms(config_parameters.mode_ind, DEACT_STATE, 1);
#else
						if((alarm_count_down == 0) && /*(config_parameters.mode_ind == DEACT_MODE4) &&*/
						(!inhibit_flag))
						{
							startAlarm(0);
							if(/*(config_parameters.mode_ind == DEACT_MODE6) &&*/ (config_parameters.enable_tx_2))
							{
								enable_freq_lock = 0;
							}
						
							if((config_parameters.mode_ind == DEACT_MODE4) && (config_parameters.deact_frame_rate == FRAME_10HZ))
							{
								//alarm_count_down = 25000;
								alarm_count_down = 40000;
							}
							else
							{
								alarm_count_down = 5000;
							}
						
							//alarm_count_down = 5000;
#if 0
							TEST_PORT.OUTSET = TEST_PIN;
#endif
							if(config_parameters.mode_ind == DEACT_MODE4)
							{
								// enable high power mode
								setMode4_HiPower();
							}
						}
#endif
					}
				}
				else
				{
#if MODE_PROCESS
#if 0
					if(config_parameters.mode_ind == DEACT_MODE4)
					{
						ledOff();
						sounderOff();
						outputOff();
					}
#endif
#endif				
					sec_tag_counter = 0;
					sec_last_alarm_count = 0;
				}			
			}
		}
	}
}

/*
** Function: resetErase()
**
** Purpose : Erases the Byte set when reset button is pressed after
**           2 seconds based on timer
**
** Parameters:
**     Input : None
**
**     Return: Never
**
** Effected Var's:
**
** Effected IO: None
**
*/
void resetErase(void)
{
	uint8_t intlk_signal_state = 0;
	// Erase the RESET Byte
	nvm_eeprom_write_byte( EEPROM_ZIRCON_RESET_STORE, previorResetValue );
	// and stop the timer
	GTimer_Stop(resetHandle_slot);
	ledOff();
	reset_led_on = 0;
	
	// If this is the case the TX/RX cycles are disabled and auto tuning is needed. A teal LED wil be lit
	// to indicate this condition
	if ( (0Xff == nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) && (TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) ) )
	{
		GTimer_unRegisterCB(autotune_overvolt_handler);
		GTimer_unRegisterCB(autotune_verify_handler);
		ledBlueGreenOn();
	}
	else
	{
		intlk_signal_state = PORTE.IN;

		// Check the if interlock is enabled and the interlock pin state is in non-active state (high).
		// Turn on the yellow LED if this is the case. 
		if(config_parameters.intlk_enable &&
		(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
		( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock)))
		{
			ledYellowOn();
		}
		else if(DEACT_VERIFY == config_parameters.mode_ind)
		{
			ledBlueOn();
		}
	}
}

#if EVOLVESTORE
// Enable the 5 second status ping when the host tasks start.
void sendPing(void)
{
#if 0
	TEST_PORT.OUTSET = TEST_PIN;
#endif
	// This change was put back since there was communication failure in sending the ping for evolve
	// from inside the main while loop 10/23/2015 NCR changes
    //Statement not true unless the code below is put back was older comment  --> The sending part is now part of the main Loop

	cli();
	// FormatAndSendSpecficCMD(ZIRCON_CONFIG_CONNECT);
     FormatAndSendSpecficCMD(ZIRCON_CONFIG_STATUS);
     // Put it inside the cli sei block
	 GTimer_Refresh(send_ping_handler, G_TIMER_2S);
	sei();
	//GTimer_Refresh(send_ping_handler, G_TIMER_5S);
	// Put this inside the cli sei block
	//--> original Place GTimer_Refresh(send_ping_handler, G_TIMER_2S);
	//did not work For Test G_TIMER_1S when we were sending the Ping from the main loop
	//GTimer_Refresh(send_ping_handler, G_TIMER_1S);
	// This change was taken out because there was communication failure in sending the ping for evolve 
	// from inside the main while loop 10/23/2015 NCR changes
	//flag_send_ping_handler = 1;
#if 0
	TEST_PORT.OUTCLR = TEST_PIN;
#endif
}

// Re-enable the RS-232 port 1 second after EvolveStore sends
// the 0x7f connect flags. This will inhibit multiple status
// messages from being sent.
void statusInhibit(void)
{
	memset(&messageBufferOut[0],0, sizeof(messageBufferOut));
	if(1 == flag_status_inhibit_handler)
	{
		dms_rs232_init();
		flag_status_inhibit_handler = 0;
	}
}

void sendAlarmPing(void)
{
	// Sending the msg is part of the main loop now
	//	cli();
	//alarmPingType= 0;
	//	FormatAndSendSpecficCMD(ZIRCON_CONFIG_ALARM_PING);
	//	sei();
	flag_send_alarm_ping_handler  = 1;
	// Set this only if it is non zero
	if (0 != alarm_ping_time)
	{
		GTimer_Refresh(send_alarm_ping_handler, alarm_ping_time);
	}

}

// call this function to build and/or retrieve the bit mapped status payload in
// either the status ping or connect ACK message.
uint16_t buildStatusPayload(uint8_t status)
{
	static uint16_t bitmappedPayload = 0;
	static uint16_t bitmappedPayloadAlarm = 0;
	static uint16_t temp = 0;
	static uint16_t temp1 = 0;
	
	switch(status)
	{
		case PAYLOAD_CLEAR_STATUS:
			bitmappedPayload = 0x0000;
			bitmappedPayloadAlarm = 0x0000;
		break;
		
		// detection and deactivation is disabled
		case PAYLOAD_ENABLE_NIGHTSAVE:
			bitmappedPayload = bitmappedPayload | (0x0001);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0001);
		break;
		
		// detection and deactivation is enabled
		case PAYLOAD_DISABLE_NIGHTSAVE:
			bitmappedPayload = bitmappedPayload & (~(0x0001));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0001));
		break;
		
		// detection and deactivation is enabled
		case PAYLOAD_KEYSWITCH_ENABLE:
			bitmappedPayload = bitmappedPayload & (~(0x0002));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0002));
		break;
		
		// detection and deactivation is disabled
		case PAYLOAD_KEYSWITCH_DISABLE:
			bitmappedPayload = bitmappedPayload | (0x0002);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0002);
		break;
		

		case PAYLOAD_MISS_TUNED:
		    // Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload | (0x0010);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0010);
		break;
		
		case PAYLOAD_TUNED:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload & (~(0x0010));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0010));
		break;

		case PAYLOAD_VOLTAGE_OVER:
	        // Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload | (0x0020);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0020);
		break;

		case PAYLOAD_VOLTAGE_NORMAL:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload & (~(0x0020));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0020));
		break;

		case PAYLOAD_INTERLOCK_ENABLED:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload | (0x0040);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0040);
		break;

		case PAYLOAD_INTERLOCK_DISABLED:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload & (~(0x0040));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0040));
		break;

		case PAYLOAD_TX3_ENABLED:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload | (0x0080);
			bitmappedPayloadAlarm = bitmappedPayloadAlarm | (0x0080);
		break;

		case PAYLOAD_TX3_DISABLED:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = bitmappedPayload & (~(0x0080));
			bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x0080));
		break;

		case PAYLOAD_MODE_4:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload =  bitmappedPayload & (~(0x000C))  ;
		break;
		
		case PAYLOAD_MODE_5:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = ((bitmappedPayload & (~(0x000C))) | (0x0004));
		break;

		case PAYLOAD_MODE_6:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = ((bitmappedPayload & (~(0x000C))) | (0x0008));
		break;
		
		case PAYLOAD_MODE_V:
			// Will Require Evolve Changes since falling in Evolve for Evolve Store 
			//bitmappedPayload = ((bitmappedPayload & (~(0x000C))) | (0x000C));
		break;

		default:
	
			if ( PAYLOAD_GET_STATUS == status)
			{
				// Will Require Evolve Changes since falling in Evolve for Evolve Store 
				//temp = 0;
				//temp = alarmCount; // No of Alarms seen by the system
				//temp = temp << 8;
				//bitmappedPayload = ((bitmappedPayload & (~(0xFF00))) | (temp)) ;
				// We don't have to accumulate the count it will be reset once it reaches 255

				return(bitmappedPayload);
			}
			else
			{
				temp = 0;
				temp = alarmCountNCR; // No of Alarm see by the system, for NCR Bit 12 –15: Will indicate the TAG Count (0 to 15)
				temp = temp << 12;  //  Changed for chris 08/05/2015 after talk with him temp << 8;
				temp1 = 0;
				temp1 = alarmRefreshCount; //Bit 8-11: Will indicate relative duration the alive TAG is in the RF field (See table for the mapping of timings)
				temp1 = temp1 << 8;	// Changed for chris 08/05/2015 after talk with him  temp1 << 12;	 		
				// We have to accumulate the alarm count as per NCR
				if ( 2 == flag_send_alarm_ping_handler)
				{ // Asynchronous msg start of alar,
					bitmappedPayloadAlarm = ((bitmappedPayloadAlarm & (~(0x000C))) | (0x0004));
				} else if ( 3 == flag_send_alarm_ping_handler)
				{
					// Asynchronous msg end of alarm
					bitmappedPayloadAlarm = ((bitmappedPayloadAlarm & (~(0x000C))) | (0x0008));
					alarmRefreshCount = 0; // one it has send this it should reset to zero, since it indicates the duration of last tag seen
				} else
				{   // synchronous msg just the Ping no alarm
					bitmappedPayloadAlarm = bitmappedPayloadAlarm & (~(0x000C)) ;
				}
				// duration of last tag seen and and alarm count
				bitmappedPayloadAlarm = ((bitmappedPayloadAlarm & (~(0xFF00))) | (temp) | (temp1)) ;
				
				
				return(bitmappedPayloadAlarm);
			}

		break;
	}
	
	return(bitmappedPayload);
}
#endif

/*
** Function: main()
**
** Purpose : Initialize GPIO and timers, starts interrupts and 
**			sets state to sleep and enters sleep mode until a
**			interlock signal is received to start deact.
**			During the PROCESS state host communications could
**			be active and in the future service tool processing
**			could occur. Host processes are executed in between
**			interrupt processing.
**
** Parameters:
**     Input : None
**
**     Return: Never
**
** Effected Var's:
**
** Effected IO: all GPIO pins are set to inputs during sleep mode
**
*/
int main(void)
{
	uint8_t return_value, i, IO_enabled;
#if PWM_DURING_INTER
	uint8_t vpa_result = 0;
#endif
	//uint8_t GPI_pin_state = 0;
	uint8_t intlk_signal_state = 0;
	uint8_t GPI_arm_switch = 0;
	uint8_t write_eeprom_flag = 1;
	uint8_t startPattern[3] = {0x7E, 0x7E, 0X7E};
#if EVOLVESTORE
	uint8_t EvolveStoreStartPattern[3] = {0x7f, 0x7f, 0X7f};
	uint8_t  SoftInterLockStartPattern[3] = {0x7a, 0x7a, 0X7a}; //test using ascii "z"
#endif
	
#if ENABLE_WD
	// Enable and set watchdog to expire in 8 secs
	// setting timeout for MAX for now until a timing study is made
	wdt_enable(WDT_PER_8KCLK_gc);
#endif

	// Initialize RS232 Buffers for DMS session
	i = 0;
	memset(&messageBufferIn[0],0, sizeof(messageBufferIn));
	memset(&messageBufferOut[0],0, sizeof(messageBufferOut));
	
	// Initialize GPIO pins to there default states
	lowlevel_init();
	
#if ENABLE_WD_TICKLE
	WDT_Reset();
#endif
	
	// Check the eeprom CRC and if corrupted or non-existence (first time)
	// read dip switches and set default parameters. If CRC is good read
	// eeprom and populate config DB. This call also provides a profile
	// default setting for each mode for non-DMS users  
	set_parameters();

	if(CPiD_HW_flag)  /* Thoralite */
	{
		// Initialize the GPIO pins for user input features
		IO_enabled = initGPIO();
	}
	else
	{
		// Disable IO for Thoralite and don't initialize GPIO
		IO_enabled = GPO_DISABLE_IO;
	}
	
	// Indicate the unit is powered up via GPO pin if this feature
	// is selected
	processGpoPin(GPO_ON_OFF_OUTPUT, GPO_SET);
	
	// Interlock pin is set only if Interlock is Enabled (Thoralite)
	if (( 1 == config_parameters.intlk_enable) && (CPiD_HW_flag))
	{
		INTERLOCK_PORT.INT0MASK = INTERLOCK_PIN;
	}
	
	// Initialized PWM timer for DC/DC boost circuit and DACs for 
	// frequency generation and VPA rail voltage adjust.
	pwm_init();
	dac_init();

#if HALFNON
	ac_init();  // used to measure the battery level
#endif

	if(CPiD_HW_flag) /* Thoralite */
	{
		// If the interlock dip switch is set (interlock enables) then
		// do not start the TX/RX cycle (frame timer) and wait for an
		// interlock signal.
		if(config_parameters.intlk_enable)
		{
			TxRx_cycle_enable = 0;
		}
		else
		{
			TxRx_cycle_enable = 1;
		}
	}
	else
	{
		TxRx_cycle_enable = 1;
	}
	
	// Tag response duration set by the DMS tool and used to 
	// detect a certain number of consecutive tags 
	tags_before_alarm = getConfigInfo(CONFIG_TAG_RATE);

	// Set frame rate, config the interlock time from the DMS, set the tag band
	// and the from the DMS. Also enable the 2nd TX if enables
	// by DMS. The deactivation mode is selected by the dip switches.
	setFrameRate(config_parameters.deact_frame_rate);
	
	configInterlock(getConfigInfo(CONFIG_INTLK_DURATION), 
					getConfigInfo(CONFIG_INTLK_RANGE), 
					INTERLOCK_HARDWIRE, 
						config_parameters.intlk_enable);

	return_value = setTagBand(config_parameters.deact_tagband);
	
	if (DEACT_MODE4 ==config_parameters.mode_ind )  //change for sending deactivation message
	{
		setDeactMode(DEACT_VERIFY, config_parameters.enable_tx_2);
	}
	else
	{
		setDeactMode(config_parameters.mode_ind, config_parameters.enable_tx_2);
	}
	
	///////////////////////////////////////////////////////////////////////////
	
	// Created the first frame jitter value (+/- 500us) for the TX/RX cycle
	createJitter(0);

	// Initialize timers and HW (sounder/LED/output) for alarming. Set the 
	// initial LED pattern for a given mode
	GTimer_Initial();
	alarmInit(config_parameters.mode_ind, config_parameters.intlk_enable, IO_enabled);

// Because of the risk using the VCO for creating TX freqs, include an option
// to use the high cost DDS.
#if USE_DDS
	DDS_mclk_timer_init();
	DDS_mclk_timer_start();
	// Initialize and enable the SPI for the DDS if used
	dds_spi_init();
	dds_spi_enable();
	
	// Init of the DDS
	ad9833_init();
	
	// Turn the DDS off
	ad9833_set_mode(AD_OFF);	
#else
	//dac_init();
#endif
#if ENABLE_WD_TICKLE
	WDT_Reset();
#endif

	sei(); // enable interrupts
	
#if USE_FREQ_COUNT

	// Sandeep: this function is called at the start to correct and measures all the 16 frequencies 
	// for further operations 
	// Note: The success of this method lies in calibrating the frequency correctly the first time
	// as it will take less cycle to converge to good value.
	measure_and_correct_frequency( ) ;

#if 0
	// Sandeep: Example code to measure 1 frequency at a time can be used in other part of the code
	gDACIndexLoaded = 0;
	xmega_freq_cntr_init();

	for (gDACIndexLoaded= 0; gDACIndexLoaded < NO_OF_FREQUENCY_TABLE_VALUES ; gDACIndexLoaded++ )
	{
		measure_and_correct_single_frequency( );
	}

#endif
#endif	
	
#if ENABLE_WD_TICKLE
	WDT_Reset();
#endif
	
	// Start the timer and callback function for the auto tuning 
	// verification which occurs sometime after the system is running.
	if(autotune_verify_handler == 0xff)
	{
		autotune_verify_handler = GTimer_RegisterCB(&verifyTuning);
	}
	if(autotune_verify_handler < G_TIMER_MAX_SLOT)
	{
		GTimer_Refresh(autotune_verify_handler, G_TIMER_1H); // original 
		//GTimer_Refresh(autotune_verify_handler, G_TIMER_30S);
	}

	if(config_parameters.mode_ind != DEACT_VERIFY)
	{
		// Start the timer and callback function for the overvoltage
		// verification which occurs sometime after the system is running.	
		if(autotune_overvolt_handler == 0xff)
		{
			autotune_overvolt_handler = GTimer_RegisterCB(&verifyovervolt);
		}
		if(autotune_overvolt_handler < G_TIMER_MAX_SLOT)
		{
			GTimer_Refresh(autotune_overvolt_handler, G_TIMER_30S);
			//GTimer_Refresh(autotune_overvolt_handler, G_TIMER_1M);
		}
	}

#if EVOLVESTORE
#if PING_ENABLE
	// setup the 15 second status ping timer
	if(send_ping_handler == 0xff)
	{
		send_ping_handler = GTimer_RegisterCB(&sendPing);
	}
	if(send_ping_handler < G_TIMER_MAX_SLOT)
	{
		GTimer_Refresh(send_ping_handler, G_TIMER_5S);
		//GTimer_Refresh(send_ping_handler, G_TIMER_1M);
	}
#endif
	// setup the 1 second RS-232 inhibit after the 0x7f connect flags
	// are sent.
	if(status_inhibit_handler == 0xff)
	{
		status_inhibit_handler = GTimer_RegisterCB(&statusInhibit);
	}
//	if(status_inhibit_handler < G_TIMER_MAX_SLOT)
//	{
//		GTimer_Refresh(status_inhibit_handler, G_TIMER_15S);
//		GTimer_Refresh(send_ping_handler, G_TIMER_1M);
//	}
#endif

// If Three type Auto tuning
#if THREE_TYPE_TUNING

	// Logic for getting the tuning parameters without going through the auto tuning process
	// start either auto tuning or manual tuning according to DMS
	if ( RESET_SUPPRESS_AUTOTUNE == config_parameters.config_reset_condition )
	{
		// In EEPROM it is already reseted
		config_parameters.config_reset_condition = RESET_NORMAL;
		// Manual Tuning
		if ( (TYPE_AUTO_TUNE_RESET != getConfigInfo(CONFIG_TUNE_ONPOWERUP) )  || (0Xff != nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) )
		{
			//startAutoTune(0 , 1, 0);
			startAutoTune(MANUAL_TUNE, NORMAL_MODE);
		}
		if ( (0Xff == nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) && (TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) ) )
		{
			GTimer_unRegisterCB(autotune_overvolt_handler);
			GTimer_unRegisterCB(autotune_verify_handler);
			ledBlueGreenOn();
		}
	}
	else
	{
		if ( TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) )
		{
			if ( 0 != (RST.STATUS & RST_EXTRF_bm) )
			{
				previorResetValue = nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE);
				if ( 1 == previorResetValue)
				{
					reset_led_on = 0;
					// Auto tune
					//startAutoTune(1 , 1, 0);
					//startAutoTune(PAR_AUTO_TUNE, 1, 0);
					startAutoTune(AUTO_TUNE, NORMAL_MODE);
					// clear the memory
					nvm_eeprom_write_byte(EEPROM_ZIRCON_RESET_STORE, 0X00);
				}
				else
				{
					//ledBlueOn();
					ledBlueRedOn();
					reset_led_on = 1;
					// write to eeprom 1 will be cleared after 2 seconds
					nvm_eeprom_write_byte(EEPROM_ZIRCON_RESET_STORE, 0X01);
					// Register the erase function and start the timer
					if( 0xff == resetHandle_slot )
					{
						resetHandle_slot = GTimer_RegisterCB(&resetErase);
					}
					if( resetHandle_slot < G_TIMER_MAX_SLOT )
					{
						GTimer_Refresh(resetHandle_slot, G_TIMER_500mS);
					}
					// Manual tune only if it ha been auto tuned earlier
					if ( 0Xff != previorResetValue )
					{
						// startAutoTune(0 , 1, 0);
						//startAutoTune(PAR_MANUAL_TUNE, 1, 0);
						startAutoTune(MANUAL_TUNE, NORMAL_MODE);
					}
				
				}
			
			}
			else
			{
				// Manual tune
				// This will indicate that we have never pressed the reset button hence no attempt to tune ever
				if ( 0Xff != nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) )
				{
					// startAutoTune(0 , 1, 0);
					//startAutoTune(PAR_MANUAL_TUNE, 1, 0);
					startAutoTune(MANUAL_TUNE, NORMAL_MODE);
				}
				// If this is the case then probably it has to be Auto tuned
				if ( (0Xff == nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) && (TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) ) )
				{
					GTimer_unRegisterCB(autotune_overvolt_handler);
					GTimer_unRegisterCB(autotune_verify_handler);
					ledBlueGreenOn();
				}
			}
		
		} 
		else if ( TYPE_MANUAL_TUNE_ONLY == getConfigInfo(CONFIG_TUNE_ONPOWERUP) )
		{
			// Manualtune
			// startAutoTune(0, 1, 0);
			//startAutoTune(PAR_MANUAL_TUNE, 1, 0);
			startAutoTune(MANUAL_TUNE, NORMAL_MODE);
		}
		else
		{
			// Autotune
			//startAutoTune(1, 1, 0);
			//startAutoTune(PAR_AUTO_TUNE, 1, 0);
			startAutoTune(AUTO_TUNE, NORMAL_MODE);
		}
	}

	RST.STATUS = RST_PORF_bm | RST_EXTRF_bm | RST_BORF_bm | RST_WDRF_bm |
					RST_PDIRF_bm | RST_SRF_bm | RST_SDRF_bm;

#else
	// Logic for getting the tuning parameters without going through the auto tuning process
	// start either auto tuning or manual tuning according to DMS
	if ( RESET_SUPPRESS_AUTOTUNE == config_parameters.config_reset_condition )
	{
		// In EEPROM it is already reseted
		config_parameters.config_reset_condition = RESET_NORMAL;
		// Manual Tuning
		startAutoTune(MANUAL_TUNE, NORMAL_MODE);
	}
	else
	{
		startAutoTune(!(getConfigInfo(CONFIG_TUNE_ONPOWERUP)), NORMAL_MODE);
	}

// End if #else  for THREE_TYPE_TUNING
#endif

	// blink blue LED if all configuration parameters are at the default value.
	if(default_config_flag)
	{
		if(default_config_handler == 0xff)
		{
			default_config_handler = GTimer_RegisterCB(&disableConfigLED);
		}
		if(default_config_handler < G_TIMER_MAX_SLOT)
		{
			GTimer_Refresh(default_config_handler, G_TIMER_5S);
		}
		
		defaultConfigBlinking();
	}
	else
	{
		if ( 0 == reset_led_on )
		{
			disableConfigLED();
		}
	}
	

#if HALFNON	
	// Enable battery monitoring (1.8v threshold)
	ac_enable();
#endif
	
// Sleep if Hafnon HW else process data in main loop	
#if HALFNON
	SET_STATE(STATE_SLEEP);
#else
	SET_STATE(STATE_PROCESS);
#endif	

	gDACIndexLoaded = 0;  // set to the first transmit frequency
	
	// disable DAC for compliance. This needs to be done in case the interlock is
	// enabled and jumper is not installed.
	dac_write_data(0);	
	
	dms_rs232_init( ); 
    
	// This is the idle loop when the system is not processing TX/RX frames which should 
	// be the majority of the frame rate time (4ms/7ms and 99ms/100ms)
    while(1) 
	{
#if ENABLE_WD_TICKLE
		WDT_Reset();
#endif
		if (GET_STATE(STATE_PROCESS))
		{	
			// Need to making timing measurements to properly place resets 
			// and set the proper timeout period.
#if ENABLE_WD_TICKLE
			WDT_Reset();
#endif

#if EVOLVESTORE
			// Creating EvolveStore payload for nightsave status
			if(config_parameters.nightsave)
			{
				buildStatusPayload(PAYLOAD_ENABLE_NIGHTSAVE);
			}
			else
			{
				buildStatusPayload(PAYLOAD_DISABLE_NIGHTSAVE);
			}
	
			// Creating EvolveStore payload for keyswitch status
			if((GPI_SWITCH_INPUT == getConfigInfo(CONFIG_GPI_APP)) &&
			(GPI_activeState()))
			{
				buildStatusPayload(PAYLOAD_KEYSWITCH_DISABLE);
			}
			else
			{
				buildStatusPayload(PAYLOAD_KEYSWITCH_ENABLE);
			}

			if(config_parameters.nightsave)
			{
				setVPA_Level(0, config_parameters.deact_frame_rate);
				// Disable alarm IO, PWM and interrupts before DMS session
				pwm_stop();
				ledOff();
				sounderOff();
				outputOff();
				frame_timer_stop();
		
				GTimer_unRegisterCB(autotune_overvolt_handler);
				autotune_overvolt_handler = 0xff;
		
				GTimer_unRegisterCB(autotune_verify_handler);
				autotune_verify_handler = 0xff;
		
				do
				{
					// Wait until RTC is not busy.
				} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
				rtc_interlock_timer_stop();
				// In night save make sure soft Interlock is disabled
				config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;				
			}
#endif // end evolveStore				
#if PWM_DURING_INTER
#if EVOLVESTORE
			if((!config_parameters.nightsave))
			{
#endif
			// If interlock is enabled and interlock pin is high (non-active state)
			// allow the VPA rail to continue to charge. This will allow the rail 
			// voltage to be at the defined level when interlock signal is received
			intlk_signal_state = PORTE.IN;
			// Take Soft interlock into consideration
			if((((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
			( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock) ) &&
			(config_parameters.intlk_enable))
			{
				// keep the VPA rail charged up during interlock
				vpa_result = PORTA.IN;
				
				// If the VPA monitor signal is low do not start the PWM VPA
				// charging output. There could be an issue with the TX circuit
				// not allowing the VPA to drain off.
				if((vpa_result & (VPA_MAX_PIN)) == VPA_MAX_PIN)
				{
					pwm_start();
				}
				else
				{
					pwm_stop();
				}
			}
#if EVOLVESTORE
			}
#endif
#endif		

#if MODE_PROCESS

#else
#if 0
			TEST_PORT.OUTSET = TEST_PIN;
#endif
			if(alarm_count_down != 0)
			{
				alarm_count_down--;
	
				if((alarm_count_down == 1)) /*&& (config_parameters.mode_ind == DEACT_MODE4))*/
				{
					//set inhibit for hi to low power transition??
					//inhibit_flag = 3000;
					inhibit_flag = 30;
#if 0
					TEST_PORT.OUTSET = TEST_PIN;
#endif
#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif

					if(config_parameters.mode_ind == DEACT_MODE4)
					{
						// fallback to low power mode
						setMode4_LoPower();
						//lo_power_flag = 1;
					}
					
#if 0				// Not sure we should disable the alarm ind at this point, for some cases it
					//looks like the response is faster with this enabled, but too fast in some
					// cases. In any case this would be only for mode 6
					// disable alarm indications
					ledOff();
					sounderOff();
					outputOff();
#endif
					alarm_count_down = 0;
				}
			}

			if(inhibit_flag > 0)
			{
				inhibit_flag--;
			}
			else // the else is only here for test purposes
			{
#if 0
				TEST_PORT.OUTCLR = TEST_PIN;
#endif
			}
#endif			

			if(CPiD_HW_flag)  /* Thoralite */
			{
				// If there is either a overvoltage (ant_fault) or mistune condition and this
				// feature is selected for the GPO, indication the condition to the user.
				// When the error clears, clear the active condition for the relay.
				if((config_parameters.ant_fault) || (config_parameters.ant_tune_mistune_ind))
				{
					processGpoPin(GPO_ERROR_OUTPUT, GPO_SET);
				}
				else
				{
					processGpoPin(GPO_ERROR_OUTPUT, GPO_CLEAR);
				}
				
				// Check for either force deactivation or keyswitch feature for
				// the GPI pin
				if(GPI_DEACT_INPUT == getConfigInfo(CONFIG_GPI_APP))
				{
					//GPI_pin_state = PORTF.IN;
					//if((GPI_pin_state & (GPI_PIN)) == 0)  // active state
					if(GPI_activeState())
					{
						// We need to change to a mode which will deact tags
						// if in the verify mode
						if(config_parameters.mode_ind == DEACT_VERIFY)
						{
							setDeactMode(DEACT_MODE6, config_parameters.enable_tx_2);
							GPI_mode_change = 1;
						}

						sounderOff();
						outputOff();
						processInterlock();

						frame_timer_start();

						// if the interlock is enabled and the interlock pin is high or if the normal
						// operating mode is verify mode use the interlock timer to either disable
						// TX/RX cycles or restore the original deactivation mode
						intlk_signal_state = PORTE.IN;
						if((((config_parameters.intlk_enable) &&
						(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
						( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock))))
						|| (GPI_mode_change))
						{
							rtc_interlock_timer_stop();
							rtc_interlock_timer_start();
						}
					}
				}
				else if(GPI_SWITCH_INPUT == getConfigInfo(CONFIG_GPI_APP))
				{
					//GPI_pin_state = PORTF.IN;
					//if((GPI_pin_state & (GPI_PIN)) == 0)  // active state
					if(GPI_activeState())
					{
						sounderOff();
						outputOff();
						
						// If the output relay for GPO is active when the keyswitch is pressed
						// make sure to put relays back to non active state.
						if((GPO_PRI_SOUND_OUTPUT == getConfigInfo(CONFIG_GPO_APP)) ||
							(GPO_PRI_NO_SOUND_OUTPUT == getConfigInfo(CONFIG_GPO_APP)) ||
							(GPO_SEC_OUTPUT == getConfigInfo(CONFIG_GPO_APP)))
						{
							GPOoutputOff(getConfigInfo(CONFIG_GPO_STATE));
						}
						
						frame_timer_stop();
						interlockLEDOn();
						GPI_arm_switch = 1;
					}
					else
					{
						if(GPI_arm_switch)  // button was released
						{
							GPI_arm_switch = 0;
							
							intlk_signal_state = PORTE.IN;
							if(!((config_parameters.intlk_enable) &&
							(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
							( SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock))))
							{
								frame_timer_start();
								interlockLEDOff();
							}
							else
							{
								frame_timer_stop();
								interlockLEDOn();
							}
						}
					}
				}
			}
			
			// An interlock signal has been received, wait for the signal to go high
			// before starting the interlock timer. This also allows some denouncing 
			// for mechanical switching
			if((start_intlk_timer) && (CPiD_HW_flag))  /* Thoralite */
			{
#if 0
				TEST2_PORT.OUTSET = TEST2_PIN;
#endif
				intlk_signal_state = PORTE.IN;
				if(((intlk_signal_state & (INTERLOCK_PIN)) == INTERLOCK_PIN) &&
				(SOFT_INTERLOCK_DISABLE == config_parameters.config_soft_interlock))
				{
					start_intlk_timer = 0;
					rtc_interlock_timer_start();
				}
#if 0
				TEST2_PORT.OUTCLR = TEST2_PIN;
#endif
			}
			
			// a scheduled tuning verification has occurred by the timer expiring
			// and exec a callback function to set this flag.	
			if(AUTOTUNE_VERIFY_EXECUTE == autotune_verify_flag)
			{
#if 0
				TEST_PORT.OUTSET = TEST_PIN;
#endif
				// if auto or manual tuning is selected by the DMS and the mode 
				// is not verify mode, start the verify tuning process.
				if(!(config_parameters.mode_ind == DEACT_VERIFY))
				{
					intlk_signal_state = PORTE.IN;

					if((config_parameters.intlk_enable == 0) ||
					((config_parameters.intlk_enable) &&
					(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
					( SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))))
					{
						// signals auto tune to compare this measured value with the
						// originally started value
						autotune_verify_started = 1;
						startAutoTune(MANUAL_TUNE, NORMAL_MODE);
					}
				}
#if 0				
				TEST_PORT.OUTCLR = TEST_PIN;
#endif
				
				autotune_verify_flag = AUTOTUNE_VERIFY_FREQ_COUNTING;  // Execute the measure and correct frequency logic in the next session

			}
			else if(AUTOTUNE_VERIFY_FREQ_COUNTING == autotune_verify_flag)
			{
				freq_counter_enabled = 1;
				// Stop the frame timer since it will interferer with the auto tuning process
				frame_timer_stop();
#if 0
				TEST_PORT.OUTSET = TEST_PIN;				
#endif
				dac_write_data(2);
				// measure and correct frequency
				measure_and_correct_frequency( );
#if 0
				TEST_PORT.OUTCLR = TEST_PIN;
#endif
				dac_write_data(0);
				freq_counter_enabled = 0;
				
				// reset flag for next session
				autotune_verify_flag = AUTOTUNE_VERIFY_RESET;
				// Reset the timer back to original values
				GTimer_Refresh(autotune_verify_handler, G_TIMER_1H);  // original
				//GTimer_Refresh(autotune_verify_handler, G_TIMER_30S);
				// Start the frame timer again
				gDACIndexLoaded = 0;
				
				if(!(config_parameters.intlk_enable))
				{
					frame_timer_start();
				}
				else // interlock enabled
				{
					// This should fix the issue with starting the frame when
					// the interlock signal is grounded during power up.
					intlk_signal_state = PORTE.IN;
					if(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
					(SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))
					{
						processInterlock();
						start_intlk_timer = 1;  // enable level monitoring in idle loop
						frame_timer_start();
						// If it is timed based Soft interlock
						if(SOFT_INTERLOCK_ENABLE_TIMED == config_parameters.config_soft_interlock)
						{
							config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;
						}						
					}
				}
			}
			
			// Perform overvoltage measurement.
			// Overvoltage is checked the first time within 30 seconds at power up.
			// After the first time it occurs every 30 minutes.
			if(autotune_overvoltmeas_flag)
			{
				intlk_signal_state = PORTE.IN;
				if((config_parameters.intlk_enable == 0) ||
				((config_parameters.intlk_enable) &&
				(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
				( SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))))
				{
#if 0
					TEST_PORT.OUTSET = TEST_PIN;
#endif
					pwm_stop();
					frame_timer_stop();
					//autotune_overvoltmeas_flag = 0;
					//GTimer_Refresh(autotune_overvolt_handler, G_TIMER_30M);
					//GTimer_Refresh(autotune_overvolt_handler, G_TIMER_30S);
					startAutoTune(MANUAL_TUNE, OVERVOLT_MODE);
#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif
				}
				
				autotune_overvoltmeas_flag = 0;
				GTimer_Refresh(autotune_overvolt_handler, G_TIMER_30M);
				//GTimer_Refresh(autotune_overvolt_handler, G_TIMER_30S);
			}
			
			// if we receive first 0x7E	we go into blocking read
			// since we assume that DMS is trying to communicate
			// So please implement all your functionality inside
			// this if and not inside the else part.
			// it will again be in non blocking read state after the DMS task is over.
#if EVOLVESTORE
			if (( 0x7E != messageBufferIn[0] ) &&  (0x7f/*0x7A*/ != messageBufferIn[0]) &&  (0x7A != messageBufferIn[0]))
#else
			if ( 0x7E != messageBufferIn[0] )
#endif
			{
				messageBufferIn[0] = dms_rs232_getchar_non_block();
			}
			else
			{
#if 0
				TEST_PORT.OUTTGL = TEST_PIN;
#endif
				// go into blocking mode
				messageBufferIn[i] = dms_rs232_getchar();
							
				if ( 0  == ( memcmp( messageBufferIn, startPattern, sizeof(startPattern) ) ) )
				{
					// Disable alarm IO, PWM and interrupts before DMS session
					pwm_stop();
					ledOff();
					sounderOff();
					outputOff();
					frame_timer_stop();
					// Disable the soft interlock
					config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;
					
					GTimer_unRegisterCB(autotune_overvolt_handler);
					autotune_overvolt_handler = 0xff;
					
					do
					{
						// Wait until RTC is not busy.
					} while ( INTERLOCK_TIMER.STATUS & RTC_SYNCBUSY_bm );
					rtc_interlock_timer_stop();
					
					// Moved writes to the EEprom here to reduce the chance of reverting
					// back to default config if reset button is rapidly pressed
					// This fixes Defect #69
					// This is done only once for each power cycle.
					if(write_eeprom_flag)
					{
						write_eeprom_flag = 0;
						writeConfigValuestForDMSToEEPROM();					
					}
							
					cli();
					bAborted = DMS_DISCONNECT_INDICATION_DEFAULT;
					// First ACK the Start Command
					FormatAndSendSpecficCMD(ZIRCON_CONFIG_CONNECT);
					// Go into DMS processing state Name of the function is smiler to the one used in Evolve
					// of it is easy to change the protocol if needed
					SerFEPTask();

					if ( ( ( NO_RESET_EXIT_DMS_MODE != config_parameters.config_reset_condition ) &&
					( RESET_INDICATOR != config_parameters.config_reset_condition ) ) ||
					( DMS_DISCONNECT_INDICATION_NOCOM == bAborted ) )
					{
						// no need to enable the interrupts as it will get enabled on restart
						software_reset();
					}
					else  // this is the path to DMS tuning
					{
						do
						{
							// Wait until RTC is not busy.
						} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
						rtc_interlock_timer_stop();
						do
						{
							// Wait until RTC is not busy.
						} while ( RTC.STATUS & RTC_SYNCBUSY_bm );
						// Set the rtc_interlock timer back to its original settings

						configInterlock(getConfigInfo(CONFIG_INTLK_DURATION),
						getConfigInfo(CONFIG_INTLK_RANGE),
						INTERLOCK_HARDWIRE,
						config_parameters.intlk_enable);
						// Initialize RS232 Buffers for DMS session
						i = 0;
						memset(&messageBufferIn[0],0, sizeof(messageBufferIn));
						memset(&messageBufferOut[0],0, sizeof(messageBufferOut));

						sei(); // enable interrupts
								
// Three type of auto tuning
#if THREE_TYPE_TUNING
						if( ( RESET_INDICATOR == config_parameters.config_reset_condition )  &&
						( (TYPE_AUTO_TUNE_RESET != getConfigInfo(CONFIG_TUNE_ONPOWERUP) )  ||
						(0Xff != nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) ) )
						{
							// We want the Manual Tuning to start in  DMS mode
							startAutoTune(MANUAL_TUNE, DMS_MODE);
							startAutoTune(MANUAL_TUNE, DMS_OV_MODE);
						}

						// Set the initial LED pattern for a given mode
						// Yellow light has priority over blue verify mode LED
						if ( (0Xff == nvm_eeprom_read_byte(EEPROM_ZIRCON_RESET_STORE) ) && (TYPE_AUTO_TUNE_RESET == getConfigInfo(CONFIG_TUNE_ONPOWERUP) ) )
						{
							ledBlueGreenOn();
						}
						else
						{
							// Set the initial LED pattern for a given mode
							// Yellow light has priority over blue verify mode LED
							// also start frame timer if interlock is enabled, but
							// pin is low or interlock is disabled.
							if((config_parameters.intlk_enable) && (CPiD_HW_flag)) /* Thoralite */
							{
								intlk_signal_state = PORTE.IN;
								if(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
								( SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))
								{
									if(DEACT_VERIFY == config_parameters.mode_ind)
									{
										ledBlueOn();
									}
			
									frame_timer_start();
								}
								else
								{
									ledYellowOn();
								}
							}
							else
							{
								if(DEACT_VERIFY == config_parameters.mode_ind)
								{
									ledBlueOn();
								}
		
								frame_timer_start();
							}
						}

#else

						// Set the initial LED pattern for a given mode
						// Yellow light has priority over blue verify mode LED
						// also start frame timer if interlock is enabled, but
						// pin is low or interlock is disabled.
						if((config_parameters.intlk_enable) && (CPiD_HW_flag))  /* Thoralite */
						{
							intlk_signal_state = PORTE.IN;
							if(((intlk_signal_state & (INTERLOCK_PIN)) == 0) ||
							(SOFT_INTERLOCK_DISABLE != config_parameters.config_soft_interlock))
							{
								if(DEACT_VERIFY == config_parameters.mode_ind)
								{
									ledBlueOn();
								}
		
								frame_timer_start();
							}
							else
							{
								ledYellowOn();
							}
						}
						else
						{
							if(DEACT_VERIFY == config_parameters.mode_ind)
							{
								ledBlueOn();
							}
	
							frame_timer_start();
						}

						if( RESET_INDICATOR == config_parameters.config_reset_condition )
						{
							// We want the Manual Tuning to start in  DMS mode
							startAutoTune(MANUAL_TUNE, DMS_MODE);
							startAutoTune(MANUAL_TUNE, DMS_OV_MODE);
						}
// end of else if THREE_TYPE_TUNING
#endif
					}
				}
#if EVOLVESTORE
				else if(( 0  == (memcmp(messageBufferIn, EvolveStoreStartPattern, sizeof(EvolveStoreStartPattern)))))
				{
					cli();
					pwm_stop();
					// For Testing
					//----------------------Enable for Testing will be removed later-----
					//config_parameters.config_enable_alarm = 0X0100;
					//flag_config_enable_alarm = 1;
					//flag_enable_hard_tag_indicator = 1;
					//alarm_ping_time = G_TIMER_15S;
					//alarm_ping_time = 0;
					 //Register the alarm ping as soon as you see the
					//if(send_alarm_ping_handler == 0xff)
					//{
					//	send_alarm_ping_handler = GTimer_RegisterCB(&sendAlarmPing);
					//}
					//----------------------------------------------------------------
					// For test
					// Will have to keep tis as we will have to stop the Ping as soon as we get this
					GTimer_unRegisterCB(send_ping_handler);
					send_ping_handler = 0xff;
					
					// Stop the Alarm ping as soon as you see disable
					// Registration happens when ZIRCON_CONFIG_DISABLE_STATUS is seen
					GTimer_Stop(send_alarm_ping_handler);
#if 0
					TEST_PORT.OUTSET = TEST_PIN;
#endif
					memset(&messageBufferIn[0],0, sizeof(messageBufferIn));
					// Two ways to control soft interlock
					// a. The one used by NCR by using the 0X7F (Disable soft Interlock ) and 0X7A (Enable soft Interlock), This method was chosen
					// since the response time was needed to be around 200 ms, with this method it is approx 100 ms, (But we should claim it to be below 200 ms )
					// b. Using DMS interface (first send 0X7E to connect) and send ZIRCON_CONFIG_SOFT_INTERLOCK with different payload, 0 : Disable interlock
					// 1: Enable Interlock, 2: Enable Time based interlock.
					// Disable the soft interlock
					config_parameters.config_soft_interlock = SOFT_INTERLOCK_DISABLE;
					// This flag is set when we receive disable status msg
					// NCR mode	
					if( 1 == flag_config_enable_alarm)
					{
						sounderOff();
						interlockLEDOn();
						frame_timer_stop();
						outputOff();
						start_intlk_timer = 0;  // enable level monitoring in idle loop
						FormatAndSendSpecficCMD(ZIRCON_CONFIG_SOFT_INTERLOCK);

					} else
					{
						FormatAndSendSpecficCMD(ZIRCON_CONFIG_CONNECT);
					}
					//  Reset in the inhipit handeler memset(&messageBufferOut[0],0, sizeof(messageBufferOut));
					dms_rs232_disable();
					flag_status_inhibit_handler = 1; // in case we dont start dms in the 100 ms handler because it will be low priority in the latest code
#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif

					sei();
					
					if(status_inhibit_handler < G_TIMER_MAX_SLOT)
					{
						// G_TIMER_1S replaced by G_TIMER_100mS G_TIMER_200mS
						GTimer_Refresh(status_inhibit_handler, G_TIMER_100mS);
					}
#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif
				} else if(( 0  == (memcmp(messageBufferIn, SoftInterLockStartPattern, sizeof(SoftInterLockStartPattern)))))
				{
					cli();
					pwm_stop();
#if 0
					TEST_PORT.OUTSET = TEST_PIN;
#endif
					memset(&messageBufferIn[0],0, sizeof(messageBufferIn));
					// Two ways to control soft interlock
					// a. The one used by NCR by using the 0X7F (Disable soft Interlock ) and 0X7A (Enable soft Interlock), This method was chosen
					// since the response time was needed to be around 200 ms, with this method it is approx 100 ms, (But we should claim it to be below 200 ms )
					// b. Using DMS interface (first send 0X7E to connect) and send ZIRCON_CONFIG_SOFT_INTERLOCK with different payload, 0 : Disable interlock
					// 1: Enable Interlock, 2: Enable Time based interlock.
					// Disable the soft interlock
					// Enable Soft Interlock
					config_parameters.config_soft_interlock = SOFT_INTERLOCK_ENABLE;
					FormatAndSendSpecficCMD(ZIRCON_CONFIG_SOFT_INTERLOCK);
					//  Reset in the inhipit handeler memset(&messageBufferOut[0],0, sizeof(messageBufferOut));
					dms_rs232_disable();
					flag_status_inhibit_handler = 1; // in case we dont start dms in the 100 ms handler because it will be low priority in the latest code
#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif
					// start the timer only if you see a non zero time
					if( (send_alarm_ping_handler < G_TIMER_MAX_SLOT) && (0 != alarm_ping_time))
					{
						GTimer_Refresh(send_alarm_ping_handler, alarm_ping_time);
					}
					
					processInterlock();
					start_intlk_timer = 1;  // enable level monitoring in idle loop
					// Set frame rate to its original value for start
					setFrameRate(config_parameters.deact_frame_rate);
					frame_timer_start();
					sei();
					// Enable the interlock
					
					if(status_inhibit_handler < G_TIMER_MAX_SLOT)
					{
						// G_TIMER_1S replaced by G_TIMER_100mS   G_TIMER_200mS
						GTimer_Refresh(status_inhibit_handler, G_TIMER_100mS);
					}

#if 0
					TEST_PORT.OUTCLR = TEST_PIN;
#endif
				}
#endif
				else
				{
					if(i > 2)
					{
						memset(&messageBufferIn[0],0, sizeof(messageBufferIn));
						i = 0;
					}
					else
					{
						i = i + 1;
					}
				}
							
			} //end of else 0X7e

			// Send all the Ping messages here , there flags are set in there respective ISR
			if(flag_send_alarm_ping_handler)
			{
				cli();
				FormatAndSendSpecficCMD(ZIRCON_CONFIG_ALARM_PING);
				// Until we have sent the previous end alarm dont let the next start alarm over write the msg
				if( 3 == flag_send_alarm_ping_handler)
				{
					flag_send_end_alarm = 0;
				}	
				flag_send_alarm_ping_handler = 0;
				sei();
	
			}
			// This change was taken out because there was communication failure in sending the ping for evolve
			// from inside the main while loop 10/23/2015 NCR changes
			// IMP Note: We have to look at it when we make any changes for the communication between Evolve and CPiD
			// It seem to be too tightly coupled
			//else if(flag_send_ping_handler)
			//{

				//cli();
				//FormatAndSendSpecficCMD(ZIRCON_CONFIG_STATUS);
			//	flag_send_ping_handler = 0;
				//sei();
			//}
			
#if 0 // This is now done in the DMS 	
			// Limit the VPA rail voltage for the 10 Hz frame rate
			if(config_parameters.deact_frame_rate == FRAME_10HZ)
			{
				if(config_parameters.tx_power > LIMIT_VPA_10HZ)
				{
					config_parameters.tx_power = LIMIT_VPA_10HZ;
					if(config_parameters.hi_low_ind)
					{
						config_parameters.config_hi_power = config_parameters.tx_power;
						if (DEFAULT_TX_POWER_HI == config_parameters.tx_power )
						{
							Set_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);// Write 2 byte  data to EEPROM
							Clr_bits(config_parameters.config_hi_power, DISPLAY_DEFAULT_DMS);
						}
						else
						{
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_HI_POWER, &config_parameters.config_hi_power, 2);
						}						
					}
					else
					{
						config_parameters.config_lo_power = config_parameters.tx_power;
						if (DEFAULT_TX_POWER_LO == config_parameters.tx_power )
						{
							Set_bits(config_parameters.config_lo_power, DISPLAY_DEFAULT_DMS);
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);// Write 2 byte  data to EEPROM
							Clr_bits(config_parameters.tx_power, DISPLAY_DEFAULT_DMS);
						}
						else
						{
							nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_LO_POWER, &config_parameters.config_lo_power, 2);
						}
					}
					
					calc_crc =  calculateCrcEeprom();
					nvm_eeprom_erase_and_write_buffer(EEPROM_ZIRCON_CONFIG_CRC, &calc_crc, 2) ;// EEPROM_ZIRCON_CONFIG_CRC, &eeprom_crc, 2					
				}
			}
#endif	
		} // end of STATE_PROCESS
#if MODE_PROCESS

#else
		else
		{
#if 0
			TEST_PORT.OUTCLR = TEST_PIN;
#endif
		}
#endif		
#if HALFNON
		else if (GET_STATE(STATE_SLEEP))
		{
			prepare_for_sleep();
			enter_sleep();
		}
#endif
	}	
	
	return 0;
}


