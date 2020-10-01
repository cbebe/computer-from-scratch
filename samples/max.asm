// comparing R0 and R1
@R0
D=M 
@R1
D=D-M
@R0GREATER
D;JGT
@R1 
D=M // load R1 in the D register
@LOAD
0;JMP
(R0GREATER)
@R0 
D=M // load R0 in the D register
(LOAD)
@R2
M=D