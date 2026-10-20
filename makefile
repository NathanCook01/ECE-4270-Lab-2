CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = Lab2

all: $(TARGET)

$(TARGET): src/Lab2.c src/Lab2.h
	$(CC) $(CFLAGS) src/Lab2.c -o $(TARGET)

assemble: $(TARGET)
	./$(TARGET) input/bubblesort.asm input/problem1_machine_code.txt
	./$(TARGET) input/fibonacci.asm input/problem2_machine_code.txt

clean:
	rm -f $(TARGET) output.txt input/*_machine_code.txt