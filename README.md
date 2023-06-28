# RTL compact simulator

This code simulates 
AND
ADD
LDA
STA
BUN
BSA
ISZ
CLA
CLE
CMA
CME
CIR
CIL
INC
SPA
SNA
SZA
SZE
HLT
.

This code uses AC,PC,E register. Not MR, IR, AR, etc..

Place your code to array M
for example, 
    M[2] = { 0,"DEC","CTR","-8" };
    M[3] = { 0,"DEC","X","15" };
    M[4] = { 0,"DEC","Y","11" };
    M[5] = { 0,"DEC","P","0" };

First component means indirect.
Second component means op-code name.
Third component means lable-name. if there is no lable-name, leave it empty.
Last component means data. this should be string type. Also, HEX data is not readable. you need to convert HEX number to DEC number so that there would be no alphabet.
