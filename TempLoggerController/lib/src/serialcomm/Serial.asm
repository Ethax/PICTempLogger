
_Serial_initialize:

;Serial.c,25 :: 		void Serial_initialize(enum BaudRate baudrate) {
;Serial.c,28 :: 		switch(baudrate) {
	GOTO        L_Serial_initialize0
;Serial.c,29 :: 		case BAUD_1200:
L_Serial_initialize2:
;Serial.c,30 :: 		UART1_Init(1200); break;
	BSF         BAUDCON+0, 3, 0
	MOVLW       6
	MOVWF       SPBRGH+0 
	MOVLW       130
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,31 :: 		case BAUD_2400:
L_Serial_initialize3:
;Serial.c,32 :: 		UART1_Init(2400); break;
	BSF         BAUDCON+0, 3, 0
	MOVLW       3
	MOVWF       SPBRGH+0 
	MOVLW       64
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,33 :: 		case BAUD_4800:
L_Serial_initialize4:
;Serial.c,34 :: 		UART1_Init(4800); break;
	BSF         BAUDCON+0, 3, 0
	MOVLW       1
	MOVWF       SPBRGH+0 
	MOVLW       160
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,35 :: 		case BAUD_9600:
L_Serial_initialize5:
;Serial.c,36 :: 		UART1_Init(9600); break;
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       207
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,37 :: 		case BAUD_19200:
L_Serial_initialize6:
;Serial.c,38 :: 		UART1_Init(19200); break;
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       103
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,39 :: 		case BAUD_38400:
L_Serial_initialize7:
;Serial.c,40 :: 		UART1_Init(38400); break;
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       51
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,41 :: 		case BAUD_57600:
L_Serial_initialize8:
;Serial.c,42 :: 		UART1_Init(57600); break;
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       34
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,43 :: 		case BAUD_115200:
L_Serial_initialize9:
;Serial.c,44 :: 		UART1_Init(115200); break;
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       16
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
	GOTO        L_Serial_initialize1
;Serial.c,45 :: 		}
L_Serial_initialize0:
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       0
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize2
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       1
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize3
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       2
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize4
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       3
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize5
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       4
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize6
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       5
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize7
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       6
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize8
	MOVF        FARG_Serial_initialize_baudrate+0, 0 
	XORLW       7
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_initialize9
L_Serial_initialize1:
;Serial.c,48 :: 		RC1IF_bit = false;
	BCF         RC1IF_bit+0, BitPos(RC1IF_bit+0) 
;Serial.c,49 :: 		RC1IE_bit = true;
	BSF         RC1IE_bit+0, BitPos(RC1IE_bit+0) 
;Serial.c,50 :: 		}
L_end_Serial_initialize:
	RETURN      0
; end of _Serial_initialize

_Serial_handleInterrupt:

;Serial.c,56 :: 		void Serial_handleInterrupt() {
;Serial.c,58 :: 		uint8_t next_byte = UART1_Read();
	CALL        _UART1_Read+0, 0
	MOVF        R0, 0 
	MOVWF       Serial_handleInterrupt_next_byte_L0+0 
;Serial.c,63 :: 		if(next_byte == '\n') {
	MOVF        R0, 0 
	XORLW       10
	BTFSS       STATUS+0, 2 
	GOTO        L_Serial_handleInterrupt10
;Serial.c,64 :: 		switch(receiveBuffer[0]) {
	GOTO        L_Serial_handleInterrupt11
;Serial.c,65 :: 		case 'T': /* Time Setting */
L_Serial_handleInterrupt13:
;Serial.c,66 :: 		Application_dispatchEvent(Serial_receivedTimeSettingEvent);
	MOVLW       _Serial_receivedTimeSettingEvent+0
	MOVWF       FARG_Application_dispatchEvent_handler+0 
	MOVLW       hi_addr(_Serial_receivedTimeSettingEvent+0)
	MOVWF       FARG_Application_dispatchEvent_handler+1 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+2 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+3 
	CALL        _Application_dispatchEvent+0, 0
;Serial.c,67 :: 		break;
	GOTO        L_Serial_handleInterrupt12
;Serial.c,68 :: 		case 'R': /* Threshold Setting */
L_Serial_handleInterrupt14:
;Serial.c,69 :: 		Application_dispatchEvent(Serial_receivedThresholdSettingEvent);
	MOVLW       _Serial_receivedThresholdSettingEvent+0
	MOVWF       FARG_Application_dispatchEvent_handler+0 
	MOVLW       hi_addr(_Serial_receivedThresholdSettingEvent+0)
	MOVWF       FARG_Application_dispatchEvent_handler+1 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+2 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+3 
	CALL        _Application_dispatchEvent+0, 0
;Serial.c,70 :: 		break;
	GOTO        L_Serial_handleInterrupt12
;Serial.c,71 :: 		case 'L': /* Log Request */
L_Serial_handleInterrupt15:
;Serial.c,72 :: 		Application_dispatchEvent(Serial_receivedLogRequestEvent);
	MOVLW       _Serial_receivedLogRequestEvent+0
	MOVWF       FARG_Application_dispatchEvent_handler+0 
	MOVLW       hi_addr(_Serial_receivedLogRequestEvent+0)
	MOVWF       FARG_Application_dispatchEvent_handler+1 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+2 
	MOVLW       0
	MOVWF       FARG_Application_dispatchEvent_handler+3 
	CALL        _Application_dispatchEvent+0, 0
;Serial.c,73 :: 		break;
	GOTO        L_Serial_handleInterrupt12
;Serial.c,74 :: 		}
L_Serial_handleInterrupt11:
	MOVF        _receiveBuffer+0, 0 
	XORLW       84
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_handleInterrupt13
	MOVF        _receiveBuffer+0, 0 
	XORLW       82
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_handleInterrupt14
	MOVF        _receiveBuffer+0, 0 
	XORLW       76
	BTFSC       STATUS+0, 2 
	GOTO        L_Serial_handleInterrupt15
L_Serial_handleInterrupt12:
;Serial.c,75 :: 		receiveCounter = 0;
	CLRF        _receiveCounter+0 
;Serial.c,76 :: 		}
	GOTO        L_Serial_handleInterrupt16
L_Serial_handleInterrupt10:
;Serial.c,81 :: 		receiveBuffer[receiveCounter++] = next_byte;
	MOVLW       _receiveBuffer+0
	MOVWF       FSR1 
	MOVLW       hi_addr(_receiveBuffer+0)
	MOVWF       FSR1H 
	MOVF        _receiveCounter+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVF        Serial_handleInterrupt_next_byte_L0+0, 0 
	MOVWF       POSTINC1+0 
	INCF        _receiveCounter+0, 1 
;Serial.c,82 :: 		}
L_Serial_handleInterrupt16:
;Serial.c,85 :: 		RC1IF_bit = false;
	BCF         RC1IF_bit+0, BitPos(RC1IF_bit+0) 
;Serial.c,86 :: 		}
L_end_Serial_handleInterrupt:
	RETURN      0
; end of _Serial_handleInterrupt

_Serial_getReceivedData:

;Serial.c,91 :: 		void* Serial_getReceivedData() {
;Serial.c,92 :: 		return (void*)&receiveBuffer[1];
	MOVLW       _receiveBuffer+1
	MOVWF       R0 
	MOVLW       hi_addr(_receiveBuffer+1)
	MOVWF       R1 
;Serial.c,93 :: 		}
L_end_Serial_getReceivedData:
	RETURN      0
; end of _Serial_getReceivedData

_Serial_sendLogEntry:

;Serial.c,98 :: 		void Serial_sendLogEntry(LogEntry* entry) {
;Serial.c,103 :: 		memcpy(transmitBuffer, entry, sizeof(LogEntry));
	MOVLW       _transmitBuffer+0
	MOVWF       FARG_memcpy_d1+0 
	MOVLW       hi_addr(_transmitBuffer+0)
	MOVWF       FARG_memcpy_d1+1 
	MOVF        FARG_Serial_sendLogEntry_entry+0, 0 
	MOVWF       FARG_memcpy_s1+0 
	MOVF        FARG_Serial_sendLogEntry_entry+1, 0 
	MOVWF       FARG_memcpy_s1+1 
	MOVLW       10
	MOVWF       FARG_memcpy_n+0 
	MOVLW       0
	MOVWF       FARG_memcpy_n+1 
	CALL        _memcpy+0, 0
;Serial.c,104 :: 		for(i = 0; i < sizeof(LogEntry); i++)
	CLRF        Serial_sendLogEntry_i_L0+0 
L_Serial_sendLogEntry17:
	MOVLW       10
	SUBWF       Serial_sendLogEntry_i_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_Serial_sendLogEntry18
;Serial.c,105 :: 		UART1_Write(transmitBuffer[i]);
	MOVLW       _transmitBuffer+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_transmitBuffer+0)
	MOVWF       FSR0H 
	MOVF        Serial_sendLogEntry_i_L0+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Serial.c,104 :: 		for(i = 0; i < sizeof(LogEntry); i++)
	INCF        Serial_sendLogEntry_i_L0+0, 1 
;Serial.c,105 :: 		UART1_Write(transmitBuffer[i]);
	GOTO        L_Serial_sendLogEntry17
L_Serial_sendLogEntry18:
;Serial.c,109 :: 		UART1_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Serial.c,110 :: 		}
L_end_Serial_sendLogEntry:
	RETURN      0
; end of _Serial_sendLogEntry

_Serial_sendAcknowledgement:

;Serial.c,115 :: 		void Serial_sendAcknowledgement() {
;Serial.c,117 :: 		UART1_Write('A'); UART1_Write('C'); UART1_Write('K');
	MOVLW       65
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
	MOVLW       67
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
	MOVLW       75
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Serial.c,121 :: 		UART1_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Serial.c,122 :: 		}
L_end_Serial_sendAcknowledgement:
	RETURN      0
; end of _Serial_sendAcknowledgement
