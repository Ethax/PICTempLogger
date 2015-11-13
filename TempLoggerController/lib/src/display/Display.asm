
_Display_initialize:

;Display.c,7 :: 		void Display_initialize() {
;Display.c,8 :: 		Lcd_Init();
	CALL        _Lcd_Init+0, 0
;Display.c,9 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Display.c,10 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Display.c,11 :: 		}
L_end_Display_initialize:
	RETURN      0
; end of _Display_initialize

_Display_writeLine:

;Display.c,17 :: 		void Display_writeLine(uint8_t line, char* text) {
;Display.c,20 :: 		int fill_length = 16 - strlen(text);
	MOVF        FARG_Display_writeLine_text+0, 0 
	MOVWF       FARG_strlen_s+0 
	MOVF        FARG_Display_writeLine_text+1, 0 
	MOVWF       FARG_strlen_s+1 
	CALL        _strlen+0, 0
	MOVF        R0, 0 
	SUBLW       16
	MOVWF       Display_writeLine_fill_length_L0+0 
	MOVF        R1, 0 
	MOVWF       Display_writeLine_fill_length_L0+1 
	MOVLW       0
	SUBFWB      Display_writeLine_fill_length_L0+1, 1 
;Display.c,24 :: 		if(line < 2)
	MOVLW       2
	SUBWF       FARG_Display_writeLine_line+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine0
;Display.c,25 :: 		Lcd_Cmd(_LCD_FIRST_ROW);
	MOVLW       128
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
	GOTO        L_Display_writeLine1
L_Display_writeLine0:
;Display.c,27 :: 		Lcd_Cmd(_LCD_SECOND_ROW);
	MOVLW       192
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
L_Display_writeLine1:
;Display.c,31 :: 		Lcd_Out_CP(text);
	MOVF        FARG_Display_writeLine_text+0, 0 
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVF        FARG_Display_writeLine_text+1, 0 
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Display.c,32 :: 		while(fill_length-- > 0)
L_Display_writeLine2:
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
	GOTO        L__Display_writeLine6
	MOVF        R1, 0 
	SUBLW       0
L__Display_writeLine6:
	BTFSC       STATUS+0, 0 
	GOTO        L_Display_writeLine3
;Display.c,33 :: 		Lcd_Chr_CP(' ');
	MOVLW       32
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
	GOTO        L_Display_writeLine2
L_Display_writeLine3:
;Display.c,34 :: 		}
L_end_Display_writeLine:
	RETURN      0
; end of _Display_writeLine
