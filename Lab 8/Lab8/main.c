#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "lab7.h" // UART functions from the previous lab
#include "systick.h" // Delay function


//Prototypes from Lab 7 (located in lab7.c)
void InitConsole(void);
unsigned char myGetChar(void);

//Student Written Functions
void ADC0_Init(void);
uint32_t Get_TempC(void);
void Print_Temps (uint32_t TempC);
uint32_t ADC0_In(void);
uint32_t Convert_Raw_To_V(uint32_t raw);
uint32_t Convert_V_To_C(uint32_t v);
uint32_t Convert_C_To_F ( uint32_t TempC);


int main(void)
{
		unsigned char keystroke; // Can be used in Part 3
		uint32_t tempC;
	
		// Initialize UART for 16 MHz clock and 9600 baud
    InitConsole();
	
		// Initialize SysTick
		SysTick_Init();
    
		//Initialize ADC0 to take temperature readings
		ADC0_Init();
    
		
		UARTprintf("Initialization Complete...\n");

    // Continually read and display the temperature
    while(1)
    {	
        //Print_Temps (Get_TempC());
				//Delay_100ms(); // Included to make console output less frequent
				
				keystroke = myGetChar();
				tempC = Get_TempC();
			
				if( (keystroke == 'c') || (keystroke == 'C') )
					UARTprintf("%d*C\n", tempC);
				else if( (keystroke == 'f') || (keystroke == 'F') )
					UARTprintf("%d*F\n", Convert_C_To_F(tempC));
				else
					UARTprintf("Unrecognized input %c! Enter 'F' for Fahrenheit or 'C' for Celcius\n", keystroke);
				
				
			}
}


 /****************************************************
 *  NOTE: You need to complete the following functions
 *****************************************************/

void ADC0_Init(void)
{
	 /*
	 // We do not need to initialize a GPIO pin since we are measuring temperature
	 //   using the internal temperature sensor within the CPU on the board.  It should be 
	 //   noted that this sensor is uncalibrated and thus it may report temperatures that
	 //   deviate from the actual chip's temperature by a number of degrees
	  
    SYSCTL_RCGCGPIO_R |= 0x10;    // 1) activate clock for Port E and allow time to stabilize
	  while((SYSCTL_RCGCGPIO_R & 0x10)==0){}	
    GPIO_PORTE_DIR_R &= ~0x10;  // 2) make PE4 input
    GPIO_PORTE_AFSEL_R |= 0x10; // 3) enable alternate function on PE4
    GPIO_PORTE_DEN_R &= ~0x10;  // 4) disable digital I/O on PE4
    GPIO_PORTE_AMSEL_R |= 0x10; // 5) enable analog functionality on PE4
	  
		*/
	SYSCTL_RCGCADC_R |= 0x0001;   // 6) activate ADC0 and allow time to stabilize
	while((SYSCTL_RCGCADC_R&0x1)==0){}
	
		
	/****************************************** 
	 * Uncomment and complete this line
	 ******************************************/
  ADC0_PC_R = 0x2;								  // 7) configure for 500K samples/sec
	
		
		
  ADC0_SSPRI_R = 0x0123;        // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;      // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // 10) seq3 is software trigger
	/*
	  // No need to choose a channel since we are measuring temperature
    
		ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 9;           // 11) set channel
	 
		*/
			
	ADC0_SSCTL3_R = 0x000E;			// // 12) no D0, yes TS0 IE0 END0
  ADC0_ACTSS_R |= 0x0008;       // 13) enable sample sequencer 3 before we sample.
}

// Returns the temperature in Celsius
// You should call ADC0_In, convertRawToVolts(), and convertVoltsToCelsius()
uint32_t Get_TempC(void){
	int i;
	uint32_t result=0;
	
	// Read raw result from ADC0
	// Try averaging multiple readings together to produce a single output
	for(i=0; i<10; i++){
		result += ADC0_In();
	}
	
	result /= 10;
	
	// For debugging, hard code the ADC output as 1746.  This will ultimately produce a temperature of 42C.
	//result = 1746;
	
	// Convert raw ADC value to millivolts
	
	result = Convert_Raw_To_V(result);
	
	// The hardcoded raw value of 1746 should convert to roughly 1407 mV.  Use the debugger to confirm 
	//   Convert_Raw_To_V() has returned the correct value.
	
	// Convert voltage to Celsius
	
	result = Convert_V_To_C(result);
	
	// Return temperature in Celsius
	return result;
}

// Take a reading from the ADC0 Sample Sequencer 3 and return the raw value
uint32_t ADC0_In(void){
	uint32_t v=0;	
	
	// 1) initiate SS3
	ADC0_PSSI_R = 0x0008;
	
  // 2) wait for conversion done
	while((ADC0_RIS_R & 0x08) == 0){};
	
  // 3) read result
	v = ADC0_SSFIFO3_R&0xFFF; 
		
  // 4) acknowledge completion
	ADC0_ISC_R = 0x0008; 
	
	return v;
}

uint32_t Convert_Raw_To_V(uint32_t raw){
	uint32_t result;
	
	// Convert raw ADC value to mV.
	// voltage = max_possible_voltage * ADC_result / max_possible_ADC_value
	
	result = 3300 * result;
	
	result /= 4095;
	
	return result;
}

// Convert temperature from millivolts to Celsius
uint32_t Convert_V_To_C(uint32_t v){
	uint32_t result;
	
	/*
	 * Equation derived from pg. 812 of the "Tiva™ TM4C123GH6PM 
	 * Microcontroller Data Sheet" (available online)
   *
	 * Voltage (mV) / 1000 = 2.7 - ((TempC + 55)/75)
	 */
	
	result = (((((v) - 2700) * -1) * 75) - 55000)/1000;
	
	return result;
}

// Convert a temperature from Celsius to Fahrenheit
uint32_t Convert_C_To_F( uint32_t TempC)
{	
	// complete this equation
	uint32_t TempF = (TempC * 1.8 + 32);

	//uint32_t TempF = TempC * 9;
	//TempF = TempF / 5;
	//TempF += 32;
	
	return TempF;
}

// Prints the temperature in Celsius
// Should later also convert to and print in Fahrenheit
void Print_Temps (uint32_t TempC)
{
	uint32_t TempF = Convert_C_To_F(TempC);
	
	// UARTprintf() works in exactly the same way as normal printf()
	UARTprintf("Temperature = %3d*C", TempC);
  UARTprintf("      Temperature = %3d*F\n", TempF);		
	
}

//EOF
