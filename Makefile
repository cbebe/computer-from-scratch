CC=gcc
CFLAGS=-O2 -Wall -Isrc

CPU:=$(wildcard cpu/*.c)
CPU_OBJ:=$(SRC:cpu/%.c=obj/c/%.o)
TESTS:=exe/cpu-test exe/asm-test
T_OBJ_DIR:=tests/obj

ASM:=$(wildcard asm/*.cpp)
ASM_OBJ:=$(ASM:asm/%.cpp=obj/cpp/%.o)

	
all: asm cpu

asm:
	cd asm && $(MAKE)

cpu:
	cd cpu && $(MAKE)

# this makefile is really messy pls do something about this
exe/cpu-test: $(T_OBJ_DIR)/cpu-test.o obj/c/cpu.o | exe
	$(CC) $^ -o $@

exe/asm-test: $(T_OBJ_DIR)/asm-test.o obj/cpp/Code.o obj/cpp/Parser.o obj/cpp/strhelp.o | exe
	$(CXX) $^ -o $@

tests/obj/asm-test.o: tests/asm-test.cpp | $(T_OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

tests/obj/cpu-test.o: tests/cpu-test.c | $(T_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(T_OBJ_DIR):
	mkdir -p $@

exe:
	mkdir -p $@

test: $(TESTS) 
	./exe/cpu-test
	./exe/asm-test

clean:
	cd code/asm && $(MAKE) clean
	cd code/cpu && $(MAKE) clean

.PHONY: all asm cpu test clean
