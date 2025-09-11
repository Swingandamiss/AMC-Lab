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
			LDR R0, =0x20000000
			LDR R1, =0x20000044
			MOV R2, #10
			MOV R3, #0
LOOP 		LDR R4, [R0]
			LDR R5, [R1]
			SUB R6, R4, R5
			CMP R6, #0
			BGE NO_NEG
			NEG R6, R6
NO_NEG 		ADD R3, R3, R6
			ADD R0, R0, #4
			ADD R1, R1, #4
			SUB R2, R2, #1
			CMP R2, #0
			BGT LOOP
			LDR R7, =0x20000088
			STR R3, [R7]
			B .
			END
