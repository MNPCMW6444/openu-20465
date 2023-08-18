; Define data segments
MS3:     .string "Multiplier program"
MULTIPLIERS: .data 2, 3, 4, 5
PRODUCT:  .data 1
; External and entry references (assuming needed)
.extern Display
MAIN:    mov PRODUCT, @r0
         mov 1, @r1
; Initialize loop variables
         mov MULTIPLIERS, @r2
         mov 4, @r3
LOOPM:   mov @r2, @r1
         inc @r2
         dec @r3
         bne LOOPM
; Store the product into PRODUCT
         mov @r1, @r0
; Display the product
         prn @r1
         jmp END
.entry MAIN
END:     stop 34
