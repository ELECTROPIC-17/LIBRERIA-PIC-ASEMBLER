
;24 x 24 Multiplication
;ENTRADAS :
; (Multiplier -Multiplier1-Multiplier2) (3 bytes )bytes compartidos con de  Producto; bytes significativos menos (+ 3..5)
;Multiplier	EQU	Product3 
;Multiplier1	EQU	Product4
;Multiplier2	EQU	Product5
;( Multiplicand -Multiplicand1-Multiplicand2) 3 bytes (no se modifica)
;Temporal
; Bitcount
;Output:
; Product-Product1-Product2-Product3-Product4-Product5 (6 bytes)
;  MLS   -    5	   -	4   -   3     -	2     -LSB
	CBLOCK	
	Product
	Product1
	Product2
	Product3
	Product4
	Product5
	BitCount
	Multiplicand
	Multiplicand1
	Multiplicand2
	
	ENDC

	Multiplier	EQU	Product3 	
	Multiplier1	EQU	Product4
	Multiplier2	EQU	Product5
	

Multiplication
        CLRF    Product         ; clear destination
        CLRF    Product1
        CLRF    Product2

        
        MOVLW   D'24'
        MOVWF   BitCount        ; number of bits

        RRF     Product3,F     ; shift out to carry
        RRF     Product4,F     ; next multiplier bit
        RRF     Product5,F

ADD_LOOP_24x24

        BTFSS   STATUS,C        ; if carry is set we must add multipland
                                ; to the product
GOTO  SKIP_LOOP_24x24 ; nope, skip this bit
                
        MOVF   	Multiplicand2,W  ; get LSB of multiplicand
        ADDWF   Product2,F     ; add it to the lsb of the product
  
        MOVF    Multiplicand1,W  ; middle byte
        BTFSC   STATUS,C        ; check carry for overflow
        INCFSZ  Multiplicand1,W  ; if carry set we add one to the source 
        ADDWF   Product1,F     ; and add it  (if not zero, in
                                ; that case mulitpland = 0xff->0x00 )
        
        MOVF    Multiplicand,W    ; MSB byte
        BTFSC   STATUS,C        ; check carry
        INCFSZ  Multiplicand,W
        ADDWF   Product,F       ; handle overflow

SKIP_LOOP_24x24
        ; note carry contains most significant bit of
        ; addition here

        ; shift in carry and shift out
        ; next multiplier bit, starting from less
        ; significant bit

        RRF     Product,F
        RRF     Product1,F
        RRF     Product2,F
        RRF     Product3,F
        RRF     Product4,F
        RRF     Product5,F

        DECFSZ  BitCount,F
        GOTO    ADD_LOOP_24x24
        RETURN