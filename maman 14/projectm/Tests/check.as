; aaaaaaaaaaaaaaaaaaaaaa
; dsfKAFHHCIZHIVABCSBKAKLFHL46511946344893

.entry L
.entry ABC
.entry CBA
	.extern A
 .extern B
.extern C



	M: mov #-2,r0
 	
	
cmp X	,	#4
cmp r3 , r4
 
 add r1,r3
sub #5 ,	X
   sub X,X
   not r0

ABC: not X

inc A
inc r7

CBA: dec B
dec r7

jmp C
bne r5


prn C
prn B
prn #-7

rts 
E: stop






STR1: .string "abcd"
STR2: .string "abcdef"
STR3: .string "abc"
X: .data +4
ARR: .data 	+5,-6	, 4 , +8,	 -3



