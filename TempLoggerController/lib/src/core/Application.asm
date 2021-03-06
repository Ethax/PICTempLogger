
_Application_initialize:

;Application.c,18 :: 		void Application_initialize() {
;Application.c,21 :: 		TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;
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
;Application.c,22 :: 		ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
	CLRF        ANSELE+0 
	MOVF        ANSELE+0, 0 
	MOVWF       ANSELD+0 
	MOVF        ANSELD+0, 0 
	MOVWF       ANSELC+0 
	MOVF        ANSELC+0, 0 
	MOVWF       ANSELB+0 
	MOVF        ANSELB+0, 0 
	MOVWF       ANSELA+0 
;Application.c,23 :: 		SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
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
;Application.c,26 :: 		ADCON0 = ADCON1 = ADCON2 = 0x00;
	CLRF        ADCON2+0 
	MOVF        ADCON2+0, 0 
	MOVWF       ADCON1+0 
	MOVF        ADCON1+0, 0 
	MOVWF       ADCON0+0 
;Application.c,27 :: 		C1ON_bit = C2ON_bit = false;
	BCF         C2ON_bit+0, BitPos(C2ON_bit+0) 
	BTFSC       C2ON_bit+0, BitPos(C2ON_bit+0) 
	GOTO        L__Application_initialize11
	BCF         C1ON_bit+0, BitPos(C1ON_bit+0) 
	GOTO        L__Application_initialize12
L__Application_initialize11:
	BSF         C1ON_bit+0, BitPos(C1ON_bit+0) 
L__Application_initialize12:
;Application.c,30 :: 		Display_initialize();
	CALL        _Display_initialize+0, 0
;Application.c,31 :: 		Alarm_initialize();
	CALL        _Alarm_initialize+0, 0
;Application.c,32 :: 		Timer_initialize();
	CALL        _Timer_initialize+0, 0
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
;Application.c,34 :: 		Storage_initialize();
	CALL        _Storage_initialize+0, 0
;Application.c,35 :: 		Serial_initialize(BAUD_9600);
	MOVLW       3
	MOVWF       FARG_Serial_initialize_baudrate+0 
	CALL        _Serial_initialize+0, 0
;Application.c,36 :: 		}
L_end_Application_initialize:
	RETURN      0
; end of _Application_initialize

_Application_dispatchEvent:

;Application.c,42 :: 		void Application_dispatchEvent(EventHandler handler) {
;Application.c,45 :: 		eventQueue.eventHandlers[eventQueue.end] = handler;
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
;Application.c,46 :: 		eventQueue.end = (eventQueue.end + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,51 :: 		if(eventQueue.end == eventQueue.begin)
	MOVF        _eventQueue+0, 0 
	XORWF       _eventQueue+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_dispatchEvent0
;Application.c,52 :: 		eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,53 :: 		}
L_end_Application_dispatchEvent:
	RETURN      0
; end of _Application_dispatchEvent

_Application_handleEvents:

;Application.c,59 :: 		void Application_handleEvents() {
;Application.c,61 :: 		if(eventQueue.begin == eventQueue.end) return;
	MOVF        _eventQueue+1, 0 
	XORWF       _eventQueue+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Application_handleEvents1
	GOTO        L_end_Application_handleEvents
L_Application_handleEvents1:
;Application.c,66 :: 		if(eventQueue.eventHandlers[eventQueue.begin]) {
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
;Application.c,67 :: 		eventQueue.eventHandlers[eventQueue.begin]();
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
;Application.c,68 :: 		eventQueue.eventHandlers[eventQueue.begin] = 0;
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
;Application.c,69 :: 		}
L_Application_handleEvents2:
;Application.c,72 :: 		eventQueue.begin = (eventQueue.begin + 1) % EVENT_QUEUE_SIZE;
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
;Application.c,73 :: 		}
L_end_Application_handleEvents:
	RETURN      0
; end of _Application_handleEvents

_Application_run:

;Application.c,79 :: 		void Application_run() {
;Application.c,82 :: 		IPEN_bit = false;
	BCF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;Application.c,83 :: 		PEIE_bit = GIE_bit = true;
	BSF         GIE_bit+0, BitPos(GIE_bit+0) 
	BTFSC       GIE_bit+0, BitPos(GIE_bit+0) 
	GOTO        L__Application_run16
	BCF         PEIE_bit+0, BitPos(PEIE_bit+0) 
	GOTO        L__Application_run17
L__Application_run16:
	BSF         PEIE_bit+0, BitPos(PEIE_bit+0) 
L__Application_run17:
;Application.c,86 :: 		while(true) Application_handleEvents();
L_Application_run3:
	CALL        _Application_handleEvents+0, 0
	GOTO        L_Application_run3
;Application.c,87 :: 		}
L_end_Application_run:
	RETURN      0
; end of _Application_run

_Storage_firstBootEvent:

;Application.c,92 :: 		void Storage_firstBootEvent() {
;Application.c,96 :: 		Display_writeLine(1, "Loading defaults");
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr1_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr1_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	CALL        _Display_writeLine+0, 0
;Application.c,97 :: 		Display_clearLine(2);
	MOVLW       2
	MOVWF       FARG_Display_clearLine_line+0 
	CALL        _Display_clearLine+0, 0
;Application.c,98 :: 		Delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_Storage_firstBootEvent5:
	DECFSZ      R13, 1, 1
	BRA         L_Storage_firstBootEvent5
	DECFSZ      R12, 1, 1
	BRA         L_Storage_firstBootEvent5
	DECFSZ      R11, 1, 1
	BRA         L_Storage_firstBootEvent5
	NOP
	NOP
;Application.c,101 :: 		default_time.second = 0;
	CLRF        Storage_firstBootEvent_default_time_L0+0 
;Application.c,102 :: 		default_time.minute = 0;
	CLRF        Storage_firstBootEvent_default_time_L0+1 
;Application.c,103 :: 		default_time.hour = 0;
	CLRF        Storage_firstBootEvent_default_time_L0+2 
;Application.c,104 :: 		default_time.day = 1;
	MOVLW       1
	MOVWF       Storage_firstBootEvent_default_time_L0+3 
;Application.c,105 :: 		default_time.month = 1;
	MOVLW       1
	MOVWF       Storage_firstBootEvent_default_time_L0+4 
;Application.c,106 :: 		default_time.year = 70;
	MOVLW       70
	MOVWF       Storage_firstBootEvent_default_time_L0+5 
;Application.c,107 :: 		Timer_setSystemTime(&default_time);
	MOVLW       Storage_firstBootEvent_default_time_L0+0
	MOVWF       FARG_Timer_setSystemTime_time_ptr+0 
	MOVLW       hi_addr(Storage_firstBootEvent_default_time_L0+0)
	MOVWF       FARG_Timer_setSystemTime_time_ptr+1 
	CALL        _Timer_setSystemTime+0, 0
;Application.c,110 :: 		Alarm_setThreshold(90.0f);
	MOVLW       0
	MOVWF       FARG_Alarm_setThreshold__threshold+0 
	MOVLW       0
	MOVWF       FARG_Alarm_setThreshold__threshold+1 
	MOVLW       52
	MOVWF       FARG_Alarm_setThreshold__threshold+2 
	MOVLW       133
	MOVWF       FARG_Alarm_setThreshold__threshold+3 
	CALL        _Alarm_setThreshold+0, 0
;Application.c,113 :: 		Storage_resetLogCounter();
	CALL        _Storage_resetLogCounter+0, 0
;Application.c,114 :: 		}
L_end_Storage_firstBootEvent:
	RETURN      0
; end of _Storage_firstBootEvent

_Storage_settingsLoadedEvent:

;Application.c,119 :: 		void Storage_settingsLoadedEvent() {
;Application.c,121 :: 		StorableData* settings_ptr = Storage_getStoredSettings();
	CALL        _Storage_getStoredSettings+0, 0
	MOVF        R0, 0 
	MOVWF       Storage_settingsLoadedEvent_settings_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Storage_settingsLoadedEvent_settings_ptr_L0+1 
;Application.c,122 :: 		Timer_setSystemTime(&settings_ptr->systemTime);
	MOVF        R0, 0 
	MOVWF       FARG_Timer_setSystemTime_time_ptr+0 
	MOVF        R1, 0 
	MOVWF       FARG_Timer_setSystemTime_time_ptr+1 
	CALL        _Timer_setSystemTime+0, 0
;Application.c,123 :: 		Alarm_setThreshold(settings_ptr->threshold);
	MOVLW       6
	ADDWF       Storage_settingsLoadedEvent_settings_ptr_L0+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      Storage_settingsLoadedEvent_settings_ptr_L0+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+3 
	CALL        _Alarm_setThreshold+0, 0
;Application.c,124 :: 		}
L_end_Storage_settingsLoadedEvent:
	RETURN      0
; end of _Storage_settingsLoadedEvent

_Timer_elapsedSecondEvent:

;Application.c,129 :: 		void Timer_elapsedSecondEvent() {
;Application.c,131 :: 		float actual_temp = Sensor_getTemperature();
	CALL        _Sensor_getTemperature+0, 0
	MOVF        R0, 0 
	MOVWF       Timer_elapsedSecondEvent_actual_temp_L0+0 
	MOVF        R1, 0 
	MOVWF       Timer_elapsedSecondEvent_actual_temp_L0+1 
	MOVF        R2, 0 
	MOVWF       Timer_elapsedSecondEvent_actual_temp_L0+2 
	MOVF        R3, 0 
	MOVWF       Timer_elapsedSecondEvent_actual_temp_L0+3 
;Application.c,136 :: 		char* date_str = Timer_timeToString(Timer_getSystemTime());
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
;Application.c,137 :: 		char* time_str = strstr(date_str, " ");
	MOVF        R0, 0 
	MOVWF       FARG_strstr_s1+0 
	MOVF        R1, 0 
	MOVWF       FARG_strstr_s1+1 
	MOVLW       ?lstr2_Application+0
	MOVWF       FARG_strstr_s2+0 
	MOVLW       hi_addr(?lstr2_Application+0)
	MOVWF       FARG_strstr_s2+1 
	CALL        _strstr+0, 0
	MOVF        R0, 0 
	MOVWF       Timer_elapsedSecondEvent_time_str_L0+0 
	MOVF        R1, 0 
	MOVWF       Timer_elapsedSecondEvent_time_str_L0+1 
;Application.c,138 :: 		*time_str++ = '\0';
	MOVFF       R0, FSR1
	MOVFF       R1, FSR1H
	CLRF        POSTINC1+0 
	INFSNZ      Timer_elapsedSecondEvent_time_str_L0+0, 1 
	INCF        Timer_elapsedSecondEvent_time_str_L0+1, 1 
;Application.c,142 :: 		Display_writeLine(1, "%a   [T]", date_str);
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr3_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr3_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	MOVF        Timer_elapsedSecondEvent_date_str_L0+0, 0 
	MOVWF       FARG_Display_writeLine_line+3 
	MOVF        Timer_elapsedSecondEvent_date_str_L0+1, 0 
	MOVWF       FARG_Display_writeLine_line+4 
	CALL        _Display_writeLine+0, 0
;Application.c,143 :: 		Display_writeLine(2, "%a %2f%cC", time_str, actual_temp, 223);
	MOVLW       2
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr4_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr4_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	MOVF        Timer_elapsedSecondEvent_time_str_L0+0, 0 
	MOVWF       FARG_Display_writeLine_line+3 
	MOVF        Timer_elapsedSecondEvent_time_str_L0+1, 0 
	MOVWF       FARG_Display_writeLine_line+4 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+0, 0 
	MOVWF       FARG_Display_writeLine_line+5 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+1, 0 
	MOVWF       FARG_Display_writeLine_line+6 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+2, 0 
	MOVWF       FARG_Display_writeLine_line+7 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+3, 0 
	MOVWF       FARG_Display_writeLine_line+8 
	MOVLW       223
	MOVWF       FARG_Display_writeLine_line+9 
	CALL        _Display_writeLine+0, 0
;Application.c,147 :: 		Alarm_checkConditions(actual_temp);
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+0, 0 
	MOVWF       FARG_Alarm_checkConditions__temperature+0 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+1, 0 
	MOVWF       FARG_Alarm_checkConditions__temperature+1 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+2, 0 
	MOVWF       FARG_Alarm_checkConditions__temperature+2 
	MOVF        Timer_elapsedSecondEvent_actual_temp_L0+3, 0 
	MOVWF       FARG_Alarm_checkConditions__temperature+3 
	CALL        _Alarm_checkConditions+0, 0
;Application.c,148 :: 		}
L_end_Timer_elapsedSecondEvent:
	RETURN      0
; end of _Timer_elapsedSecondEvent

_Timer_elapsedMinuteEvent:

;Application.c,153 :: 		void Timer_elapsedMinuteEvent() {
;Application.c,155 :: 		Storage_writeLog(Timer_getSystemTime(), Sensor_getTemperature());
	CALL        _Sensor_getTemperature+0, 0
	MOVF        R0, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+0 
	MOVF        R1, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+1 
	MOVF        R2, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+2 
	MOVF        R3, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+3 
	CALL        _Timer_getSystemTime+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Storage_writeLog_timeStamp+0 
	MOVF        R1, 0 
	MOVWF       FARG_Storage_writeLog_timeStamp+1 
	MOVF        FLOC__Timer_elapsedMinuteEvent+0, 0 
	MOVWF       FARG_Storage_writeLog_value+0 
	MOVF        FLOC__Timer_elapsedMinuteEvent+1, 0 
	MOVWF       FARG_Storage_writeLog_value+1 
	MOVF        FLOC__Timer_elapsedMinuteEvent+2, 0 
	MOVWF       FARG_Storage_writeLog_value+2 
	MOVF        FLOC__Timer_elapsedMinuteEvent+3, 0 
	MOVWF       FARG_Storage_writeLog_value+3 
	CALL        _Storage_writeLog+0, 0
;Application.c,156 :: 		Delay_ms(5);
	MOVLW       13
	MOVWF       R12, 0
	MOVLW       251
	MOVWF       R13, 0
L_Timer_elapsedMinuteEvent6:
	DECFSZ      R13, 1, 1
	BRA         L_Timer_elapsedMinuteEvent6
	DECFSZ      R12, 1, 1
	BRA         L_Timer_elapsedMinuteEvent6
	NOP
	NOP
;Application.c,157 :: 		Storage_storeSettings(Timer_getSystemTime(), Alarm_getThreshold());
	CALL        _Alarm_getThreshold+0, 0
	MOVF        R0, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+0 
	MOVF        R1, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+1 
	MOVF        R2, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+2 
	MOVF        R3, 0 
	MOVWF       FLOC__Timer_elapsedMinuteEvent+3 
	CALL        _Timer_getSystemTime+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Storage_storeSettings__systemTime+0 
	MOVF        R1, 0 
	MOVWF       FARG_Storage_storeSettings__systemTime+1 
	MOVF        FLOC__Timer_elapsedMinuteEvent+0, 0 
	MOVWF       FARG_Storage_storeSettings__threshold+0 
	MOVF        FLOC__Timer_elapsedMinuteEvent+1, 0 
	MOVWF       FARG_Storage_storeSettings__threshold+1 
	MOVF        FLOC__Timer_elapsedMinuteEvent+2, 0 
	MOVWF       FARG_Storage_storeSettings__threshold+2 
	MOVF        FLOC__Timer_elapsedMinuteEvent+3, 0 
	MOVWF       FARG_Storage_storeSettings__threshold+3 
	CALL        _Storage_storeSettings+0, 0
;Application.c,158 :: 		}
L_end_Timer_elapsedMinuteEvent:
	RETURN      0
; end of _Timer_elapsedMinuteEvent

_Alarm_thresholdExceededEvent:

;Application.c,163 :: 		void Alarm_thresholdExceededEvent() {
;Application.c,165 :: 		Display_writeLine(1, "     ALARM!");
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr5_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr5_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	CALL        _Display_writeLine+0, 0
;Application.c,166 :: 		Display_clearLine(2);
	MOVLW       2
	MOVWF       FARG_Display_clearLine_line+0 
	CALL        _Display_clearLine+0, 0
;Application.c,167 :: 		Alarm_playAlarmSound();
	CALL        _Alarm_playAlarmSound+0, 0
;Application.c,168 :: 		}
L_end_Alarm_thresholdExceededEvent:
	RETURN      0
; end of _Alarm_thresholdExceededEvent

_Serial_receivedTimeSettingEvent:

;Application.c,173 :: 		void Serial_receivedTimeSettingEvent() {
;Application.c,175 :: 		Timer_setSystemTime((PICTime*)Serial_getReceivedData());
	CALL        _Serial_getReceivedData+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Timer_setSystemTime_time_ptr+0 
	MOVF        R1, 0 
	MOVWF       FARG_Timer_setSystemTime_time_ptr+1 
	CALL        _Timer_setSystemTime+0, 0
;Application.c,176 :: 		Serial_sendAcknowledgement();
	CALL        _Serial_sendAcknowledgement+0, 0
;Application.c,177 :: 		}
L_end_Serial_receivedTimeSettingEvent:
	RETURN      0
; end of _Serial_receivedTimeSettingEvent

_Serial_receivedThresholdSettingEvent:

;Application.c,182 :: 		void Serial_receivedThresholdSettingEvent() {
;Application.c,185 :: 		Alarm_setThreshold(*(float*)Serial_getReceivedData());
	CALL        _Serial_getReceivedData+0, 0
	MOVFF       R0, FSR0
	MOVFF       R1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Alarm_setThreshold__threshold+3 
	CALL        _Alarm_setThreshold+0, 0
;Application.c,186 :: 		Serial_sendAcknowledgement();
	CALL        _Serial_sendAcknowledgement+0, 0
;Application.c,189 :: 		Display_writeLine(1, "New threshold:");
	MOVLW       1
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr6_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr6_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	CALL        _Display_writeLine+0, 0
;Application.c,190 :: 		Display_writeLine(2, "%2f%cC", Alarm_getThreshold(), 223);
	CALL        _Alarm_getThreshold+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Display_writeLine_line+3 
	MOVF        R1, 0 
	MOVWF       FARG_Display_writeLine_line+4 
	MOVF        R2, 0 
	MOVWF       FARG_Display_writeLine_line+5 
	MOVF        R3, 0 
	MOVWF       FARG_Display_writeLine_line+6 
	MOVLW       2
	MOVWF       FARG_Display_writeLine_line+0 
	MOVLW       ?lstr7_Application+0
	MOVWF       FARG_Display_writeLine_format+0 
	MOVLW       hi_addr(?lstr7_Application+0)
	MOVWF       FARG_Display_writeLine_format+1 
	MOVLW       223
	MOVWF       FARG_Display_writeLine_line+7 
	CALL        _Display_writeLine+0, 0
;Application.c,191 :: 		Delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_Serial_receivedThresholdSettingEvent7:
	DECFSZ      R13, 1, 1
	BRA         L_Serial_receivedThresholdSettingEvent7
	DECFSZ      R12, 1, 1
	BRA         L_Serial_receivedThresholdSettingEvent7
	DECFSZ      R11, 1, 1
	BRA         L_Serial_receivedThresholdSettingEvent7
	NOP
	NOP
;Application.c,192 :: 		}
L_end_Serial_receivedThresholdSettingEvent:
	RETURN      0
; end of _Serial_receivedThresholdSettingEvent

_Serial_receivedLogRequestEvent:

;Application.c,197 :: 		void Serial_receivedLogRequestEvent() {
;Application.c,200 :: 		while((entry = Storage_readEarliestLog()))
L_Serial_receivedLogRequestEvent8:
	CALL        _Storage_readEarliestLog+0, 0
	MOVF        R0, 0 
	MOVWF       Serial_receivedLogRequestEvent_entry_L0+0 
	MOVF        R1, 0 
	MOVWF       Serial_receivedLogRequestEvent_entry_L0+1 
	MOVF        R0, 0 
	IORWF       R1, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_receivedLogRequestEvent9
;Application.c,201 :: 		Serial_sendLogEntry(entry);
	MOVF        Serial_receivedLogRequestEvent_entry_L0+0, 0 
	MOVWF       FARG_Serial_sendLogEntry_entry+0 
	MOVF        Serial_receivedLogRequestEvent_entry_L0+1, 0 
	MOVWF       FARG_Serial_sendLogEntry_entry+1 
	CALL        _Serial_sendLogEntry+0, 0
	GOTO        L_Serial_receivedLogRequestEvent8
L_Serial_receivedLogRequestEvent9:
;Application.c,204 :: 		Serial_sendAcknowledgement();
	CALL        _Serial_sendAcknowledgement+0, 0
;Application.c,205 :: 		}
L_end_Serial_receivedLogRequestEvent:
	RETURN      0
; end of _Serial_receivedLogRequestEvent
