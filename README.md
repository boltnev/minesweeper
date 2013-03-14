This is simple game named Minesweeper. Rules known to all. Not very stable at now this moment, but quite playable.

Instructions:

1. To compile: 

just run 

$ make

2. To run the game:

just run 

$ ./minesweeper

you will see the minefield 10X10 with 10 mines hidden in it.

3. To play 

put on your keyboard 3 digits separated by spaces: the X-coordinate, the Y-coordinate, and action 
if action == 1, it will open the place on (X, Y) position. If action != 1, then flag will be placed on (X, Y)

For example:

>> 1 2 1 // open place on (1, 2)  

>> 3 5 2 // set flag in (3, 5)

etc...

Game ends when all places, except mines, will be opened(win case) or when you open any place with mine in it :)  