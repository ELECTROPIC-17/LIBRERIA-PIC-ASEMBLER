;************************* Librería "RETARDOS_10MHZ.INC"******************************
;
;      Librería de retardos para oscilador de 10 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;*************************************************************************************

;----------------------------------------------------------------------------------------

; Delay = 1e-05 seconds
; Clock frequency = 10 MHz

; Actual delay = 1e-05 seconds = 25 cycles
; Error = 0 %

	cblock
	r1
	endc

Retardo_10micros
			;19 cycles
	movlw	0x06
	movwf	r1
Retardo_10micros_0
	decfsz	r1, f
	goto	Retardo_10micros_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5e-06 seconds
; Clock frequency = 10 MHz

; Actual delay = 5.2e-06 seconds = 13 cycles
; Error = -4 %

Retardo_5micros
			;9 cycles
	goto	$+1
	goto	$+1
	goto	$+1
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 4e-06 seconds
; Clock frequency = 10 MHz

; Actual delay = 4e-06 seconds = 10 cycles
; Error = 0 %

Retardo_4micros
			;6 cycles
	goto	$+1
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0005 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.0005 seconds = 1250 cycles
; Error = 0 %

	cblock
	r2
	r3
	endc

Retardo_500micros
			;1243 cycles
	movlw	0xF8
	movwf	r2
	movlw	0x01
	movwf	r3
Retardo_500micros_0
	decfsz	r2, f
	goto	$+2
	decfsz	r3, f
	goto	Retardo_500micros_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0002 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.0002 seconds = 500 cycles
; Error = 0 %

	cblock
	r4
	endc

Retardo_200micros
			;496 cycles
	movlw	0xA5
	movwf	r4
Retardo_200micros_0
	decfsz	r4, f
	goto	Retardo_200micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0001 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.0001 seconds = 250 cycles
; Error = 0 %

	cblock
	r5
	endc

Retardo_100micros
			;244 cycles
	movlw	0x51
	movwf	r5
Retardo_100micros_0
	decfsz	r5, f
	goto	Retardo_100micros_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5e-05 seconds
; Clock frequency = 10 MHz

; Actual delay = 5e-05 seconds = 125 cycles
; Error = 0 %

	cblock
	r6
	endc

Retardo_50micros
			;121 cycles
	movlw	0x28
	movwf	r6
Retardo_50micros_0
	decfsz	r6, f
	goto	Retardo_50micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2e-05 seconds
; Clock frequency = 10 MHz

; Actual delay = 2e-05 seconds = 50 cycles
; Error = 0 %

	cblock
	r7
	endc

Retardo_20micros
			;46 cycles
	movlw	0x0F
	movwf	r7
Retardo_20micros_0
	decfsz	r7, f
	goto	Retardo_20micros_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.2 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.2 seconds = 500000 cycles
; Error = 0 %

	cblock
	r8
	r9
	r10
	endc

Retardo_200ms
			;499994 cycles
	movlw	0x03
	movwf	r8
	movlw	0x18
	movwf	r9
	movlw	0x02
	movwf	r10
Retardo_200ms_0
	decfsz	r8, f
	goto	$+2
	decfsz	r9, f
	goto	$+2
	decfsz	r10, f
	goto	Retardo_200ms_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.1 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.1 seconds = 250000 cycles
; Error = 0 %

	cblock
	r11
	r12
	endc

Retardo_100ms
			;249993 cycles
	movlw	0x4E
	movwf	r11
	movlw	0xC4
	movwf	r12
Retardo_100ms_0
	decfsz	r11, f
	goto	$+2
	decfsz	r12, f
	goto	Retardo_100ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.05 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.05 seconds = 125000 cycles
; Error = 0 %

	cblock
	r13
	r14
	endc

Retardo_50ms
			;124993 cycles
	movlw	0xA6
	movwf	r13
	movlw	0x62
	movwf	r14
Retardo_50ms_0
	decfsz	r13, f
	goto	$+2
	decfsz	r14, f
	goto	Retardo_50ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.02 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.02 seconds = 50000 cycles
; Error = 0 %

	cblock
	r15
	r16
	endc

Retardo_20ms
			;49993 cycles
	movlw	0x0E
	movwf	r15
	movlw	0x28
	movwf	r16
Retardo_20ms_0
	decfsz	r15, f
	goto	$+2
	decfsz	r16, f
	goto	Retardo_20ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.01 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.01 seconds = 25000 cycles
; Error = 0 %

	cblock
	r17
	r18
	endc

Retardo_10ms
			;24993 cycles
	movlw	0x86
	movwf	r17
	movlw	0x14
	movwf	r18
Retardo_10ms_0
	decfsz	r17, f
	goto	$+2
	decfsz	r18, f
	goto	Retardo_10ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.005 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.005 seconds = 12500 cycles
; Error = 0 %

	cblock
	r19
	r20
	endc

Retardo_5ms
			;12493 cycles
	movlw	0xC2
	movwf	r19
	movlw	0x0A
	movwf	r20
Retardo_5ms_0
	decfsz	r19, f
	goto	$+2
	decfsz	r20, f
	goto	Retardo_5ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.002 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.002 seconds = 5000 cycles
; Error = 0 %

	cblock
	r21
	r22
	endc

Retardo_2ms
			;4993 cycles
	movlw	0xE6
	movwf	r21
	movlw	0x04
	movwf	r22
Retardo_2ms_0
	decfsz	r21, f
	goto	$+2
	decfsz	r22, f
	goto	Retardo_2ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.001 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.001 seconds = 2500 cycles
; Error = 0 %

	cblock
	r23
	r24
	endc

Retardo_1ms
			;2493 cycles
	movlw	0xF2
	movwf	r23
	movlw	0x02
	movwf	r24
Retardo_1ms_0
	decfsz	r23, f
	goto	$+2
	decfsz	r24, f
	goto	Retardo_1ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 20 seconds
; Clock frequency = 10 MHz

; Actual delay = 20 seconds = 50000000 cycles
; Error = 0 %

	cblock
	r25
	r26
	r27
	endc

Retardo_20s
			;49999990 cycles
	movlw	0xC7
	movwf	r25
	movlw	0xFE
	movwf	r26
	movlw	0x6D
	movwf	r27
Retardo_20s_0
	decfsz	r25, f
	goto	$+2
	decfsz	r26, f
	goto	$+2
	decfsz	r27, f
	goto	Retardo_20s_0

			;6 cycles
	goto	$+1
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 10 seconds
; Clock frequency = 10 MHz

; Actual delay = 10 seconds = 25000000 cycles
; Error = 0 %

	cblock
	r28
	r29
	r30
	endc

Retardo_10s
			;24999994 cycles
	movlw	0xE3
	movwf	r28
	movlw	0x7F
	movwf	r29
	movlw	0x37
	movwf	r30
Retardo_10s_0
	decfsz	r28, f
	goto	$+2
	decfsz	r29, f
	goto	$+2
	decfsz	r30, f
	goto	Retardo_10s_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5 seconds
; Clock frequency = 10 MHz

; Actual delay = 5 seconds = 12500000 cycles
; Error = 0 %

	cblock
	r31
	r32
	r33
	endc

Retardo_5s
			;12499996 cycles
	movlw	0x71
	movwf	r31
	movlw	0x40
	movwf	r32
	movlw	0x1C
	movwf	r33
Retardo_5s_0
	decfsz	r31, f
	goto	$+2
	decfsz	r32, f
	goto	$+2
	decfsz	r33, f
	goto	Retardo_5s_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2 seconds
; Clock frequency = 10 MHz

; Actual delay = 2 seconds = 5000000 cycles
; Error = 0 %

	cblock
	r34
	r35
	r36
	endc

Retardo_2s
			;4999993 cycles
	movlw	0x2C
	movwf	r34
	movlw	0xE7
	movwf	r35
	movlw	0x0B
	movwf	r36
Retardo_2s_0
	decfsz	r34, f
	goto	$+2
	decfsz	r35, f
	goto	$+2
	decfsz	r36, f
	goto	Retardo_2s_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 1 seconds
; Clock frequency = 10 MHz

; Actual delay = 1 seconds = 2500000 cycles
; Error = 0 %

	cblock
	r37
	r38
	r39
	endc

Retardo_1s
			;2499992 cycles
	movlw	0x15
	movwf	r37
	movlw	0x74
	movwf	r38
	movlw	0x06
	movwf	r39
Retardo_1s_0
	decfsz	r37, f
	goto	$+2
	decfsz	r38, f
	goto	$+2
	decfsz	r39, f
	goto	Retardo_1s_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.5 seconds
; Clock frequency = 10 MHz

; Actual delay = 0.5 seconds = 1250000 cycles
; Error = 0 %

	cblock
	r40
	r41
	r42
	endc

Retardo_500ms
			;1249995 cycles
	movlw	0x8A
	movwf	r40
	movlw	0xBA
	movwf	r41
	movlw	0x03
	movwf	r42
Retardo_500ms_0
	decfsz	r40, f
	goto	$+2
	decfsz	r41, f
	goto	$+2
	decfsz	r42, f
	goto	Retardo_500ms_0

			;1 cycle
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 30 seconds
; Clock frequency = 10 MHz

; Actual delay = 30 seconds = 75000000 cycles
; Error = 0 %

	cblock
	r43
	r44
	r45
	endc

Retardo_30s
			;74999993 cycles
	movlw	0xAC
	movwf	r43
	movlw	0x7D
	movwf	r44
	movlw	0xA4
	movwf	r45
Retardo_30s_0
	decfsz	r43, f
	goto	$+2
	decfsz	r44, f
	goto	$+2
	decfsz	r45, f
	goto	Retardo_30s_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 60 seconds
; Clock frequency = 10 MHz

; Actual delay = 60 seconds = 150000000 cycles
; Error = 0 %

	cblock
	r46
	r47
	r48
	r49
	endc

Retardo_60s
			;149999992 cycles
	movlw	0x29
	movwf	r46
	movlw	0x51
	movwf	r47
	movlw	0xFF
	movwf	r48
	movlw	0x01
	movwf	r49
Retardo_60s_0
	decfsz	r46, f
	goto	$+2
	decfsz	r47, f
	goto	$+2
	decfsz	r48, f
	goto	$+2
	decfsz	r49, f
	goto	Retardo_60s_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;-----------------------------------------------------------------------------------------
;
;      Librería de retardos para oscilador de 10 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;*****************************************************************************************