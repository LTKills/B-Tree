COMPILER=gcc
FLAGS = -Wall
SRC=./src/*.c
INCLUDEDIR=./include/
BINARY=t2
INPUT=input.csv

all:
	clear
	$(COMPILER) $(FLAGS) $(SRC) -I$(INCLUDEDIR) -o $(BINARY)

run:
	./$(BINARY) $(INPUT)
	clear
clean:
	rm *.dat *.idx vgcore* $(BINARY)

# for denugging purposes only
bug:
	$(COMPILER) $(SRC) -I$(INCLUDEDIR) -o $(BINARY) -g
	valgrind ./$(BINARY) $(INPUT)
	
# For Bruno's private use
open:
	gedit $(SRC) $(INCLUDEDIR)*.h
	
test:
	clear
	$(COMPILER) test.c -o teste
	./teste


