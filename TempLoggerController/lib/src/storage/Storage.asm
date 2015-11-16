
_Storage_initialize:

;Storage.c,24 :: 		void Storage_initialize() {
;Storage.c,25 :: 		ExternalEEPROM_initialize(0x01);
	MOVLW       1
	MOVWF       FARG_ExternalEEPROM_initialize_i2c_address+0 
	CALL        _ExternalEEPROM_initialize+0, 0
;Storage.c,26 :: 		if(Storage_getStoredSettings())
	CALL        _Storage_getStoredSettings+0, 0
	MOVF        R0, 0 
	IORWF       R1, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_Storage_initialize0
;Storage.c,27 :: 		Storage_settingsLoadedEvent();
	CALL        _Storage_settingsLoadedEvent+0, 0
L_Storage_initialize0:
;Storage.c,28 :: 		}
L_end_Storage_initialize:
	RETURN      0
; end of _Storage_initialize

_Storage_getStoredSettings:

;Storage.c,34 :: 		StorableData* Storage_getStoredSettings() {
;Storage.c,39 :: 		if(!isLoadedAlready) {
	MOVF        _isLoadedAlready+0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_Storage_getStoredSettings1
;Storage.c,40 :: 		checksum = ExternalEEPROM_readSequence(0x00, &systemSettings, sizeof(StorableData));
	CLRF        FARG_ExternalEEPROM_readSequence_address+0 
	MOVLW       _systemSettings+0
	MOVWF       FARG_ExternalEEPROM_readSequence__data+0 
	MOVLW       hi_addr(_systemSettings+0)
	MOVWF       FARG_ExternalEEPROM_readSequence__data+1 
	MOVLW       12
	MOVWF       FARG_ExternalEEPROM_readSequence_length+0 
	CALL        _ExternalEEPROM_readSequence+0, 0
	MOVF        R0, 0 
	MOVWF       Storage_getStoredSettings_checksum_L0+0 
;Storage.c,41 :: 		Delay_ms(5);
	MOVLW       13
	MOVWF       R12, 0
	MOVLW       251
	MOVWF       R13, 0
L_Storage_getStoredSettings2:
	DECFSZ      R13, 1, 1
	BRA         L_Storage_getStoredSettings2
	DECFSZ      R12, 1, 1
	BRA         L_Storage_getStoredSettings2
	NOP
	NOP
;Storage.c,42 :: 		if(checksum == ExternalEEPROM_read(sizeof(StorableData)))
	MOVLW       12
	MOVWF       FARG_ExternalEEPROM_read_address+0 
	CALL        _ExternalEEPROM_read+0, 0
	MOVF        Storage_getStoredSettings_checksum_L0+0, 0 
	XORWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Storage_getStoredSettings3
;Storage.c,43 :: 		isLoadedAlready = true;
	MOVLW       1
	MOVWF       _isLoadedAlready+0 
	GOTO        L_Storage_getStoredSettings4
L_Storage_getStoredSettings3:
;Storage.c,45 :: 		return 0;
	CLRF        R0 
	CLRF        R1 
	GOTO        L_end_Storage_getStoredSettings
L_Storage_getStoredSettings4:
;Storage.c,46 :: 		}
L_Storage_getStoredSettings1:
;Storage.c,50 :: 		logBegin = systemSettings.logBegin;
	MOVF        _systemSettings+10, 0 
	MOVWF       _logBegin+0 
;Storage.c,51 :: 		logEnd = systemSettings.logEnd;
	MOVF        _systemSettings+11, 0 
	MOVWF       _logEnd+0 
;Storage.c,52 :: 		return &systemSettings;
	MOVLW       _systemSettings+0
	MOVWF       R0 
	MOVLW       hi_addr(_systemSettings+0)
	MOVWF       R1 
;Storage.c,53 :: 		}
L_end_Storage_getStoredSettings:
	RETURN      0
; end of _Storage_getStoredSettings

_Storage_storeSettings:

;Storage.c,59 :: 		void Storage_storeSettings(PICTime* _systemTime, float _threshold) {
;Storage.c,63 :: 		memcpy(&systemSettings.systemTime, _systemTime, sizeof(PICTime));
	MOVLW       _systemSettings+0
	MOVWF       FARG_memcpy_d1+0 
	MOVLW       hi_addr(_systemSettings+0)
	MOVWF       FARG_memcpy_d1+1 
	MOVF        FARG_Storage_storeSettings__systemTime+0, 0 
	MOVWF       FARG_memcpy_s1+0 
	MOVF        FARG_Storage_storeSettings__systemTime+1, 0 
	MOVWF       FARG_memcpy_s1+1 
	MOVLW       6
	MOVWF       FARG_memcpy_n+0 
	MOVLW       0
	MOVWF       FARG_memcpy_n+1 
	CALL        _memcpy+0, 0
;Storage.c,64 :: 		systemSettings.threshold = _threshold;
	MOVF        FARG_Storage_storeSettings__threshold+0, 0 
	MOVWF       _systemSettings+6 
	MOVF        FARG_Storage_storeSettings__threshold+1, 0 
	MOVWF       _systemSettings+7 
	MOVF        FARG_Storage_storeSettings__threshold+2, 0 
	MOVWF       _systemSettings+8 
	MOVF        FARG_Storage_storeSettings__threshold+3, 0 
	MOVWF       _systemSettings+9 
;Storage.c,65 :: 		systemSettings.logBegin = logBegin;
	MOVF        _logBegin+0, 0 
	MOVWF       _systemSettings+10 
;Storage.c,66 :: 		systemSettings.logEnd = logEnd;
	MOVF        _logEnd+0, 0 
	MOVWF       _systemSettings+11 
;Storage.c,70 :: 		isLoadedAlready = false;
	CLRF        _isLoadedAlready+0 
;Storage.c,71 :: 		checksum = ExternalEEPROM_writeRow(0x00, &systemSettings, sizeof(StorableData));
	CLRF        FARG_ExternalEEPROM_writeRow_address+0 
	MOVLW       _systemSettings+0
	MOVWF       FARG_ExternalEEPROM_writeRow__data+0 
	MOVLW       hi_addr(_systemSettings+0)
	MOVWF       FARG_ExternalEEPROM_writeRow__data+1 
	MOVLW       12
	MOVWF       FARG_ExternalEEPROM_writeRow_length+0 
	CALL        _ExternalEEPROM_writeRow+0, 0
	MOVF        R0, 0 
	MOVWF       Storage_storeSettings_checksum_L0+0 
;Storage.c,72 :: 		Delay_ms(5);
	MOVLW       13
	MOVWF       R12, 0
	MOVLW       251
	MOVWF       R13, 0
L_Storage_storeSettings5:
	DECFSZ      R13, 1, 1
	BRA         L_Storage_storeSettings5
	DECFSZ      R12, 1, 1
	BRA         L_Storage_storeSettings5
	NOP
	NOP
;Storage.c,73 :: 		ExternalEEPROM_write(sizeof(StorableData), checksum);
	MOVLW       12
	MOVWF       FARG_ExternalEEPROM_write_address+0 
	MOVF        Storage_storeSettings_checksum_L0+0, 0 
	MOVWF       FARG_ExternalEEPROM_write__data+0 
	CALL        _ExternalEEPROM_write+0, 0
;Storage.c,74 :: 		}
L_end_Storage_storeSettings:
	RETURN      0
; end of _Storage_storeSettings

_Storage_writeLog:

;Storage.c,79 :: 		void Storage_writeLog(PICTime* timeStamp, float value) {
;Storage.c,84 :: 		memcpy(&new_log.timeStamp, timeStamp, sizeof(PICTime));
	MOVLW       Storage_writeLog_new_log_L0+0
	MOVWF       FARG_memcpy_d1+0 
	MOVLW       hi_addr(Storage_writeLog_new_log_L0+0)
	MOVWF       FARG_memcpy_d1+1 
	MOVF        FARG_Storage_writeLog_timeStamp+0, 0 
	MOVWF       FARG_memcpy_s1+0 
	MOVF        FARG_Storage_writeLog_timeStamp+1, 0 
	MOVWF       FARG_memcpy_s1+1 
	MOVLW       6
	MOVWF       FARG_memcpy_n+0 
	MOVLW       0
	MOVWF       FARG_memcpy_n+1 
	CALL        _memcpy+0, 0
;Storage.c,85 :: 		new_log.value = value;
	MOVF        FARG_Storage_writeLog_value+0, 0 
	MOVWF       Storage_writeLog_new_log_L0+6 
	MOVF        FARG_Storage_writeLog_value+1, 0 
	MOVWF       Storage_writeLog_new_log_L0+7 
	MOVF        FARG_Storage_writeLog_value+2, 0 
	MOVWF       Storage_writeLog_new_log_L0+8 
	MOVF        FARG_Storage_writeLog_value+3, 0 
	MOVWF       Storage_writeLog_new_log_L0+9 
;Storage.c,86 :: 		ExternalEEPROM_writeRow(logEnd, &new_log, sizeof(LogEntry));
	MOVF        _logEnd+0, 0 
	MOVWF       FARG_ExternalEEPROM_writeRow_address+0 
	MOVLW       Storage_writeLog_new_log_L0+0
	MOVWF       FARG_ExternalEEPROM_writeRow__data+0 
	MOVLW       hi_addr(Storage_writeLog_new_log_L0+0)
	MOVWF       FARG_ExternalEEPROM_writeRow__data+1 
	MOVLW       10
	MOVWF       FARG_ExternalEEPROM_writeRow_length+0 
	CALL        _ExternalEEPROM_writeRow+0, 0
;Storage.c,90 :: 		logEnd = ((logEnd & 0xF0) % (LOG_SIZE << 4)) + 0x10;
	MOVLW       240
	ANDWF       _logEnd+0, 0 
	MOVWF       R0 
	MOVLW       240
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       16
	ADDWF       R0, 0 
	MOVWF       R1 
	MOVF        R1, 0 
	MOVWF       _logEnd+0 
;Storage.c,91 :: 		if(logBegin == logEnd)
	MOVF        _logBegin+0, 0 
	XORWF       R1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Storage_writeLog6
;Storage.c,92 :: 		logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;
	MOVLW       240
	ANDWF       _logBegin+0, 0 
	MOVWF       R0 
	MOVLW       240
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       16
	ADDWF       R0, 0 
	MOVWF       _logBegin+0 
L_Storage_writeLog6:
;Storage.c,93 :: 		}
L_end_Storage_writeLog:
	RETURN      0
; end of _Storage_writeLog

_Storage_readEarliestLog:

;Storage.c,99 :: 		LogEntry* Storage_readEarliestLog() {
;Storage.c,103 :: 		if(logBegin == logEnd) return 0;
	MOVF        _logBegin+0, 0 
	XORWF       _logEnd+0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L_Storage_readEarliestLog7
	CLRF        R0 
	CLRF        R1 
	GOTO        L_end_Storage_readEarliestLog
L_Storage_readEarliestLog7:
;Storage.c,107 :: 		ExternalEEPROM_readSequence(logBegin, &read_log, sizeof(LogEntry));
	MOVF        _logBegin+0, 0 
	MOVWF       FARG_ExternalEEPROM_readSequence_address+0 
	MOVLW       Storage_readEarliestLog_read_log_L0+0
	MOVWF       FARG_ExternalEEPROM_readSequence__data+0 
	MOVLW       hi_addr(Storage_readEarliestLog_read_log_L0+0)
	MOVWF       FARG_ExternalEEPROM_readSequence__data+1 
	MOVLW       10
	MOVWF       FARG_ExternalEEPROM_readSequence_length+0 
	CALL        _ExternalEEPROM_readSequence+0, 0
;Storage.c,108 :: 		logBegin = ((logBegin & 0xF0) % (LOG_SIZE << 4)) + 0x10;
	MOVLW       240
	ANDWF       _logBegin+0, 0 
	MOVWF       R0 
	MOVLW       240
	MOVWF       R4 
	CALL        _Div_8x8_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVLW       16
	ADDWF       R0, 0 
	MOVWF       _logBegin+0 
;Storage.c,111 :: 		return &read_log;
	MOVLW       Storage_readEarliestLog_read_log_L0+0
	MOVWF       R0 
	MOVLW       hi_addr(Storage_readEarliestLog_read_log_L0+0)
	MOVWF       R1 
;Storage.c,112 :: 		}
L_end_Storage_readEarliestLog:
	RETURN      0
; end of _Storage_readEarliestLog
