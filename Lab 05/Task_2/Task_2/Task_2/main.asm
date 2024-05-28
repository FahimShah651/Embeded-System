;
; Task_2.asm
;
; Created: 5/16/2023 3:40:53 PM
; Author : fahim
;


; Replace with your application code

.org 0
ldi R20,HIGH(RAMEND)
out SPH,R20
ldi R20,LOW(RAMEND)
out SPL,R20

CBI DDRB,0
CBI DDRB,1
SBI DDRD,0
SBI DDRD,1

START:
  SBIC PINB,0
  RJMP ON
RJMP START

ON:
  SBI PORTD,0
  SBI PORTD,1
  SBIC PINB,1
  RJMP OFF
  RJMP ON

OFF:
  CBI PORTD,0
  CBI PORTD,1
  RJMP START

