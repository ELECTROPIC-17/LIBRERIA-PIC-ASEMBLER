;DIVISION DE 24 BIT CON 16 BITS
;
;Entradas: 
; Dividendo - AARGB0:AARGB1:AARGB2 (0 - ¡el más significativo!) 
; Divisor - BARGB0:BARGB1 
;Temporal: 
; Contador - LOOPCOUNT 
; Resto- REMB0:REMB1 
;Salida: 
; Cociente - AARGB0:AARGB1:AARGB2 
; 

CBLOCK
AARGB0
AARGB1
AARGB2
BARGB0
BARGB1
LOOPCOUNT
REMB0
REMB1
ENDC

FXD2416U
        CLRF REMB0
        CLRF REMB1
        MOVLW .24
        MOVWF LOOPCOUNT
LOOPU2416
        RLF AARGB2, W           ;shift dividend left to move next bit to remainder
        RLF AARGB1, F           ;
        RLF AARGB0, F           ;

        RLF REMB1, F            ;shift carry (next dividend bit) into remainder
        RLF REMB0, F

        RLF AARGB2, F           ;finish shifting the dividend and save  carry in AARGB2.0,
                                ;since remainder can be 17 bit long in some cases
                                ;(e.g. 0x800000/0xFFFF). This bit will also serve
                                ;as the next result bit.
         
        MOVF BARGB1, W          ;substract divisor from 16-bit remainder
        SUBWF REMB1, F          ;
        MOVF BARGB0, W          ;
        BTFSS STATUS, C         ;
        INCFSZ BARGB0, W        ;
        SUBWF REMB0, F          ;

;here we also need to take into account the 17th bit of remainder, which
;is in AARGB2.0. If we don't have a borrow after subtracting from lower
;16 bits of remainder, then there is no borrow regardless of 17th bit 
;value. But, if we have the borrow, then that will depend on 17th bit 
;value. If it is 1, then no final borrow will occur. If it is 0, borrow
;will occur. These values match the borrow flag polarity.

        SKPNC                   ;if no borrow after 16 bit subtraction
         BSF AARGB2, 0          ;then there is no borrow in result. Overwrite
                                ;AARGB2.0 with 1 to indicate no
                                ;borrow.
                                ;if borrow did occur, AARGB2.0 already
                                ;holds the final borrow value (0-borrow,
                                ;1-no borrow)

        BTFSC AARGB2, 0         ;if no borrow after 17-bit subtraction
         GOTO UOK46LL           ;skip remainder restoration.

        ADDWF REMB0, F          ;restore higher byte of remainder. (w 
                                ;contains the value subtracted from it
                                ;previously)
        MOVF BARGB1, W          ;restore lower byte of remainder
        ADDWF REMB1, F          ;

UOK46LL

        DECFSZ LOOPCOUNT, f     ;decrement counter
         GOTO LOOPU2416         ;and repeat the loop if not zero.

        RETURN
