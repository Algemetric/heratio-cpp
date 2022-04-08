CXX=clang++
LIBS = ntl
LINKFLAGS = $(addprefix -l, $(LIBS))
CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=heratio_demo

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^ $(LINKFLAGS)

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)