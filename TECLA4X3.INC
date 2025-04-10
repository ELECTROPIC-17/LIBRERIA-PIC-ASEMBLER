;**************************** Libreria "TECLADO.INC" ***********************************


; Libreria de subrutinas para la gestion de un teclado organizado en una matriz de 3 x 4  12 Teclas, y 
; conectado al Puerto B segun la disposicion siguiente.
;
;	 	 RB4 RB5 RB6 
;		   ^    ^    ^    ^
;		|----|----|----|----|
;	RB0 -->	|  0 |  1 |  2  
;		|----|----|----|----|
;	RB1 -->	|  3 |  4 |  5 
;		|----|----|----|----|
;	RB2 -->	|  6 |  7 | 8 
;		|----|----|----|----|
;	RB3 -->	| 9 | 10 | 11 
;		|----|----|----|----|

; Los numeros que se han dibujado dentro de cada cuadrado son el orden de las teclas
; que no tienen por que coincidir con lo serigrafiado sobre ellas. El paso del numero de orden
; de la tecla al valor que hay serigrafiado sobre la misma se hace con una tabla de conversion.

; ZONA DE DATOS **********************************************************************

	CBLOCK
	Tecl_TeclaOrden				; Orden de la tecla a chequear.
	ENDC

Tecl_UltimaTecla	EQU	d'11'		; Valor de orden de la última tecla utilizada.

; Subrutina "Teclado_LeeHex" ************************************************************

; Cada tecla tiene asignado un numero de orden que es contabilizado en la variable
; Tecl_TeclaOrden. Para convertir a su valor segun el tipo de teclado en concreto se
; utiliza una tabla de conversion. 
; A continuacion se expone la relacion entre el numero de orden de la tecla y los
; valores correspondientes para el teclado hexadecimal de 12 teclas.

;	      ORDEN DE TECLA:				 TECLADO HEX. UTILIZADO:
;		 0   1   2   					1  2  3  
;		 3   4   5   					4  5  6  
;		 6   7   8  					7  8  9  
;	         9  10  11	 				A  0  B  
;
; Asi en este ejemplo, la tecla "7" ocupa el orden 8, la tecla "B" ocupa el orden 12 y la
; tecla "9" el orden 10.

; Si cambia el teclado tambien hay cambiar de tabla de conversion.

; Entrada:	En (W) el orden de la tecla pulsada.
; Salida:		En (W) el valor hexadecimal para este teclado concreto.

Teclado_LeeHex
	call		Teclado_LeeOrdenTecla		; Lee el Orden de la tecla pulsada.
	btfss	STATUS,C				; ¿Pulsa alguna tecla?, ¿C=1?
	goto	Tecl_FinLeeHex				; No, por tanto sale.
	call		Tecl_ConvierteOrdenEnHex	; Lo convierte en su valor real mediante tabla.
	bsf		STATUS,C					; Vuelve a posicionar el Carry, porque la
	Tecl_FinLeeHex					; instruccion "addwf PCL,F" lo pone a "0".
	return

Tecl_ConvierteOrdenEnHex				; Segun el teclado utilizado resulta:
	addwf	PCL,F
	DT	1h,2h,3h				; Primera fila del teclado.		
	DT	4h,5h,6h				; Segunda fila del teclado	
	DT	7h,8h,9h				; Tercera fila del teclado.
	DT	0Ah,0h,0Bh				; Cuarta fila del teclado.
Teclado_FinTablaHex

; Esta tabla se situa al principio de la libreria con el proposito de que no supere la
; posicion 0FFh de memoria ROM de programa. De todas formas, en caso que asi fuera 
; visualizaria el siguiente mensaje de error en el proceso de ensamblado:

	IF (Teclado_FinTablaHex > 0xFF)
		ERROR	"Atencion: La tabla ha superado el tamano de la pagina de los"
		MESSG	"primeros 256 bytes de memoria ROM. NO funcionara correctamente."
	ENDIF
	
; Subrutina "Teclado_Inicializa" --------------------------------------------------------

; Esta subrutina configura las lineas del Puerto B segun la conexion del teclado realizada
; y comprueba que no hay pulsada tecla alguna al principio.

Teclado_Inicializa
	bsf	STATUS,RP0				; Configura las lineas del puerto:
	movlw	b'01110000'				; <RB6:RB4> entradas, <RB3:RB0> y RB7 salidas
	movwf	PORTB
	bcf	OPTION_REG,NOT_RBPU			; Habilita resistencia de Pull-Up del Puerto B.
	bcf	STATUS,RP0				; Acceso al banco 0.
	call	Teclado_EsperaDejePulsar
	return

; Subrutina "Teclado_EsperaDejePulsar" --------------------------------------------------

;Permanece en esta subrutina mientras siga pulsada la tecla.

Teclado_Comprobacion	EQU	b'11110000'

Teclado_EsperaDejePulsar:
	movlw	Teclado_Comprobacion			; Pone a cero las cuatro lineas de salida del 
	movwf	PORTB					; Puerto B.
Teclado_SigueEsperando
	call	Retardo_20ms				; Espera a que se estabilicen los niveles de tension.
	movf	PORTB,W					; Lee el Puerto B.
	sublw	Teclado_Comprobacion			; Si es lo mismo que escribio es que ya no pulsa 
	btfss	STATUS,Z				; tecla alguna.
	goto	Teclado_SigueEsperando
	return

; Subrutina "Teclado_LeeOrdenTecla" -----------------------------------------------------

; Lee el teclado, obteniendo el orden de la tecla pulsada. 

; Salida:	En (W) el numero de orden de la tecla pulsada. Ademas Carry se pone a "1" si
; se pulsa una tecla ó a "0" si no se pulsa tecla alguna.

Teclado_LeeOrdenTecla
	clrf	Tecl_TeclaOrden				; Todavia no ha empezado a chequear el teclado.
	movlw	b'11111110'				; Va a chequear primera fila.
Tecl_ChequeaFila					; (Ver esquema de conexion).
	movwf	PORTB
	call	Retardo_20ms				; Activa la fila correspondiente.
Tecl_Columna1
	btfss	PORTB,4					; Chequea la 1ª columna buscando un cero. 
	goto	Tecl_GuardaValor			; si, es cero y por tanto guarda su valor y sale.
	incf	Tecl_TeclaOrden,F			; Va a chequear la siguiente tecla.
Tecl_Columna2			 			; Repite proceso para las siguientes 
	btfss	PORTB,5					; columnas.
	goto	Tecl_GuardaValor
	incf	Tecl_TeclaOrden,F
Tecl_Columna3		
	btfss	PORTB,6
	goto	Tecl_GuardaValor
	incf	Tecl_TeclaOrden,F
;Tecl_Columna4						; Estas instruciones se husarian para un Teclado de 4x4
;	btfss	PORTB,7
;	goto	Tecl_GuardaValor
;	incf	Tecl_TeclaOrden,F

; Comprueba si ha chequeado la última tecla, en cuyo caso sale. Para ello testea si
; el contenido del registro Tecl_TeclaOrden es igual al numero de teclas del teclado.

Tecl_TerminaColumnas
	movlw	Tecl_UltimaTecla
	subwf	Tecl_TeclaOrden,W			; (W) = (Tecl_TeclaOrden)-Tecl_UltimaTecla.
	btfsc	STATUS,C				; ¿C=0?, ¿(W) negativo?, ¿(Tecl_TeclaOrden)<11?
	goto	Tecl_NoPulsada				; No, se ha llegado al final del chequeo.
	bsf	STATUS,C						; Si. Va a chequear la siguiente fila.
	rlf	PORTB,W					; Apunta a la siguiente fila.
	goto	Tecl_ChequeaFila	
Tecl_NoPulsada
	bcf	STATUS,C				; Posiciona C=0, indicando que no ha pulsado
	goto	Tecl_FinTecladoLee			; tecla alguna y sale.
Tecl_GuardaValor
	movf	Tecl_TeclaOrden,W			; El orden de la tecla pulsada en (W) y sale.
	bsf	STATUS,C				; Como hay tecla tecla pulsada, pone C=1. 
Tecl_FinTecladoLee
	return