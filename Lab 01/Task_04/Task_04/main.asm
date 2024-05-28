;
; Task_04.asm
;
; Created: 3/28/2023 11:29:26 PM
; Author : fahim
;


; Replace with your application code
start:
    LDI R16, 0x44            ; Loading register with value
	STS 0x212, R16           ; Storing the register in the given adress 
    LDI R16, 0x95            ; here was the register error because load register are from 16 to 31
    STS 0x213, R15           ; Storing the register in the given adress 
    LDI R17, 0x54            ; Loading register with value
	.EQU temp = 0X323        ; I ctreated the temp memmory 
    STS temp, R17            ; Storing the register in the temp 
    LDI R20, 0x26            ; Loading register with value
    STS 0x215, R20           ; Storing the register in the given adress 
    Add R20, R18             ; Adding the registers and storing the values in the R20 register
    SUBI R17, 0x10           ; Subtracting the register from the value 
		Here: JMP Here
