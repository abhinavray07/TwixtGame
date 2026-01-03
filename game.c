#include <stdio.h>
#include "game.h"
#include <stdbool.h>
#include <string.h>

#define RESET "\033[0m"
#define WHITE "\033[37m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

const int KNIGHT_MOVES[8][2] = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

Game initGame(){
    Game g;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++){
        g.grid[i] = CELL_EMPTY;
    }       

    g.isRedTurn = true;
    g.linkCount = 0;
    return g;
}

bool doLinksIntersect(int x1, int y1, int x2,int y2,int x3, int y3,int x4,int y4){
    int d1x = x2 - x1, d1y = y2 -y1;
    int d2x = x4 - x3, d2y = y4-y3;
    int d3x = x3 - x1, d3y = y3- y1;

    long long cross1 = (long long)d1x*d3y - (long long)d1y*d3x;
    long long cross2 = (long long)d1x*(y4 - y1) -(long long)d1y*(x4 - x1);
    long long cross3 = (long long)d2x*(-d3y) -(long long)d2y* (-d3x);
    long long cross4 = (long long)d2x*(y2 - y3) -(long long)d2y *(x2 - x3);

    if (cross1 * cross2 < 0 && cross3 * cross4 < 0)return true;

    return false;
}

bool wouldLinkCross(Game *g, int x1, int y1, int x2, int y2){
    for (int i = 0; i < g->linkCount; i++){
        Link *link = &g->links[i];
        if (doLinksIntersect(x1, y1, x2, y2, link->x1, link->y1, link->x2, link->y2))return true;
    }
    return false;
}

void addLink(Game *g, int x1, int y1, int x2, int y2, int color){
    if (g->linkCount < MAX_LINKS){
        g->links[g->linkCount].x1 =x1;
        g->links[g->linkCount].y1 =y1;
        g->links[g->linkCount].x2 =x2;
        g->links[g->linkCount].y2 =y2;
        g->links[g->linkCount].color = color;
        g->linkCount++;
    }
}

void createLinksFromPin(Game *g, int x, int y, int color){
    for (int i = 0; i < 8; i++){
        int nx = x +KNIGHT_MOVES[i][0];
        int ny = y +KNIGHT_MOVES[i][1];
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE){
            int index = ny * BOARD_SIZE + nx;
            if (g->grid[index] == color){
                if (!wouldLinkCross(g, x, y, nx, ny)) addLink(g, x, y, nx, ny, color);
            }
        }
    }
}

void printBoard(Game *g){
    printf("\n");
    
    printf("      ");
    for (int x = 0; x < BOARD_SIZE; x++) printf(" %2d", x);
    printf("\n\n");
    
    printf(" %2d    ", 0);
    for (int x = 0; x < BOARD_SIZE; x++){
        if (x == 0 || x == BOARD_SIZE - 1) {
            printf("   ");  
        } else {
            int index = 0 * BOARD_SIZE + x;
            if (g->grid[index] == CELL_RED) printf(" %s●%s ", RED, RESET);
            else if (g->grid[index] == CELL_BLACK) printf(" %s●%s ", BLUE, RESET);
            else printf(" %s.%s ", WHITE, RESET);
        }
    }
    printf("\n");
    
    printf("          ");
    for (int x = 1; x < BOARD_SIZE - 1; x++) printf("%s───%s", RED, RESET);
    printf("\n");
    
    for (int y = 1; y < BOARD_SIZE - 1; y++){
        printf(" %2d     ", y);
        
        int left_index = y * BOARD_SIZE + 0;
        if (g->grid[left_index] == CELL_RED) printf("%s●%s", RED, RESET);
        else if (g->grid[left_index] == CELL_BLACK) printf("%s●%s", BLUE, RESET);
        else printf("%s.%s", WHITE, RESET);
        
        printf("%s│%s", BLUE, RESET);
        
        for (int x = 1; x < BOARD_SIZE - 1; x++){
            int index = y * BOARD_SIZE + x;
            if (g->grid[index] == CELL_RED) printf(" %s●%s ", RED, RESET);
            else if (g->grid[index] == CELL_BLACK) printf(" %s●%s ", BLUE, RESET);
            else printf(" %s.%s ", WHITE, RESET);
        }
        
        printf("%s│%s", BLUE, RESET);
        
        int right_index = y * BOARD_SIZE + (BOARD_SIZE - 1);
        if (g->grid[right_index] == CELL_RED) printf("%s●%s", RED, RESET);
        else if (g->grid[right_index] == CELL_BLACK) printf("%s●%s", BLUE, RESET);
        else printf("%s.%s", WHITE, RESET);
        
        printf("\n");
    }
    
    printf("          ");
    for (int x = 1; x < BOARD_SIZE - 1; x++) printf("%s───%s", RED, RESET);
    printf("\n");
    
    printf(" %2d    ", BOARD_SIZE - 1);
    for (int x = 0; x < BOARD_SIZE; x++){
        if (x == 0 || x == BOARD_SIZE - 1) {
            printf("   ");
        } else {
            int index = (BOARD_SIZE - 1) * BOARD_SIZE + x;
            if (g->grid[index] == CELL_RED) printf(" %s●%s ", RED, RESET);
            else if (g->grid[index] == CELL_BLACK) printf(" %s●%s ", BLUE, RESET);
            else printf(" %s.%s ", WHITE, RESET);
        }
    }
    printf("\n");
    printf("\nLinks: %d\n", g->linkCount);
}

bool dfsPath(Game *g, int x, int y, int color, bool visited[BOARD_SIZE][BOARD_SIZE],int targetStart, int targetEnd, bool isVertical){
    if (isVertical) if (y == targetEnd) return true;
    else if (x == targetEnd) return true;
    
    visited[y][x] = true;
    
    for (int i = 0; i < g->linkCount; i++){
        Link *link = &g->links[i];
        if (link->color != color) continue;
        
        int nx = -1, ny = -1;
        
        if (link->x1 == x && link->y1 == y){
            nx = link->x2;
            ny = link->y2;
        } 
        else if (link->x2 == x && link->y2 == y){
            nx = link->x1;
            ny = link->y1;
        }
        
        if (nx != -1 && !visited[ny][nx]){
            if (dfsPath(g, nx, ny, color, visited, targetStart, targetEnd, isVertical)) return true;
        }
    }
    
    return false;
}

bool checkWinCondition(Game *g, int color) {
    bool visited[BOARD_SIZE][BOARD_SIZE];
    memset(visited, 0, sizeof(visited));
    
    if (color == CELL_RED){
        for(int x = 1; x < BOARD_SIZE - 1; x++){
            int index = 0 * BOARD_SIZE + x;
            if (g->grid[index] == CELL_RED) {
                memset(visited, 0, sizeof(visited));
                if (dfsPath(g, x, 0, CELL_RED, visited, 0, BOARD_SIZE - 1, true)) {
                    return true;
                }
            }
        }
    }
    else{
        for(int y = 1; y < BOARD_SIZE - 1; y++){
            int index = y * BOARD_SIZE + 0;
            if (g->grid[index] == CELL_BLACK){
                memset(visited, 0, sizeof(visited));
                if (dfsPath(g, 0, y, CELL_BLACK, visited, 0, BOARD_SIZE - 1, false)) return true;
            }
        }
    }
    
    return false;
}

int placePinAndSwitch(Game *g, int x, int y){
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return 0;
    if ((x == 0 && y == 0)|| (x == BOARD_SIZE - 1 && y == 0) || (x == 0 && y == BOARD_SIZE - 1)  || (x == BOARD_SIZE - 1 && y == BOARD_SIZE - 1)){
        return 0;
    }
    
    if (g->isRedTurn) {
        if (x == 0 || x == BOARD_SIZE - 1) {
            printf("Red cannot place on left/right borders!\n");
            return 0;
        }
    } else {
        if (y == 0 || y == BOARD_SIZE - 1) {
            printf("Black cannot place on top/bottom borders!\n");
            return 0;
        }
    }

    int index = y * BOARD_SIZE + x;
    if (g->grid[index] != CELL_EMPTY) return 0;
    int color = g->isRedTurn ? CELL_RED : CELL_BLACK;
    g->grid[index] = color;
    createLinksFromPin(g, x, y, color);
    if (checkWinCondition(g, color)) {
        printf("\n %s WINS! \n", g->isRedTurn ? "RED" : "BLACK");
        printBoard(g);
        return 2;  
    }
    g->isRedTurn = !g->isRedTurn;
    return 1;
}
