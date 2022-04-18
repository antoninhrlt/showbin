# This file is part of "showbin"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

# Constants
CC = gcc
DEBUG_FLAGS = -W -Wall -Wextra -g -pedantic -DDEBUG
RELEASE_FLAGS = -O2
FLAGS = -I inc/

# Variables
OUT_DIR = build/out
BIN = build/showbin

# Files
SRC = $(shell find src/ -name '*.c')
OBJ = $(patsubst src/%.c, $(OUT_DIR)/%.o, $(SRC))

_init: 
	mkdir -p build/ build/out

# A call to `_init` should be done after this :
clean:
	rm -rf build/

# Builder
build: _init $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

$(OUT_DIR)/%.o : src/%.c
	$(CC) $(FLAGS) -c -o $@ $<

# Tests runner

TESTS = $(shell find tests/ -name '*.c')
TESTS_BIN = $(patsubst tests/%.c, tests/%.test, $(TESTS))

define run_test
	@ echo "--- test :$(1) ---"
	- $(1)
	@ echo "--- end of test --\n"
endef

tests: build $(TESTS_BIN)

_tests:

tests/%.test : tests/%.c
	gcc -o $@ $<
	$(call run_test, $(BIN) $@ -o tests/$@.asm)

mem: build
	valgrind $(BIN)
