minesweeper: minesweeper.o
						 gcc minesweeper.c -o minesweeper
debug:			 minesweeper.o
						 gcc minesweeper.c -g -o minesweeper
clean:
						 rm -rf *.o
