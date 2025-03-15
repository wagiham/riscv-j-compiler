.text
.p2align 2
.globl square
square:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw fp, 0(sp)
    addi fp, sp, 8
    # Handle GET_ARG
   addi sp, sp, -4 
sw a0, 0(sp)
    lw t0, 0(sp)     # Load the top item into t0
    addi sp, sp, -4  # Move the stack pointer down
    sw t0, 0(sp)     # Store t0 back onto the stack
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    mul t2, t1, t0  # t2 = t1 * t0
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
lw fp, 0(sp)
lw ra, 4(sp)
addi sp, sp, 8
jr ra
.globl main
main:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw fp, 0(sp)
    addi fp, sp, 8
    # Handle LITERAL: 4
    li t0, 4       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
call square
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
    # Handle LITERAL: 5
    li t0, 5       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
call square
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
lw fp, 0(sp)
lw ra, 4(sp)
addi sp, sp, 8
jr ra
