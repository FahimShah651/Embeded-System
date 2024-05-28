;
; Lab_06_Task_01.asm
;
; Created: 5/23/2023 1:22:39 PM
; Author : fahim
;


; Replace with your application code

CBI DDRB,0 ; set PORTB pin 0 as an input
CBI DDRB,1 ; set PORTB pin 1 as an input
SBI DDRD,0 ; set PORTD pin 0 as an output
SBI DDRD,1 ; set PORTD pin 1 as an output

START:
SBIC PINB,0 ; Skip next instruction if PORTB pin 0 is clear (low)
RJMP ON ; Jump to ON label if PORTB pin 0 is high
RJMP START ; Jump back to START label if PORTB pin 0 is low

ON:
SBI PORTD,0 ; Set bit 0 of PORTD to turn on PORTD pin 0 (output high)
SBI PORTD,1 ; Set bit 1 of PORTD to turn on PORTD pin 1 (output high)
SBIS PINB,1 ; Skip next instruction if PORTB pin 1 is set (high)
RJMP OFF ; Jump to OFF label if PORTB pin 1 is set low
RJMP ON ; Jump back to ON label if PORTB pin 1 is high

OFF:
CBI PORTD,0 ; Clear bit 0 of PORTD to turn off PORTD pin 0 (output low)
CBI PORTD,1 ; Clear bit 1 of PORTD to turn off PORTD pin 1 (output low)
RJMP START ; Jump back to START label to begin the loop again
