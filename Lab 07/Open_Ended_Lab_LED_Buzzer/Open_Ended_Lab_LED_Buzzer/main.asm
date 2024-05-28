; Open_Ended_Lab_LED_Buzzer.asm
;
; Created: 5/30/2023 1:13:45 PM
; Author : fahim
;

; Replace with your application code

CBI DDRD,0 ; Set PORTD pin 0 as an INput
CBI DDRD,1 ; Set PORTD pin 1 as an INput
SBI DDRB,0 ; Set PORTB pin 0 as an OUTput
SBI DDRB,1 ; Set PORTB pin 1 as an OUTput
SBI DDRC,0 ; Set PORTC pin 0 as an OUTput

START:
   IN R20,PIND ; Read the value of PIND register into R20
   CPI R20,0b00000010 ; Compare R20 with binary value 00000010
   BREQ CASE_1 ; Branch to CASE_1 if the result of the comparison is equal
   CPI R20,0b00000001 ; Compare R20 with binary value 00000001
   BREQ CASE_2 ; Branch to CASE_2 if the result of the comparison is equal
   CPI R20,0b00000011 ; Compare R20 with binary value 00000011
   BREQ CASE_3 ; Branch to CASE_3 if the result of the comparison is equal
   CPI R20,0b00000000 ; Compare R20 with binary value 00000000
   BREQ CASE_4 ; Branch to CASE_4 if the result of the comparison is equal

   RJMP START ; Unconditional jump back to the START label

CASE_1:
    SBI PORTB,0 ; Set PORTB pin 0 HIGH
	SBI PORTB,1 ; Set PORTB pin 1 HIGH
	CALL DELAY ; Call the DELAY subroutine
	SBI PORTC,0 ; Set PORTC pin 0 HIGH
	RJMP START ; Unconditional jump back to the START label

CASE_2:
    SBI PORTC,0 ; Set PORTC pin 0 HIGH
	CALL DELAY ; Call the DELAY subroutine
	SBI PORTB,0 ; Set PORTB pin 0 HIGH
	SBI PORTB,1 ; Set PORTB pin 1 HIGH
	RJMP START ; Unconditional jump back to the START label

CASE_3:
    SBI PORTB,0 ; Set PORTB pin 0 HIGH
	SBI PORTB,1 ; Set PORTB pin 1 HIGH
	CBI PORTC,0 ; Set PORTC pin 0 LOW
	RJMP START ; Unconditional jump back to the START label

CASE_4:
    SBI PORTC,0 ; Set PORTC pin 0 HIGH
	CBI PORTB,0 ; Set PORTB pin 0 LOW
	CBI PORTB,1 ; Set PORTB pin 1 LOW
	RJMP START ; Unconditional jump back to the START label

DELAY:
   LDI R16,100 ; Load immediate value 100 into R16       
   LOOP1:
      LDI R17,100 ; Load immediate value 100 into R17      
	  LOOP2:
	     LDI R18,50 ; Load immediate value 50 into R18  
		 LOOP3:
		    NOP ; No operation       
			DEC R18 ; Decrement R18        
		    BRNE LOOP3 ; Branch to LOOP3 if R18 is not equal to zero      
		 DEC R17 ; Decrement R17          
		 BRNE LOOP2 ; Branch to LOOP2 if R17 is not equal to zero         
	   DEC R16 ; Decrement R16            
	   BRNE LOOP1 ; Branch to LOOP1 if R16 is not equal to zero          
   RET ; Return from subroutine
