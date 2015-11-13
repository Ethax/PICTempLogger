
_Application_initialize:

;Application.c,14 :: 		void Application_initialize() {
;Application.c,17 :: 		TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
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
;Application.c,18 :: 		ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
	CLRF        ANSELE+0 
	MOVF        ANSELE+0, 0 
	MOVWF       ANSELD+0 
	MOVF        ANSELD+0, 0 
	MOVWF       ANSELC+0 
	MOVF        ANSELC+0, 0 
	MOVWF       ANSELB+0 
	MOVF        ANSELB+0, 0 
	MOVWF       ANSELA+0 
;Application.c,19 :: 		SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
	CLRF        LATE+0 
	MOVF        LATE+0, 0 
	MOVWF       LATD+0 
	MOVF        LATD+0, 0 
	MOVWF       LATC+0 
	MOVF        LATC+0, 0 
	MOVWF       LATB+0 
	MOVF        LATB+0, 0 
	MOVWF       LATA+0 
	MOVF        LATA+0, 0 
	MOVWF       SLRCON+0 
;Application.c,22 :: 		ADCON0 = ADCON1 = ADCON2 = 0x00;
	CLRF        ADCON2+0 
	MOVF        ADCON2+0, 0 
	MOVWF       ADCON1+0 
	MOVF        ADCON1+0, 0 
	MOVWF       ADCON0+0 
;Application.c,23 :: 		C1ON_bit = C2ON_bit = false;
	BCF         C2ON_bit+0, BitPos(C2ON_bit+0) 
	BTFSC       C2ON_bit+0, BitPos(C2ON_bit+0) 
	GOTO        L__Application_initialize6
	BCF         C1ON_bit+0, BitPos(C1ON_bit+0) 
	GOTO        L__Application_initialize7
L__Application_initialize6:
	BSF         C1ON_bit+0, BitPos(C1ON_bit+0) 
L__Application_initialize7:
;Application.c,26 :: 		Timer_initialize();
	CALL        _Timer_initialize+0, 0
;Application.c,27 :: 		Display_initialize();
	CALL        _Display_initialize+0, 0
;Application.c,28 :: 		}
L_end_Application_initialize:
	RETURN      0
; end of _Application_initialize

_Application_dispatchEvent:

;Application.c,34 :: 		void Application_dispatchEvent(EventHandler handler) {
;Application.c,37 :: 		eventQueue.eventHandlers[eventQueue.end] = handler;
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
;Application.c,38 :: 		eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
	MOVF        _eventQueue+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       20
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
;Application.c,43 :: 		if(eventQueue.end == eventQueue.next)
	MOVF        R0, 0 
	XORWF       _eventQueue+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_dispatchEvent0
;Application.c,44 :: 		eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
	MOVF        _eventQueue+1, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       20
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
L_Application_dispatchEvent0:
;Application.c,45 :: 		}
L_end_Application_dispatchEvent:
	RETURN      0
; end of _Application_dispatchEvent

_Application_handleEvents:

;Application.c,51 :: 		void Application_handleEvents() {
;Application.c,53 :: 		if(eventQueue.next == eventQueue.end) return;
	MOVF        _eventQueue+1, 0 
	XORWF       _eventQueue+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_handleEvents1
	GOTO        L_end_Application_handleEvents
L_Application_handleEvents1:
;Application.c,58 :: 		if(eventQueue.eventHandlers[eventQueue.next]) {
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
	GOTO        L_Application_handleEvents2
;Application.c,59 :: 		eventQueue.eventHandlers[eventQueue.next]();
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
;Application.c,60 :: 		eventQueue.eventHandlers[eventQueue.next] = 0;
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
;Application.c,61 :: 		}
L_Application_handleEvents2:
;Application.c,64 :: 		eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
	MOVF        _eventQueue+1, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       20
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
;Application.c,65 :: 		}
L_end_Application_handleEvents:
	RETURN      0
; end of _Application_handleEvents

_Application_run:

;Application.c,71 :: 		void Application_run() {
;Application.c,74 :: 		IPEN_bit = false;
	BCF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;Application.c,75 :: 		PEIE_bit = GIE_bit = true;
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
	BTFSC       GIE_bit+0, BitPos(GIE_bit+0) 
	GOTO        L__Application_run11
	BCF         PEIE_bit+0, BitPos(PEIE_bit+0) 
	GOTO        L__Application_run12
L__Application_run11:
	BSF         PEIE_bit+0, BitPos(PEIE_bit+0) 
L__Application_run12:
;Application.c,78 :: 		while(true) Application_handleEvents();
L_Application_run3:
	CALL        _Application_handleEvents+0, 0
	GOTO        L_Application_run3
;Application.c,79 :: 		}
L_end_Application_run:
	RETURN      0
; end of _Application_run

_Timer_elapsedSecondEvent:

;Application.c,84 :: 		void Timer_elapsedSecondEvent() {
;Application.c,87 :: 		sprinti(output, "Second event: %d", event_num);
	MOVLW       Timer_elapsedSecondEvent_output_L0+0
	MOVWF       FARG_sprinti_wh+0 
	MOVLW       hi_addr(Timer_elapsedSecondEvent_output_L0+0)
	MOVWF       FARG_sprinti_wh+1 
	MOVLW       ?lstr_1_Application+0
	MOVWF       FARG_sprinti_f+0 
	MOVLW       hi_addr(?lstr_1_Application+0)
	MOVWF       FARG_sprinti_f+1 
	MOVLW       higher_addr(?lstr_1_Application+0)
	MOVWF       FARG_sprinti_f+2 
	MOVF        Timer_elapsedSecondEvent_event_num_L0+0, 0 
	MOVWF       FARG_sprinti_wh+5 
	MOVF        Timer_elapsedSecondEvent_event_num_L0+1, 0 
	MOVWF       FARG_sprinti_wh+6 
	CALL        _sprinti+0, 0
;Application.c,88 :: 		Display_writeLine(1, output);
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       Timer_elapsedSecondEvent_output_L0+0
	MOVWF       FARG_Display_writeLine_text+0 
	MOVLW       hi_addr(Timer_elapsedSecondEvent_output_L0+0)
	MOVWF       FARG_Display_writeLine_text+1 
	CALL        _Display_writeLine+0, 0
;Application.c,89 :: 		}
L_end_Timer_elapsedSecondEvent:
	RETURN      0
; end of _Timer_elapsedSecondEvent

_Timer_elapsedMinuteEvent:

;Application.c,94 :: 		void Timer_elapsedMinuteEvent() {
;Application.c,97 :: 		sprinti(output, "Minute event: %d", event_num);
	MOVLW       Timer_elapsedMinuteEvent_output_L0+0
	MOVWF       FARG_sprinti_wh+0 
	MOVLW       hi_addr(Timer_elapsedMinuteEvent_output_L0+0)
	MOVWF       FARG_sprinti_wh+1 
	MOVLW       ?lstr_2_Application+0
	MOVWF       FARG_sprinti_f+0 
	MOVLW       hi_addr(?lstr_2_Application+0)
	MOVWF       FARG_sprinti_f+1 
	MOVLW       higher_addr(?lstr_2_Application+0)
	MOVWF       FARG_sprinti_f+2 
	MOVF        Timer_elapsedMinuteEvent_event_num_L0+0, 0 
	MOVWF       FARG_sprinti_wh+5 
	MOVF        Timer_elapsedMinuteEvent_event_num_L0+1, 0 
	MOVWF       FARG_sprinti_wh+6 
	CALL        _sprinti+0, 0
;Application.c,98 :: 		Display_writeLine(2, output);
	MOVLW       2
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       Timer_elapsedMinuteEvent_output_L0+0
	MOVWF       FARG_Display_writeLine_text+0 
	MOVLW       hi_addr(Timer_elapsedMinuteEvent_output_L0+0)
	MOVWF       FARG_Display_writeLine_text+1 
	CALL        _Display_writeLine+0, 0
;Application.c,99 :: 		}
L_end_Timer_elapsedMinuteEvent:
	RETURN      0
; end of _Timer_elapsedMinuteEvent
