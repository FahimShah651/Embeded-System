start :
.include "m328pdef.inc" ; Include ATmega328P definitions
.org 0x00000000
 
.DEF NUM = R21
.DEF DENOMINATOR = R22
.DEF QUOTIENT = R23



; Initialize NUM, DENOMINATOR, and QUOTIENT
LDI NUM, 10        ; Load the numerator with 16
LDI DENOMINATOR, 4 ; Load the denominator with 4
CLR QUOTIENT       ; Clear the quotient

;port selection

 out DDRB, R25 ; Set data direction register for Port B for quotient 
 out DDRC, R26 ; Set data direction register for Port C for remainder
; Perform integer division using repeated subtraction
L1:
  INC QUOTIENT     ; Increment the quotient
  SUB NUM, DENOMINATOR ; Subtract the denominator from the numerator
  BRCC L1          ; If the carry flag is clear, branch to L1
  DEC QUOTIENT     ; Decrement the quotient
  ADD NUM, DENOMINATOR ; Add the denominator back to the numerator

  ;
  mov R25, QUOTIENT ; Set Quotient
  out PORTB, R25 ; Write to Port B

  mov R26, NUM ; Set Rmaider
  out PORTC, R26 ; Write to Port c

; Loop forever
HERE: JMP HERE      ; Jump back to HERE indefinitely
