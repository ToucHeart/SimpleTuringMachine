; the finite set of states
#Q = {0,match,write1,write2,rewrite,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1}

; the complete set of tape symbols
#G = {1,_,t,r,u,e,f,a,l,s,x}

; the set of final states
#F = {halt_accept}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the number of tapes
#N = 3

; the transition functions

; State 0: start state
0 ___ ___ *** accept ; empty input
0 1__ 11x *** match  ; begin match

match 11x __x rrr match 
match 11_ ___ rrr match
match _*_ ___ *** reject ; no 1 left
match ___ ___ *** accept ;
match 1__ 11_ *rr write1 ; down tape is over, write more 1

write1 1__ 11_ *ll write2 ;write more 2

write2 11_ 11_ *ll rewrite ;rewrite before blank

rewrite 1__ 11_ *ll rewrite 
rewrite 1_x 11x *** match


; State accept*: write 'true' on 1st tape
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

; State reject*: write 'false' on 1st tape
reject _*_ ___ *** reject
reject ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject






