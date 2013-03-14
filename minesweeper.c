#include "minesweeper.h"

Minefield *initEmptyMinefield(unsigned x, unsigned y){
    Minefield minefield;
   
    int i, j;
    
    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++){
            minefield.places[i][j].mine = EMPTY;
            minefield.places[i][j].state = HIDDEN;
            minefield.places[i][j].numberOfMinesNear = 0;
        }
    minefield.xSize = x;
    minefield.ySize = y;
    return &minefield;
}

Minefield *makeGame(unsigned x, unsigned y, unsigned mines){
    int i, j;  
    Minefield *minefield = initEmptyMinefield(x, y);
    unsigned minesToPlace = mines;
    srand(time(NULL));
    while(minesToPlace > 0){
      i = rand() % x;
      j = rand() % y;

      if(minefield->places[i][j].mine)
          continue;
   
      minefield->places[i][j].mine = MINE;
      printf("%d, %d\n", i, j);
      minesToPlace--;      
    }  
    minefield->minesNumber = mines;
    return minefield;
}

void increaseNumberOfMilesAround(Minefield *field, int x, int y ){
    int s, t;
    for(s = x - 1; s <= x + 1; s++)
        for(t = y - 1; t <= y + 1; t++)
            if((s >= 0 && t >= 0) &&
               (s < field->xSize && t < field->ySize)) 
               field->places[s][t].numberOfMinesNear++;
}

void placeNumbers(Minefield *field){
    int i, j, s, t;
    for(i = 0; i < field->xSize; i++)
        for(j = 0; j < field->ySize; j++)
            if(field->places[i][j].mine)
                increaseNumberOfMilesAround(field, i, j);
}

void openNearbyPlaces(Minefield *field, int x, int y){
    openPlace(field, x - 1, y); 
    openPlace(field, x, y - 1); 
    openPlace(field, x + 1, y ); 
    openPlace(field, x, y + 1);
}

void openPlace(Minefield *field, int x, int y){
    if(x < 0 || x >= field->xSize || y < 0 || y >= field->ySize)
        return;
    if(field->places[x][y].state != VISIBLE){
       field->places[x][y].state = VISIBLE;
       if(field->places[x][y].numberOfMinesNear == 0)
            openNearbyPlaces(field, x, y);
    }
}

int moveWith(Minefield *field, int x, int y, int action){

    if(x >= 0 && x < field->xSize && y >= 0 && y < field->ySize){
        if(action == 1)
            openPlace(field, x, y);
        else
            field->places[x][y].state = FLAG;
       
        checkGameState(field);
        if(Gamestate != PLAY)
            return 0;
        else
            return 1;
    }
    return 0;
}

void updateMinesPlaces(Minefield *field, int newState){
    int i, j;
    for(i = 0; i < field->xSize; i++)
        for(j = 0; j < field->ySize; j++)
            if(field->places[i][j].mine == MINE)
                field->places[i][j].state = newState;
}

void checkGameState(Minefield *field){
    int i, j;
    int countOfVisibles = 0;
    int xSize = field->xSize;
    int ySize = field->ySize;
    for(i = 0; i < xSize; i++){
        for(j = 0; j < ySize; j++){
            if(field->places[i][j].state == VISIBLE && field->places[i][j].mine == MINE){
                Gamestate = FAIL;
                updateMinesPlaces(field, VISIBLE);
                return;
            }

            if(field->places[i][j].state == VISIBLE)
                countOfVisibles++;
        }
    }


    if(countOfVisibles == xSize*ySize - field->minesNumber){
        Gamestate = WIN;
        updateMinesPlaces(field, FLAG);
        return;
    }
}

/* Simple controls, may be replaced by more advanced */
int makeMove(Minefield *field){
    int x, y, action;
    printf(">> ");
    scanf("%d %d %d", &x, &y, &action);
    return moveWith(field, x, y, action);
}

int makeFirstMove(Minefield *field){

    int x, y;
    int action;
    int i, j;

    printf(">> ");
    scanf("%d %d %d", &x, &y, &action);
    srand(time(NULL));
    
    while(field->places[x][y].mine == MINE){
        // remove mine
        field->places[x][y].mine = EMPTY;
        // place a new mine
        i = rand() % field->xSize;
        j = rand() & field->ySize;
        field->places[i][j].mine = MINE;
    }
    
    placeNumbers(field);
        
    return moveWith(field, x, y, action);
}
/* Simple view */
void drawField(Minefield *field){
    int i, j;
    for(i = 0; i < field->xSize; i++){
        for(j = 0; j < field->ySize; j++)
            switch(field->places[i][j].state){
                case VISIBLE:
                {
                     if(field->places[i][j].mine)
                         printf("*");
                     else
                        printf("%d", field->places[i][j].numberOfMinesNear);
                }break;
                case HIDDEN:
                {
                     printf("?");
                }break;
                case FLAG:
                {
                     printf("F");
                }break;
                default:
                break;
            }
        printf("\n");
    }
}
/**/

int play(Minefield *field){
    int startTime = time(NULL);
    int playTime;
    
    drawField(field);
    makeFirstMove(field);
      
    while( Gamestate == PLAY ){
        drawField(field); 
        makeMove(field);
    };
    if( Gamestate == FAIL )
    {
        printf("\n*****GAME OVER!*****\n");
        drawField(field);
    }
    if( Gamestate == WIN )
    {
        printf("\n*****YOU WIN!*****\n");
        drawField(field);
    }
    
    playTime = time(NULL) - startTime;
    printf("time: %d seconds\n", playTime);
    return 0;
}

int main(int argc, char* argv[]){
    
    if(argc == 1){
        Minefield *gameField = makeGame(DEFAULT_X, DEFAULT_Y, DEFAULT_MINES);
        play(gameField);        
    }
    return 0;
}
