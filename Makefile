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
	clear
clean:
	rm *.dat *.idx $(BINARY)

# for denugging purposes only
bug:
	$(COMPILER) $(SRC) -I$(INCLUDEDIR) -o $(BINARY) -g
	valgrind $(VALFLAGS) ./$(BINARY) $(INPUT)
	
# For Bruno's private use
open:
	gedit $(SRC) $(INCLUDEDIR)*.h
	
test:
	clear
	$(COMPILER) test.c -o teste
	./teste


