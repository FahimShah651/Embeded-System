.include "m328pdef.inc" ; Include ATmega328P definitions

.org 0x0000 ; Reset vector
    ldi r16, 0xFF ; Set all pins as output
    out DDRB, r16 ; Set data direction register for Port B
    out DDRC, r16 ; Set data direction register for Port C
    out DDRD, r16 ; Set data direction register for Port D
    
loop: ; Main loop
    ; Turn on LEDs connected to Port B
    ldi r16, 0b00000111 ; Set pins 0, 1, and 2 of Port B high
    out PORTB, r16 ; Write to Port B
    call delay ; Delay for approximately 1 second
    
    ; Turn on LEDs connected to Port C
    ldi r16, 0b00000111 ; Set pins 0, 1, and 2 of Port C high
    out PORTC, r16 ; Write to Port C
    call delay ; Delay for approximately 1 second
    
    ; Turn on LEDs connected to Port D
    ldi r16, 0b00000111 ; Set pins 0, 1, and 2 of Port D high
    out PORTD, r16 ; Write to Port D
    call delay ; Delay for approximately 1 second
    
    ; Turn off all LEDs
    ldi r16, 0 ; Set all pins low
    out PORTB, r16 ; Write to Port B
    out PORTC, r16 ; Write to Port C
    out PORTD, r16 ; Write to Port D
    call delay ; Delay for approximately 1 second
    
    rjmp loop ; Jump back to the beginning of the loop
    
; Delay subroutine

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