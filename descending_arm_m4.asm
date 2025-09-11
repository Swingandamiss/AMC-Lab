;This is the first ARM Assembly language program you see in the lab
;This program template was created by Airs Lin @ 2017 California State University of Los Angeles.
;When you write your program, you could have your info at the top document block
;For Example:  Your Name, Student Number, what the program is for, and what it does etc.

; Constant Variable Here
STACK_ADDR_123G EQU     0x20008000

            THUMB

; Vector Table Mapped to Address 0 at Reset
; Linker requires __Vectors to be exported

            AREA    RESET, DATA, READONLY
            EXPORT  __Vectors
__Vectors
            DCD     STACK_ADDR_123G         ; stack pointer value when stack is empty
            DCD     Reset_Handler           ; reset vector

            ALIGN

            AREA    |.text|, CODE, READONLY
            ENTRY                           ; mark first instruction to execute
            EXPORT Reset_Handler
Reset_Handler


;;;;;;;;;; Your Main Code Starts from the next line ;;;;;;;;;;;;
			LDR R4, =0x20000000
            MOV     R5, #10                 
            SUB R5, R5, #1                  
OuterLoop	MOV     R6, R5                  
            MOV     R7, R4                  
InnerLoop	LDR     R0, [R7]    
			LDR		R1, [R7, #4]              
            CMP     R0, R1                  
            BGE     NoSwap                  
            STR     R1, [R7]    
            STR     R0, [R7, #4]
NoSwap		ADD     R7, R7, #4              
            SUB     R6, R6, #1              
            CMP     R6, #0                 
            BGT     InnerLoop               
            SUB     R5, R5, #1              
            CMP     R5, #0                  
            BGT     OuterLoop
			B .
            END
