CC = g++
LIBS = -llua

CFLAGS = -Wall -O -ggdb -std=c++14 $(LIBS)

SRC = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f main $(OBJ)