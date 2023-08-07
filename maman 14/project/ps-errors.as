MAIN: mov S1.1 ,LENGTH
 add r9,STR
LOOP: jmp
prn #r
sub r1, r4, r5
m1
bne LOOP
END: hlt #3
m1
STR: .string "abcdef
LENGTH: .data 6,-9,15
K: .data 22
S1: .struct 8, "ab" 