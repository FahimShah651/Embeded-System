;
; Task_03.asm
;
; Created: 3/28/2023 9:55:41 PM
; Author : Fahim Ur Rehman Shah
;


; Replace with your application code
start:
;TAKING TWO NUMBERS
   .EQU NUM1 = 2
   .EQU NUM2 = 4
;LOADING VALUES TO THE REGISTERS
   LDI R16 , NUM1
   LDI R17 , NUM2
;LEFT SHIFT THE REGISTER
   LSL R17
;STORE REGISTER VALUE TO THE MEMORY
   STS $101 , R17
   HERE: JMP HERE
