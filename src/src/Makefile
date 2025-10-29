# Week 5 Makefile
# Usage:
#   make            # build all
#   make run1       # run task 1
#   make run2       # run task 2
#   make run3       # run task 3 (menu app)
#   make run4       # run bonus task 4 (binary I/O) if built
#   make clean
#   make lab5       # sanity compile check (all with -Wall)

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2

BIN1    := week5_task1_file_io
BIN2    := week5_task2_struct_save_load
BIN3    := week5_task3_student_management_system
BIN4    := week5_task4_struct_binary_io

SRC1    := week5_task1_file_io.c
SRC2    := week5_task2_struct_save_load.c
SRC3    := week5_task3_student_management_system.c
SRC4    := week5_task4_struct_binary_io.c

.PHONY: all clean run1 run2 run3 run4 lab5

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)

$(BIN1): $(SRC1)
	$(CC) $(CFLAGS) $< -o $@

$(BIN2): $(SRC2)
	$(CC) $(CFLAGS) $< -o $@

$(BIN3): $(SRC3)
	$(CC) $(CFLAGS) $< -o $@

$(BIN4): $(SRC4)
	$(CC) $(CFLAGS) $< -o $@

run1: $(BIN1)
	./$(BIN1)

run2: $(BIN2)
	./$(BIN2)

run3: $(BIN3)
	./$(BIN3)

run4: $(BIN4)
	./$(BIN4)

lab5: all
	@echo "All targets compiled with $(CFLAGS)"

clean:
	$(RM) $(BIN1) $(BIN2) $(BIN3) $(BIN4) data.txt student.txt student.bin students.txt

