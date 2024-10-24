execute: main.o sudoku.o
	g++ main.o sudoku.o -o execute

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp main.o 

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp -o sudoku.o 

clean: 
	rm -f main.o sudoku.o *~
