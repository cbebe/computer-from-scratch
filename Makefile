CC=gcc
CXX=g++
CFLAGS=-O2 -Wall -Isrc
CPPFLAGS=-O2 -Wall -Iasm

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/c/%.o)
TESTS:=exe/cpu-test exe/asm-test
T_OBJ_DIR:=tests/obj

ASM:=$(wildcard asm/*.cpp)
ASM_OBJ:=$(ASM:asm/%.cpp=obj/cpp/%.o)

test: $(TESTS) 
	./exe/cpu-test
	./exe/asm-test

# this makefile is really messy pls do something about this
exe/cpu-test: $(T_OBJ_DIR)/cpu-test.o obj/c/cpu.o | exe
	$(CC) $^ -o $@

exe/asm-test: $(T_OBJ_DIR)/asm-test.o obj/cpp/Code.o obj/cpp/Parser.o | exe
	$(CXX) $^ -o $@

tests/obj/asm-test.o: tests/asm-test.cpp | $(T_OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

tests/obj/cpu-test.o: tests/cpu-test.c | $(T_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

obj/c/%.o: src/%.c | obj/c
	$(CC) $(CFLAGS) -c $< -o $@

obj/cpp/%.o: asm/%.cpp | obj/cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(T_OBJ_DIR):
	mkdir $@

obj/c:
	mkdir -p $@

obj/cpp:
	mkdir -p $@

exe:
	mkdir $@

.PHONY:
clean:
	@rm -rf obj
	@rm -rf exe
	@rm -rf tests/obj
