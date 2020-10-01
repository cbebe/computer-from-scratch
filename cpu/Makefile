SRC:=$(wildcard ./*.c)
OBJ:=$(SRC:./%.c=obj/%.o)
INCLUDE_DIR:=include

# comment out for prod
DEBUG:=-g

CC:=gcc
CFLAGS:=-O2 -Wall -I. $(DEBUG)

all: $(OBJ)

obj/%.o: ./%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p $@

.PHONY:
clean:
	@rm $(OBJ) 