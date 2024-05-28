; Lab_06_Task_02.asm
; Created: 5/23/2023 1:54:25 PM
; Author : fahim
; Replace with your application code

SBI DDRD,0    ; Set bit 0 of DDRD to set PORTD pin 0 as an output
SBI DDRD,1    ; Set bit 1 of DDRD to set PORTD pin 1 as an output

START:
   SBI PORTD,0    ; Set bit 0 of PORTD to turn on PORTD pin 0 (output high)
   CBI PORTD,1    ; Clear bit 1 of PORTD to turn off PORTD pin 1 (output low)
   CALL ON        ; Call the ON subroutine
   CBI PORTD,0    ; Clear bit 0 of PORTD to turn off PORTD pin 0 (output low)
   SBI PORTD,1    ; Set bit 1 of PORTD to turn on PORTD pin 1 (output high)
   CALL OFF       ; Call the OFF subroutine
RJMP START        ; Jump back to START label to begin the loop again

; ON subroutine
ON:
   LDI R19,0x64         ; Load immediate value 0x64 (100 in decimal) into register R19
   LOOP1:
      LDI R20,0x64      ; Load immediate value 0x64 (100 in decimal) into register R20
	  LOOP2:
	     LDI R21,0x18   ; Load immediate value 0x18 (24 in decimal) into register R21
		 LOOP3:
		    NOP             ; No operation
			DEC R21         ; Decrement register R21
		    BRNE LOOP3      ; Branch to LOOP3 if R21 is not equal to zero
		 DEC R20            ; Decrement register R20
		 BRNE LOOP2         ; Branch to LOOP2 if R20 is not equal to zero
	   DEC R19              ; Decrement register R19
	   BRNE LOOP1           ; Branch to LOOP1 if R19 is not equal to zero
	RET                     ; Return from the subroutine

; OFF subroutine
OFF:
   LDI R22,0xC8         ; Load immediate value 0xC8 (200 in decimal) into register R22
   LOO1:
      LDI R23,0x64      ; Load immediate value 0x64 (100 in decimal) into register R23
	  LOO2:
	     LDI R24,0x4    ; Load immediate value 0x4 (4 in decimal) into register R24
		 LOO3:
		    NOP              ; No operation
			DEC R24          ; Decrement register R24
		    BRNE LOO3        ; Branch to LOO3 if R24 is not equal to zero
		 DEC R23             ; Decrement register R23
		 BRNE LOO2           ; Branch to LOO2 if R23 is not equal to zero
	   DEC R22               ; Decrement register R22
	   BRNE LOO1             ; Branch to LOO1 if R22 is not equal to zero
	RET                      ; Return from the subroutine
