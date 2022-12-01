; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {0,cp,cmp,mh,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}  ;dasfasfasdf

; the finite set of input symbols
#S = {0,1}     ;dasfasfasdf

; the complete set of tape symbols
#G = {0,1,_,t,r,u,e,f,a,l,s}  ;dasfasfasdf

; the set of final states
#F = {halt_accept} ;dasfasfasdf

; the start state
#q0 = halt_accept ;dasfasfasdf

; the blank symbol
#B =   _  ;dasfasfasdf

; the number of tapes
#N =   223    ;dasfasfasdf

; the transition functions