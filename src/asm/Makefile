SRC:=$(wildcard src/*.cpp)
OBJ:=$(SRC:src/%.cpp=obj/%.o)
INCLUDE_DIR:=include

# comment out for prod
DEBUG:=-g

CXX:=g++
CXXFLAGS:=-O2 -Wall -I$(INCLUDE_DIR) $(DEBUG)

EXE:=hasm

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p $@

PHONY:
clean:
	@rm $(OBJ) $(EXE)
	@rmdir obj