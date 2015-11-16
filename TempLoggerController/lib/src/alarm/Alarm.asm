
_playTheImperialMarch:

;melody.h,130 :: 		void playTheImperialMarch() {
;melody.h,131 :: 		Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch0:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch0
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch0
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch0
;melody.h,132 :: 		Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch1:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch1
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch1
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch1
;melody.h,133 :: 		Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch2:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch2
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch2
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch2
;melody.h,134 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch3:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch3
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch3
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch3
;melody.h,135 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch4:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch4
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch4
	NOP
;melody.h,137 :: 		Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch5:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch5
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch5
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch5
;melody.h,138 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch6:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch6
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch6
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch6
;melody.h,139 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch7:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch7
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch7
	NOP
;melody.h,140 :: 		Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       238
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       8
	MOVWF       R11, 0
	MOVLW       159
	MOVWF       R12, 0
	MOVLW       159
	MOVWF       R13, 0
L_playTheImperialMarch8:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch8
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch8
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch8
;melody.h,142 :: 		Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch9:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch9
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch9
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch9
;melody.h,143 :: 		Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch10:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch10
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch10
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch10
;melody.h,144 :: 		Sound_Play(Tone_E6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch11:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch11
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch11
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch11
;melody.h,145 :: 		Sound_Play(Tone_F6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       116
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch12:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch12
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch12
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch12
;melody.h,146 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch13:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch13
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch13
	NOP
;melody.h,148 :: 		Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       62
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch14:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch14
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch14
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch14
;melody.h,149 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch15:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch15
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch15
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch15
;melody.h,150 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch16:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch16
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch16
	NOP
;melody.h,151 :: 		Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       238
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       8
	MOVWF       R11, 0
	MOVLW       159
	MOVWF       R12, 0
	MOVLW       159
	MOVWF       R13, 0
L_playTheImperialMarch17:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch17
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch17
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch17
;melody.h,153 :: 		Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       224
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch18:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch18
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch18
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch18
;melody.h,154 :: 		Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch19:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch19
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch19
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch19
;melody.h,155 :: 		Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch20:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch20
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch20
	NOP
;melody.h,156 :: 		Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       224
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch21:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch21
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch21
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch21
;melody.h,157 :: 		Sound_Play(Tone_Ab6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       125
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch22:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch22
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch22
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch22
;melody.h,158 :: 		Sound_Play(Tone_G6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       31
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch23:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch23
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch23
	NOP
;melody.h,160 :: 		Sound_Play(Tone_Gb6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       199
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch24:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch24
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch24
	NOP
;melody.h,161 :: 		Sound_Play(Tone_E6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch25:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch25
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch25
	NOP
;melody.h,162 :: 		Sound_Play(Tone_F6, Eighth); Delay_ms(1 + Eighth);
	MOVLW       116
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch26:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch26
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch26
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch26
	NOP
;melody.h,163 :: 		Delay_ms(1 + Eighth);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch27:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch27
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch27
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch27
	NOP
;melody.h,164 :: 		Sound_Play(Tone_Bb5, Eighth); Delay_ms(1 + Eighth);
	MOVLW       164
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch28:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch28
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch28
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch28
	NOP
;melody.h,165 :: 		Sound_Play(Tone_Eb6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       220
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch29:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch29
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch29
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch29
;melody.h,166 :: 		Sound_Play(Tone_D6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       150
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch30:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch30
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch30
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch30
;melody.h,167 :: 		Sound_Play(Tone_Db6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       84
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch31:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch31
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch31
	NOP
;melody.h,169 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch32:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch32
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch32
	NOP
;melody.h,170 :: 		Sound_Play(Tone_B5, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       219
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch33:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch33
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch33
	NOP
;melody.h,171 :: 		Sound_Play(Tone_C6, Eighth); Delay_ms(1 + Eighth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch34:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch34
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch34
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch34
	NOP
;melody.h,172 :: 		Delay_ms(1 + Eighth);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch35:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch35
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch35
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch35
	NOP
;melody.h,173 :: 		Sound_Play(Tone_F5, Eighth); Delay_ms(1 + Eighth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch36:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch36
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch36
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch36
	NOP
;melody.h,174 :: 		Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       62
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch37:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch37
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch37
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch37
;melody.h,175 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch38:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch38
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch38
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch38
;melody.h,176 :: 		Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch39:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch39
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch39
	NOP
;melody.h,178 :: 		Sound_Play(Tone_C6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch40:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch40
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch40
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch40
;melody.h,179 :: 		Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch41:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch41
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch41
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch41
;melody.h,180 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch42:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch42
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch42
	NOP
;melody.h,181 :: 		Sound_Play(Tone_E6, Half); Delay_ms(1 + Half);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       238
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       8
	MOVWF       R11, 0
	MOVLW       159
	MOVWF       R12, 0
	MOVLW       159
	MOVWF       R13, 0
L_playTheImperialMarch43:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch43
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch43
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch43
;melody.h,183 :: 		Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       224
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch44:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch44
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch44
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch44
;melody.h,184 :: 		Sound_Play(Tone_A5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch45:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch45
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch45
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch45
;melody.h,185 :: 		Sound_Play(Tone_A5, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch46:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch46
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch46
	NOP
;melody.h,186 :: 		Sound_Play(Tone_A6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       224
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch47:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch47
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch47
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch47
;melody.h,187 :: 		Sound_Play(Tone_Ab6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       125
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch48:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch48
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch48
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch48
;melody.h,188 :: 		Sound_Play(Tone_G6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       31
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       6
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch49:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch49
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch49
	NOP
;melody.h,190 :: 		Sound_Play(Tone_Gb6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       199
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch50:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch50
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch50
	NOP
;melody.h,191 :: 		Sound_Play(Tone_E6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       38
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch51:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch51
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch51
	NOP
;melody.h,192 :: 		Sound_Play(Tone_F6, Eighth); Delay_ms(1 + Eighth);
	MOVLW       116
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       5
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch52:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch52
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch52
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch52
	NOP
;melody.h,193 :: 		Delay_ms(1 + Eighth);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch53:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch53
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch53
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch53
	NOP
;melody.h,194 :: 		Sound_Play(Tone_Bb5, Eighth); Delay_ms(1 + Eighth);
	MOVLW       164
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch54:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch54
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch54
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch54
	NOP
;melody.h,195 :: 		Sound_Play(Tone_Eb6, Quarter); Delay_ms(1 + Quarter);
	MOVLW       220
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch55:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch55
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch55
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch55
;melody.h,196 :: 		Sound_Play(Tone_D6, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       150
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch56:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch56
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch56
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch56
;melody.h,197 :: 		Sound_Play(Tone_Db6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       84
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch57:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch57
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch57
	NOP
;melody.h,199 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch58:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch58
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch58
	NOP
;melody.h,200 :: 		Sound_Play(Tone_B5, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       219
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch59:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch59
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch59
	NOP
;melody.h,201 :: 		Sound_Play(Tone_C6, Eighth); Delay_ms(1 + Eighth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch60:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch60
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch60
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch60
	NOP
;melody.h,202 :: 		Delay_ms(1 + Eighth);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch61:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch61
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch61
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch61
	NOP
;melody.h,203 :: 		Sound_Play(Tone_F5, Eighth); Delay_ms(1 + Eighth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       187
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       233
	MOVWF       R12, 0
	MOVLW       76
	MOVWF       R13, 0
L_playTheImperialMarch62:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch62
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch62
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch62
	NOP
;melody.h,204 :: 		Sound_Play(Tone_Ab5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       62
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch63:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch63
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch63
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch63
;melody.h,205 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch64:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch64
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch64
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch64
;melody.h,206 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch65:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch65
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch65
	NOP
;melody.h,208 :: 		Sound_Play(Tone_A5, Quarter); Delay_ms(1 + Quarter);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       119
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       4
	MOVWF       R11, 0
	MOVLW       209
	MOVWF       R12, 0
	MOVLW       155
	MOVWF       R13, 0
L_playTheImperialMarch66:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch66
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch66
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch66
;melody.h,209 :: 		Sound_Play(Tone_F5, Eighth + Sixteenth); Delay_ms(1 + Eighth + Sixteenth);
	MOVLW       186
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       24
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       1
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       218
	MOVWF       R12, 0
	MOVLW       219
	MOVWF       R13, 0
L_playTheImperialMarch67:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch67
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch67
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch67
;melody.h,210 :: 		Sound_Play(Tone_C6, Sixteenth); Delay_ms(1 + Sixteenth);
	MOVLW       22
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       4
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       93
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       0
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       245
	MOVWF       R12, 0
	MOVLW       38
	MOVWF       R13, 0
L_playTheImperialMarch68:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch68
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch68
	NOP
;melody.h,211 :: 		Sound_Play(Tone_A5, Half); Delay_ms(1 + Half);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       238
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       2
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
	MOVLW       8
	MOVWF       R11, 0
	MOVLW       159
	MOVWF       R12, 0
	MOVLW       159
	MOVWF       R13, 0
L_playTheImperialMarch69:
	DECFSZ      R13, 1, 1
	BRA         L_playTheImperialMarch69
	DECFSZ      R12, 1, 1
	BRA         L_playTheImperialMarch69
	DECFSZ      R11, 1, 1
	BRA         L_playTheImperialMarch69
;melody.h,212 :: 		}
L_end_playTheImperialMarch:
	RETURN      0
; end of _playTheImperialMarch

_Alarm_initialize:

;Alarm.c,26 :: 		void Alarm_initialize() {
;Alarm.c,27 :: 		Sound_Init(&PORTC, 2);
	MOVLW       PORTC+0
	MOVWF       FARG_Sound_Init_snd_port+0 
	MOVLW       hi_addr(PORTC+0)
	MOVWF       FARG_Sound_Init_snd_port+1 
	MOVLW       2
	MOVWF       FARG_Sound_Init_snd_pin+0 
	CALL        _Sound_Init+0, 0
;Alarm.c,28 :: 		Alarm_beep();
	CALL        _Alarm_beep+0, 0
;Alarm.c,29 :: 		}
L_end_Alarm_initialize:
	RETURN      0
; end of _Alarm_initialize

_Alarm_setThreshold:

;Alarm.c,34 :: 		void Alarm_setThreshold(float _threshold) {
;Alarm.c,35 :: 		threshold = _threshold;
	MOVF        FARG_Alarm_setThreshold__threshold+0, 0 
	MOVWF       _threshold+0 
	MOVF        FARG_Alarm_setThreshold__threshold+1, 0 
	MOVWF       _threshold+1 
	MOVF        FARG_Alarm_setThreshold__threshold+2, 0 
	MOVWF       _threshold+2 
	MOVF        FARG_Alarm_setThreshold__threshold+3, 0 
	MOVWF       _threshold+3 
;Alarm.c,36 :: 		isThresholdSet = true;
	MOVLW       1
	MOVWF       _isThresholdSet+0 
;Alarm.c,37 :: 		}
L_end_Alarm_setThreshold:
	RETURN      0
; end of _Alarm_setThreshold

_Alarm_getThreshold:

;Alarm.c,42 :: 		float Alarm_getThreshold() {
;Alarm.c,43 :: 		return threshold;
	MOVF        _threshold+0, 0 
	MOVWF       R0 
	MOVF        _threshold+1, 0 
	MOVWF       R1 
	MOVF        _threshold+2, 0 
	MOVWF       R2 
	MOVF        _threshold+3, 0 
	MOVWF       R3 
;Alarm.c,44 :: 		}
L_end_Alarm_getThreshold:
	RETURN      0
; end of _Alarm_getThreshold

_Alarm_clearThreshold:

;Alarm.c,49 :: 		void Alarm_clearThreshold() {
;Alarm.c,50 :: 		threshold = 0.0f;
	CLRF        _threshold+0 
	CLRF        _threshold+1 
	CLRF        _threshold+2 
	CLRF        _threshold+3 
;Alarm.c,51 :: 		isThresholdSet = false;
	CLRF        _isThresholdSet+0 
;Alarm.c,52 :: 		}
L_end_Alarm_clearThreshold:
	RETURN      0
; end of _Alarm_clearThreshold

_Alarm_checkConditions:

;Alarm.c,58 :: 		void Alarm_checkConditions(float _temperature) {
;Alarm.c,61 :: 		if(!isThresholdSet) return;
	MOVF        _isThresholdSet+0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_Alarm_checkConditions70
	GOTO        L_end_Alarm_checkConditions
L_Alarm_checkConditions70:
;Alarm.c,66 :: 		if(_temperature > threshold && !isAlerted) {
	MOVF        FARG_Alarm_checkConditions__temperature+0, 0 
	MOVWF       R4 
	MOVF        FARG_Alarm_checkConditions__temperature+1, 0 
	MOVWF       R5 
	MOVF        FARG_Alarm_checkConditions__temperature+2, 0 
	MOVWF       R6 
	MOVF        FARG_Alarm_checkConditions__temperature+3, 0 
	MOVWF       R7 
	MOVF        _threshold+0, 0 
	MOVWF       R0 
	MOVF        _threshold+1, 0 
	MOVWF       R1 
	MOVF        _threshold+2, 0 
	MOVWF       R2 
	MOVF        _threshold+3, 0 
	MOVWF       R3 
	CALL        _Compare_Double+0, 0
	MOVLW       1
	BTFSC       STATUS+0, 0 
	MOVLW       0
	MOVWF       R0 
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_Alarm_checkConditions73
	MOVF        _isAlerted+0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_Alarm_checkConditions73
L__Alarm_checkConditions79:
;Alarm.c,67 :: 		isAlerted = true;
	MOVLW       1
	MOVWF       _isAlerted+0 
;Alarm.c,68 :: 		Alarm_thresholdExceededEvent();
	CALL        _Alarm_thresholdExceededEvent+0, 0
;Alarm.c,69 :: 		}
	GOTO        L_Alarm_checkConditions74
L_Alarm_checkConditions73:
;Alarm.c,70 :: 		else if(_temperature <= threshold && isAlerted) {
	MOVF        FARG_Alarm_checkConditions__temperature+0, 0 
	MOVWF       R4 
	MOVF        FARG_Alarm_checkConditions__temperature+1, 0 
	MOVWF       R5 
	MOVF        FARG_Alarm_checkConditions__temperature+2, 0 
	MOVWF       R6 
	MOVF        FARG_Alarm_checkConditions__temperature+3, 0 
	MOVWF       R7 
	MOVF        _threshold+0, 0 
	MOVWF       R0 
	MOVF        _threshold+1, 0 
	MOVWF       R1 
	MOVF        _threshold+2, 0 
	MOVWF       R2 
	MOVF        _threshold+3, 0 
	MOVWF       R3 
	CALL        _Compare_Double+0, 0
	MOVLW       0
	BTFSC       STATUS+0, 0 
	MOVLW       1
	MOVWF       R0 
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_Alarm_checkConditions77
	MOVF        _isAlerted+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_Alarm_checkConditions77
L__Alarm_checkConditions78:
;Alarm.c,71 :: 		isAlerted = false;
	CLRF        _isAlerted+0 
;Alarm.c,72 :: 		}
L_Alarm_checkConditions77:
L_Alarm_checkConditions74:
;Alarm.c,73 :: 		}
L_end_Alarm_checkConditions:
	RETURN      0
; end of _Alarm_checkConditions

_Alarm_playAlarmSound:

;Alarm.c,78 :: 		void Alarm_playAlarmSound() {
;Alarm.c,79 :: 		playTheImperialMarch();
	CALL        _playTheImperialMarch+0, 0
;Alarm.c,80 :: 		}
L_end_Alarm_playAlarmSound:
	RETURN      0
; end of _Alarm_playAlarmSound

_Alarm_beep:

;Alarm.c,85 :: 		void Alarm_beep() {
;Alarm.c,86 :: 		Sound_Play(880, 1000);
	MOVLW       112
	MOVWF       FARG_Sound_Play_freq_in_hz+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_freq_in_hz+1 
	MOVLW       232
	MOVWF       FARG_Sound_Play_duration_ms+0 
	MOVLW       3
	MOVWF       FARG_Sound_Play_duration_ms+1 
	CALL        _Sound_Play+0, 0
;Alarm.c,87 :: 		}
L_end_Alarm_beep:
	RETURN      0
; end of _Alarm_beep
