minesweeper: main.o
						 gcc main.c -o minesweeper
debug:			 main.o
						 gcc main.c -g -o minesweeper
clean:
						 rm -rf *.o
