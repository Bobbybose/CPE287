#include "SysTick.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

// Used in part 3
volatile uint32_t g_handler_calls;
int i;
//Initialize Systick
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup

  NVIC_ST_RELOAD_R = 0x00FFFFFF;// reload value

  NVIC_ST_CURRENT_R = 0;      // any write to current clears it

  NVIC_ST_CTRL_R = 0x07; // enable SysTick with core clock and interrupts
}


// Configure SysTick to generate an interrupt every 20ms
// Assume 16 MHz clock
void SysTick_Init_Interrupts(void){
	g_handler_calls = 0; //Initialize counter as 0

	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 319999;
	NVIC_ST_CURRENT_R = 0; 
	NVIC_ST_CTRL_R = 0x07;

}


// Clock speed is 16 MHz
static void SysTick_Delay1ms_16MHz(void){
	//Use the Systick Timer to generate a 1ms delay
	
	NVIC_ST_RELOAD_R = 16000;
	
	NVIC_ST_CURRENT_R = 0; // Any value written to write clears it
	while((NVIC_ST_CTRL_R&0x00010000)==0){} // Wait for count flag
}


// Write code to generate a 2 sec delay
// Your code should call SysTick_Delay1ms()
void SysTick_Delay2s_16MHz(void){
	for (i = 0; i < 2000; i++) {
		SysTick_Delay1ms_16MHz();
	}
} 


// Write code to generate 1ms delay assuming a clock speed of 50MHz
static void SysTick_Delay1ms_50MHz(void){
	NVIC_ST_RELOAD_R = 50000;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){}
}


//// Write code to generate a 2 sec delay when the clock speed is 50MHz
//// Your code should call SysTick_Delay1ms_50MHz()
void SysTick_Delay2s_50MHz(void){
	for (i = 0; i < 2000; i++) {
			SysTick_Delay1ms_50MHz();
		}
}
	


// Toggle green LED every 2 seconds
// Toggle blue LED every 1 second
void SysTick_Handler(void){
	
	g_handler_calls++;
	if (g_handler_calls == 50) {
		GPIO_PORTF_DATA_R ^= 0x4;
	}
	else if (g_handler_calls == 100) {
		GPIO_PORTF_DATA_R ^= 0x4;
		GPIO_PORTF_DATA_R ^= 0x8;
		g_handler_calls = 0;
	}
}