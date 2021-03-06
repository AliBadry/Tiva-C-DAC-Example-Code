

#include "DAC.h"
#include "..//tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x00000002;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_AMSEL_R &= ~0x0F;
	GPIO_PORTB_PCTL_R &= ~0x0000FFFF;
	GPIO_PORTB_AFSEL_R &= ~0x0F;
	GPIO_PORTB_DIR_R |= 0x0F;
	GPIO_PORTB_DEN_R |= 0x0F;
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R= data;
}
