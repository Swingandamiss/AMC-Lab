        ORG 0000h	
        MOV P1, #0FFh
        MOV P3, #0FFh
        MOV P2, #00h

MAIN:   MOV A, P3
        ANL A, #03h          

        CJNE A, #03h, SEL2   
        MOV C, P1.3
        MOV P2.0, C
        SJMP MAIN

SEL2:   CJNE A, #02h, SEL1   
        MOV C, P1.2
        MOV P2.0, C
        SJMP MAIN

SEL1:   CJNE A, #01h, SEL0  
        MOV C, P1.1
        MOV P2.0, C
        SJMP MAIN

SEL0:                      
        MOV C, P1.0
        MOV P2.0, C
        SJMP MAIN

        END
