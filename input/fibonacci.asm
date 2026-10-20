# Problem 2: Calculate the Fibonacci number of n = 10
# Result F(10) = 55 is stored in x10 (a0) and at memory address 256 (0x100)

addi x11, zero, 10      # x11 = n = 10
addi x10, zero, 0       # x10 = F(0) = 0 (holds result)
beq x11, zero, fib_done # if n == 0, result is 0

addi x12, zero, 0       # x12 = prev = 0
addi x10, zero, 1       # x10 = curr = 1
addi x13, zero, 1       # x13 = i = 1

fib_loop:
bge x13, x11, fib_done  # if i >= n, loop finished
add x14, x12, x10       # x14 = next = prev + curr
addi x12, x10, 0        # prev = curr
addi x10, x14, 0        # curr = next
addi x13, x13, 1        # i++
j fib_loop

fib_done:
addi x8, zero, 256      # x8 = 0x100 (data memory address for result)
sw x10, 0(x8)           # Mem[0x100] = F(10) = 55
addi x0, x0, 0          # nop (end of program)