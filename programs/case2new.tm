; the finite set of states
#Q = {0,matchR,matchL,writeR1,writeL1,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1}

; the complete set of tape symbols
#G = {1,_,t,r,u,e,f,a,l,s}

; the set of final states
#F = {halt_accept}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the number of tapes
#N = 2

; the transition functions

; State 0: start state
0 __ __ ** accept  ; empty input
0 1_ _1 rr matchR  ; begin matchR

matchR 1_ 11 *r writeR1
matchR 11 _1 rr matchR
matchR __ __ ** accept
matchR _1 _1 ** reject

writeR1 1_ _1 rl matchL

matchL _1 _1 ** reject
matchL __ __ ** accept
matchL 11 _1 rl matchL
matchL 1_ 11 *l writeL1

writeL1 1_ _1 rr matchR

; State accept*: write 'true' on 1st tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; State reject*: write 'false' on 1st tape
reject _* __ ** reject
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject