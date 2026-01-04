ORG	0000H
               DB            01000000B; IN R0
               DB            10000100B; LAD R1,[10H](Direct addressing
               DB            00010000B; 10H
               DB            10001001B; LAD R2,[R1](Register indirect addressing
               DB            10000100B; LAD R1,[16H](Direct addressing 
               DB            00010110B; 16H
               DB            01101100B; MOV R3,R0
               DB            11010001B; ADD R0,R1
               DB            11000111B; SUB R1,R3
               DB            10100001B; RR R0
               DB            11110001B; OR R0,R1
               DB            00100100B; INC R1
               DB            10010100B; STA(STO) 00H,R1
               DB            00000000B; 00H
               DB            00010000B; JUMP 18H
               DB            00011000B; 18H
               DB            00010011B; 13H
               DB            00000000B; NOP
               DB            00010101B; 15H
               DB            00110010B; 32H
               DB            00000000B; NOP
               DB            01110101B; 75H
               DB            00101000B; 28H
               DB            00000000B; NOP
               DB            01010100B; OUT R1,PORT0
               DB            11010100B; ADDI R1,11H
               DB            00010001B; 11H
               DB            01010100B; OUT R1,PORT0
               DB            00110100B; SET R1,[12H]
               DB            00010010B; 12H
               DB            01010100B; OUT R1,PORT0
               DB            00000001B; HLT
END