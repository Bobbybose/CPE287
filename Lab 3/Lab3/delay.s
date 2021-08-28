
	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT	delay
	EXPORT delay_numTimes
		
	;Be sure to export your created functions

DELAYVAL		EQU 133333	;Change to calculated value
numTimes	RN 0

delay_numTimes
	PUSH{LR}
	BL delay
	POP{LR}
	SUBS numTimes, numTimes, #1
	BNE delay_numTimes
	BX LR

delay
	LDR R1, =DELAYVAL
delay_loop
		;Add Part 2 code here
	SUBS R1, R1, #1				; R0 = R0 - 1
	BNE delay_loop		; repeat until R0 == 0
	BX LR

	
	ALIGN
	END