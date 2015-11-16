
_interrupt:

;Main.c,22 :: 		void interrupt() {
;Main.c,24 :: 		if(TMR0IF_bit && TMR0IE_bit)
	BTFSS       TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
	GOTO        L_interrupt2
	BTFSS       TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
	GOTO        L_interrupt2
L__interrupt8:
;Main.c,25 :: 		Timer_handleInterrupt();
	CALL        _Timer_handleInterrupt+0, 0
	GOTO        L_interrupt3
L_interrupt2:
;Main.c,28 :: 		else if(RC1IF_bit && RC1IE_bit)
	BTFSS       RC1IF_bit+0, BitPos(RC1IF_bit+0) 
	GOTO        L_interrupt6
	BTFSS       RC1IE_bit+0, BitPos(RC1IE_bit+0) 
	GOTO        L_interrupt6
L__interrupt7:
;Main.c,29 :: 		Serial_handleInterrupt();
	CALL        _Serial_handleInterrupt+0, 0
L_interrupt6:
L_interrupt3:
;Main.c,30 :: 		}
L_end_interrupt:
L__interrupt10:
	RETFIE      1
; end of _interrupt

_main:

;Main.c,35 :: 		void main() {
;Main.c,37 :: 		Application_initialize();
	CALL        _Application_initialize+0, 0
;Main.c,38 :: 		Application_run();
	CALL        _Application_run+0, 0
;Main.c,39 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
