
GPIO_PORTF_DATA_R  EQU 0x400253FC

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start
	EXPORT 	Example_Function
	EXPORT 	Part3_Function
	EXPORT	Part4_Function
	EXPORT	Part5_Function
	IMPORT	delay
	IMPORT	leds_off
	IMPORT  PortF_Init
	IMPORT	Example
	IMPORT	Part3
	IMPORT  Part4
	IMPORT	Part5
		
Start
	BL PortF_Init 	; Initialize the LEDs and Pushbuttons
	BL debug		; Useful for parts 2 and 3
loop
	LDR R1, =GPIO_PORTF_DATA_R
	LDR R0, [R1]
	AND R0, #0x11	;Get just the pushbutton values
	CMP R0, #0x11	;No buttons pressed?
	BNE checkSW1
	BL Example
	B loop
checkSW1
	CMP R0, #0x01 	;SW1 pressed?
	BNE checkSW2
	BL Part3
	B blink
checkSW2
	CMP R0, #0x10 	;SW2 pressed?
	BNE both
	BL Part4
	B blink
both
	BL Part5		;Both must be pressed
	
	;Create blinking effect
blink
	BL delay
	BL leds_off
	BL delay

	B loop



debug
	;Place parts 1 and 2 here
	
	LDR R0, =0x00000008

	LDR R1, =0xFFFFFFFD
	
	LDR R2, =0x7FFFFFFF
	
	ADDS R3, R0, R1
	SUBS R3, R0, R0
	ADDS R3, R0, R2
	SUBS R3, R1, R2
	ADDS R3, R2, R3
	

	MOV R7, #0x20000000
	ADD R7, #2
	
	LDR R6, [R7]
	LDRH R6, [R7]
	LDRB R6, [R7]
	LDRSH R6, [R7]
	LDRSB R6, [R7]

	BX LR ;Returns to main function



; Returns Z = A+B
; A and B are in R0 and R1, respectively
; Z should be placed in R0
Example_Function
	ADD R0, R0, R1 ;Comment out this instruction to see the Example fail
	BX LR


; Should return Z = (A << 2)|(B & 15)
; Assume A and B are in R0 and R1, respectively
; The value of Z should be placed in R0 at the end
Part3_Function

	;Your code here

	LSL R0, R0, #2
	AND R1, R1, #15
	ORR R0, R0, R1


	BX LR
	
	
; Should return Z = ((A + B) + (A - B)) | (A << B)
; Assume A and B are in R0 and R1, respectively
; The value of Z should be placed in R0 at the end
Part4_Function

	;Your code here

	ADD R2, R0, R1
	
	SUB R3, R0, R1
	
	ADD R2, R2, R3
	
	LSL R3, R0, R1

	ORR R0, R2, R3
	
	BX LR


; Should return Z = X + Y
; Where X = ((A*8)|(B*4)|(C*2))
; and Y = ((B xor 2)|(C xor 4)
; Assume A, B, and C are in R0, R1, and R2, respectively
; The value of Z should be placed in R0 at the end
Part5_Function

	;Your code here

	LSL R3, R0, #3
	LSL R4, R1, #2
	LSL R5, R2, #1
	
	ORR R6, R3, R4
	ORR R6, R6, R5  ;R6 is X
	
	
	EOR R3, R1, #2
	EOR R4, R2, #4
	ORR R7, R3, R4 ; R7 is Y
	
	ADD R0, R6, R7
	
	BX LR



	ALIGN        ; make sure the end of this section is aligned
	END          ; end of file