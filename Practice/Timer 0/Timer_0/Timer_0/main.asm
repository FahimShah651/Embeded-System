;
; DelayUsingTimerv2.asm
;
; Created: 29/10/2022 7:42:02 AM
; Author : vooiy
;
		.include "M328Pdef.inc"
		.Equ Value = E27B ;Timing value to give 1 sec delay

Main:	Ldi R17,0xFF		;Data for output mode
		Out DDRB, R17		;Set DDRB to output mode

Again:	Sbi PORTB,0			;LSB LED on
		Call Delay			;Delay
		Cbi PORTB,0			;LSB LED off
		Call Delay			;Delay
		Rjmp Again			;Repeat
;===============================================================
Delay:						;1 sec delay using Timer1
		Ldi R30, High(Value)
		Sts TCNT1H, R30
		Ldi R30, Low(Value)
		Sts TCNT1L, R30		;Setup Timer Counter TCNT1 = Value
;---------------------------------------------------------------
		Ldi R31, 0x00		;0b00000000 - normal mode
		Sts TCCR1A, R31
		Ldi R31, 0x05		;0b00000101, prescaler = 1024 
		Sts TCCR1B, R31		;Timer will start counting after this 
							;instruction is executed.
;---------------------------------------------------------------
Loop: 	Sbis TIFR1, TOV1	;If TOV1=1, skip next instruction
		Rjmp Loop			;else, loop back and check TOV1 flag
;---------------------------------------------------------------
		sbi TIFR1, TOV1		;Clear TOV1 bit by writing a 1 to it
;---------------------------------------------------------------
		Ldi R30, 0xFF		;0b11111111
		Sts TCCR1B, R30		;Stop timer1
		Ret