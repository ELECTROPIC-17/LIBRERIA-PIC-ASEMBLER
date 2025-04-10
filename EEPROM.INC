;***************************** Librería "EEPROM.INC" **********************************
;
;	====================================================================
;	  Del libro "MICROCONTROLADOR PIC16F84. DESARROLLO DE PROYECTOS".
;	  E. Palacios, F. Remiro y L. López.
; 	  Editorial Ra-Ma.  www.ra-ma.es
;	====================================================================
;
; Estas subrutinas permiten realizar las tareas básicas de escritura y lectura de la
; memoria EEPROM de datos del PIC.
;
; Subrutina "EEPROM_LeeDato" ------------------------------------------------------------
;
; El microcontrolador lee el dato que hay escrito en la posición de la EEPROM del PIC apuntada
; por el contenido del registro de trabajo W. El resultado se proporciona en el mismo W.
;
; Entrada: En (W) la dirección de la memoria EEPROM a leer.
; Salida :  En (W) el byte leído.

EEPROM_LeeDato
	bsf	STATUS,RP0		; Asegura que trabaja con el Banco 0.
	movwf	EEADR			; Dirección a leer.
;	bcf	EECON1,EEPGD
	bsf	EECON1,RD		; Orden de lectura.
EEPROM_SigueLeyendo
	btfsc	EECON1,RD		; El PIC indica que ha terminado la lectura
	goto	EEPROM_SigueLeyendo	; poniendo en bajo este bit.					
	movf	EEDATA,W		; El byte leído al registro W.
	bcf	STATUS,RP0

	return

; Subrutina "EEPROM_EscribeDato" --------------------------------------------------------
;
; Escribe el dato introducido en el registro de trabajo W en la posición de memoria EEPROM del
; PIC apuntada por el registro EEADR.
;
; Como altera el valor del registro INTCON al posicionar el flag GIE, éste se debe guardar al
; principio de la subrutina y restaurarlo al final.
;
; Entradas:	En el registro EEADR la dirección de la memoria EEPROM a escribir.
;		En el registro W el byte a escribir.
;
	CBLOCK
	EEPROM_GuardaINTCON
	ENDC

EEPROM_EscribeDato
	bsf	STATUS,RP0		; Asegura que trabaja con el Banco 0.
	movwf	EEDATA			; El byte a escribir.
;	movf	INTCON,W		; Reserva el valor anterior de INTCON
;	movwf	EEPROM_GuardaINTCON
		; Acceso al Banco 3
					; Deshabilita todas las interrupciones.
		
;	bcf	EECON1,EEPGD
	bsf	EECON1,WREN
; El fabricante especifica que hay que seguir esta secuencia para escritura en EEPROM:
;
;	bcf	INTCON,GIE
	movlw	0x55
	movwf	EECON2
	movlw	0xAA
	movwf	EECON2
	bsf	EECON1,WR		; Inicia la escritura.
EEPROM_TerminaEscribir
	btfsc	EECON1,WR		; Comprueba que termina de escribir en la EEPROM.
	goto	EEPROM_TerminaEscribir
	bcf	EECON1,WREN		; Desautoriza la escritura en EEPROM.
	bcf	EECON1,EEIF		; Limpia este flag.
	bcf	STATUS,RP0
;	movf	EEPROM_GuardaINTCON,W ; Restaura el valor anterior de INTCON.
;	movwf	INTCON
	return

;	====================================================================
;	  Del libro "MICROCONTROLADOR PIC16F84. DESARROLLO DE PROYECTOS".
;	  E. Palacios, F. Remiro y L. López.
; 	  Editorial Ra-Ma.  www.ra-ma.es
;	====================================================================
