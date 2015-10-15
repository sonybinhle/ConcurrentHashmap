CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=celeraoneEx2

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
$(CXX) -o $(BIN) $^

%.o: %.c
$(CXX) $@ -c $<

clean:
rm -rf *.o $(BIN)
