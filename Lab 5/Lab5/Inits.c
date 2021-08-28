#include "Inits.h"
#include "tm4c123gh6pm.h" // Hardware register definitions
#include "stdint.h"

// Initialize PD1 and PD0 as inputs
// Leave everything else unchanged
void PortD_Init(void){
	SYSCTL_RCGC2_R |= 0x08;
	
	GPIO_PORTD_AMSEL_R &= ~0x03;
	GPIO_PORTD_PCTL_R &= ~0x0000FFFF;
	
	GPIO_PORTD_DIR_R &= 0xFC;
	GPIO_PORTD_AFSEL_R &= ~0x03;
	GPIO_PORTD_DEN_R |= 0x03;
}

// Initialize PE5, PE4, and PE3 as outputs
// Leave everything else unchanged
void PortE_Init(void){
	SYSCTL_RCGC2_R |= 0x10;
	
	GPIO_PORTE_AMSEL_R &= ~0x38;
	GPIO_PORTE_PCTL_R &= ~0x0000FFFF;
	
	GPIO_PORTE_DIR_R |= 0x38;
	GPIO_PORTE_AFSEL_R &= ~0x38;
	GPIO_PORTE_DEN_R |= 0x38;
}


void PortF_Init(void){
	SYSCTL_RCGC2_R |= 0x20;
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B;			//Unlocking GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;							//Allow changes to PF4-0
	
	GPIO_PORTF_AMSEL_R &= 0x00;
	GPIO_PORTF_PCTL_R &= 0x00000000;
	
	GPIO_PORTF_DIR_R |= 0x0E;						//PF3-1 Outputs
	GPIO_PORTF_DIR_R &= 0x0E;						//PF0 and PF4 Inputs

	GPIO_PORTF_AFSEL_R &= 0x00;
	
	GPIO_PORTF_PUR_R |= 0x11;
	GPIO_PORTF_DEN_R |= 0x1F;
}
