



	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start
	IMPORT  PortF_Init;
	IMPORT  delay
	IMPORT	delay_dim
	IMPORT  blue_led_on
	IMPORT  blue_led_off
	IMPORT  red_led_on
	IMPORT  red_led_off
	IMPORT  green_led_on
	IMPORT  green_led_off

Start
	BL PortF_Init; ; Initialize the LEDs and Pushbuttons

loop

	B parts34 ;Uncomment this line to skip the toggling routine used in Parts 1 and 2

	BL red_led_on
	BL delay
	BL red_led_off
	BL delay
	B loop


parts34
red EQU 4
	LDR R2, =red

red_function
	BL red_led_on
	BL delay
	BL red_led_off
	BL delay
	SUBS R2, R2, #1	
	BNE red_function
bg EQU 3
	LDR r3, = bg
bg_loop
blue EQU 3
	LDR r2, =blue
blue_function
	BL blue_led_on
	BL delay
	BL blue_led_off
	BL delay
	SUBS R2, R2, #1
	BNE blue_function
		
green EQU 2
	LDR r2, =green
green_function
	BL green_led_on
	BL delay
	BL green_led_off
	BL delay
	SUBS r2, r2, #1
	BNE green_function
	SUBS R3, R3, #1
	BNE bg_loop
	B parts34
	
	ALIGN        ; make sure the end of this section is aligned
	END          ; end of file