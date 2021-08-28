

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT Start
	IMPORT PortF_Init
	IMPORT LEDs_on
	IMPORT red_on
	IMPORT blue_on
	IMPORT red_toggle
	IMPORT blue_toggle
	IMPORT green_toggle
	IMPORT all_off
	IMPORT buttons
	IMPORT delay
	
	
	;Be sure to import your created I/O functions


		
Start
	BL PortF_Init
loop
	;Used by Part 1 to prove PortF_Init is correct
	;BL LEDs_on ;Comment out for later parts
	
		
	; Part 3
	; Call delay
	; Read the state of the buttons
	; None -> Call toggle
	; SW1 -> Call blue_on
	; SW2 -> Call red_on
	; Both -> Call toggle, blue_on, red_on
		
	BL delay
	BL buttons
	
	CMP R0, #0x11
	BEQ noButtons
	
	CMP R0, #0x01
	BEQ onlyOne
	
	CMP R0, #0x10
	BEQ onlyTwo
	
	CMP R0, #0x00
	BEQ bothButtons
	
	B done
	
noButtons
	BL all_off
	BL delay
	BL green_toggle

	B done

onlyOne
	BL all_off
	BL blue_on
	B done
	
onlyTwo
	BL all_off
	BL red_on
	B done

bothButtons
;PROC {}
	BL all_off
	
	BL buttons
	CMP R0, #0x00
	BNE done
	BL delay
	
	BL red_on
	BL blue_on
	BL green_toggle
	
	BL buttons
	CMP R0, #0x00
	BNE done
	BL delay
	
	BL green_toggle
	
	BL buttons
	CMP R0, #0x00
	BNE done
	BL delay
	
	BL green_toggle
	BL red_toggle
	BL blue_toggle
		
	B done


done
	B loop

	ALIGN
	END