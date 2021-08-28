#include "IO.h"
#include "tm4c123gh6pm.h"

//Place the definition for bit specific addressing here.  
//The below example is for PortA pin 5
//#define PA5 (*((volatile uint32_t *)0x40004080))

#define PF0 (*((volatile unsigned long *)0x40025004))		//Button/Switch 2
#define PF1 (*((volatile unsigned long *)0x40025008))		//Red LED
#define PF2 (*((volatile unsigned long *)0x40025010))		//Blue LED
#define PF3 (*((volatile unsigned long *)0x40025020))		//Green LED
#define PF4 (*((volatile unsigned long *)0x40025040))		//Button/Switch 1


//Place your pushbutton and led functions here

//Turns off all LEDs
void LEDs_off(void){
	PF1 = 0x00;
	PF2 = 0x00;
	PF3 = 0x00;
}

void green_toggle(void){
	PF3 ^= 0x08;
}

void blue_toggle(void){
	PF2 ^= 0x04;
}

void red_toggle(void){
	PF1 ^= 0x02;
}

//Should return the button states
uint32_t pushbuttons(void){
	
	// Set to 42 because the compiler expects a return value.  
	// Your function only needs to return a value denoting the button states
	// rather than the answer to life, the universe, and everything...	
	
	if ( (PF0 == 0x00) && (PF4 == 0x00)  )					//If both are being pressed
		return 3;
	else if ( (PF0 == 0x00) && (PF4 == 0x10) )			//If only button 2 is being pressed
		return 2;
	else if ( (PF0 == 0x01) && (PF4 == 0x00) )			//If only button 1 is being pressed
		return 1;
	else if ( (PF0 == 0x01) && (PF4 == 0x10) )			//If neither buttons are being pressed
		return 4;
	
	
	return 42;
}

void delay(void){
	int i;
	
	for(i=0; i<1000000; i++){
	}
	
}

int delay2(void){
		int k=0;
		for(k=0; k<71250; k++){
			
			if(pushbuttons() == 0x02){

				return 0;
			}	
		}

		return 1;
}

