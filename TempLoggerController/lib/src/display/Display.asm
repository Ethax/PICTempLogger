
_Display_initialize:

;Display.c,8 :: 		void Display_initialize() {
;Display.c,9 :: 		Lcd_Init();
	CALL        _Lcd_Init+0, 0
;Display.c,10 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Display.c,11 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Display.c,12 :: 		Lcd_Out(1, 5, "Ready...");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       5
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_Display+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_Display+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Display.c,13 :: 		}
L_end_Display_initialize:
	RETURN      0
; end of _Display_initialize

_Display_writeLine:

;Display.c,19 :: 		void Display_writeLine(uint8_t line, char* format, ...) {
;Display.c,20 :: 		int fill_length = 16;
	MOVLW       16
	MOVWF       Display_writeLine_fill_length_L0+0 
	MOVLW       0
	MOVWF       Display_writeLine_fill_length_L0+1 
;Display.c,27 :: 		if(line < 2)
	MOVLW       2
	SUBWF       FARG_Display_writeLine_line+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine0
;Display.c,28 :: 		Lcd_Cmd(_LCD_FIRST_ROW);
	MOVLW       128
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
	GOTO        L_Display_writeLine1
L_Display_writeLine0:
;Display.c,30 :: 		Lcd_Cmd(_LCD_SECOND_ROW);
	MOVLW       192
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
L_Display_writeLine1:
;Display.c,33 :: 		va_start(va, format);
	MOVLW       FARG_Display_writeLine_format+2
	MOVWF       Display_writeLine_va_L0+0 
	MOVLW       hi_addr(FARG_Display_writeLine_format+2)
	MOVWF       Display_writeLine_va_L0+1 
;Display.c,34 :: 		while((actual_char = *(format++))) {
L_Display_writeLine2:
	MOVF        FARG_Display_writeLine_format+0, 0 
	MOVWF       R0 
	MOVF        FARG_Display_writeLine_format+1, 0 
	MOVWF       R1 
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
	MOVFF       R0, FSR0
	MOVFF       R1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       Display_writeLine_actual_char_L0+0 
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine3
;Display.c,38 :: 		if(actual_char == '%') {
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       37
	BTFSS       STATUS+0, 2 
	GOTO        L_Display_writeLine4
;Display.c,39 :: 		actual_char = *(format++);
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       Display_writeLine_actual_char_L0+0 
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,40 :: 		switch(actual_char) {
	GOTO        L_Display_writeLine5
;Display.c,41 :: 		case 'a': /* alphanumeric */
L_Display_writeLine7:
;Display.c,42 :: 		string_ptr = va_arg(va, char*);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVF        POSTINC0+0, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,43 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,44 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,45 :: 		case 'c': /* char */
L_Display_writeLine8:
;Display.c,46 :: 		fill_length--;
	MOVLW       1
	SUBWF       Display_writeLine_fill_length_L0+0, 1 
	MOVLW       0
	SUBWFB      Display_writeLine_fill_length_L0+1, 1 
;Display.c,47 :: 		Lcd_Chr_CP(va_arg(va, char));
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,48 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,49 :: 		case 's': /* (signed) short int */
L_Display_writeLine9:
;Display.c,50 :: 		string_ptr = intToString(va_arg(va, short), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVLW       0
	BTFSC       FARG_intToString_value+3, 7 
	MOVLW       255
	MOVWF       FARG_intToString_value+1 
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       0
	BTFSC       FARG_intToString_value+0, 7 
	MOVLW       255
	MOVWF       FARG_intToString_value+1 
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,51 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,52 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,53 :: 		case 'i': /* (signed) int */
L_Display_writeLine10:
;Display.c,54 :: 		string_ptr = intToString(va_arg(va, int), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+1 
	MOVLW       0
	BTFSC       FARG_intToString_value+3, 7 
	MOVLW       255
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       0
	BTFSC       FARG_intToString_value+1, 7 
	MOVLW       255
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,55 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,56 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,57 :: 		case 'l': /* (signed) long int */
L_Display_writeLine11:
;Display.c,58 :: 		string_ptr = intToString(va_arg(va, long), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,59 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,60 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,61 :: 		case 'u': /* unsigned */
L_Display_writeLine12:
;Display.c,62 :: 		actual_char = *(format++);
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       Display_writeLine_actual_char_L0+0 
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,63 :: 		switch(actual_char) {
	GOTO        L_Display_writeLine13
;Display.c,64 :: 		case 's': /* unsigned short int */
L_Display_writeLine15:
;Display.c,65 :: 		string_ptr = intToString(va_arg(va, unsigned short), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVLW       0
	MOVWF       FARG_intToString_value+1 
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       0
	MOVWF       FARG_intToString_value+1 
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,66 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,67 :: 		break;
	GOTO        L_Display_writeLine14
;Display.c,68 :: 		case 'i': /* unsigned int */
L_Display_writeLine16:
;Display.c,69 :: 		string_ptr = intToString(va_arg(va, unsigned int), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+1 
	MOVLW       0
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       0
	MOVWF       FARG_intToString_value+2 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,70 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,71 :: 		break;
	GOTO        L_Display_writeLine14
;Display.c,72 :: 		case 'l': /* unsigned long int */
L_Display_writeLine17:
;Display.c,73 :: 		string_ptr = intToString(va_arg(va, unsigned long), 10);
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,74 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,75 :: 		break;
	GOTO        L_Display_writeLine14
;Display.c,76 :: 		}
L_Display_writeLine13:
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       115
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine15
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       105
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine16
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       108
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine17
L_Display_writeLine14:
;Display.c,77 :: 		break;
	GOTO        L_Display_writeLine6
;Display.c,78 :: 		default:
L_Display_writeLine18:
;Display.c,79 :: 		if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
	MOVLW       48
	SUBWF       Display_writeLine_actual_char_L0+0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L_Display_writeLine21
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	SUBLW       57
	BTFSS       STATUS+0, 0 
	GOTO        L_Display_writeLine21
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	XORLW       102
	BTFSS       STATUS+0, 2 
	GOTO        L_Display_writeLine21
L__Display_writeLine32:
;Display.c,80 :: 		string_ptr = floatToString(va_arg(va, float), actual_char - '0');
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_floatToString_value+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_floatToString_value+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_floatToString_value+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_floatToString_value+3 
	MOVLW       48
	SUBWF       Display_writeLine_actual_char_L0+0, 0 
	MOVWF       FARG_floatToString_precision+0 
	CALL        _floatToString+0, 0
	MOVF        R0, 0 
	MOVWF       Display_writeLine_string_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_string_ptr_L0+1 
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,81 :: 		Lcd_Out_CP(string_ptr);
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,82 :: 		format++;
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,83 :: 		}
	GOTO        L_Display_writeLine22
L_Display_writeLine21:
;Display.c,85 :: 		fill_length--;
	MOVLW       1
	SUBWF       Display_writeLine_fill_length_L0+0, 1 
	MOVLW       0
	SUBWFB      Display_writeLine_fill_length_L0+1, 1 
;Display.c,86 :: 		Lcd_Chr_CP(actual_char);
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;Display.c,87 :: 		}
L_Display_writeLine22:
;Display.c,88 :: 		}
	GOTO        L_Display_writeLine6
L_Display_writeLine5:
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       97
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine7
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       99
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine8
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       115
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine9
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       105
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine10
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       108
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine11
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       117
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine12
	GOTO        L_Display_writeLine18
L_Display_writeLine6:
;Display.c,93 :: 		if(string_ptr) {
	MOVF        Display_writeLine_string_ptr_L0+0, 0 
	IORWF       Display_writeLine_string_ptr_L0+1, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine23
;Display.c,94 :: 		fill_length -= strlen(string_ptr);
	MOVF        Display_writeLine_string_ptr_L0+0, 0 
	MOVWF       FARG_strlen_s+0 
	MOVF        Display_writeLine_string_ptr_L0+1, 0 
	MOVWF       FARG_strlen_s+1 
	CALL        _strlen+0, 0
	MOVF        R0, 0 
	SUBWF       Display_writeLine_fill_length_L0+0, 1 
	MOVF        R1, 0 
	SUBWFB      Display_writeLine_fill_length_L0+1, 1 
;Display.c,95 :: 		string_ptr = 0;
	CLRF        Display_writeLine_string_ptr_L0+0 
	CLRF        Display_writeLine_string_ptr_L0+1 
;Display.c,96 :: 		}
L_Display_writeLine23:
;Display.c,97 :: 		}
	GOTO        L_Display_writeLine24
L_Display_writeLine4:
;Display.c,101 :: 		fill_length--;
	MOVLW       1
	SUBWF       Display_writeLine_fill_length_L0+0, 1 
	MOVLW       0
	SUBWFB      Display_writeLine_fill_length_L0+1, 1 
;Display.c,102 :: 		Lcd_Chr_CP(actual_char);
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;Display.c,103 :: 		}
L_Display_writeLine24:
;Display.c,104 :: 		}
	GOTO        L_Display_writeLine2
L_Display_writeLine3:
;Display.c,108 :: 		while(fill_length-- > 0)
L_Display_writeLine25:
	MOVF        Display_writeLine_fill_length_L0+0, 0 
	MOVWF       R1 
	MOVF        Display_writeLine_fill_length_L0+1, 0 
	MOVWF       R2 
	MOVLW       1
	SUBWF       Display_writeLine_fill_length_L0+0, 1 
	MOVLW       0
	SUBWFB      Display_writeLine_fill_length_L0+1, 1 
	MOVLW       128
	MOVWF       R0 
	MOVLW       128
	XORWF       R2, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Display_writeLine35
	MOVF        R1, 0 
	SUBLW       0
L__Display_writeLine35:
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine26
;Display.c,109 :: 		Lcd_Chr_CP(' ');
	MOVLW       32
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
	GOTO        L_Display_writeLine25
L_Display_writeLine26:
;Display.c,110 :: 		}
L_end_Display_writeLine:
	RETURN      0
; end of _Display_writeLine

_Display_clearLine:

;Display.c,115 :: 		void Display_clearLine(uint8_t line) {
;Display.c,120 :: 		if(line < 2)
	MOVLW       2
	SUBWF       FARG_Display_clearLine_line+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_clearLine27
;Display.c,121 :: 		Lcd_Cmd(_LCD_FIRST_ROW);
	MOVLW       128
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
	GOTO        L_Display_clearLine28
L_Display_clearLine27:
;Display.c,123 :: 		Lcd_Cmd(_LCD_SECOND_ROW);
	MOVLW       192
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
L_Display_clearLine28:
;Display.c,127 :: 		for(current_char = 0; current_char < 16; current_char++)
	CLRF        Display_clearLine_current_char_L0+0 
L_Display_clearLine29:
	MOVLW       16
	SUBWF       Display_clearLine_current_char_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_clearLine30
;Display.c,128 :: 		Lcd_Chr_CP(' ');
	MOVLW       32
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;Display.c,127 :: 		for(current_char = 0; current_char < 16; current_char++)
	INCF        Display_clearLine_current_char_L0+0, 1 
;Display.c,128 :: 		Lcd_Chr_CP(' ');
	GOTO        L_Display_clearLine29
L_Display_clearLine30:
;Display.c,129 :: 		}
L_end_Display_clearLine:
	RETURN      0
; end of _Display_clearLine
