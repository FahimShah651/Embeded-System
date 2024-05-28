;
; Led_Blinking.asm
;
; Created: 4/11/2023 12:31:08 PM
; Author : fahim
;


; Replace with your application code
start:
    .include "m328pdef.inc" ; Include ATmega328P definitions

.org 0x0000 ; Reset vector
    ldi r16, 0xFF ; Set all pins as output
    out DDRB, r16 ; Set data direction register for Port B
    
loop: ; Main loop
    ; Turn on LEDs connected to Port B
    ldi r16, 0b00000100 ; Set pins 0, 1, and 2 of Port B high
    out PORTB, r16 ; Write to Port B
    call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
    
   
    
    ; Turn off all LEDs
    ldi r16, 0 ; Set all pins low
    out PORTB, r16 ; Write to Port B
    call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
	call delay ; Delay for approximately 1 second
    
    rjmp loop ; Jump back to the beginning of the loop
    
; Delay subroutine
delay:
    ldi r16, 0x00 ; Load counter with initial value
delay_loop:
    ldi r18, 0xFF ; Load inner loop counter
inner_loop:
    dec r18 ; Decrement inner loop counter
    brne inner_loop ; Loop until inner loop counter reaches zero
    dec r16 ; Decrement delay counter
    brne delay_loop ; Loop until delay counter reaches zero
    ret ; Return from subroutine

