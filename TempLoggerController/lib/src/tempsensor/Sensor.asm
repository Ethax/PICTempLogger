
_Sensor_initialize:

;Sensor.c,5 :: 		void Sensor_initialize(const float _vref) {
;Sensor.c,6 :: 		ANSELE = 0x02;                     // Configure RE1 pin as analog
	MOVLW       2
	MOVWF       ANSELE+0 
;Sensor.c,7 :: 		TRISE1_bit = 1;                    // Configure RE1 pin as input
	BSF         TRISE1_bit+0, BitPos(TRISE1_bit+0) 
;Sensor.c,9 :: 		ADC_Init();
	CALL        _ADC_Init+0, 0
;Sensor.c,10 :: 		VREF = _vref;
	MOVF        FARG_Sensor_initialize__vref+0, 0 
	MOVWF       _VREF+0 
	MOVF        FARG_Sensor_initialize__vref+1, 0 
	MOVWF       _VREF+1 
	MOVF        FARG_Sensor_initialize__vref+2, 0 
	MOVWF       _VREF+2 
	MOVF        FARG_Sensor_initialize__vref+3, 0 
	MOVWF       _VREF+3 
;Sensor.c,11 :: 		}
L_end_Sensor_initialize:
	RETURN      0
; end of _Sensor_initialize

_Sensor_getTemperature:

;Sensor.c,13 :: 		float Sensor_getTemperature() {
;Sensor.c,14 :: 		unsigned int temp_res = ADC_Get_Sample(6);     // Get 10-bit results of AD conversion
	MOVLW       6
	MOVWF       FARG_ADC_Get_Sample_channel+0 
	CALL        _ADC_Get_Sample+0, 0
;Sensor.c,15 :: 		return ((float)temp_res * VREF) / 10.240;  // Calculate temperature in Celsuis
	CALL        _Word2Double+0, 0
	MOVF        _VREF+0, 0 
	MOVWF       R4 
	MOVF        _VREF+1, 0 
	MOVWF       R5 
	MOVF        _VREF+2, 0 
	MOVWF       R6 
	MOVF        _VREF+3, 0 
	MOVWF       R7 
	CALL        _Mul_32x32_FP+0, 0
	MOVLW       10
	MOVWF       R4 
	MOVLW       215
	MOVWF       R5 
	MOVLW       35
	MOVWF       R6 
	MOVLW       130
	MOVWF       R7 
	CALL        _Div_32x32_FP+0, 0
;Sensor.c,18 :: 		}
L_end_Sensor_getTemperature:
	RETURN      0
; end of _Sensor_getTemperature
