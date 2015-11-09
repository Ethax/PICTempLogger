
_Application_initialize:

;Application.c,13 :: 		void Application_initialize() {
;Application.c,16 :: 		TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
	MOVLW       255
	MOVWF       TRISE+0 
	MOVF        TRISE+0, 0 
	MOVWF       TRISD+0 
	MOVF        TRISD+0, 0 
	MOVWF       TRISC+0 
	MOVF        TRISC+0, 0 
	MOVWF       TRISB+0 
	MOVF        TRISB+0, 0 
	MOVWF       TRISA+0 
;Application.c,17 :: 		LATA = LATB = LATC = LATD = LATE = 0x00;
	CLRF        LATE+0 
	MOVF        LATE+0, 0 
	MOVWF       LATD+0 
	MOVF        LATD+0, 0 
	MOVWF       LATC+0 
	MOVF        LATC+0, 0 
	MOVWF       LATB+0 
	MOVF        LATB+0, 0 
	MOVWF       LATA+0 
;Application.c,20 :: 		ADCON0 = ADCON1 = ADCON2 = 0x00;
	CLRF        ADCON2+0 
	MOVF        ADCON2+0, 0 
	MOVWF       ADCON1+0 
	MOVF        ADCON1+0, 0 
	MOVWF       ADCON0+0 
;Application.c,21 :: 		C1ON_bit = C2ON_bit = false;
	BCF         C2ON_bit+0, BitPos(C2ON_bit+0) 
	BTFSC       C2ON_bit+0, BitPos(C2ON_bit+0) 
	GOTO        L__Application_initialize5
	BCF         C1ON_bit+0, BitPos(C1ON_bit+0) 
	GOTO        L__Application_initialize6
L__Application_initialize5:
	BSF         C1ON_bit+0, BitPos(C1ON_bit+0) 
L__Application_initialize6:
;Application.c,24 :: 		}
L_end_Application_initialize:
	RETURN      0
; end of _Application_initialize

_Application_dispatchEvent:

;Application.c,30 :: 		void Application_dispatchEvent(EventHandler handler) {
;Application.c,31 :: 		eventQueue.eventHandlers[eventQueue.end] = handler;
	MOVF        _eventQueue+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       _eventQueue+2
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(_eventQueue+2)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	MOVF        FARG_Application_dispatchEvent_handler+0, 0 
	MOVWF       POSTINC1+0 
	MOVF        FARG_Application_dispatchEvent_handler+1, 0 
	MOVWF       POSTINC1+0 
	MOVF        FARG_Application_dispatchEvent_handler+2, 0 
	MOVWF       POSTINC1+0 
	MOVF        FARG_Application_dispatchEvent_handler+3, 0 
	MOVWF       POSTINC1+0 
;Application.c,32 :: 		eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
	MOVF        _eventQueue+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       _eventQueue+0 
;Application.c,33 :: 		}
L_end_Application_dispatchEvent:
	RETURN      0
; end of _Application_dispatchEvent

_Application_handleEvents:

;Application.c,39 :: 		void Application_handleEvents() {
;Application.c,41 :: 		if(eventQueue.next == eventQueue.end) return;
	MOVF        _eventQueue+1, 0 
	XORWF       _eventQueue+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_handleEvents0
	GOTO        L_end_Application_handleEvents
L_Application_handleEvents0:
;Application.c,46 :: 		if(eventQueue.eventHandlers[eventQueue.next]) {
	MOVF        _eventQueue+1, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       _eventQueue+2
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_eventQueue+2)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	IORWF       POSTINC0+0, 0 
	IORWF       POSTINC0+0, 0 
	IORWF       POSTINC0+0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_Application_handleEvents1
;Application.c,47 :: 		eventQueue.eventHandlers[eventQueue.next]();
	MOVF        _eventQueue+1, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       _eventQueue+2
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_eventQueue+2)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVF        POSTINC0+0, 0 
	MOVWF       R1 
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        POSTINC0+0, 0 
	MOVWF       R3 
	CALL        _____DoIFC+0, 0
;Application.c,48 :: 		eventQueue.eventHandlers[eventQueue.next] = 0;
	MOVF        _eventQueue+1, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       _eventQueue+2
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(_eventQueue+2)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	CLRF        POSTINC1+0 
	CLRF        POSTINC1+0 
	CLRF        POSTINC1+0 
	CLRF        POSTINC1+0 
;Application.c,49 :: 		}
L_Application_handleEvents1:
;Application.c,52 :: 		eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
	MOVF        _eventQueue+1, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       _eventQueue+1 
;Application.c,53 :: 		}
L_end_Application_handleEvents:
	RETURN      0
; end of _Application_handleEvents

_Application_run:

;Application.c,59 :: 		void Application_run() {
;Application.c,62 :: 		IPEN_bit = false;
	BCF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;Application.c,63 :: 		PEIE_bit = GIE_bit = true;
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
	BTFSC       GIE_bit+0, BitPos(GIE_bit+0) 
	GOTO        L__Application_run10
	BCF         PEIE_bit+0, BitPos(PEIE_bit+0) 
	GOTO        L__Application_run11
L__Application_run10:
	BSF         PEIE_bit+0, BitPos(PEIE_bit+0) 
L__Application_run11:
;Application.c,66 :: 		while(true) Application_handleEvents();
L_Application_run2:
	CALL        _Application_handleEvents+0, 0
	GOTO        L_Application_run2
;Application.c,67 :: 		}
L_end_Application_run:
	RETURN      0
; end of _Application_run

_Timer_elapsedSecondEvent:

;Application.c,69 :: 		void Timer_elapsedSecondEvent() {
;Application.c,71 :: 		}
L_end_Timer_elapsedSecondEvent:
	RETURN      0
; end of _Timer_elapsedSecondEvent

_Timer_elapsedMinuteEvent:

;Application.c,73 :: 		void Timer_elapsedMinuteEvent() {
;Application.c,75 :: 		}
L_end_Timer_elapsedMinuteEvent:
	RETURN      0
; end of _Timer_elapsedMinuteEvent
