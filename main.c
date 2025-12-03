#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "game.h"

void showHelp(){
    printf("Commands:\n");
    printf("  place x y  - place a pin\n");
    printf("  show       - print board\n");
    printf("  links      - show all links\n");
    printf("  help       - show this menu\n");
    printf("  quit       - exit game\n");
    printf("\nRules:\n");
    printf("  - Red connects TOP to BOTTOM\n");
    printf("  - Black connects LEFT to RIGHT\n");
    printf("  - Pins auto-link to nearby same-color pins (knight's move)\n");
    printf("  - Links cannot cross each other\n");
    printf("  - Red cannot place on left/right borders\n");
    printf("  - Black cannot place on top/bottom borders\n");
}

void showLinks(Game *g){
    printf("\n=== ALL LINKS ===\n");
    
    int redCount = 0, blackCount = 0;
    for (int i = 0; i < g->linkCount; i++){
        if (g->links[i].color == CELL_RED) redCount++;
        else blackCount++;
    }
    
    printf("Total Links: %d (Red: %d, Black: %d)\n\n", g->linkCount, redCount, blackCount);
    
    if(g->linkCount == 0){
        printf("No links yet.\n");
        return;
    }
    
    if(redCount > 0){
        printf("RED LINKS:\n");
        for (int i = 0; i < g->linkCount; i++){
            if (g->links[i].color == CELL_RED){
                printf("  (%d,%d) <--> (%d,%d)\n", 
                       g->links[i].x1, g->links[i].y1, 
                       g->links[i].x2, g->links[i].y2);
            }
        }
        printf("\n");
    }
    if(blackCount > 0){
        printf("BLACK LINKS:\n");
        for (int i = 0; i < g->linkCount; i++){
            if (g->links[i].color == CELL_BLACK) printf("  (%d,%d) <--> (%d,%d)\n",g->links[i].x1, g->links[i].y1,g->links[i].x2, g->links[i].y2);
        }
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Game game = initGame();
    char cmd[100];
    printf("Welcome to Twixt CLI!\n");
    showHelp();

    while (1){
        printf("\n(%s)> ", game.isRedTurn ? "Red" : "Black");
        fgets(cmd, sizeof(cmd), stdin);
        switch(cmd[0]){
            case 'q':  
                if (strncmp(cmd, "quit", 4) == 0){
                    printf("Godbye!\n");
                    return 0;
                }
                printf("Unknown comand.\n");
                break;
            case 'h':  
                if (strncmp(cmd, "help", 4) == 0){
                    showHelp();
                }
                else {
                    printf("Unknown comand.\n");
                }
                break;
            case 'l':  
                if (strncmp(cmd, "links", 5) == 0){
                    showLinks(&game);
                }
                else {
                    printf("Unknown command.\n");
                }
                break;
            case 's':  
                if (strncmp(cmd, "show", 4) == 0){
                    printBoard(&game);
                }
                else {
                    printf("Unknown comand.\n");
                }
                break;
            case 'p':  
                if (strncmp(cmd, "place", 5) == 0){
                    int x, y;
                    if (sscanf(cmd, "place %d %d", &x, &y) == 2){
                        int result = placePinAndSwitch(&game, x, y);
                        if (result == 0) {
                            printf("Invalid placement.\n");
                        } else if (result == 2) {
                            printf("\nPlay again? (y/n): ");
                            fgets(cmd, sizeof(cmd), stdin);
                            if (cmd[0] == 'y' || cmd[0] == 'Y') {
                                game = initGame();
                                printf("\nNew game started!\n");
                            } else {
                                return 0;
                            }
                        }
                    }
                    else {
                        printf("Usage: place x y\n");
                    }
                }
                else {
                    printf("Unknown command.\n");
                }
                break;
            default:
                printf("Unknown comand.\n");
                break;
        }
    }

    return 0;
}
