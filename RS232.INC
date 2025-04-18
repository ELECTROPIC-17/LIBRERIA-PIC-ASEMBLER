
; Estas subrutinas permiten realizar las tareas b�sicas de control de la transmisi�n
; ser�e asincrona seg�n normas RS-232.
;
; Los par�metros adoptados para la comunicaci�n son los siguientes:
; - Velocidad de transmisi�n de 9600 baudios. La duraci�n de cada bit ser� 104 �s.
; - Un bit de inicio o Start a nivel bajo.
; - Dato de 8 bits.
; - Sin paridad.
; - Dos bits de final o Stop a nivel alto.
;
; El tiempo entre bit y bit  debe coincidir con el periodo de la se�al le�da o enviada.
; Como la velocidad de transmisi�n o recepci�n es de 9600 baudios, el periodo ser�:
; 1/9600 Baudios = 104 �s. Se utilizar� pues la subrutina Retardos_100micros.

	CBLOCK
	RS232_ContadorBits
	RS232_Dato
	ENDC

#DEFINE  RS232_Entrada	PORTA,4	; L�nea por la que se reciben los datos.
#DEFINE  RS232_Salida	PORTA,3	; L�nea por la que se env�an los datos.
;
; Subrutina "RS232_Inicializa" -------------------------------------------------------------
;
; Configura las l�neas de salida y entrada del microcontrolador.

RS232_Inicializa
	movlw	0x07
	movwf	CMCON
	bsf	STATUS,RP0
	bsf	RS232_Entrada		; Esta l�nea se configura como entrada.
	bcf	RS232_Salida		; Esta l�nea se configura como salida.
	bcf	STATUS,RP0
	return

; Subrutina "RS232_LeeDato" -------------------------------------------------------------
;
; El microcontrolador lee el dato por la l�nea de entrada comenzando por el bit de menor
; peso. El dato le�do se env�a finalmente en el registro de trabajo W.
;
; El ordenador parte siempre de un nivel alto, que es el estado que tiene cuando no 
; env�a informaci�n. La secuencia utilizada es:
; 1� 	Espera que se ejecute el pulso negativo del bit Start o flanco de bajada.
; 2�	Deja pasar un tiempo una y media veces mayor que el periodo de transmisi�n para
;	saltarse el bit de Start y lee el primer bit en su mitad.
; 3�	Lee el resto de los bits de datos, esperando un tiempo igual a la duraci�n del
;	periodo entre lectura y lectura para testearlos en mitad del bit.
;
; Salida: En el registro de trabajo W el byte le�do.

RS232_LeeDato
	movlw	d'8'			; N�mero de bits a recibir.
	movwf	RS232_ContadorBits
RS232_EsperaBitStart
	btfsc	RS232_Entrada 		; Lee la entrada y espera a que sea "0".
	goto	RS232_EsperaBitStart	; No, pues espera el nivel bajo.
	call 	Retardo_100micros		; El primer bit debe leerlo un tiempo igual a una
	call 	Retardo_50micros 		; vez y media el periodo de transmisi�n.
RS232_LeeBit
	bcf	STATUS,C		; Ahora lee el pin. En principio supone que es 0.
	btfsc	RS232_Entrada		; �Realmente es cero?
	bsf	STATUS,C		; No, pues cambia a "1".
	rrf	RS232_Dato,F		; Introduce el bit en el registro de lectura.
	call	Retardo_100micros		; Los siguientes bits los lee un periodo m�s tarde.
	decfsz 	RS232_ContadorBits,F	; Comprueba que es el �ltimo bit.
	goto	RS232_LeeBit		; Si no es el �ltimo bit pasa a leer el siguiente.
	call	Retardo_200micros		; Espera un tiempo igual al los 2 bits de Stop.
	movf	RS232_Dato,W		; El resultado en el registro W.
	return	

; Subrutinas "RS232_EnviaDato" y "RS232_EnviaN�mero" -------------------------------------
;
; El microcontrolador env�a un dato por la l�nea de salida comenzando por el bit de menor
; peso. En dato enviado ser� el que le llegue a trav�s del registro de trabajo W.
; 1�.	Env�a un "0" durante un tiempo igual al periodo de la velocidad de transmisi�n.
;	Este es el bit de "Start".
; 2�.	Env�a el bit correspondiente:
; 	- Si va a enviar un "0" permanece en bajo durante el periodo correspondiente.
;	- Si va a escribir un "1" permanece en alto durante el periodo correspondiente.
; 3�.	Env�a dos bits "1" durante un tiempo igual al per�odo de la velocidad de 
;	transmisi�n cada uno. Estos son los dos bits de Stop.
;
; Entrada:	En (W) el dato a enviar.

RS232_EnviaNumero			; Env�a el c�digo ASCII de un n�mero.
	addlw	'0'			; Lo pasa a c�digo ASCII sum�ndole el ASCII del 0.
RS232_EnviaDato
	movwf	RS232_Dato		; Guarda el contenido del byte a transmitir.
	movlw	d'8'			; Este es el n�mero de bits a transmitir.
	movwf	RS232_ContadorBits
	bcf	RS232_Salida		; Bit de Start.
	call	Retardo_100micros
RS232_EnviaBit				; Comienza a enviar datos.
	rrf	RS232_Dato,F		; Lleva el bit que se quiere enviar al Carry para
	btfss	STATUS,C		; deducir su valor. �Es un "1" el bit a transmitir?
	goto	RS232_EnviaCero		; No, pues env�a un "0".
RS232_EnviaUno
	bsf	RS232_Salida		; Transmite un "1".
	goto	RS232_FinEnviaBit
RS232_EnviaCero
	bcf	RS232_Salida		; Transmite un "0".
RS232_FinEnviaBit
	call	Retardo_100micros		; Este es el tiempo que estar� en alto o bajo.
	decfsz 	RS232_ContadorBits,F	; Comprueba que es el �ltimo bit.
	goto	RS232_EnviaBit		; Como no es el �ltimo bit repite la operaci�n.
	bsf	RS232_Salida		; Env�a dos bits de Stop.
	call	Retardo_100micros
	return
	
