
_calculateChecksum:

;ExternalEEPROM.c,13 :: 		void calculateChecksum(unsigned char* checksum_ptr, unsigned char value) {
;ExternalEEPROM.c,15 :: 		for(i = 8; i; i--) {
	MOVLW       8
	MOVWF       R3 
L_calculateChecksum0:
	MOVF        R3, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_calculateChecksum1
;ExternalEEPROM.c,16 :: 		if((*checksum_ptr ^ value) & 0x80)
	MOVFF       FARG_calculateChecksum_checksum_ptr+0, FSR0
	MOVFF       FARG_calculateChecksum_checksum_ptr+1, FSR0H
	MOVF        FARG_calculateChecksum_value+0, 0 
	XORWF       POSTINC0+0, 0 
	MOVWF       R1 
	BTFSS       R1, 7 
	GOTO        L_calculateChecksum3
;ExternalEEPROM.c,17 :: 		*checksum_ptr = (*checksum_ptr << 1) ^ 0x31;
	MOVFF       FARG_calculateChecksum_checksum_ptr+0, FSR0
	MOVFF       FARG_calculateChecksum_checksum_ptr+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        R2, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVFF       FARG_calculateChecksum_checksum_ptr+0, FSR1
	MOVFF       FARG_calculateChecksum_checksum_ptr+1, FSR1H
	MOVLW       49
	XORWF       R0, 0 
	MOVWF       POSTINC1+0 
	GOTO        L_calculateChecksum4
L_calculateChecksum3:
;ExternalEEPROM.c,19 :: 		*checksum_ptr <<= 1;
	MOVFF       FARG_calculateChecksum_checksum_ptr+0, FSR0
	MOVFF       FARG_calculateChecksum_checksum_ptr+1, FSR0H
	MOVF        POSTINC0+0, 0 
	MOVWF       R2 
	MOVF        R2, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVFF       FARG_calculateChecksum_checksum_ptr+0, FSR1
	MOVFF       FARG_calculateChecksum_checksum_ptr+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
L_calculateChecksum4:
;ExternalEEPROM.c,20 :: 		value <<= 1;
	RLCF        FARG_calculateChecksum_value+0, 1 
	BCF         FARG_calculateChecksum_value+0, 0 
;ExternalEEPROM.c,15 :: 		for(i = 8; i; i--) {
	DECF        R3, 1 
;ExternalEEPROM.c,21 :: 		}
	GOTO        L_calculateChecksum0
L_calculateChecksum1:
;ExternalEEPROM.c,22 :: 		}
L_end_calculateChecksum:
	RETURN      0
; end of _calculateChecksum

_ExternalEEPROM_initialize:

;ExternalEEPROM.c,28 :: 		void ExternalEEPROM_initialize(uint8_t i2c_address) {
;ExternalEEPROM.c,29 :: 		hardwareAddress = (i2c_address & 0b00000111) << 1;
	MOVLW       7
	ANDWF       FARG_ExternalEEPROM_initialize_i2c_address+0, 0 
	MOVWF       _hardwareAddress+0 
	RLCF        _hardwareAddress+0, 1 
	BCF         _hardwareAddress+0, 0 
;ExternalEEPROM.c,30 :: 		I2C1_Init(100000);
	MOVLW       20
	MOVWF       SSP1ADD+0 
	CALL        _I2C1_Init+0, 0
;ExternalEEPROM.c,31 :: 		}
L_end_ExternalEEPROM_initialize:
	RETURN      0
; end of _ExternalEEPROM_initialize

_ExternalEEPROM_write:

;ExternalEEPROM.c,36 :: 		void ExternalEEPROM_write(uint8_t address, uint8_t _data) {
;ExternalEEPROM.c,39 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;ExternalEEPROM.c,40 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,44 :: 		I2C1_Wr(address);
	MOVF        FARG_ExternalEEPROM_write_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,45 :: 		I2C1_Wr(_data);
	MOVF        FARG_ExternalEEPROM_write__data+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,46 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;ExternalEEPROM.c,47 :: 		}
L_end_ExternalEEPROM_write:
	RETURN      0
; end of _ExternalEEPROM_write

_ExternalEEPROM_read:

;ExternalEEPROM.c,52 :: 		uint8_t ExternalEEPROM_read(uint8_t address) {
;ExternalEEPROM.c,57 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;ExternalEEPROM.c,58 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,59 :: 		I2C1_Wr(address);
	MOVF        FARG_ExternalEEPROM_read_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,63 :: 		I2C1_Repeated_Start();
	CALL        _I2C1_Repeated_Start+0, 0
;ExternalEEPROM.c,64 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	BSF         FARG_I2C1_Wr_data_+0, 0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,68 :: 		_data = I2C1_Rd(false);
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       ExternalEEPROM_read__data_L0+0 
;ExternalEEPROM.c,69 :: 		while(!I2C1_Is_Idle());
L_ExternalEEPROM_read5:
	CALL        _I2C1_Is_Idle+0, 0
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_ExternalEEPROM_read6
	GOTO        L_ExternalEEPROM_read5
L_ExternalEEPROM_read6:
;ExternalEEPROM.c,73 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;ExternalEEPROM.c,74 :: 		return _data;
	MOVF        ExternalEEPROM_read__data_L0+0, 0 
	MOVWF       R0 
;ExternalEEPROM.c,75 :: 		}
L_end_ExternalEEPROM_read:
	RETURN      0
; end of _ExternalEEPROM_read

_ExternalEEPROM_writeRow:

;ExternalEEPROM.c,81 :: 		uint8_t ExternalEEPROM_writeRow(uint8_t address, void* _data, uint8_t length) {
;ExternalEEPROM.c,82 :: 		uint8_t checksum = 0, i, current_byte;
	CLRF        ExternalEEPROM_writeRow_checksum_L0+0 
;ExternalEEPROM.c,86 :: 		if(length > 16 || (address & 0x0F)) return 0;
	MOVF        FARG_ExternalEEPROM_writeRow_length+0, 0 
	SUBLW       16
	BTFSS       STATUS+0, 0 
	GOTO        L__ExternalEEPROM_writeRow20
	MOVLW       15
	ANDWF       FARG_ExternalEEPROM_writeRow_address+0, 0 
	MOVWF       R0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ExternalEEPROM_writeRow20
	GOTO        L_ExternalEEPROM_writeRow9
L__ExternalEEPROM_writeRow20:
	CLRF        R0 
	GOTO        L_end_ExternalEEPROM_writeRow
L_ExternalEEPROM_writeRow9:
;ExternalEEPROM.c,90 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;ExternalEEPROM.c,91 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,95 :: 		I2C1_Wr(address);
	MOVF        FARG_ExternalEEPROM_writeRow_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,96 :: 		for(i = 0; i < length; i++) {
	CLRF        ExternalEEPROM_writeRow_i_L0+0 
L_ExternalEEPROM_writeRow10:
	MOVF        FARG_ExternalEEPROM_writeRow_length+0, 0 
	SUBWF       ExternalEEPROM_writeRow_i_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_ExternalEEPROM_writeRow11
;ExternalEEPROM.c,97 :: 		current_byte = *((uint8_t*)_data + i);
	MOVF        ExternalEEPROM_writeRow_i_L0+0, 0 
	ADDWF       FARG_ExternalEEPROM_writeRow__data+0, 0 
	MOVWF       FSR0 
	MOVLW       0
	ADDWFC      FARG_ExternalEEPROM_writeRow__data+1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       R0 
	MOVF        R0, 0 
	MOVWF       ExternalEEPROM_writeRow_current_byte_L0+0 
;ExternalEEPROM.c,98 :: 		I2C1_Wr(current_byte);
	MOVF        R0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,99 :: 		calculateChecksum(&checksum, current_byte);
	MOVLW       ExternalEEPROM_writeRow_checksum_L0+0
	MOVWF       FARG_calculateChecksum_checksum_ptr+0 
	MOVLW       hi_addr(ExternalEEPROM_writeRow_checksum_L0+0)
	MOVWF       FARG_calculateChecksum_checksum_ptr+1 
	MOVF        ExternalEEPROM_writeRow_current_byte_L0+0, 0 
	MOVWF       FARG_calculateChecksum_value+0 
	CALL        _calculateChecksum+0, 0
;ExternalEEPROM.c,100 :: 		Delay_us(80);
	MOVLW       53
	MOVWF       R13, 0
L_ExternalEEPROM_writeRow13:
	DECFSZ      R13, 1, 1
	BRA         L_ExternalEEPROM_writeRow13
;ExternalEEPROM.c,96 :: 		for(i = 0; i < length; i++) {
	INCF        ExternalEEPROM_writeRow_i_L0+0, 1 
;ExternalEEPROM.c,101 :: 		}
	GOTO        L_ExternalEEPROM_writeRow10
L_ExternalEEPROM_writeRow11:
;ExternalEEPROM.c,105 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;ExternalEEPROM.c,106 :: 		return checksum;
	MOVF        ExternalEEPROM_writeRow_checksum_L0+0, 0 
	MOVWF       R0 
;ExternalEEPROM.c,107 :: 		}
L_end_ExternalEEPROM_writeRow:
	RETURN      0
; end of _ExternalEEPROM_writeRow

_ExternalEEPROM_readSequence:

;ExternalEEPROM.c,113 :: 		uint8_t ExternalEEPROM_readSequence(uint8_t address, void* _data, uint8_t length) {
;ExternalEEPROM.c,114 :: 		uint8_t checksum = 0, i, current_byte;
	CLRF        ExternalEEPROM_readSequence_checksum_L0+0 
;ExternalEEPROM.c,119 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;ExternalEEPROM.c,120 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_WRITE);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,121 :: 		I2C1_Wr(address);
	MOVF        FARG_ExternalEEPROM_readSequence_address+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,125 :: 		I2C1_Repeated_Start();
	CALL        _I2C1_Repeated_Start+0, 0
;ExternalEEPROM.c,126 :: 		I2C1_Wr(EEPROM_FIXED_ID | hardwareAddress | I2C_READ);
	MOVLW       160
	IORWF       _hardwareAddress+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	BSF         FARG_I2C1_Wr_data_+0, 0 
	CALL        _I2C1_Wr+0, 0
;ExternalEEPROM.c,131 :: 		for(i = 0; i < length - 1; i++) {
	CLRF        ExternalEEPROM_readSequence_i_L0+0 
L_ExternalEEPROM_readSequence14:
	DECF        FARG_ExternalEEPROM_readSequence_length+0, 0 
	MOVWF       R1 
	CLRF        R2 
	MOVLW       0
	SUBWFB      R2, 1 
	MOVLW       128
	MOVWF       R0 
	MOVLW       128
	XORWF       R2, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ExternalEEPROM_readSequence27
	MOVF        R1, 0 
	SUBWF       ExternalEEPROM_readSequence_i_L0+0, 0 
L__ExternalEEPROM_readSequence27:
	BTFSC       STATUS+0, 0 
	GOTO        L_ExternalEEPROM_readSequence15
;ExternalEEPROM.c,132 :: 		current_byte = I2C1_Rd(true);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       ExternalEEPROM_readSequence_current_byte_L0+0 
;ExternalEEPROM.c,133 :: 		calculateChecksum(&checksum, current_byte);
	MOVLW       ExternalEEPROM_readSequence_checksum_L0+0
	MOVWF       FARG_calculateChecksum_checksum_ptr+0 
	MOVLW       hi_addr(ExternalEEPROM_readSequence_checksum_L0+0)
	MOVWF       FARG_calculateChecksum_checksum_ptr+1 
	MOVF        R0, 0 
	MOVWF       FARG_calculateChecksum_value+0 
	CALL        _calculateChecksum+0, 0
;ExternalEEPROM.c,134 :: 		*((uint8_t*)_data + i) = current_byte;
	MOVF        ExternalEEPROM_readSequence_i_L0+0, 0 
	ADDWF       FARG_ExternalEEPROM_readSequence__data+0, 0 
	MOVWF       FSR1 
	MOVLW       0
	ADDWFC      FARG_ExternalEEPROM_readSequence__data+1, 0 
	MOVWF       FSR1H 
	MOVF        ExternalEEPROM_readSequence_current_byte_L0+0, 0 
	MOVWF       POSTINC1+0 
;ExternalEEPROM.c,135 :: 		Delay_us(80);
	MOVLW       53
	MOVWF       R13, 0
L_ExternalEEPROM_readSequence17:
	DECFSZ      R13, 1, 1
	BRA         L_ExternalEEPROM_readSequence17
;ExternalEEPROM.c,131 :: 		for(i = 0; i < length - 1; i++) {
	INCF        ExternalEEPROM_readSequence_i_L0+0, 1 
;ExternalEEPROM.c,136 :: 		}
	GOTO        L_ExternalEEPROM_readSequence14
L_ExternalEEPROM_readSequence15:
;ExternalEEPROM.c,140 :: 		current_byte = I2C1_Rd(false);
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       ExternalEEPROM_readSequence_current_byte_L0+0 
;ExternalEEPROM.c,141 :: 		calculateChecksum(&checksum, current_byte);
	MOVLW       ExternalEEPROM_readSequence_checksum_L0+0
	MOVWF       FARG_calculateChecksum_checksum_ptr+0 
	MOVLW       hi_addr(ExternalEEPROM_readSequence_checksum_L0+0)
	MOVWF       FARG_calculateChecksum_checksum_ptr+1 
	MOVF        R0, 0 
	MOVWF       FARG_calculateChecksum_value+0 
	CALL        _calculateChecksum+0, 0
;ExternalEEPROM.c,142 :: 		*((uint8_t*)_data + i) = current_byte;
	MOVF        ExternalEEPROM_readSequence_i_L0+0, 0 
	ADDWF       FARG_ExternalEEPROM_readSequence__data+0, 0 
	MOVWF       FSR1 
	MOVLW       0
	ADDWFC      FARG_ExternalEEPROM_readSequence__data+1, 0 
	MOVWF       FSR1H 
	MOVF        ExternalEEPROM_readSequence_current_byte_L0+0, 0 
	MOVWF       POSTINC1+0 
;ExternalEEPROM.c,143 :: 		while(!I2C1_Is_Idle());
L_ExternalEEPROM_readSequence18:
	CALL        _I2C1_Is_Idle+0, 0
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_ExternalEEPROM_readSequence19
	GOTO        L_ExternalEEPROM_readSequence18
L_ExternalEEPROM_readSequence19:
;ExternalEEPROM.c,147 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;ExternalEEPROM.c,148 :: 		return checksum;
	MOVF        ExternalEEPROM_readSequence_checksum_L0+0, 0 
	MOVWF       R0 
;ExternalEEPROM.c,149 :: 		}
L_end_ExternalEEPROM_readSequence:
	RETURN      0
; end of _ExternalEEPROM_readSequence
