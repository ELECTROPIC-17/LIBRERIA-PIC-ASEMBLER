;********************************************
;*** Division de 24bits / 16bits = 24bits ***
;********************************************

; <Dividendo_c;Dividendo_b;Dividendo_a>/<Divisor_b;Divisor_a>=<Dividendo_c;Dividendo_b;Dividendo_a>


;REGISTROS
Dividendo_a
Dividendo_b
Dividendo_c

Divisor_a
Divisor_b

Temp0		
Resto_b			
Resto_a		
	

;Rutina
Division
	clrf 	Resto_b
	clrf 	Resto_a
	movlw 	d'24'
	movwf 	Temp0
Div_1	
	rlf 	Dividendo_a,w
	rlf 	Dividendo_b,f
	rlf 	Dividendo_c,f
	rlf 	Resto_a,f
	rlf 	Resto_b,f
	rlf 	Dividendo_a,f
	movf 	Divisor_a,w
	subwf 	Resto_a,f
	movf 	Divisor_b,w
	btfss 	STATUS,C
	incfsz 	Divisor_b,w
	subwf 	Resto_b,f
	btfsc	STATUS,C
	bsf 	Dividendo_a,0
	btfsc 	Dividendo_a,0
	goto 	Div_2
	addwf 	Resto_b,f
	movf 	Divisor_a,w
	addwf 	Resto_a,f
Div_2	
	decfsz 	Temp0,f
	goto 	Div_1
Salir
