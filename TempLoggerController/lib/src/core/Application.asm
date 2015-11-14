
_Application_initialize:

;Application.c,19 :: 		void Application_initialize() {
;Application.c,22 :: 		TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
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
;Application.c,23 :: 		ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
	CLRF        ANSELE+0 
	MOVF        ANSELE+0, 0 
	MOVWF       ANSELD+0 
	MOVF        ANSELD+0, 0 
	MOVWF       ANSELC+0 
	MOVF        ANSELC+0, 0 
	MOVWF       ANSELB+0 
	MOVF        ANSELB+0, 0 
	MOVWF       ANSELA+0 
;Application.c,24 :: 		SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
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
;Application.c,27 :: 		ADCON0 = ADCON1 = ADCON2 = 0x00;
	CLRF        ADCON2+0 
	MOVF        ADCON2+0, 0 
	MOVWF       ADCON1+0 
	MOVF        ADCON1+0, 0 
	MOVWF       ADCON0+0 
;Application.c,28 :: 		C1ON_bit = C2ON_bit = false;
	BCF         C2ON_bit+0, BitPos(C2ON_bit+0) 
	BTFSC       C2ON_bit+0, BitPos(C2ON_bit+0) 
	GOTO        L__Application_initialize6
	BCF         C1ON_bit+0, BitPos(C1ON_bit+0) 
	GOTO        L__Application_initialize7
L__Application_initialize6:
	BSF         C1ON_bit+0, BitPos(C1ON_bit+0) 
L__Application_initialize7:
;Application.c,31 :: 		Timer_initialize();
	CALL        _Timer_initialize+0, 0
;Application.c,32 :: 		Display_initialize();
	CALL        _Display_initialize+0, 0
;Application.c,33 :: 		Sensor_initialize(3.3f);
	MOVLW       51
	MOVWF       FARG_Sensor_initialize__vref+0 
	MOVLW       51
	MOVWF       FARG_Sensor_initialize__vref+1 
	MOVLW       83
	MOVWF       FARG_Sensor_initialize__vref+2 
	MOVLW       128
	MOVWF       FARG_Sensor_initialize__vref+3 
	CALL        _Sensor_initialize+0, 0
;Application.c,34 :: 		}
L_end_Application_initialize:
	RETURN      0
; end of _Application_initialize

_Application_dispatchEvent:

;Application.c,40 :: 		void Application_dispatchEvent(EventHandler handler) {
;Application.c,43 :: 		eventQueue.eventHandlers[eventQueue.end] = handler;
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
;Application.c,44 :: 		eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,49 :: 		if(eventQueue.end == eventQueue.next)
	MOVF        R0, 0 
	XORWF       _eventQueue+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_dispatchEvent0
;Application.c,50 :: 		eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,51 :: 		}
L_end_Application_dispatchEvent:
	RETURN      0
; end of _Application_dispatchEvent

_Application_handleEvents:

;Application.c,57 :: 		void Application_handleEvents() {
;Application.c,59 :: 		if(eventQueue.next == eventQueue.end) return;
	MOVF        _eventQueue+1, 0 
	XORWF       _eventQueue+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_handleEvents1
	GOTO        L_end_Application_handleEvents
L_Application_handleEvents1:
;Application.c,64 :: 		if(eventQueue.eventHandlers[eventQueue.next]) {
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
;Application.c,65 :: 		eventQueue.eventHandlers[eventQueue.next]();
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
;Application.c,66 :: 		eventQueue.eventHandlers[eventQueue.next] = 0;
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
;Application.c,67 :: 		}
L_Application_handleEvents2:
;Application.c,70 :: 		eventQueue.next = (eventQueue.next + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,71 :: 		}
L_end_Application_handleEvents:
	RETURN      0
; end of _Application_handleEvents

_Application_run:

;Application.c,77 :: 		void Application_run() {
;Application.c,80 :: 		IPEN_bit = false;
	BCF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;Application.c,81 :: 		PEIE_bit = GIE_bit = true;
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
	BTFSC       GIE_bit+0, BitPos(GIE_bit+0) 
	GOTO        L__Application_run11
	BCF         PEIE_bit+0, BitPos(PEIE_bit+0) 
	GOTO        L__Application_run12
L__Application_run11:
	BSF         PEIE_bit+0, BitPos(PEIE_bit+0) 
L__Application_run12:
;Application.c,84 :: 		while(true) Application_handleEvents();
L_Application_run3:
	CALL        _Application_handleEvents+0, 0
	GOTO        L_Application_run3
;Application.c,85 :: 		}
L_end_Application_run:
	RETURN      0
; end of _Application_run

_Timer_elapsedSecondEvent:

;Application.c,90 :: 		void Timer_elapsedSecondEvent() {
;Application.c,94 :: 		char* date_str = Timer_timeToString(Timer_getSystemTime());
	CALL        _Timer_getSystemTime+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Timer_timeToString_time_ptr+0 
	MOVF        R1, 0 
	MOVWF       FARG_Timer_timeToString_time_ptr+1 
	CALL        _Timer_timeToString+0, 0
	MOVF        R0, 0 
	MOVWF       Timer_elapsedSecondEvent_date_str_L0+0 
	MOVF        R1, 0 
	MOVWF       Timer_elapsedSecondEvent_date_str_L0+1 
;Application.c,95 :: 		char* time_str = strstr(date_str, " ");
	MOVF        R0, 0 
	MOVWF       FARG_strstr_s1+0 
	MOVF        R1, 0 
	MOVWF       FARG_strstr_s1+1 
	MOVLW       ?lstr1_Application+0
	MOVWF       FARG_strstr_s2+0 
	MOVLW       hi_addr(?lstr1_Application+0)
	MOVWF       FARG_strstr_s2+1 
	CALL        _strstr+0, 0
	MOVF        R0, 0 
	MOVWF       Timer_elapsedSecondEvent_time_str_L0+0 
	MOVF        R1, 0 
	MOVWF       Timer_elapsedSecondEvent_time_str_L0+1 
;Application.c,96 :: 		*time_str++ = '\0';
	MOVFF       R0, FSR1
	MOVFF       R1, FSR1H
	CLRF        POSTINC1+0 
	INFSNZ      Timer_elapsedSecondEvent_time_str_L0+0, 1 
	INCF        Timer_elapsedSecondEvent_time_str_L0+1, 1 
;Application.c,100 :: 		Display_writeLine(1, "%a   [T]", date_str);
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr2_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr2_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	MOVF        Timer_elapsedSecondEvent_date_str_L0+0, 0 
	MOVWF       FARG_Display_writeLine_line+3 
	MOVF        Timer_elapsedSecondEvent_date_str_L0+1, 0 
	MOVWF       FARG_Display_writeLine_line+4 
	CALL        _Display_writeLine+0, 0
;Application.c,101 :: 		Display_writeLine(2, "%a %2f%cC  ", time_str, Sensor_getTemperature(), 223);
	CALL        _Sensor_getTemperature+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Display_writeLine_line+5 
	MOVF        R1, 0 
	MOVWF       FARG_Display_writeLine_line+6 
	MOVF        R2, 0 
	MOVWF       FARG_Display_writeLine_line+7 
	MOVF        R3, 0 
	MOVWF       FARG_Display_writeLine_line+8 
	MOVLW       2
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr3_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr3_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	MOVF        Timer_elapsedSecondEvent_time_str_L0+0, 0 
	MOVWF       FARG_Display_writeLine_line+3 
	MOVF        Timer_elapsedSecondEvent_time_str_L0+1, 0 
	MOVWF       FARG_Display_writeLine_line+4 
	MOVLW       223
	MOVWF       FARG_Display_writeLine_line+9 
	CALL        _Display_writeLine+0, 0
;Application.c,102 :: 		}
L_end_Timer_elapsedSecondEvent:
	RETURN      0
; end of _Timer_elapsedSecondEvent

_Timer_elapsedMinuteEvent:

;Application.c,107 :: 		void Timer_elapsedMinuteEvent() {
;Application.c,109 :: 		}
L_end_Timer_elapsedMinuteEvent:
	RETURN      0
; end of _Timer_elapsedMinuteEvent
