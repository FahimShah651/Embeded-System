;
; Practice_Task.asm
;
; Created: 4/4/2023 12:02:02 PM
; Author : fahim
;


; Replace with your application code
start:
.include "m328pdef.inc"
	.org 0x00
	ldi R16,0b00000001
	out DDRB,R16
	out PORTB,R16

    loop : rjmp loop

