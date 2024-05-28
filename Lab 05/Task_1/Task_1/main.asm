;
; Task_1.asm
;
; Created: 5/16/2023 1:13:27 PM
; Author : fahim
; Replace with your application code
;.include "m328pdef.inc"
;ldi r16,0x00
;out ddrb,r16
;ldi r16,0xFF
;out ddrd,r16

;start:
  ;ldi r17,0x00
 ; in r17,PINB
 ; and r17,r18
 ; out PORTD,r17

;rjmp start

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

