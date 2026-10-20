# Problem 1: Bubble Sort of 10 integers A = {5, 3, 6, 8, 9, 1, 4, 7, 2, 10}
# Base address of array A in data memory: x8 = 256 (0x100)

addi x8, zero, 256      # x8 = base address of A in data segment (0x100)

# Store initial array values A = {5, 3, 6, 8, 9, 1, 4, 7, 2, 10} into memory
addi x5, zero, 5
sw x5, 0(x8)            # A[0] = 5
addi x5, zero, 3
sw x5, 4(x8)            # A[1] = 3
addi x5, zero, 6
sw x5, 8(x8)            # A[2] = 6
addi x5, zero, 8
sw x5, 12(x8)           # A[3] = 8
addi x5, zero, 9
sw x5, 16(x8)           # A[4] = 9
addi x5, zero, 1
sw x5, 20(x8)           # A[5] = 1
addi x5, zero, 4
sw x5, 24(x8)           # A[6] = 4
addi x5, zero, 7
sw x5, 28(x8)           # A[7] = 7
addi x5, zero, 2
sw x5, 32(x8)           # A[8] = 2
addi x5, zero, 10
sw x5, 36(x8)           # A[9] = 10

# Bubble Sort initialization
addi x9, zero, 9        # x9 = n - 1 = 9 (outer loop bound)
addi x10, zero, 0       # x10 = i = 0 (outer loop counter)

outer_loop:
bge x10, x9, done       # if i >= 9, sorting is complete
sub x12, x9, x10        # x12 = 9 - i (inner loop bound)
addi x11, zero, 0       # x11 = j = 0 (inner loop counter)

inner_loop:
bge x11, x12, next_outer # if j >= 9 - i, finish inner pass
slli x13, x11, 2        # x13 = j * 4 (byte offset)
add x13, x8, x13        # x13 = &A[j]
lw x14, 0(x13)          # x14 = A[j]
lw x15, 4(x13)          # x15 = A[j + 1]
bge x15, x14, no_swap   # if A[j + 1] >= A[j], no swap needed
sw x15, 0(x13)          # A[j] = x15
sw x14, 4(x13)          # A[j + 1] = x14

no_swap:
addi x11, x11, 1        # j++
j inner_loop

next_outer:
addi x10, x10, 1        # i++
j outer_loop

done:
addi x0, x0, 0          # nop (end of program)