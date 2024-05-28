;
; Task_1.asm
;
; Created: 3/28/2023 12:30:52 PM
; Author : fahim
;
; Replace with your application code
start:
   LDI R16 , $11
   STS $101, R16
   LDI R17 , $12
   STS $102, R17
   LDI R18 , $13
   STS $103, R17
   LDI R19 , $14
   STS $104, R19
   LDI R20 , $15
   STS $105, R20

   ADD R20 , R16
   ADD R20 , R17
   ADD R20 , R18
   ADD R20 , R19
   STS $106, R20 
   HERE: JMP HERE
