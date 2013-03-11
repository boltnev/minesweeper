#include <stdio.h>
#include <time.h>
#include <assert.h>
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
    Place places[MAX_X][MAX_Y];
};

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
    
    srand(time(NULL));
    while(mines > 0){
      i = rand() % x;
      j = rand() % y;

      if(minefield->places[i][j].mine)
          continue;
   
      minefield->places[i][j].mine = MINE;
      mines--;      
    }  
     
    return minefield;
}

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
void placeNumbers(Minefield *field){

    int i, j, s, t;
    for(i = 0; i < field->xSize; i++){
        for(j = 0; j < field->ySize; j++)
            if(field->places[i][j].mine)
            {
                for(s = i - 1; s <= i + 1; s++)
                    for(t = j - 1; t <= j + 1; t++)
                        if(s >= 0 && t >= 0 && s < field->xSize && t < field->ySize)
                            field->places[s][t].numberOfMinesNear++;
            }
    }
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

void openNearbyPlaces(Minefield *field, int x, int y){
    //x - 1, y - 1, 
    //x - 1 y + 1, 
    //x + 1, y - 1, 
    //x + 1, y + 1
    openPlace(field, x - 1, y); 
    openPlace(field, x, y - 1); 
    openPlace(field, x + 1, y ); 
    openPlace(field, x, y + 1);
}

/* Simple controls, may be replaced by more advanced */
int makeMove(Minefield *field){
    int x, y, action;
    printf(">> ");
    scanf("%d %d %d", &x, &y, &action);
    
    if(x >= 0 && x < field->xSize && y >= 0 && y < field->ySize){
        if(action == 1)
            openPlace(field, x, y);
        else
            field->places[x][y].state = FLAG;
        
        if(field->places[x][y].state == VISIBLE && field->places[x][y].mine == MINE){
            printf("\nGAME OVER!\n");
            return 0;
        }
              
        return 1;
    }
    return 0;
}
/**/

int play(Minefield *field){

    placeNumbers(field);
    do 
    {
        drawField(field); 
    }while( makeMove(field) );

    drawField(field);
    return 0;
}

int main(int argc, char* argv[]){
    
    if(argc == 1){
        Minefield *gameField = makeGame(DEFAULT_X, DEFAULT_Y, DEFAULT_MINES);
        play(gameField);        
    }
    return 0;
}
