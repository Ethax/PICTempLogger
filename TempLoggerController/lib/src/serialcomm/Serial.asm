
_Serial_initialize:

;Serial.c,3 :: 		void Serial_initialize() {
;Serial.c,5 :: 		}
L_end_Serial_initialize:
	RETURN      0
; end of _Serial_initialize

_Serial_handleInterrupt:

;Serial.c,7 :: 		void Serial_handleInterrupt() {
;Serial.c,9 :: 		RC1IF_bit = false;
	BCF         RC1IF_bit+0, BitPos(RC1IF_bit+0) 
;Serial.c,10 :: 		}
L_end_Serial_handleInterrupt:
	RETURN      0
; end of _Serial_handleInterrupt
