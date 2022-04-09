CXX=clang++
CFLAGS=-g -std=c++11 -Wall -pedantic
LIBS = ntl
LINKFLAGS = $(addprefix -l,$(LIBS))
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
APPNAME=heratio_demo
BIN=$(BINDIR)/$(APPNAME)

all:$(BIN)

$(BIN):$(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(BIN) $(LINKFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) -r $(BINDIR)/* $(OBJ)/*