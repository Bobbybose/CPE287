

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	export exp
	EXPORT mulsum4
	IMPORT green_led_on
	IMPORT red_led_on
	IMPORT leds_off
	;Be sure to export created functions
	
	
	

		

;Should perform the operation (R0+R1)^R0
;Takes the sum of R0 and R1 and multiplies it by itself R0 times (i.e. raises R0+R1 to the power of R0)
;Assume R0 is greater than 0
;Should return the result in R0
;Inputs: R0 and R1
;Outputs: R0
exp
	
	; Your code here
	ADD R2, R0, R1	;R2 is A+B
	
	MOV R3, R0		;R3 is number of times to loop
	
	MOV R0, R2		;R0 is used for answer

	SUBS R3, R3, #1	;Looping times is exponent - 1
		
	BNE loop		;If A was not one, we enter loop
	
	BX LR
	
loop	
	
	MUL R0, R0, R2	;Multiplying Current Answer * (A+B) 
	
	SUBS R3, R3, #1
	
	BNE loop
	
	BX LR



;Should perform the operation (A+B+C)*(B+C+D)*2	
;A, B, C, and D are passed in order in R0-R3
;Should return the result in R0
;Inputs: R0, R1, R2, and R3
;Outputs: R0
mulsum4

	; Your code here
	; Should make calls to both sum3 and mul3
	
	PUSH{LR}
	
	PUSH{R1-R3} ;Storing B, C, D
		
	BL sum3		 ;R0=A+B+C
	
	MOV R12, R0  ;R12=A+B+C
	
	POP{R0-R2} ; Retrieving R0=B   R1=C    R2=D
	
	BL sum3		;R0=B+C+D
	
	MOV R1, R12	;R1=A+B+C
	
	MOV R2, #2	;R2=2

	BL mul3		;R0 = (B+C+D)*(A+B+C)*2x
	
	POP{LR}
	
	BX LR
	
	
	
	
;Performs the operation R0+R1+R2
;Returns the sum in R0
;Inputs: R0, R1, and R2
;Outputs: R0
sum3
	ADD R3, R0, R1
	ADD R0, R2, R3
	BX LR

;Should perform the operation R0*R1*R2
;Should return the product in R0
;Inputs: R0, R1, and R2
;Outputs: R0
mul3
	
	;Your code here
	
	MUL R3, R0, R1
	MUL R0, R3, R2
	BX LR


	ALIGN
	END