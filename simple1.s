main:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    # Handle LITERAL: 5
    li t0, 5       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    # Handle LITERAL: 3
    li t0, 3       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    # Handle LITERAL: 2
    li t0, 2       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    mul t2, t1, t0  # t2 = t1 * t0
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    add t2, t1, t0  # t2 = t1 + t0
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
    # Handle LITERAL: 3
    li t0, 3       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    # Handle LITERAL: 4
    li t0, 4       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
    # Handle LITERAL: 5
    li t0, 5       # Load literal value into t0
    addi sp, sp, -4  # Adjust stack pointer
    sw t0, 0(sp)     # Store literal value on stack
lw t0, 0(sp)
lw t1, 4(sp)
lw t2, 8(sp)
sw t2, 0(sp)
sw t0, 4(sp)
sw t1, 8(sp)
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    mul t2, t1, t0  # t2 = t1 * t0
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
    lw t0, 0(sp)    # t0 = top of stack
    lw t1, 4(sp)    # t1 = second item in stack
    add t2, t1, t0  # t2 = t1 + t0
    addi sp, sp, 4  # Adjust stack pointer
    sw t2, 0(sp)    # Store result
    lw t0, 0(sp)     # Load value from top of stack
    addi sp, sp, 4   # Adjust stack pointer (pop)
    mv a0, t0       # Move value to argument register a0
    lw ra, 12(sp)
    lw s0, 8(sp)
    addi sp, sp, 16
ret
