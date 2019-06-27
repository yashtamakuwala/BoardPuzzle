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
#define ERR_INSUFFICIENT_MEMORY -5

void printValidationMsg(int code);

int main()
{
    Board input_Board = createBoard();
    int validity = input_Board->error;  //to check for errors while input-parsing

    if(validity<0){
        printf("\nWhile input parsing, Input board has ");
        printValidationMsg(validity);
        free_pointers(input_Board);
        return EXIT_FAILURE;
    }
       
    validity = is_board_valid(input_Board);

    if(validity<0){
        printf("\nInput board has ");
        printValidationMsg(validity);
        free(input_Board);
        return EXIT_FAILURE;
    }
    
    printf("\nstart: ");
    display_board(input_Board);

    Board goal_Board = createBoard();
    validity = goal_Board->error;

    if(validity<0){
        printf("\nGoal board has ");
        printValidationMsg(validity);
        free_pointers(goal_Board);
        return EXIT_FAILURE;
    }
       
    validity = is_board_valid(goal_Board);

    if(validity<0){
        printf("\nGoal board has ");
        printValidationMsg(validity);
        free(goal_Board);
        return EXIT_FAILURE;
    }

    printf("\ngoal: ");
    display_board(goal_Board);
    validity = is_board_valid(goal_Board);
    // printf("\nGoal State validity :%d\n", validity);

    if(input_Board->size != goal_Board->size){
        printf("\nInvalid boards");
    } else {
        solvable(input_Board, goal_Board) ? printf("\nsolvable") : printf("\nunsolvable");
    }

    free_pointers(input_Board);
    free(goal_Board);
    return EXIT_SUCCESS;
}

void printValidationMsg(int code){
    switch (code){
        case -1:
            printf("invalid Board Size\n");
            break;
        
        case -2:
            printf("duplicate Tiles present. Invalid Board.\n");
            break;

        case -3:
            printf("one or more Tiles missing. Invalid Board\n");
            break;

        case -4:
            printf("\none or more Tile(s) invalid. Invalid Board\n");
            break;       

        case -5:
            fprintf(stderr,"\nnot been allocated memory\n");
            break;

        default:
            printf("\nInvalid Board. Please check input\n");
            break;
    }
}