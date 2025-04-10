;************************* Librería "RETARDOS_20MHZ.INC"******************************
;
;      Librería de retardos para oscilador de 20 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;************************************************************************************

;----------------------------------------------------------------------------------------

; Delay = 1e-05 seconds
; Clock frequency = 20 MHz

; Actual delay = 1e-05 seconds = 50 cycles
; Error = 0 %

	cblock
	r1
	endc

Retardo_10micros
			;46 cycles
	movlw	0x0F
	movwf	r1
Retardo_10micros_0
	decfsz	r1, f
	goto	Retardo_10micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5e-06 seconds
; Clock frequency = 20 MHz

; Actual delay = 5e-06 seconds = 25 cycles
; Error = 0 %

	cblock
	r2
	endc

Retardo_5micros
			;19 cycles
	movlw	0x06
	movwf	r2
Retardo_5micros_0
	decfsz	r2, f
	goto	Retardo_5micros_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 4e-06 seconds
; Clock frequency = 20 MHz

; Actual delay = 4e-06 seconds = 20 cycles
; Error = 0 %

	cblock
	r3
	endc

Retardo_4micros
			;16 cycles
	movlw	0x05
	movwf	r3
Retardo_4micros_0
	decfsz	r3, f
	goto	Retardo_4micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0005 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.0005 seconds = 2500 cycles
; Error = 0 %

	cblock
	r4
	r5
	endc

Retardo_500micros
			;2493 cycles
	movlw	0xF2
	movwf	r4
	movlw	0x02
	movwf	r5
Retardo_500micros_0
	decfsz	r4, f
	goto	$+2
	decfsz	r5, f
	goto	Retardo_500micros_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0002 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.0002 seconds = 1000 cycles
; Error = 0 %

	cblock
	r6
	r7
	endc

Retardo_200micros
			;993 cycles
	movlw	0xC6
	movwf	r6
	movlw	0x01
	movwf	r7
Retardo_200micros_0
	decfsz	r6, f
	goto	$+2
	decfsz	r7, f
	goto	Retardo_200micros_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0001 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.0001 seconds = 500 cycles
; Error = 0 %

	cblock
	r8
	endc

Retardo_100micros
			;496 cycles
	movlw	0xA5
	movwf	r8
Retardo_100micros_0
	decfsz	r8, f
	goto	Retardo_100micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5e-05 seconds
; Clock frequency = 20 MHz

; Actual delay = 5e-05 seconds = 250 cycles
; Error = 0 %

	cblock
	r9
	endc

Retardo_50micros
			;244 cycles
	movlw	0x51
	movwf	r9
Retardo_50micros_0
	decfsz	r9, f
	goto	Retardo_50micros_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2e-05 seconds
; Clock frequency = 20 MHz

; Actual delay = 2e-05 seconds = 100 cycles
; Error = 0 %

	cblock
	r10
	endc

Retardo_20micros
			;94 cycles
	movlw	0x1F
	movwf	r10
Retardo_20micros_0
	decfsz	r10, f
	goto	Retardo_20micros_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.2 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.2 seconds = 1000000 cycles
; Error = 0 %

	cblock
	r11
	r12
	r13
	endc

Retardo_200ms
			;999990 cycles
	movlw	0x07
	movwf	r11
	movlw	0x2F
	movwf	r12
	movlw	0x03
	movwf	r13
Retardo_200ms_0
	decfsz	r11, f
	goto	$+2
	decfsz	r12, f
	goto	$+2
	decfsz	r13, f
	goto	Retardo_200ms_0

			;6 cycles
	goto	$+1
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.1 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.1 seconds = 500000 cycles
; Error = 0 %

	cblock
	r14
	r15
	r16
	endc

Retardo_100ms
			;499994 cycles
	movlw	0x03
	movwf	r14
	movlw	0x18
	movwf	r15
	movlw	0x02
	movwf	r16
Retardo_100ms_0
	decfsz	r14, f
	goto	$+2
	decfsz	r15, f
	goto	$+2
	decfsz	r16, f
	goto	Retardo_100ms_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.05 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.05 seconds = 250000 cycles
; Error = 0 %

	cblock
	r17
	r18
	endc

Retardo_50ms
			;249993 cycles
	movlw	0x4E
	movwf	r17
	movlw	0xC4
	movwf	r18
Retardo_50ms_0
	decfsz	r17, f
	goto	$+2
	decfsz	r18, f
	goto	Retardo_50ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.02 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.02 seconds = 100000 cycles
; Error = 0 %

	cblock
	r19
	r20
	endc

Retardo_20ms
			;99993 cycles
	movlw	0x1E
	movwf	r19
	movlw	0x4F
	movwf	r20
Retardo_20ms_0
	decfsz	r19, f
	goto	$+2
	decfsz	r20, f
	goto	Retardo_20ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.01 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.01 seconds = 50000 cycles
; Error = 0 %

	cblock
	r21
	r22
	endc

Retardo_10ms
			;49993 cycles
	movlw	0x0E
	movwf	r21
	movlw	0x28
	movwf	r22
Retardo_10ms_0
	decfsz	r21, f
	goto	$+2
	decfsz	r22, f
	goto	Retardo_10ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.005 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.005 seconds = 25000 cycles
; Error = 0 %

	cblock
	r23
	r24
	endc

Retardo_5ms
			;24993 cycles
	movlw	0x86
	movwf	r23
	movlw	0x14
	movwf	r24
Retardo_5ms_0
	decfsz	r23, f
	goto	$+2
	decfsz	r24, f
	goto	Retardo_5ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.002 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.002 seconds = 10000 cycles
; Error = 0 %

	cblock
	r25
	r26
	endc

Retardo_2ms
			;9993 cycles
	movlw	0xCE
	movwf	r25
	movlw	0x08
	movwf	r26
Retardo_2ms_0
	decfsz	r25, f
	goto	$+2
	decfsz	r26, f
	goto	Retardo_2ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.001 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.001 seconds = 5000 cycles
; Error = 0 %

	cblock
	r27
	r28
	endc

Retardo_1ms
			;4993 cycles
	movlw	0xE6
	movwf	r27
	movlw	0x04
	movwf	r28
Retardo_1ms_0
	decfsz	r27, f
	goto	$+2
	decfsz	r28, f
	goto	Retardo_1ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 20 seconds
; Clock frequency = 20 MHz

; Actual delay = 20 seconds = 100000000 cycles
; Error = 0 %

	cblock
	r30
	r31
	r32
	endc

Retardo_20s
			;99999996 cycles
	movlw	0x91
	movwf	r30
	movlw	0xFC
	movwf	r31
	movlw	0xDA
	movwf	r32
Retardo_20s_0
	decfsz	r30, f
	goto	$+2
	decfsz	r31, f
	goto	$+2
	decfsz	r32, f
	goto	Retardo_20s_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 10 seconds
; Clock frequency = 20 MHz

; Actual delay = 10 seconds = 50000000 cycles
; Error = 0 %

	cblock
	r33
	r34
	r35
	endc

Retardo_10s
			;49999990 cycles
	movlw	0xC7
	movwf	r33
	movlw	0xFE
	movwf	r34
	movlw	0x6D
	movwf	r35
Retardo_10s_0
	decfsz	r33, f
	goto	$+2
	decfsz	r34, f
	goto	$+2
	decfsz	r35, f
	goto	Retardo_10s_0

			;6 cycles
	goto	$+1
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5 seconds
; Clock frequency = 20 MHz

; Actual delay = 5 seconds = 25000000 cycles
; Error = 0 %

	cblock
	r36
	r37
	r38
	endc

Retardo_5s
			;24999994 cycles
	movlw	0xE3
	movwf	r36
	movlw	0x7F
	movwf	r37
	movlw	0x37
	movwf	r38
Retardo_5s_0
	decfsz	r36, f
	goto	$+2
	decfsz	r37, f
	goto	$+2
	decfsz	r38, f
	goto	Retardo_5s_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2 seconds
; Clock frequency = 20 MHz

; Actual delay = 2 seconds = 10000000 cycles
; Error = 0 %

	cblock
	r39
	r40
	r41
	endc

Retardo_2s
			;9999995 cycles
	movlw	0x5A
	movwf	r39
	movlw	0xCD
	movwf	r40
	movlw	0x16
	movwf	r41
Retardo_2s_0
	decfsz	r39, f
	goto	$+2
	decfsz	r40, f
	goto	$+2
	decfsz	r41, f
	goto	Retardo_2s_0

			;1 cycle
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 1 seconds
; Clock frequency = 20 MHz

; Actual delay = 1 seconds = 5000000 cycles
; Error = 0 %

	cblock
	r42
	r43
	r44
	endc

Retardo_1s
			;4999993 cycles
	movlw	0x2C
	movwf	r42
	movlw	0xE7
	movwf	r43
	movlw	0x0B
	movwf	r44
Retardo_1s_0
	decfsz	r42, f
	goto	$+2
	decfsz	r43, f
	goto	$+2
	decfsz	r44, f
	goto	Retardo_1s_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.5 seconds
; Clock frequency = 20 MHz

; Actual delay = 0.5 seconds = 2500000 cycles
; Error = 0 %

	cblock
	r45
	r46
	r47
	endc

Retardo_500ms
			;2499992 cycles
	movlw	0x15
	movwf	r45
	movlw	0x74
	movwf	r46
	movlw	0x06
	movwf	r47
Retardo_500ms_0
	decfsz	r45, f
	goto	$+2
	decfsz	r46, f
	goto	$+2
	decfsz	r47, f
	goto	Retardo_500ms_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 30 seconds
; Clock frequency = 20 MHz

; Actual delay = 30 seconds = 150000000 cycles
; Error = 0 %

	cblock
	r48
	r49
	r50
	r51
	endc

Retardo_30s
			;149999992 cycles
	movlw	0x29
	movwf	r48
	movlw	0x51
	movwf	r49
	movlw	0xFF
	movwf	r50
	movlw	0x01
	movwf	r51
Retardo_30s_0
	decfsz	r48, f
	goto	$+2
	decfsz	r49, f
	goto	$+2
	decfsz	r50, f
	goto	$+2
	decfsz	r51, f
	goto	Retardo_30s_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 60 seconds
; Clock frequency = 20 MHz

; Actual delay = 60 seconds = 300000000 cycles
; Error = 0 %

	cblock
	r52
	r53
	r54
	r55
	endc

Retardo_60s
			;299999995 cycles
	movlw	0x54
	movwf	r52
	movlw	0xA1
	movwf	r53
	movlw	0xFD
	movwf	r54
	movlw	0x02
	movwf	r55
Retardo_60s_0
	decfsz	r52, f
	goto	$+2
	decfsz	r53, f
	goto	$+2
	decfsz	r54, f
	goto	$+2
	decfsz	r55, f
	goto	Retardo_60s_0

			;1 cycle
	nop

			;4 cycles (including call)
	return

;-----------------------------------------------------------------------------------------
;
;      Librería de retardos para oscilador de 20 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;*****************************************************************************************

;----------------------------------------------------------------------------------------
