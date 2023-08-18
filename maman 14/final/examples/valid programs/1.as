; Define some strings and data
MS2:     .string "New program"
VALUES:  .data 5, 7, 12, -3
SUM:     .data 0

; External and entry references (assuming needed)
.extern PrintVal

MAIN:
        mov SUM, @r0   ; Load the address of SUM into register r0
        clr @r1        ; Clear register r1 to store our running total
        
        ; Initialize loop variables
        mov VALUES, @r2    ; Load the address of VALUES into register r2
        mov 4, @r3         ; We have 4 values in the VALUES segment

LOOP:
        add @r2, @r1       ; Add value pointed by r2 to r1
        inc @r2            ; Move to the next value
        dec @r3            ; Decrease the count of remaining values
        bne LOOP           ; If we haven't processed all values, loop again

        ; Store the sum into SUM
        mov @r1, @r0

        ; (Assuming there's a function called PrintVal that can print an integer value)
        prn @r1            ; Print the sum
        jmp END            ; Jump to the end of the program

.entry MAIN

END:    
        stop               ; Terminate the program
