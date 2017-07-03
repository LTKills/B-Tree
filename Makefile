COMPILER=gcc
FLAGS = -Wall
VALFLAGS = --leak-check=full
SRC=./src/*.c
INCLUDEDIR=./include/
BINARY=t2
INPUT=input.csv

all: compile

compile:
	clear
	$(COMPILER) $(FLAGS) $(SRC) -I$(INCLUDEDIR) -o $(BINARY)

run: $(BINARY) $(INPUT)
	./$(BINARY) $(INPUT)

clean:
	rm *.dat *.idx vgcore* $(BINARY)


