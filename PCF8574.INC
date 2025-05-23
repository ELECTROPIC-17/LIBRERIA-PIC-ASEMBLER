;**************************** Librer�a "PCF8574.INC" **********************************
;
;
; Estas subrutinas permiten realizar las tareas de manejo del expansor de bus I2C PCF8574
; que convierte un bus de 8 l�neas paralelo a bus serie I2C y viceversa.
;
; Como es posible que haya m�s de un expansor en el mismo circuito, se deja a la subrutina
; de llamada a �stas que determine las direcciones de escritura y lectura mediante las
; etiquetas "PCF8574_DireccionLectura" y "PCF8574_DireccionEscritura", atendiendo a las
; caracter�sticas del hardware utilizado.
;
; ZONA DE DATOS **********************************************************************

	CBLOCK
	PCF8574_Dato			; Aqu� guarda el resultado del dato le�do o que
	ENDC				; se va a escribir.

; Subrutina "PCF8574_Lee" -------------------------------------------------------------
;
; Lee el perif�rico conectado al bus paralelo de 8 l�neas del PCF8574 que act�a como
; entrada y el resultado lo proporciona en el registro de trabajo W.

PCF8574_Lee
	call	I2C_EnviaStart		; Env�a la condici�n de Start.
	movlw	PCF8574_DireccionLectura	; Apunta al expansor de lectura.
	call	I2C_EnviaByte
	bsf	I2C_UltimoByteLeer
	call	I2C_LeeByte		; Lee el puerto.
	movwf	PCF8574_Dato		; Lo guarda en el registro correspondiente.
	call	I2C_EnviaStop		; Acaba de leer.
	movf	PCF8574_Dato,W		; Recupera el valor del dato le�do.
	return

; Subrutina "PCF8574_Escribe" ----------------------------------------------------------
;
; Escribe en el perif�rico conectado bus paralelo de 8 l�neas del expansor PCF8574 que
; act�a como salida, el dato que le llega por el registro de trabajo W. El dato escrito
; es recuperado finalmente en el registro W.
;
PCF8574_Escribe
	movwf	PCF8574_Dato		; Guarda el dato a escribir.
	call	I2C_EnviaStart		; Envia condici�n de Start.
	movlw	PCF8574_DireccionEscritura	; Apunta al expansor que act�a como salida.
	call	I2C_EnviaByte
	movf	PCF8574_Dato,W		; Recupera el valor del dato a enviar.
	call	I2C_EnviaByte		; Env�a el dato.
	call	I2C_EnviaStop		; Termina.
	movf	PCF8574_Dato,W		; Recupera el valor del dato escrito.
	return

