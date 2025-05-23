
;
; Estas subrutinas permiten transmitir mensajes desde el microcontrolador hacia el 
; ordenador a trav�s del puerto serie RS232.
;
; Subrutina "RS232_Mensaje" -------------------------------------------------------------
;
; Env�a por el puerto serie el mensaje apuntado por el registro W y grabado en memoria
; de programa del PIC. El mensaje se visualizar� en el monitor del ordenador. Esta
; subrutina sigue la estructura de funcionamiento similar a la ya conocida "LCD_Mensaje"
; para visualizaci�n de mensajes en pantallas de  modulos LCD.
;
	CBLOCK
	RS232_ApuntaCaracter		; Apunta al car�cter a visualizar.
	RS232_ValorCaracter		; Valor ASCII del car�cter a visualizar.
	ENDC

RS232_Mensaje
	movwf	RS232_ApuntaCaracter	; Posici�n del primer car�cter del mensaje.
	movlw	Mensajes			; Halla la posici�n relativa del primer car�cter
	subwf	RS232_ApuntaCaracter,F	; del mensaje respecto del comienzo de todos los
					; mensajes (identificados mediante la etiqueta
					; "Mensajes").
	decf	RS232_ApuntaCaracter,F	; Para compensar la posici�n que ocupa la 
RS232_VisualizaOtroCaracter			; instrucci�n "addwf PCL,F".
	movf	RS232_ApuntaCaracter,W	; Apunta al car�cter a visualizar.
	call	Mensajes			; Obtiene el c�digo ASCII del car�cter apuntado.
	movwf	RS232_ValorCaracter	; Guarda el valor de car�cter.
	movf	RS232_ValorCaracter,F	; Lo �nico que hace es posicionar flag Z. En caso
	btfsc	STATUS,Z		; que sea "0x00", que es c�digo indicador final	
	goto	RS232_FinMensaje 		; de mensaje, sale fuera.
RS232_NoUltimoCaracter
	call	RS232_EnviaDato		; Visualiza el car�cter ASCII le�do.
	incf	RS232_ApuntaCaracter,F	; Apunta a la posici�n del siguiente car�cter
	goto	RS232_VisualizaOtroCaracter	; dentro del mensaje.
RS232_FinMensaje
	return

; Subrutina "RS232_LineasBlanco" ------------------------------------------------
;
; Visualiza unas cuantas l�neas en blanco en el monitor del ordenador.

	CBLOCK
	RS232_ContadorLineas
	ENDC

RS232_LineasBlanco
	movlw	d'10'			; Por ejemplo este n�mero de l�neas en
	movwf	RS232_ContadorLineas	; blanco.
R232_LineasBlancoLazo
	movlw	.10			; C�digo del salto de l�nea
	call	RS232_EnviaDato
	decfsz	RS232_ContadorLineas,F
	goto	R232_LineasBlancoLazo
	movlw	.13			; C�digo del retorno de carro.
	call	RS232_EnviaDato		; Finaliza con un retorno de carro.
	return
	
