
    LDR r4, =primes
    MOV r5, #0
    MOV r6, #2

loop_main:
    CMP r5, #20
    BEQ end
    MOV r7, #2
    MOV r10, #1

loop_div:
    MUL r9, r7, r7
    CMP r9, r6
    BGT store_prime
    MOV r8, r6

div_check:
    CMP r8, r7
    BLT next_div
    SUB r8, r8, r7
    CMP r8, #0
    BEQ not_prime
    B div_check

next_div:
    ADD r7, r7, #1
    B loop_div

not_prime:
    MOV r10, #0

store_prime:
    CMP r10, #1
    BNE skip_store
    MOV r0, r5
    LSL r0, r0, #2
    ADD r1, r4, r0
    STR r6, [r1]
    ADD r5, r5, #1

skip_store:
    ADD r6, r6, #1
    B loop_main

end:
    B end

