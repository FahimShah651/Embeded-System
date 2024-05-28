.include "m328pdef.inc"  ; Include device specific definitions

; Set up timer 1 for Fast PWM mode with a 20% duty cycle
ldi r16, (1<<WGM10)   ; Set WGM10 bit to 1 for Fast PWM mode with TOP = 0xFF
sts TCCR1A, r16       ; Write TCCR1A register
ldi r16, (1<<WGM12)   ; Set WGM12 bit to 1 for Fast PWM mode with TOP = 0xFF
sts TCCR1B, r16       ; Write TCCR1B register
ldi r16, (1<<CS10)    ; Set CS10 bit to 1 for a prescaler of 1
sts TCCR1B, r16       ; Write TCCR1B register

; Set the output compare value to 51 for a 20% duty cycle
ldi r16, 51           ; Set OCR1A to 51 (20% of 255)
sts OCR1A, r16        ; Write OCR1A register

; Enable output compare match interrupt
ldi r16, (1<<OCIE1A)  ; Set OCIE1A bit to 1
sts TIMSK1, r16       ; Write TIMSK1 register

sei                   ; Enable global interrupts

; Main loop
main:
  rjmp main           ; Loop forever

; Interrupt service routine for output compare match A
ISR(TIMER1_COMPA_vect)
  ; Toggle the output on PB1
  lds r16, PORTB
  eor r16, (1<<PB1)
  sts PORTB, r16
