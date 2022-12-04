; the finite set of states
#Q = {0,starthalt,copy1,copymore,topback,writelast1,downtapereturn,copyleft,halt}

; the finite set of input symbols
#S = {1,0}

; the complete set of tape symbols
#G = {1,_,0}

; the set of final states
#F = {halt}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the number of tapes
#N = 2

; the transition functions

; State 0: start state
0 __ __ ** starthalt                         ;empty string
0 1_ 11 rr copy1                        ;copy first one
0 0_ 00 rr copy1 

copy1 __ __ ** starthalt                     ;only one character
copy1 1_ 11 rr copymore                 ;more than one character
copy1 0_ 00 rr copymore

copymore 1_ 11 rr copymore              
copymore 0_ 00 rr copymore
copymore __ __ ll topback               ;top tape head back to first

topback ** ** l* topback                
topback _* _* r* writelast1             ;writelast1 to first one

writelast1 *1 11 rl downtapereturn      ;second tape head back to first
writelast1 *0 00 rl downtapereturn      

downtapereturn ** ** *l downtapereturn
downtapereturn *_ *_ *r copyleft        ;copy from 2 to last

copyleft *0 00 rr copyleft
copyleft *1 11 rr copyleft

copyleft _* _* ** starthalt                  ;halt

starthalt _* _* ll halt                       ;set head left to _
starthalt __ __ ll halt