; Define data segments
MS4:     .string "Maximum finder program"
NUMBERS: .data 10, -7, 12, -15
MAXIMUM: .data 0
; External and entry references (assuming needed)
.extern Display
MAIN:    mov NUMBERS, @r2
         mov @r2, @r1
         mov 4, @r3
LOOPMAX: cmp @r1, @r2
         jmp UPDATE
         inc @r2
         dec @r3
         bne LOOPMAX
         jmp CONTINUE
UPDATE:  mov @r2, @r1
         jmp LOOPMAX
CONTINUE: mov @r1, @r0
; Display the maximum value
         prn @r1
         jmp END
.entry MAIN
END:     stop