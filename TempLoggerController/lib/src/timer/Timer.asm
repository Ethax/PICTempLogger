
_Timer_initialize:

;Timer.c,7 :: 		void Timer_initialize() {
;Timer.c,10 :: 		T0CON = 0x84;
	MOVLW       132
	MOVWF       T0CON+0 
;Timer.c,11 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;Timer.c,12 :: 		TMR0L = 0xDC;
	MOVLW       220
	MOVWF       TMR0L+0 
;Timer.c,13 :: 		TMR0IE_bit = true;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;Timer.c,14 :: 		}
L_end_Timer_initialize:
	RETURN      0
; end of _Timer_initialize

_Timer_handleInterrupt:

;Timer.c,20 :: 		void Timer_handleInterrupt() {
;Timer.c,22 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;Timer.c,23 :: 		TMR0L = 0xDC;
	MOVLW       220
	MOVWF       TMR0L+0 
;Timer.c,24 :: 		TMR0IF_bit = false;
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;Timer.c,25 :: 		}
L_end_Timer_handleInterrupt:
	RETURN      0
; end of _Timer_handleInterrupt
