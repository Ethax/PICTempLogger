
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
;Display.c,12 :: 		}
L_end_Display_initialize:
	RETURN      0
; end of _Display_initialize

_Display_writeLine_O:

;Display.c,18 :: 		void Display_writeLine_O(uint8_t line, char* text) {
;Display.c,21 :: 		int fill_length = 16 - strlen(text);
	MOVF        FARG_Display_writeLine_O_text+0, 0 
	MOVWF       FARG_strlen_s+0 
	MOVF        FARG_Display_writeLine_O_text+1, 0 
	MOVWF       FARG_strlen_s+1 
	CALL        _strlen+0, 0
	MOVF        R0, 0 
	SUBLW       16
	MOVWF       Display_writeLine_O_fill_length_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_O_fill_length_L0+1 
	MOVLW       0
	SUBFWB      Display_writeLine_O_fill_length_L0+1, 1 
;Display.c,25 :: 		if(line < 2)
	MOVLW       2
	SUBWF       FARG_Display_writeLine_O_line+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine_O0
;Display.c,26 :: 		Lcd_Cmd(_LCD_FIRST_ROW);
	MOVLW       128
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
	GOTO        L_Display_writeLine_O1
L_Display_writeLine_O0:
;Display.c,28 :: 		Lcd_Cmd(_LCD_SECOND_ROW);
	MOVLW       192
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
L_Display_writeLine_O1:
;Display.c,32 :: 		Lcd_Out_CP(text);
	MOVF        FARG_Display_writeLine_O_text+0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        FARG_Display_writeLine_O_text+1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,33 :: 		while(fill_length-- > 0)
L_Display_writeLine_O2:
	MOVF        Display_writeLine_O_fill_length_L0+0, 0 
	MOVWF       R1 
	MOVF        Display_writeLine_O_fill_length_L0+1, 0 
	MOVWF       R2 
	MOVLW       1
	SUBWF       Display_writeLine_O_fill_length_L0+0, 1 
	MOVLW       0
	SUBWFB      Display_writeLine_O_fill_length_L0+1, 1 
	MOVLW       128
	MOVWF       R0 
	MOVLW       128
	XORWF       R2, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Display_writeLine_O31
	MOVF        R1, 0 
	SUBLW       0
L__Display_writeLine_O31:
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine_O3
;Display.c,34 :: 		Lcd_Chr_CP(' ');
	MOVLW       32
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
	GOTO        L_Display_writeLine_O2
L_Display_writeLine_O3:
;Display.c,35 :: 		}
L_end_Display_writeLine_O:
	RETURN      0
; end of _Display_writeLine_O

_Display_writeLine:

;Display.c,37 :: 		void Display_writeLine(uint8_t line, char* format, ...) {
;Display.c,43 :: 		if(line < 2)
	MOVLW       2
	SUBWF       FARG_Display_writeLine_line+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine4
;Display.c,44 :: 		Lcd_Cmd(_LCD_FIRST_ROW);
	MOVLW       128
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
	GOTO        L_Display_writeLine5
L_Display_writeLine4:
;Display.c,46 :: 		Lcd_Cmd(_LCD_SECOND_ROW);
	MOVLW       192
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
L_Display_writeLine5:
;Display.c,48 :: 		va_start(va, format);
	MOVLW       FARG_Display_writeLine_format+2
	MOVWF       Display_writeLine_va_L0+0 
	MOVLW       hi_addr(FARG_Display_writeLine_format+2)
	MOVWF       Display_writeLine_va_L0+1 
;Display.c,49 :: 		while((actual_char = *(format++))) {
L_Display_writeLine6:
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
	GOTO        L_Display_writeLine7
;Display.c,50 :: 		if(actual_char == '%') {
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       37
	BTFSS       STATUS+0, 2 
	GOTO        L_Display_writeLine8
;Display.c,51 :: 		actual_char = *(format++);
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       Display_writeLine_actual_char_L0+0 
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,52 :: 		switch(actual_char) {
	GOTO        L_Display_writeLine9
;Display.c,53 :: 		case 'a':
L_Display_writeLine11:
;Display.c,54 :: 		Lcd_Out_CP(va_arg(va, char*));
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,55 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,57 :: 		case 'c':
L_Display_writeLine12:
;Display.c,58 :: 		Lcd_Chr_CP(va_arg(va, char));
	MOVFF       Display_writeLine_va_L0+0, FSR0
	MOVFF       Display_writeLine_va_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,59 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,61 :: 		case 's':
L_Display_writeLine13:
;Display.c,62 :: 		Lcd_Out_CP(intToString(va_arg(va, short), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,63 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,65 :: 		case 'i':
L_Display_writeLine14:
;Display.c,66 :: 		Lcd_Out_CP(intToString(va_arg(va, int), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,67 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,69 :: 		case 'l':
L_Display_writeLine15:
;Display.c,70 :: 		Lcd_Out_CP(intToString(va_arg(va, long), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,71 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,73 :: 		case 'u':
L_Display_writeLine16:
;Display.c,74 :: 		actual_char = *(format++);
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       Display_writeLine_actual_char_L0+0 
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,75 :: 		switch(actual_char) {
	GOTO        L_Display_writeLine17
;Display.c,76 :: 		case 's':
L_Display_writeLine19:
;Display.c,77 :: 		Lcd_Out_CP(intToString(va_arg(va, unsigned short), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	INFSNZ      Display_writeLine_va_L0+0, 1 
	INCF        Display_writeLine_va_L0+1, 1 
;Display.c,78 :: 		break;
	GOTO        L_Display_writeLine18
;Display.c,80 :: 		case 'i':
L_Display_writeLine20:
;Display.c,81 :: 		Lcd_Out_CP(intToString(va_arg(va, unsigned int), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       2
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,82 :: 		break;
	GOTO        L_Display_writeLine18
;Display.c,84 :: 		case 'l':
L_Display_writeLine21:
;Display.c,85 :: 		Lcd_Out_CP(intToString(va_arg(va, unsigned long), 10));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,86 :: 		break;
	GOTO        L_Display_writeLine18
;Display.c,87 :: 		}
L_Display_writeLine17:
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       115
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine19
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       105
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine20
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       108
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine21
L_Display_writeLine18:
;Display.c,88 :: 		break;
	GOTO        L_Display_writeLine10
;Display.c,90 :: 		default:
L_Display_writeLine22:
;Display.c,91 :: 		if(actual_char >= '0' && actual_char <= '9' && *format == 'f') {
	MOVLW       48
	SUBWF       Display_writeLine_actual_char_L0+0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L_Display_writeLine25
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	SUBLW       57
	BTFSS       STATUS+0, 0 
	GOTO        L_Display_writeLine25
	MOVFF       FARG_Display_writeLine_format+0, FSR0
	MOVFF       FARG_Display_writeLine_format+1, FSR0H
	MOVF        POSTINC0+0, 0 
	XORLW       102
	BTFSS       STATUS+0, 2 
	GOTO        L_Display_writeLine25
L__Display_writeLine28:
;Display.c,92 :: 		Lcd_Out_CP(floatToString(va_arg(va, float), actual_char - '0'));
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
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        R1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
	MOVLW       4
	ADDWF       Display_writeLine_va_L0+0, 1 
	MOVLW       0
	ADDWFC      Display_writeLine_va_L0+1, 1 
;Display.c,93 :: 		format++;
	INFSNZ      FARG_Display_writeLine_format+0, 1 
	INCF        FARG_Display_writeLine_format+1, 1 
;Display.c,94 :: 		}
	GOTO        L_Display_writeLine26
L_Display_writeLine25:
;Display.c,96 :: 		Lcd_Chr_CP(actual_char);
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;Display.c,97 :: 		}
L_Display_writeLine26:
;Display.c,98 :: 		}
	GOTO        L_Display_writeLine10
L_Display_writeLine9:
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       97
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine11
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       99
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine12
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       115
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine13
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       105
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine14
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       108
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine15
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	XORLW       117
	BTFSC       STATUS+0, 2 
	GOTO        L_Display_writeLine16
	GOTO        L_Display_writeLine22
L_Display_writeLine10:
;Display.c,99 :: 		}
	GOTO        L_Display_writeLine27
L_Display_writeLine8:
;Display.c,101 :: 		Lcd_Chr_CP(actual_char);
	MOVF        Display_writeLine_actual_char_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;Display.c,102 :: 		}
L_Display_writeLine27:
;Display.c,103 :: 		}
	GOTO        L_Display_writeLine6
L_Display_writeLine7:
;Display.c,104 :: 		}
L_end_Display_writeLine:
	RETURN      0
; end of _Display_writeLine
