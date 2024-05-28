;
; Ahtesham.asm
;
; Created: 3/29/2023 8:02:36 AM
; Author : fahim
;


; Replace with your application code
start:
    ?
LDI R16, 0x44 STS 0x212, R16
LDI R15, 0x95
STS 0x213, R15
LDI R17, 0x54
STS temp, R17
LDI R20, 0x26
STS 0x215, R20
Add R20, R18
SUBI R17, 0x10
Here: JMP Here
