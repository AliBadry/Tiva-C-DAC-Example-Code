

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

unsigned long Index;
const unsigned char sinwave[16] = {2,4,6,8,10,12,14,15,14,12,10,8,6,4,2,1};
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
	Index= 0;
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R& 0x00FFFFFF)|0x20000000; //PRIORITY 1
	NVIC_ST_CTRL_R = 0x0007;
	
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	NVIC_ST_RELOAD_R = period-1;
	NVIC_ST_CTRL_R = 0x0007;
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	NVIC_ST_CTRL_R = 0;
	GPIO_PORTB_DATA_R=0;
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
   Index=(Index+1) & 0x0F;
	DAC_Out(sinwave[Index]);
}
