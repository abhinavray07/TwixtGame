#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define BOARD_SIZE 24
#define CELL_EMPTY 0
#define CELL_RED 1
#define CELL_BLACK 2
#define MAX_LINKS 2000

typedef struct {
    int x1, y1;  
    int x2,y2;  
    int color;   
} Link;

typedef struct{
    int grid[BOARD_SIZE * BOARD_SIZE]; 
    bool isRedTurn;
    Link links[MAX_LINKS];
    int linkCount;
} Game;

Game initGame();  
void printBoard(Game *g);
int placePinAndSwitch(Game *g, int x,int y); 
bool checkWinCondition(Game *g,int color); 

#endif
