#ifndef __ALARM_H__
#define __ALARM_H__

#define GPO_DISABLE_SOUNDER				1
#define GPO_DISABLE_IO					2
#define GPO_ENABLE_ALL					0

// enables and disables frequency locking
extern uint8_t enable_freq_lock;
extern uint8_t  alarmHandle_solt;
// initialize sounder, led and output gpios
// Deact_mode: This is the deactivation mode (Modes 4, 5, 6 and Verifier). 
// enable: This value is read from a dip switch and used to determine if the interlock is disabled 
void alarmInit(uint8_t deact_mode, uint8_t enable, uint8_t IO);

void startAlarm(uint8_t loop);

// when interlock timer expired, turn on the interlock led
void interlockLEDOn(void);

//when interlock interrupt coming, turn off the led
void interlockLEDOff(void);

// this function is used for mis-tuning occurs
// indicate user by blinking red led
void misTuningBlinking(void);

void misTuningBlinkingOff(void);

void DefaultBlinkingExpired(void);
void defaultConfigBlinking(void);
void defaultConfigBlinkingOff(uint8_t interlock_status);


void  ledYellowOn(void);
void  ledBlueOn(void);
void  ledRedOn(void);
void  ledBlueGreenOn(void);
void ledBlueRedOn(void);
void ledOff(void);

void sounderOn(void);
void sounderOff(void);

void outputOn(void);
void outputOff(void);

void GPOoutputOff(uint8_t active_state);

void IncrementAlarmRate(void);

#endif

