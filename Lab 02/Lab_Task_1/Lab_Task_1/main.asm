;
; Lab_Task_1.asm
;
; Created: 4/4/2023 12:59:00 PM
; Author : fahim
;
; Replace with your application code
start:
    .include "m328pdef.inc"
	.org 0x00
	;ldi r16,0b00000111
	;out DDRB,r16
	;out PORTB,r16

	;out DDRC,r16
	;out PORTC,r16

	;out DDRD,r16
	;out PORTD,r16

	sbi DDRD,1
    loop :
	 SBI PORTD ,1
	 SBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	 CBI PORTD ,1
	
	 rjmp loop

