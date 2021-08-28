#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"

// In this file you should insert your code from the previous lab


// Initialize UART0
// Assumes 16 MHz clock, creates 9600 baud rate
void InitConsole(void){
		SYSCTL_RCGC1_R |= 0x1;	// Enable UART0
		SYSCTL_RCGC2_R |= 0x1;	// Enable PortA clk
		UART0_CTL_R &= ~0x1;		// Disable UART0
	
		// Set the baud rate - need to change for Part 1
		UART0_IBRD_R = 104;
		UART0_FBRD_R = 11;
	
		UART0_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
	
		// Uncomment these lines in a friendly manner
		GPIO_PORTA_AFSEL_R |= 0x03;	// Enable alt function on PA1, PA0
		GPIO_PORTA_PCTL_R  |= (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;	// Set PCT to choose UART alt function on PortA
		GPIO_PORTA_AMSEL_R  &= 0x00;	// Clear AMSEL to disable analog
		GPIO_PORTA_DEN_R  |= 0x03;		// Enable PA1, PA0
	
	
		UART0_CTL_R |= 0x1;  // Enable UART0
	
		// Needed for the UARTprintf() functions to work correctly.  
		// Intentially broken to remove normal behavior.
		// UART0 will not work without correctly completing the above initialization.
    UARTStdioConfig(0, 9600, 16000000);
}

// Should block until the user presses a key and then returns that value
// Returns a newline until it has been correctly implemented
unsigned char myGetChar(void){
		char retchar = '\n';
		
		// Wait for the proper FIFO flag to be 0
	  while((UART0_FR_R & 0x10) != 0){}
		// Return the received value
    retchar = (unsigned char) (UART0_DR_R & 0xFF);
		return retchar;
}
