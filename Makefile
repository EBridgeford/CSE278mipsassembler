CC = g++
FILES = main.cpp
OUT_EXE = mips_assembler.o
FLAG = -std=c++11

build:
	$(CC) $(FLAG) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

.PHONY: clean
rebuild: clean build
