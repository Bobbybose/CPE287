#include "Inits.h"
#include "IO.h"
#include "stdint.h"

int main(){

	// Must be volatile to guarantee a new button state being retrieved
	volatile uint32_t buttons;

	//PortD_Init();
	//PortE_Init();
	PortF_Init();
	
	// You will need to write more functions than just these
	
//	while(1){
//		green_toggle();
//		delay();
//		green_toggle();
//		
//		blue_toggle();
//		delay();
//		blue_toggle();
//		
//		red_toggle();
//		delay();
//		
//		green_toggle();
//		blue_toggle();
//		delay();
//		
//		LEDs_off();
//		
//		buttons  = pushbuttons();
//		
//		delay();
//	}


//Red bit 0
//Green bit 1
//Blue bit 2
// BGR
	while(1){
				
		LEDs_off();
	
		buttons = pushbuttons();
		
		if(buttons == 0x01){
			
			//000
			delay();
			
			//001
			red_toggle();
			delay();
			
			//010
			red_toggle();
			green_toggle();
			delay();
			
			//011
			red_toggle();
			delay();
			
			//100
			red_toggle();
			green_toggle();
			blue_toggle();
			delay();
			
			//101
			red_toggle();
			delay();
			
			//110
			red_toggle();
			green_toggle();
			delay();
			
			//111
			red_toggle();
			delay();
			
		}
		
		
		if(buttons == 0x02){
			delay();
			delay();

			do{
			
				LEDs_off();	
				
				//010
				green_toggle();
				
				if(delay2() == 0){
					LEDs_off();
					delay();
					delay();
					break;
				}


				//101
				red_toggle();
				green_toggle();
				blue_toggle();

				if(delay2() == 0){
					LEDs_off();
					delay();
					delay();
					break;
				}
			
			
				buttons = pushbuttons();
				} while(buttons != 0x02);
			
			}
			
			
		buttons = pushbuttons();

	}
	
	return 0;
}

