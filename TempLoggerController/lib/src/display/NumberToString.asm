
_intToString:

;NumberToString.c,7 :: 		char* intToString(int32_t value, uint8_t base) {
;NumberToString.c,10 :: 		uint8_t max_length = 14;
	MOVLW       14
	MOVWF       intToString_max_length_L0+0 
;NumberToString.c,13 :: 		bool isNegative = value < 0 ? true : false;
	MOVLW       128
	XORWF       FARG_intToString_value+3, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__intToString42
	MOVLW       0
	SUBWF       FARG_intToString_value+2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__intToString42
	MOVLW       0
	SUBWF       FARG_intToString_value+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__intToString42
	MOVLW       0
	SUBWF       FARG_intToString_value+0, 0 
L__intToString42:
	BTFSC       STATUS+0, 0 
	GOTO        L_intToString0
	MOVLW       1
	MOVWF       R0 
	GOTO        L_intToString1
L_intToString0:
	CLRF        R0 
L_intToString1:
	MOVF        R0, 0 
	MOVWF       intToString_isNegative_L0+0 
;NumberToString.c,14 :: 		if(isNegative) value = -value;
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_intToString2
	CLRF        R0 
	CLRF        R1 
	CLRF        R2 
	CLRF        R3 
	MOVF        FARG_intToString_value+0, 0 
	SUBWF       R0, 1 
	MOVF        FARG_intToString_value+1, 0 
	SUBWFB      R1, 1 
	MOVF        FARG_intToString_value+2, 0 
	SUBWFB      R2, 1 
	MOVF        FARG_intToString_value+3, 0 
	SUBWFB      R3, 1 
	MOVF        R0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        R1, 0 
	MOVWF       FARG_intToString_value+1 
	MOVF        R2, 0 
	MOVWF       FARG_intToString_value+2 
	MOVF        R3, 0 
	MOVWF       FARG_intToString_value+3 
L_intToString2:
;NumberToString.c,19 :: 		if(base < 2 || base > 16 || !value) return "0";
	MOVLW       2
	SUBWF       FARG_intToString_base+0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L__intToString38
	MOVF        FARG_intToString_base+0, 0 
	SUBLW       16
	BTFSS       STATUS+0, 0 
	GOTO        L__intToString38
	MOVF        FARG_intToString_value+0, 0 
	IORWF       FARG_intToString_value+1, 0 
	IORWF       FARG_intToString_value+2, 0 
	IORWF       FARG_intToString_value+3, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L__intToString38
	GOTO        L_intToString5
L__intToString38:
	MOVLW       ?lstr1_NumberToString+0
	MOVWF       R0 
	MOVLW       hi_addr(?lstr1_NumberToString+0)
	MOVWF       R1 
	GOTO        L_end_intToString
L_intToString5:
;NumberToString.c,22 :: 		result[max_length + isNegative + 1] = '\0';
	MOVF        intToString_isNegative_L0+0, 0 
	ADDWF       intToString_max_length_L0+0, 0 
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	INFSNZ      R0, 1 
	INCF        R1, 1 
	MOVLW       intToString_result_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(intToString_result_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	CLRF        POSTINC1+0 
;NumberToString.c,23 :: 		for(; value && max_length ; --max_length, value /= base)
L_intToString6:
	MOVF        FARG_intToString_value+0, 0 
	IORWF       FARG_intToString_value+1, 0 
	IORWF       FARG_intToString_value+2, 0 
	IORWF       FARG_intToString_value+3, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_intToString7
	MOVF        intToString_max_length_L0+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_intToString7
L__intToString37:
;NumberToString.c,24 :: 		result[max_length + isNegative] = DIGIT_MAP[value % base];
	MOVF        intToString_isNegative_L0+0, 0 
	ADDWF       intToString_max_length_L0+0, 0 
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       intToString_result_L0+0
	ADDWF       R0, 0 
	MOVWF       FLOC__intToString+0 
	MOVLW       hi_addr(intToString_result_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FLOC__intToString+1 
	MOVF        FARG_intToString_base+0, 0 
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVWF       R6 
	MOVWF       R7 
	MOVF        FARG_intToString_value+0, 0 
	MOVWF       R0 
	MOVF        FARG_intToString_value+1, 0 
	MOVWF       R1 
	MOVF        FARG_intToString_value+2, 0 
	MOVWF       R2 
	MOVF        FARG_intToString_value+3, 0 
	MOVWF       R3 
	CALL        _Div_32x32_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R10, 0 
	MOVWF       R2 
	MOVF        R11, 0 
	MOVWF       R3 
	MOVLW       intToString_DIGIT_MAP_L0+0
	ADDWF       R0, 0 
	MOVWF       TBLPTRL 
	MOVLW       hi_addr(intToString_DIGIT_MAP_L0+0)
	ADDWFC      R1, 0 
	MOVWF       TBLPTRH 
	MOVLW       higher_addr(intToString_DIGIT_MAP_L0+0)
	ADDWFC      R2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, R0
	MOVFF       FLOC__intToString+0, FSR1
	MOVFF       FLOC__intToString+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
;NumberToString.c,23 :: 		for(; value && max_length ; --max_length, value /= base)
	DECF        intToString_max_length_L0+0, 1 
	MOVF        FARG_intToString_base+0, 0 
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVWF       R6 
	MOVWF       R7 
	MOVF        FARG_intToString_value+0, 0 
	MOVWF       R0 
	MOVF        FARG_intToString_value+1, 0 
	MOVWF       R1 
	MOVF        FARG_intToString_value+2, 0 
	MOVWF       R2 
	MOVF        FARG_intToString_value+3, 0 
	MOVWF       R3 
	CALL        _Div_32x32_S+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        R1, 0 
	MOVWF       FARG_intToString_value+1 
	MOVF        R2, 0 
	MOVWF       FARG_intToString_value+2 
	MOVF        R3, 0 
	MOVWF       FARG_intToString_value+3 
;NumberToString.c,24 :: 		result[max_length + isNegative] = DIGIT_MAP[value % base];
	GOTO        L_intToString6
L_intToString7:
;NumberToString.c,28 :: 		if(isNegative) result[max_length + 1] = '-';
	MOVF        intToString_isNegative_L0+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_intToString11
	MOVF        intToString_max_length_L0+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       intToString_result_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR1 
	MOVLW       hi_addr(intToString_result_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR1H 
	MOVLW       45
	MOVWF       POSTINC1+0 
L_intToString11:
;NumberToString.c,29 :: 		return &result[max_length + 1];
	MOVF        intToString_max_length_L0+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	ADDWFC      R1, 1 
	MOVLW       intToString_result_L0+0
	ADDWF       R0, 1 
	MOVLW       hi_addr(intToString_result_L0+0)
	ADDWFC      R1, 1 
;NumberToString.c,30 :: 		}
L_end_intToString:
	RETURN      0
; end of _intToString

_floatToString:

;NumberToString.c,36 :: 		char* floatToString(float value, uint8_t precision) {
;NumberToString.c,39 :: 		int32_t mantissa, int_part = 0, frac_part = 0;
	CLRF        floatToString_int_part_L0+0 
	CLRF        floatToString_int_part_L0+1 
	CLRF        floatToString_int_part_L0+2 
	CLRF        floatToString_int_part_L0+3 
	CLRF        floatToString_frac_part_L0+0 
	CLRF        floatToString_frac_part_L0+1 
	CLRF        floatToString_frac_part_L0+2 
	CLRF        floatToString_frac_part_L0+3 
;NumberToString.c,47 :: 		_value.float_value = value;
	MOVF        FARG_floatToString_value+0, 0 
	MOVWF       floatToString__value_L0+0 
	MOVF        FARG_floatToString_value+1, 0 
	MOVWF       floatToString__value_L0+1 
	MOVF        FARG_floatToString_value+2, 0 
	MOVWF       floatToString__value_L0+2 
	MOVF        FARG_floatToString_value+3, 0 
	MOVWF       floatToString__value_L0+3 
;NumberToString.c,48 :: 		exponent = (uint8_t)(_value.raw_value >> 24) - 127;
	MOVF        floatToString__value_L0+3, 0 
	MOVWF       R0 
	MOVLW       0
	BTFSC       floatToString__value_L0+3, 7 
	MOVLW       255
	MOVWF       R3 
	MOVLW       127
	SUBWF       R0, 0 
	MOVWF       R1 
	MOVF        R1, 0 
	MOVWF       floatToString_exponent_L0+0 
;NumberToString.c,49 :: 		mantissa = (_value.raw_value & 0xFFFFFF) | 0x800000;
	MOVLW       255
	ANDWF       floatToString__value_L0+0, 0 
	MOVWF       floatToString_mantissa_L0+0 
	MOVLW       255
	ANDWF       floatToString__value_L0+1, 0 
	MOVWF       floatToString_mantissa_L0+1 
	MOVLW       255
	ANDWF       floatToString__value_L0+2, 0 
	MOVWF       floatToString_mantissa_L0+2 
	MOVLW       0
	ANDWF       floatToString__value_L0+3, 0 
	MOVWF       floatToString_mantissa_L0+3 
	BSF         floatToString_mantissa_L0+2, 7 
;NumberToString.c,53 :: 		if(exponent >= 31 || exponent < -23 || !_value.raw_value) return "0.0";
	MOVLW       128
	XORWF       R1, 0 
	MOVWF       R0 
	MOVLW       128
	XORLW       31
	SUBWF       R0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L__floatToString40
	MOVLW       128
	XORWF       floatToString_exponent_L0+0, 0 
	MOVWF       R0 
	MOVLW       128
	XORLW       233
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L__floatToString40
	MOVF        floatToString__value_L0+0, 0 
	IORWF       floatToString__value_L0+1, 0 
	IORWF       floatToString__value_L0+2, 0 
	IORWF       floatToString__value_L0+3, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L__floatToString40
	GOTO        L_floatToString14
L__floatToString40:
	MOVLW       ?lstr2_NumberToString+0
	MOVWF       R0 
	MOVLW       hi_addr(?lstr2_NumberToString+0)
	MOVWF       R1 
	GOTO        L_end_floatToString
L_floatToString14:
;NumberToString.c,56 :: 		if(exponent >= 23) {
	MOVLW       128
	XORWF       floatToString_exponent_L0+0, 0 
	MOVWF       R0 
	MOVLW       128
	XORLW       23
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L_floatToString15
;NumberToString.c,57 :: 		int_part = mantissa << (exponent - 23);
	MOVLW       23
	SUBWF       floatToString_exponent_L0+0, 0 
	MOVWF       R0 
	MOVLW       0
	BTFSC       floatToString_exponent_L0+0, 7 
	MOVLW       255
	MOVWF       R1 
	MOVLW       0
	SUBWFB      R1, 1 
	MOVF        floatToString_mantissa_L0+0, 0 
	MOVWF       floatToString_int_part_L0+0 
	MOVF        floatToString_mantissa_L0+1, 0 
	MOVWF       floatToString_int_part_L0+1 
	MOVF        floatToString_mantissa_L0+2, 0 
	MOVWF       floatToString_int_part_L0+2 
	MOVF        floatToString_mantissa_L0+3, 0 
	MOVWF       floatToString_int_part_L0+3 
	MOVF        R0, 0 
L__floatToString44:
	BZ          L__floatToString45
	RLCF        floatToString_int_part_L0+0, 1 
	BCF         floatToString_int_part_L0+0, 0 
	RLCF        floatToString_int_part_L0+1, 1 
	RLCF        floatToString_int_part_L0+2, 1 
	RLCF        floatToString_int_part_L0+3, 1 
	ADDLW       255
	GOTO        L__floatToString44
L__floatToString45:
;NumberToString.c,58 :: 		}
	GOTO        L_floatToString16
L_floatToString15:
;NumberToString.c,59 :: 		else if(exponent >= 0) {
	MOVLW       128
	XORWF       floatToString_exponent_L0+0, 0 
	MOVWF       R0 
	MOVLW       128
	XORLW       0
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 0 
	GOTO        L_floatToString17
;NumberToString.c,60 :: 		int_part = mantissa >> (23 - exponent);
	MOVF        floatToString_exponent_L0+0, 0 
	SUBLW       23
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	BTFSC       floatToString_exponent_L0+0, 7 
	MOVLW       255
	SUBWFB      R1, 1 
	MOVF        floatToString_mantissa_L0+0, 0 
	MOVWF       floatToString_int_part_L0+0 
	MOVF        floatToString_mantissa_L0+1, 0 
	MOVWF       floatToString_int_part_L0+1 
	MOVF        floatToString_mantissa_L0+2, 0 
	MOVWF       floatToString_int_part_L0+2 
	MOVF        floatToString_mantissa_L0+3, 0 
	MOVWF       floatToString_int_part_L0+3 
	MOVF        R0, 0 
L__floatToString46:
	BZ          L__floatToString47
	RRCF        floatToString_int_part_L0+3, 1 
	RRCF        floatToString_int_part_L0+2, 1 
	RRCF        floatToString_int_part_L0+1, 1 
	RRCF        floatToString_int_part_L0+0, 1 
	BCF         floatToString_int_part_L0+3, 7 
	BTFSC       floatToString_int_part_L0+3, 6 
	BSF         floatToString_int_part_L0+3, 7 
	ADDLW       255
	GOTO        L__floatToString46
L__floatToString47:
;NumberToString.c,61 :: 		frac_part = (mantissa << (exponent + 1)) & 0xFFFFFF;
	MOVF        floatToString_exponent_L0+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	BTFSC       floatToString_exponent_L0+0, 7 
	MOVLW       255
	ADDWFC      R1, 1 
	MOVF        floatToString_mantissa_L0+0, 0 
	MOVWF       floatToString_frac_part_L0+0 
	MOVF        floatToString_mantissa_L0+1, 0 
	MOVWF       floatToString_frac_part_L0+1 
	MOVF        floatToString_mantissa_L0+2, 0 
	MOVWF       floatToString_frac_part_L0+2 
	MOVF        floatToString_mantissa_L0+3, 0 
	MOVWF       floatToString_frac_part_L0+3 
	MOVF        R0, 0 
L__floatToString48:
	BZ          L__floatToString49
	RLCF        floatToString_frac_part_L0+0, 1 
	BCF         floatToString_frac_part_L0+0, 0 
	RLCF        floatToString_frac_part_L0+1, 1 
	RLCF        floatToString_frac_part_L0+2, 1 
	RLCF        floatToString_frac_part_L0+3, 1 
	ADDLW       255
	GOTO        L__floatToString48
L__floatToString49:
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+0, 1 
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+1, 1 
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+2, 1 
	MOVLW       0
	ANDWF       floatToString_frac_part_L0+3, 1 
;NumberToString.c,62 :: 		}
	GOTO        L_floatToString18
L_floatToString17:
;NumberToString.c,64 :: 		frac_part = (mantissa & 0xFFFFFF) >> -(exponent + 1);
	MOVLW       255
	ANDWF       floatToString_mantissa_L0+0, 0 
	MOVWF       floatToString_frac_part_L0+0 
	MOVLW       255
	ANDWF       floatToString_mantissa_L0+1, 0 
	MOVWF       floatToString_frac_part_L0+1 
	MOVLW       255
	ANDWF       floatToString_mantissa_L0+2, 0 
	MOVWF       floatToString_frac_part_L0+2 
	MOVLW       0
	ANDWF       floatToString_mantissa_L0+3, 0 
	MOVWF       floatToString_frac_part_L0+3 
	MOVF        floatToString_exponent_L0+0, 0 
	ADDLW       1
	MOVWF       R0 
	CLRF        R1 
	MOVLW       0
	BTFSC       floatToString_exponent_L0+0, 7 
	MOVLW       255
	ADDWFC      R1, 1 
	MOVF        R0, 0 
	SUBLW       0
	MOVWF       R0 
	MOVF        R1, 0 
	MOVWF       R1 
	MOVLW       0
	SUBFWB      R1, 1 
	MOVF        R0, 0 
L__floatToString50:
	BZ          L__floatToString51
	RRCF        floatToString_frac_part_L0+3, 1 
	RRCF        floatToString_frac_part_L0+2, 1 
	RRCF        floatToString_frac_part_L0+1, 1 
	RRCF        floatToString_frac_part_L0+0, 1 
	BCF         floatToString_frac_part_L0+3, 7 
	BTFSC       floatToString_frac_part_L0+3, 6 
	BSF         floatToString_frac_part_L0+3, 7 
	ADDLW       255
	GOTO        L__floatToString50
L__floatToString51:
;NumberToString.c,65 :: 		}
L_floatToString18:
L_floatToString16:
;NumberToString.c,69 :: 		result_ptr = result;
	MOVLW       floatToString_result_L0+0
	MOVWF       floatToString_result_ptr_L0+0 
	MOVLW       hi_addr(floatToString_result_L0+0)
	MOVWF       floatToString_result_ptr_L0+1 
;NumberToString.c,70 :: 		if(_value.raw_value & 0x800000) *result_ptr++ = '-';
	BTFSS       floatToString__value_L0+2, 7 
	GOTO        L_floatToString19
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVLW       45
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
L_floatToString19:
;NumberToString.c,73 :: 		if(int_part == 0) {
	MOVLW       0
	MOVWF       R0 
	XORWF       floatToString_int_part_L0+3, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString52
	MOVF        R0, 0 
	XORWF       floatToString_int_part_L0+2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString52
	MOVF        R0, 0 
	XORWF       floatToString_int_part_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString52
	MOVF        floatToString_int_part_L0+0, 0 
	XORLW       0
L__floatToString52:
	BTFSS       STATUS+0, 2 
	GOTO        L_floatToString20
;NumberToString.c,74 :: 		*result_ptr++ = '0';
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVLW       48
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
;NumberToString.c,75 :: 		}
	GOTO        L_floatToString21
L_floatToString20:
;NumberToString.c,77 :: 		str_ptr = intToString(int_part, 10);
	MOVF        floatToString_int_part_L0+0, 0 
	MOVWF       FARG_intToString_value+0 
	MOVF        floatToString_int_part_L0+1, 0 
	MOVWF       FARG_intToString_value+1 
	MOVF        floatToString_int_part_L0+2, 0 
	MOVWF       FARG_intToString_value+2 
	MOVF        floatToString_int_part_L0+3, 0 
	MOVWF       FARG_intToString_value+3 
	MOVLW       10
	MOVWF       FARG_intToString_base+0 
	CALL        _intToString+0, 0
	MOVF        R0, 0 
	MOVWF       floatToString_str_ptr_L0+0 
	MOVF        R1, 0 
	MOVWF       floatToString_str_ptr_L0+1 
;NumberToString.c,78 :: 		while(*str_ptr)
L_floatToString22:
	MOVFF       floatToString_str_ptr_L0+0, FSR0
	MOVFF       floatToString_str_ptr_L0+1, FSR0H
	MOVF        POSTINC0+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_floatToString23
;NumberToString.c,79 :: 		*result_ptr++ = *str_ptr++;
	MOVFF       floatToString_str_ptr_L0+0, FSR0
	MOVFF       floatToString_str_ptr_L0+1, FSR0H
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVF        POSTINC0+0, 0 
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
	INFSNZ      floatToString_str_ptr_L0+0, 1 
	INCF        floatToString_str_ptr_L0+1, 1 
	GOTO        L_floatToString22
L_floatToString23:
;NumberToString.c,80 :: 		}
L_floatToString21:
;NumberToString.c,83 :: 		*result_ptr++ = '.';
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVLW       46
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
;NumberToString.c,84 :: 		if(frac_part == 0) {
	MOVLW       0
	MOVWF       R0 
	XORWF       floatToString_frac_part_L0+3, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString53
	MOVF        R0, 0 
	XORWF       floatToString_frac_part_L0+2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString53
	MOVF        R0, 0 
	XORWF       floatToString_frac_part_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__floatToString53
	MOVF        floatToString_frac_part_L0+0, 0 
	XORLW       0
L__floatToString53:
	BTFSS       STATUS+0, 2 
	GOTO        L_floatToString24
;NumberToString.c,85 :: 		*result_ptr++ = '0';
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVLW       48
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
;NumberToString.c,86 :: 		}
	GOTO        L_floatToString25
L_floatToString24:
;NumberToString.c,88 :: 		max_length = precision ? precision : (sizeof(result) - (result_ptr - result) - 1);
	MOVF        FARG_floatToString_precision+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_floatToString26
	MOVF        FARG_floatToString_precision+0, 0 
	MOVWF       R2 
	MOVLW       0
	MOVWF       R3 
	GOTO        L_floatToString27
L_floatToString26:
	MOVLW       floatToString_result_L0+0
	SUBWF       floatToString_result_ptr_L0+0, 0 
	MOVWF       R0 
	MOVLW       hi_addr(floatToString_result_L0+0)
	SUBWFB      floatToString_result_ptr_L0+1, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	SUBLW       15
	MOVWF       R0 
	DECF        R0, 1 
	MOVF        R0, 0 
	MOVWF       R2 
	MOVLW       0
	MOVWF       R3 
L_floatToString27:
	MOVF        R2, 0 
	MOVWF       floatToString_max_length_L0+0 
;NumberToString.c,89 :: 		if(max_length > 7) max_length = 7;
	MOVF        R2, 0 
	SUBLW       7
	BTFSC       STATUS+0, 0 
	GOTO        L_floatToString28
	MOVLW       7
	MOVWF       floatToString_max_length_L0+0 
L_floatToString28:
;NumberToString.c,93 :: 		for(length = 0; length < max_length; length++) {
	CLRF        floatToString_length_L0+0 
L_floatToString29:
	MOVF        floatToString_max_length_L0+0, 0 
	SUBWF       floatToString_length_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_floatToString30
;NumberToString.c,94 :: 		frac_part = (frac_part << 3) + (frac_part << 1);
	MOVLW       3
	MOVWF       R0 
	MOVF        floatToString_frac_part_L0+0, 0 
	MOVWF       R5 
	MOVF        floatToString_frac_part_L0+1, 0 
	MOVWF       R6 
	MOVF        floatToString_frac_part_L0+2, 0 
	MOVWF       R7 
	MOVF        floatToString_frac_part_L0+3, 0 
	MOVWF       R8 
	MOVF        R0, 0 
L__floatToString54:
	BZ          L__floatToString55
	RLCF        R5, 1 
	BCF         R5, 0 
	RLCF        R6, 1 
	RLCF        R7, 1 
	RLCF        R8, 1 
	ADDLW       255
	GOTO        L__floatToString54
L__floatToString55:
	MOVF        floatToString_frac_part_L0+0, 0 
	MOVWF       R0 
	MOVF        floatToString_frac_part_L0+1, 0 
	MOVWF       R1 
	MOVF        floatToString_frac_part_L0+2, 0 
	MOVWF       R2 
	MOVF        floatToString_frac_part_L0+3, 0 
	MOVWF       R3 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	MOVF        R0, 0 
	ADDWF       R5, 1 
	MOVF        R1, 0 
	ADDWFC      R6, 1 
	MOVF        R2, 0 
	ADDWFC      R7, 1 
	MOVF        R3, 0 
	ADDWFC      R8, 1 
	MOVF        R5, 0 
	MOVWF       floatToString_frac_part_L0+0 
	MOVF        R6, 0 
	MOVWF       floatToString_frac_part_L0+1 
	MOVF        R7, 0 
	MOVWF       floatToString_frac_part_L0+2 
	MOVF        R8, 0 
	MOVWF       floatToString_frac_part_L0+3 
;NumberToString.c,95 :: 		*result_ptr++ = (frac_part >> 24) + '0';
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       0
	BTFSC       R8, 7 
	MOVLW       255
	MOVWF       R3 
	MOVLW       48
	ADDWF       R0, 1 
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
;NumberToString.c,96 :: 		frac_part &= 0xFFFFFF;
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+0, 1 
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+1, 1 
	MOVLW       255
	ANDWF       floatToString_frac_part_L0+2, 1 
	MOVLW       0
	ANDWF       floatToString_frac_part_L0+3, 1 
;NumberToString.c,93 :: 		for(length = 0; length < max_length; length++) {
	INCF        floatToString_length_L0+0, 1 
;NumberToString.c,97 :: 		}
	GOTO        L_floatToString29
L_floatToString30:
;NumberToString.c,101 :: 		for(--result_ptr; result_ptr[0] == '0' && result_ptr[-1] != '.'; --result_ptr);
	MOVLW       1
	SUBWF       floatToString_result_ptr_L0+0, 1 
	MOVLW       0
	SUBWFB      floatToString_result_ptr_L0+1, 1 
L_floatToString32:
	MOVFF       floatToString_result_ptr_L0+0, FSR0
	MOVFF       floatToString_result_ptr_L0+1, FSR0H
	MOVF        POSTINC0+0, 0 
	XORLW       48
	BTFSS       STATUS+0, 2 
	GOTO        L_floatToString33
	MOVLW       255
	ADDWF       floatToString_result_ptr_L0+0, 0 
	MOVWF       FSR0 
	MOVLW       255
	ADDWFC      floatToString_result_ptr_L0+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	XORLW       46
	BTFSC       STATUS+0, 2 
	GOTO        L_floatToString33
L__floatToString39:
	MOVLW       1
	SUBWF       floatToString_result_ptr_L0+0, 1 
	MOVLW       0
	SUBWFB      floatToString_result_ptr_L0+1, 1 
	GOTO        L_floatToString32
L_floatToString33:
;NumberToString.c,102 :: 		++result_ptr;
	INFSNZ      floatToString_result_ptr_L0+0, 1 
	INCF        floatToString_result_ptr_L0+1, 1 
;NumberToString.c,103 :: 		}
L_floatToString25:
;NumberToString.c,107 :: 		*result_ptr = '\0';
	MOVFF       floatToString_result_ptr_L0+0, FSR1
	MOVFF       floatToString_result_ptr_L0+1, FSR1H
	CLRF        POSTINC1+0 
;NumberToString.c,108 :: 		return result;
	MOVLW       floatToString_result_L0+0
	MOVWF       R0 
	MOVLW       hi_addr(floatToString_result_L0+0)
	MOVWF       R1 
;NumberToString.c,109 :: 		}
L_end_floatToString:
	RETURN      0
; end of _floatToString
