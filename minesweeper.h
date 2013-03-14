#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DEFAULT_X 10
#define DEFAULT_Y 10
#define DEFAULT_MINES 10
#define MAX_X     500
#define MAX_Y     500
#define MAX_MINES 20000

//Place holds:
enum{
  EMPTY,
  MINE
};

//Place states;
enum{
  HIDDEN,
  VISIBLE,
  FLAG
};
//game Result
enum{
  WIN,
  FAIL,
  PLAY
};

typedef int gamestate;

typedef struct t_Place Place;

struct t_Place{
    unsigned numberOfMinesNear;
    int mine;
    int state;
};

typedef struct t_Minefield Minefield;

struct t_Minefield{
    int xSize;
    int ySize;
    unsigned minesNumber;
    Place places[MAX_X][MAX_Y];
};

gamestate Gamestate = PLAY;

Minefield *initEmptyMinefield(unsigned x, unsigned y);
Minefield *makeGame(unsigned x, unsigned y, unsigned mines);
void drawField(Minefield *field);
void increaseNumberOfMilesAround(Minefield * field, int x, int y);
void placeNumbers(Minefield *field);
void openNearbyPlaces(Minefield *field, int x, int y);
void openPlace(Minefield *field, int x, int y);

int moveWith(Minefield *field, int x, int y, int action);

/* Simple controls, may be replaced by more advanced */
int makeMove(Minefield *field);

int makeFirstMove(Minefield *field);

/**/

int play(Minefield *field);
