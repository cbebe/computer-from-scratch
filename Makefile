CC=gcc
CFLAGS=-O2 -Wall -Isrc

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)
TESTS:=exe/cpu-test



test: $(TESTS) 
	./exe/cpu-test

exe/cpu-test: tests/obj/cpu-test.o obj/cpu.o | exe
	$(CC) $^ -o $@

tests/obj/cpu-test.o: tests/cpu-test.c | tests/obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

tests/obj:
	mkdir $@

obj:
	mkdir $@

exe:
	mkdir $@

.PHONY:
clean:
	@rm -rf obj
	@rm -rf exe
	@rm -rf tests/obj
