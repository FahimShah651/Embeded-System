start:
    .include "m328pdef.inc"
	.org 0x00

	ldi r16,0b00000111
	out DDRB,r16
	out DDRC,r16
	out DDRD,r16

	out PORTB,r16
	call delay
	out PORTC,r16
	call delay
	out PORTD,r16
	call delay

	loop : rjmp loop

	delay:
    ldi r17,8        ; Set loop counter to 3
outer:
    ldi r18,100      ; Set inner loop counter 1 to 100
inner1:
    ldi r19,100      ; Set inner loop counter 2 to 100
inner2:
    ldi r20,100      ; Set inner loop counter 3 to 100
inner3:
    dec r20          ; Decrement inner loop counter 3
    brne inner3      ; Loop until it becomes zero
    dec r19          ; Decrement inner loop counter 2
    brne inner2      ; Loop until it becomes zero
    dec r18          ; Decrement inner loop counter 1
    brne inner1      ; Loop until it becomes zero
    dec r17          ; Decrement outer loop counter
    brne outer       ; Loop until it becomes zero
    ret              ; Return from delay function