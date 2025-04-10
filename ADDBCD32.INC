	CBLOCK	
	ACa3   	 ; 32-bit del acumulador a, lsb + 3, ms-byte
	ACa2  	 ; 32-bit acumulador A, lsb + 2
	ACa1 	 ; 32-bit acumulador A, lsb + 1
	ACa0 	 ; 32-bit del acumulador a, ls-byte	
	
	ACb3 	 ; 32-bit del acumulador b, lsb + 3, ms-byte
	ACb2 	 ; 32-bit del acumulador b, lsb + 2
	ACb1 	 ; 32-bit del acumulador b, lsb + 1
	ACb0 	 ; 32-bit del acumulador b, ls-byte
	bitcnt	; número de bits
	BCD9	; 10^9,Billones
	BCD8	; 10^8
	BCD7	; 10^7
	BCD6	; 10^6, millones
	BCD5	; 10^5
	BCD4	; 10^4
	BCD3	; 10^3, miles
	BCD2	; 10^2	centena
	BCD1	; 10^1	decena
	BCD0	; 10^0	unidad
	digcnt
	ENDC
;ENTRDA PARA SUMA
;SUMADOR	    //	SUMANDO
;ACa3-ACa2-ACa1-ACa0//ACb3-ACb2-ACb1-ACb0
;MSB-	-	-LSB//MSB -	-    -LSB	
;RESULTADO:ACb3-ACb2-ACb1-ACb0	

Suma	
	movf    ACa0,w
	addwf   ACb0,f        ;Add lsb
	btfss   STATUS,C      ;Test for carry
	goto	q_2           ; go if no carry
	incf    ACb1,f        ;Add carry to lsb+1
	btfss	STATUS,Z      ;Test for carry ripple (FF --> 00)
	goto	q_2           ; and go if no carry
	incf	ACb2,f        ;Add carry to lsb+2
	btfsc	STATUS,Z      ;Test for carry ripple
	incf	ACb3,f        ; add carry to lsb+3, msb
q_2	movf    ACa1,w
	addwf   ACb1,f        ;Add lsb+1
	btfss   STATUS,C      ;Test for carry
	goto	q_4           ; go if no carry
	incf	ACb2,f        ;Add carry to lsb+2
	btfsc	STATUS,Z      ;Test for carry ripple
	incf	ACb3,f        ; add carry to lsb+3, msb
q_4	movf    ACa2,w
	addwf   ACb2,f        ;Add lsb+2
	btfsc   STATUS,C      ;Test for carry
	incf    ACb3,f        ; add carry to lsb+3, msb
	movf    ACa3,w
	addwf   ACb3,f        ;Add msb
	retlw   0



;ENTRADA PARA BCD 32 BITS
;ACb3-ACb2-ACb1-ACb0
;MSB-    -     -LSB
;SALIDA
;BCD9-BCD8-BCD7-BCD6-BCD5-BCD4-BCD3-BCD2-BCD1-BCD0
;MSB-	-	-	-	-	-    -LSB

BINBCD_32
	clrf	BCD9         ;Clear all bcd digits
	clrf	BCD8
	clrf	BCD7
	clrf	BCD6
	clrf	BCD5
	clrf	BCD4
	clrf	BCD3
	clrf	BCD2
	clrf	BCD1
	clrf	BCD0
	movlw	D'32'        ;Outer loop
	movwf	bitcnt       ; bit counter
b2bcd1
	rlf	ACb0,f       ;Shift 32-bit accumulator
	rlf	ACb1,f       ; left to 
	rlf	ACb2,f       ;  put ms-bit 
	rlf	ACb3,f       ;   into Carry
	movlw	BCD0         ;Point to address of least 
	movwf	FSR          ; significant bcd digit
	movlw	D'10'        ;Inner loop
	movwf	digcnt       ; digit counter
b2bcd2
	rlf	INDF,f       ;Shift Carry into bcd digit
	movlw	D'10'        ;Subtract ten from digit then
	subwf	INDF,w       ; check and adjust for decimal overflow
	btfsc   STATUS,C     ;If Carry = 1 (result >= 0)
	movwf	INDF         ; adjust for decimal overflow
	decf	FSR,f        ;Point to next bcd digit
	decfsz	digcnt,f     ;Decrement digit counter
	goto	b2bcd2       ; - go if digcnt > 0
	decfsz	bitcnt,f     ;Decrement bit counter
	goto	b2bcd1       ; - go if bitcnt > 0
	retlw   0	