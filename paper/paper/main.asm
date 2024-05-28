.INCLUDE "m328pdef.inc"

.org 0x00

start :
   ldi R16,0xFF
   out DDRB,R16

   ldi R16,0x00
   out DDRD,R16

   loop:
     in R17,PIND
	 LDI R19,0b11111111
	 out PORTD,R19
	
	 rjmp loop
     
