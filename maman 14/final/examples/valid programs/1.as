; Define some strings and data
MS2:     .string "New program"
VALUES:  .data 5, 7, 12, -3
SUM:     .data 0

; External and entry references (assuming needed)
.extern PrintVal

MAIN:
        mov SUM, @r0   
        clr @r1        
        
        ; Initialize loop variables
        mov VALUES, @r2    
        mov 4, @r3         

LOOP:
        add @r2, @r1       
        inc @r2            
        dec @r3            
        bne LOOP           

        ; Store the sum into SUM
        mov @r1, @r0

        ; (Assuming there's a function called PrintVal that can print an integer value)
        prn @r1            
        jmp END            

.entry MAIN

END:    
        stop               ; Terminate the program
