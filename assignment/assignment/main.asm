.include "m328pdef.inc"

.equ F_CPU = 10000000 ; set CPU frequency to 10 MHz

ldi r16, 0b00000001 ; set bit 0 of DDRB to 1 to make Pin 4 output
out DDRB, r16

loop:
    sbis PINC, 3 ; check if Pin 3 of Port C is low
    rjmp loop ; if it's high, continue looping

    sbi PORTB, 4 ; set Pin 4 of Port B to high to turn on buzzer

    ldi r17, 0x7F ; load delay counter
    delay:
        dec r17 ; decrement the delay counter
        brne delay ; continue looping until the counter is zero

    cbi PORTB, 4 ; set Pin 4 of Port B to low to turn off buzzer
    rjmp loop ; repeat loop
