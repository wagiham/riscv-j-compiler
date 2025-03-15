.text
.p2align 2
.globl gcd
gcd:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw fp, 0(sp)
    addi fp, sp, 8
    # Handle GET_ARG
   addi sp, sp, -4 
sw a1, 0(sp)
    # Handle LITERAL: 0
    li t0, 0       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    sub t2, t1, t0  # t2 = t1 - t0
    seqz t2, t2     # t2 = (t1 == t0)
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
IF_1:
    lw t0, 0(sp)        # Load condition value
    addi sp, sp, 4      # Pop condition from stack
    beqz t0, SKIP_0    # Branch to ELSE if condition is false
    j ENDIF_0          # Jump to ENDIF
SKIP_0:
ENDIF_0:
    lw a0, 0(sp)    # Load return value into a0 (x10)
    addi sp, sp, 4
    mv sp, fp
    lw ra, -4(sp)
    lw fp, -8(sp)
    jr ra
.globl main
main:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw fp, 0(sp)
    addi fp, sp, 8
    # Handle LITERAL: 462
    li t0, 462       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    # Handle LITERAL: 1071
    li t0, 1071       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a1, t0       # Move value to argument register a1
call gcd
addi sp, sp, -4
sw x10, 0(sp)
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
call print_int
addi sp, sp, -4
sw x10, 0(sp)
call endl
addi sp, sp, -4
sw x10, 0(sp)
    lw a0, 0(sp)    # Load return value into a0 (x10)
    addi sp, sp, 4
    mv sp, fp
    lw ra, -4(sp)
    lw fp, -8(sp)
    jr ra
