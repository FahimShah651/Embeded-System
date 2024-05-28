.include "m328pdef.inc" ; Include ATmega328P definitions
.org 0x00000000        ; Set the program counter to start at 0

; Define some registers for our variables
.DEF NUM = R21
.DEF DENOMINATOR = R22
.DEF QUOTIENT = R23

; Initialize NUM, DENOMINATOR, and QUOTIENT
LDI NUM, 10        ; Load the numerator with 10
LDI DENOMINATOR, 4 ; Load the denominator with 4
CLR QUOTIENT       ; Clear the quotient

; Set the data direction registers for Port B and C
; Port B will be used to output the quotient, Port C for remainder
out DDRB, R25 ; Set data direction register for Port B for quotient 
out DDRC, R26 ; Set data direction register for Port C for remainder

; Perform integer division using repeated subtraction
L1:
  INC QUOTIENT          ; Increment the quotient
  SUB NUM, DENOMINATOR  ; Subtract the denominator from the numerator
  BRCC L1               ; If the carry flag is clear, branch to L1
  DEC QUOTIENT          ; Decrement the quotient
  ADD NUM, DENOMINATOR  ; Add the denominator back to the numerator

; Output the quotient to Port B and the remainder to Port C
mov R25, QUOTIENT ; Move the value of the quotient to R25
out PORTB, R25    ; Output the quotient to Port B
mov R26, NUM      ; Move the value of the remainder to R26
out PORTC, R26    ; Output the remainder to Port C

; Loop forever
HERE: JMP HERE      ; Jump back to HERE indefinitely
