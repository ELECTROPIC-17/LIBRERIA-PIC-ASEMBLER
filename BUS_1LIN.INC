
;
; Estas subrutinas permiten realizar las tareas b�sicas de control del bus de una sola l�nea
; seg�n el protocolo del fabricante de semiconductores Dallas Semiconductors.
;
; ZONA DE DATOS **********************************************************************

	CBLOCK
	Bus1Linea_Dato			; Guarda dato a transmitir o recibir por el bus.
	Bus1Linea_ContadorBits		; Cuenta los bits a transmitir o a recibir.
	ENDC

#DEFINE  Bus1Linea	PORTB,3		; L�nea donde se conecta el DS1820.

; Subrutina "Bus1Linea_AltaImpedancia" --------------------------------------------------
;
; Configura la l�nea �nica de 1-Wire Bus como entrada. Lo pone en alta impedancia.

Bus1Linea_AltaImpedancia
	bsf	STATUS,RP0
	bsf	Bus1Linea		; La l�nea como entrada, por tanto, en alta
	bcf	STATUS,RP0		; impedancia.
	return

; Subrutina "Bus1Linea_Bajo" ------------------------------------------------------------
;
; Mantiene el pin de datos del Bus de 1 l�nea en bajo.
 
Bus1Linea_Bajo
	bsf	STATUS,RP0
	bcf	Bus1Linea		; La l�nea como salida.
	bcf	STATUS,RP0
	bcf	Bus1Linea		; Pasa a bajo.
	return

; Subrutina "Bus1Linea_Reset" -----------------------------------------------------------
;
; Env�a un impulso de Reset al dispositivo conectado en el bus de 1 l�nea y despu�s
; espera recibir un impulso de Presence". Esto consiste en:
; 1�.	El PIC manda un impulso en bajo durante unos 500 �s. (El protocolo permite entre 480
;	y 960 �s).
; 2�. 	El PIC pasa a modo entrada, espera 20 �s. (El protocolo fija entre 15 y 60 �s).
; 3�. 	El PIC lee la l�nea de entrada y si es bajo est� correcto (pulso de "Presence").
;	Se interpreta como que el procedimiento est� correctamente inicializado.

Bus1Linea_Reset
	call	Bus1Linea_AltaImpedancia	; Empieza en alto para conseguir el flanco de
					; bajada con la siguiente instrucci�n.
	call	Bus1Linea_Bajo		; El bus de 1 l�nea en bajo durante 500 �s.
	call	Retardo_500micros
	call	Bus1Linea_AltaImpedancia	; Permanece en alta impedancia (nivel alto por
	call	Retardo_20micros		; las resistencias de Pull-Up) durante unos �s.
Bus1Linea_EsperaLeerBajo
	btfsc	Bus1Linea		; Espera a que el dispositivo le env�e el pulso
	goto	Bus1Linea_EsperaLeerBajo	; en bajo de "Presence".
Bus1Linea_EsperaLeerAlto
	btfss	Bus1Linea		; Y ahora el dispositivo lo debe poner en alto.
	goto	Bus1Linea_EsperaLeerAlto
	return

; Subrutina "Bus1Linea_EscribeByte" -----------------------------------------------------
;
; El maestro escribe un byte al esclavo conectado al bus de 1 l�nea comenzando por el bit LSB.
; Consiste en enviar 8 bits, repitiendo 8 veces la siguiente secuencia:
; 1�	El PIC manda un impulso en bajo durante unos microsegundos. (El protocolo fija un
;	m�nimo de 1 �s y sin exceder con lo que viene a continuaci�n de 60 �s) A continuaci�n:
;	- Si va a enviar un "0" permanece en bajo durante 50 �s.
;	- Si va a escribir un "1" se pone en alta impedancia durante 50 �s. (El protocolo
;	  permite unos valores entre 15 y 60 �s para ambos casos).
; 2� 	Para escribir otro bit se pone en alta impedancia durante unos �s. (El protocolo
;	establece un m�nimo de 1 �s).
;
; Entrada:	En (W) el dato a enviar.

Bus1Linea_EscribeByte
	movwf	Bus1Linea_Dato		; Guarda el byte a transmitir.
	movlw	0x08			; 8 bits a transmitir.
	movwf	Bus1Linea_ContadorBits
	call	Bus1Linea_AltaImpedancia	; Empieza en alta impedancia.
Bus1Linea_EnviaBit
	call	Bus1Linea_Bajo		; Flanco de bajada.
;
; Pregunta por el valor del bit a transmitir.
;
	rrf	Bus1Linea_Dato,F		; Lleva el bit de menor peso LSB al Carry. 
	btfss	STATUS,C		; �Es un "1" el bit a transmitir?.
	goto	Bus1Linea_EnviaCero	; No, pues env�a un "0".	
Bus1Linea_EnviaUno
	call	Bus1Linea_AltaImpedancia	; Transmite un "1".
	goto	Bus1Linea_Espera50us
Bus1Linea_EnviaCero
	call	Bus1Linea_Bajo		; Transmite un "0".
Bus1Linea_Espera50us
	call	Retardo_50micros
	call	Bus1Linea_AltaImpedancia	; Flanco de subida.
	decfsz	Bus1Linea_ContadorBits,1	; Comprueba que es el �ltimo bit.
	goto	Bus1Linea_EnviaBit	; Como no es el �ltimo bit repite la operaci�n.
	return
;
; Subrutina "Bus1Linea_LeeByte" ---------------------------------------------------------
;
; El microcontrolador maestro lee un byte del dispositivo esclavo conectado al bus de
; 1 l�nea. Consiste en leer 8 bits, repitiendo 8 veces la siguiente secuencia:
; 1�	El PIC manda un pulso en bajo durante unos �s. (El protocolo fija un m�nimo de 1 �s).
; 2� 	El PIC se pone en entrada (alta impedancia) durante otros 10 �s (con un total de 15 �s
;	desde el flanco de bajada) para proceder a la lectura de la l�nea.
; 3�	El PIC espera 50 �s para realizar la siguiente lectura (total unos 65 �s desde el
;	flanco de bajada). El protocolo fija que las lecturas se har�n cada 60 �s � m�s.
;
; Salida:	En (W) el dato le�do.

Bus1Linea_LeeByte
	movlw	0x08			; 8 bits a recibir.
	movwf	Bus1Linea_ContadorBits
	call	Bus1Linea_AltaImpedancia	; Empieza en alta impedancia.
Bus1Linea_LeeBit
	call	Bus1Linea_Bajo		; Flanco de bajada.
	call	Bus1Linea_AltaImpedancia
	call	Retardo_10micros		; A�adiendo las instrucciones anteriores, supone
					; un total de 15 �s desde el flanco de bajada.
	bcf	STATUS,C		; Ahora lee el pin. En principio supone que es 0.
	btfsc	Bus1Linea		; �Realmente es cero?.
	bsf	STATUS,C		; No, pues cambia a uno.
	rrf	Bus1Linea_Dato,1		; Introduce el bit en el registro.
	call	Retardo_50micros		; Espera.
	call	Bus1Linea_AltaImpedancia	; Flanco de subida del pulso positivo.
	decfsz 	Bus1Linea_ContadorBits,1	; Comprueba que es el �ltimo bit.
	goto	Bus1Linea_LeeBit		; Si no es el �ltimo bit pasa a leer el siguiente.
	movf	Bus1Linea_Dato,W		; El resultado en el registro W.
	return
	
