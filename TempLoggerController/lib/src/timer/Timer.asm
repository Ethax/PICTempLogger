
_Timer_initialize:

;Timer.c,19 :: 		void Timer_initialize() {
;Timer.c,22 :: 		T0CON = 0x84;
	MOVLW       132
	MOVWF       T0CON+0 
;Timer.c,23 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;Timer.c,24 :: 		TMR0L = 0xDC;
	MOVLW       220
	MOVWF       TMR0L+0 
;Timer.c,25 :: 		TMR0IE_bit = true;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;Timer.c,26 :: 		}
L_end_Timer_initialize:
	RETURN      0
; end of _Timer_initialize

_Timer_handleInterrupt:

;Timer.c,32 :: 		void Timer_handleInterrupt() {
;Timer.c,36 :: 		if(++systemTime.second > 59) {
	MOVF        _systemTime+0, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+0 
	MOVF        _systemTime+0, 0 
	SUBLW       59
	BTFSC       STATUS+0, 0 
	GOTO        L_Timer_handleInterrupt0
;Timer.c,37 :: 		systemTime.second = 0;
	CLRF        _systemTime+0 
;Timer.c,38 :: 		if(++systemTime.minute > 59) {
	MOVF        _systemTime+1, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+1 
	MOVF        _systemTime+1, 0 
	SUBLW       59
	BTFSC       STATUS+0, 0 
	GOTO        L_Timer_handleInterrupt1
;Timer.c,39 :: 		systemTime.minute = 0;
	CLRF        _systemTime+1 
;Timer.c,40 :: 		if(++systemTime.hour > 23) {
	MOVF        _systemTime+2, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+2 
	MOVF        _systemTime+2, 0 
	SUBLW       23
	BTFSC       STATUS+0, 0 
	GOTO        L_Timer_handleInterrupt2
;Timer.c,41 :: 		systemTime.hour = 0;
	CLRF        _systemTime+2 
;Timer.c,42 :: 		if(++systemTime.day > monthsLength[systemTime.month - 1]) {
	MOVF        _systemTime+3, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+3 
	DECF        _systemTime+4, 0 
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	SUBWFB      R1, 1 
	MOVLW       _monthsLength+0
	ADDWF       R0, 0 
	MOVWF       FSR2 
	MOVLW       hi_addr(_monthsLength+0)
	ADDWFC      R1, 0 
	MOVWF       FSR2H 
	MOVF        _systemTime+3, 0 
	SUBWF       POSTINC2+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Timer_handleInterrupt3
;Timer.c,43 :: 		systemTime.day = 1;
	MOVLW       1
	MOVWF       _systemTime+3 
;Timer.c,44 :: 		if(++systemTime.month > 12) {
	MOVF        _systemTime+4, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+4 
	MOVF        _systemTime+4, 0 
	SUBLW       12
	BTFSC       STATUS+0, 0 
	GOTO        L_Timer_handleInterrupt4
;Timer.c,45 :: 		systemTime.month = 1;
	MOVLW       1
	MOVWF       _systemTime+4 
;Timer.c,46 :: 		systemTime.year++;
	MOVF        _systemTime+5, 0 
	ADDLW       1
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       _systemTime+5 
;Timer.c,47 :: 		if(!(systemTime.year && 0b00000011))
	MOVF        _systemTime+5, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_Timer_handleInterrupt6
	MOVLW       1
	MOVWF       R0 
	GOTO        L_Timer_handleInterrupt5
L_Timer_handleInterrupt6:
	CLRF        R0 
L_Timer_handleInterrupt5:
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_Timer_handleInterrupt7
;Timer.c,48 :: 		monthsLength[1] = 29;
	MOVLW       29
	MOVWF       _monthsLength+1 
	GOTO        L_Timer_handleInterrupt8
L_Timer_handleInterrupt7:
;Timer.c,50 :: 		monthsLength[1] = 28;
	MOVLW       28
	MOVWF       _monthsLength+1 
L_Timer_handleInterrupt8:
;Timer.c,51 :: 		}
L_Timer_handleInterrupt4:
;Timer.c,52 :: 		}
L_Timer_handleInterrupt3:
;Timer.c,53 :: 		}
L_Timer_handleInterrupt2:
;Timer.c,54 :: 		}
L_Timer_handleInterrupt1:
;Timer.c,55 :: 		Application_dispatchEvent(Timer_elapsedMinuteEvent);
	MOVLW       _Timer_elapsedMinuteEvent+0
	MOVWF       FARG_Application_dispatchEvent_handler+0 
	MOVLW       hi_addr(_Timer_elapsedMinuteEvent+0)
	MOVWF       FARG_Application_dispatchEvent_handler+1 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+2 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+3 
	CALL        _Application_dispatchEvent+0, 0
;Timer.c,56 :: 		}
L_Timer_handleInterrupt0:
;Timer.c,57 :: 		Application_dispatchEvent(Timer_elapsedSecondEvent);
	MOVLW       _Timer_elapsedSecondEvent+0
	MOVWF       FARG_Application_dispatchEvent_handler+0 
	MOVLW       hi_addr(_Timer_elapsedSecondEvent+0)
	MOVWF       FARG_Application_dispatchEvent_handler+1 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+2 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+3 
	CALL        _Application_dispatchEvent+0, 0
;Timer.c,61 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;Timer.c,62 :: 		TMR0L = 0xDC;
	MOVLW       220
	MOVWF       TMR0L+0 
;Timer.c,63 :: 		TMR0IF_bit = false;
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;Timer.c,64 :: 		}
L_end_Timer_handleInterrupt:
	RETURN      0
; end of _Timer_handleInterrupt

_Timer_getSystemTime:

;Timer.c,69 :: 		PICTime* Timer_getSystemTime() {
;Timer.c,70 :: 		return &systemTime;
	MOVLW       _systemTime+0
	MOVWF       R0 
	MOVLW       hi_addr(_systemTime+0)
	MOVWF       R1 
;Timer.c,71 :: 		}
L_end_Timer_getSystemTime:
	RETURN      0
; end of _Timer_getSystemTime

_Timer_setSystemTime:

;Timer.c,76 :: 		void Timer_setSystemTime(PICTime* time_ptr) {
;Timer.c,79 :: 		TMR0IE_bit = false;
	BCF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;Timer.c,80 :: 		memcpy(&systemTime, time_ptr, sizeof(PICTime));
	MOVLW       _systemTime+0
	MOVWF       FARG_memcpy_d1+0 
	MOVLW       hi_addr(_systemTime+0)
	MOVWF       FARG_memcpy_d1+1 
	MOVF        FARG_Timer_setSystemTime_time_ptr+0, 0 
	MOVWF       FARG_memcpy_s1+0 
	MOVF        FARG_Timer_setSystemTime_time_ptr+1, 0 
	MOVWF       FARG_memcpy_s1+1 
	MOVLW       6
	MOVWF       FARG_memcpy_n+0 
	MOVLW       0
	MOVWF       FARG_memcpy_n+1 
	CALL        _memcpy+0, 0
;Timer.c,84 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;Timer.c,85 :: 		TMR0L = 0xDC;
	MOVLW       220
	MOVWF       TMR0L+0 
;Timer.c,86 :: 		TMR0IE_bit = true;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;Timer.c,87 :: 		}
L_end_Timer_setSystemTime:
	RETURN      0
; end of _Timer_setSystemTime

_Timer_timeToString:

;Timer.c,93 :: 		char* Timer_timeToString(PICTime* time_ptr) {
;Timer.c,95 :: 		uint8_t i = 0;
	CLRF        Timer_timeToString_i_L0+0 
;Timer.c,98 :: 		time_str[i++] = ((1900 + time_ptr->year) / 1000) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       5
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR2 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR2H 
	MOVLW       108
	MOVWF       R0 
	MOVLW       7
	MOVWF       R1 
	MOVF        POSTINC2+0, 0 
	ADDWF       R0, 1 
	BTFSC       STATUS+0, 0 
	INCF        R1, 1 
	MOVLW       232
	MOVWF       R4 
	MOVLW       3
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,99 :: 		time_str[i++] = (((1900 + time_ptr->year) % 1000) / 100) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       5
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR2 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR2H 
	MOVLW       108
	MOVWF       R0 
	MOVLW       7
	MOVWF       R1 
	MOVF        POSTINC2+0, 0 
	ADDWF       R0, 1 
	BTFSC       STATUS+0, 0 
	INCF        R1, 1 
	MOVLW       232
	MOVWF       R4 
	MOVLW       3
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       100
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,100 :: 		time_str[i++] = (((1900 + time_ptr->year) % 100) / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       5
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR2 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR2H 
	MOVLW       108
	MOVWF       R0 
	MOVLW       7
	MOVWF       R1 
	MOVF        POSTINC2+0, 0 
	ADDWF       R0, 1 
	BTFSC       STATUS+0, 0 
	INCF        R1, 1 
	MOVLW       100
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,101 :: 		time_str[i++] = ((1900 + time_ptr->year) % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       5
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR2 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR2H 
	MOVLW       108
	MOVWF       R0 
	MOVLW       7
	MOVWF       R1 
	MOVF        POSTINC2+0, 0 
	ADDWF       R0, 1 
	BTFSC       STATUS+0, 0 
	INCF        R1, 1 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,102 :: 		time_str[i++] = '-';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       45
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,105 :: 		time_str[i++] = ((time_ptr->month) / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       4
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,106 :: 		time_str[i++] = ((time_ptr->month) % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       4
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,107 :: 		time_str[i++] = '-';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       45
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,110 :: 		time_str[i++] = (time_ptr->day / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       3
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,111 :: 		time_str[i++] = (time_ptr->day % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       3
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,112 :: 		time_str[i++] = ' ';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       32
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,115 :: 		time_str[i++] = (time_ptr->hour / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       2
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,116 :: 		time_str[i++] = (time_ptr->hour % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       2
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,117 :: 		time_str[i++] = ':';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       58
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,120 :: 		time_str[i++] = (time_ptr->minute / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       1
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,121 :: 		time_str[i++] = (time_ptr->minute % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVLW       1
	ADDWF       FARG_Timer_timeToString_time_ptr+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_Timer_timeToString_time_ptr+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,122 :: 		time_str[i++] = ':';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       58
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,125 :: 		time_str[i++] = (time_ptr->second / 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVFF       FARG_Timer_timeToString_time_ptr+0, FSR0
	MOVFF       FARG_Timer_timeToString_time_ptr+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,126 :: 		time_str[i++] = (time_ptr->second % 10) + '0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FLOC__Timer_timeToString+0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FLOC__Timer_timeToString+1 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FLOC__Timer_timeToString+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__Timer_timeToString+1, 1 
	MOVFF       FARG_Timer_timeToString_time_ptr+0, FSR0
	MOVFF       FARG_Timer_timeToString_time_ptr+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVLW       10
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       FLOC__Timer_timeToString+0, FSR1
	MOVFF       FLOC__Timer_timeToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,127 :: 		time_str[i++] = '\0';
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       FSR1H 
	MOVF        Timer_timeToString_i_L0+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	CLRF        POSTINC1+0 
	INCF        Timer_timeToString_i_L0+0, 1 
;Timer.c,130 :: 		return time_str;
	MOVLW       Timer_timeToString_time_str_L0+0
	MOVWF       R0 
	MOVLW       hi_addr(Timer_timeToString_time_str_L0+0)
	MOVWF       R1 
;Timer.c,131 :: 		}
L_end_Timer_timeToString:
	RETURN      0
; end of _Timer_timeToString
