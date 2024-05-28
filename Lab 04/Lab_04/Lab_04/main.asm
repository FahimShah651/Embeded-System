;
; Lab_04.asm
;
; Created: 5/2/2023 1:23:24 PM
; Author : fahim
;


; Replace with your application code
start:
    .include "m328Pdef.inc"

	;sbi DDRD,0b00000000
	cbi DDRB,0
	ldi r16,0b00000001    ; constant3
	out DDRD,r16
	 
	

here: in R21,PINB
      
	  

	  ldi r17,0    ;input
	  ldi r18,0    ;constant
	  mov r17,R21    
	  mov r18,r16

	  and r17,R18
      out PORTD,r17
	  
	 ; clr r17
	  ldi r19,2
	  mov r17,R21
	  add r17,r19
	  and R18,r17
	  out PORTD,r18
	 

	  rjmp here
