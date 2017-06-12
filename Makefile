COMPILER=gcc
SRC=./src/*.c
INCLUDEDIR=./include/
BINARY=t2
INPUT=

all:
	$(COMPILER) $(SRC) -I$(INCLUDEDIR) -o $(BINARY)

run:
	./$(BINARY) $(INPUT)

clear:
	rm *.dat *.idx vgcore* $(BINARY)

# for denugging purposes only
bug:
	$(COMPILER) $(SRC) -I$(INCLUDEDIR) -o $(BINARY) -g


