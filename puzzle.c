#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "boardADT.h"
#include <math.h>


#define ERR_INVALID_SIZE -1
#define ERR_DUPLICATE_TILE -2
#define ERR_MISSING_TILES -3
#define ERR_INVALID_TILE -4

void printValidationMsg(int code);

int main()
{
    Board input_Board = createBoard();
    printf("\nElements : %d\n", input_Board->no_of_elements);
    display_board(input_Board);
    
    int validity = is_board_valid(input_Board);
    printf("\nInput validity :%d\n", validity);

    if(validity<0){
        printValidationMsg(validity);
        return EXIT_FAILURE;
    }

    // Board goal_Board = createBoard();
    // display_board(goal_Board);
    // validity = is_board_valid(goal_Board);
    // printf("\nGoal State validity :%d\n", validity);

    // printf("\nSolvable%d", solvable(input_Board, goal_Board));
    return EXIT_SUCCESS;
}

void printValidationMsg(int code){
    switch (code){
        case -1:
            printf("\nInvalid Board Size");
            break;
        
        case -2:
            printf("\nDuplicate Tiles present. Invalid Board.");
            break;

        case -3:
            printf("\nOne or more Tiles are missing. Invalid Board");
            break;

        case -4:
            printf("\nOne or more Tile(s) are invalid. Invalid Board");
            break;       

        default:
            printf("\nInvalid Board. Please check input");
            break;
    }
}