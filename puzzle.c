// Created by:- Yash Umeshkumar Tamakuwala (z5248584)
// Client that creates input and goal boards, shows errors if any and prints if they are solvable/unsolvable.


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
#define INPUT_BOARD 0
#define GOAL_BOARD 1

void printValidationMsg(int code);
void validateAndFree(int validity, Board board, int boardType);

int main()
{
    Board input_Board = createBoard();
    int validity = errorInBoard(input_Board);  //to check for errors while input-parsing

    if (validity < 0) {
        validateAndFree(validity, input_Board, INPUT_BOARD);
    }
    
    validity = is_board_valid(input_Board);

    if (validity < 0) {
        validateAndFree(validity, input_Board, INPUT_BOARD);
    }

    printf("\nstart: ");
    display_board(input_Board);

    Board goal_Board = createBoard();
    validity = errorInBoard(goal_Board);

    
    if (validity < 0) {
        validateAndFree(validity, goal_Board, GOAL_BOARD);
    }
       
    validity = is_board_valid(goal_Board);

    if (validity < 0) {
        validateAndFree(validity, goal_Board, GOAL_BOARD);
    }

    printf("\ngoal: ");
    display_board(goal_Board);
    validity = is_board_valid(goal_Board);

    if (sizeCheck(input_Board, goal_Board)) {
        printf("\nInvalid boards as their sizes don't match.");
    } else {
        if (solvable(input_Board, goal_Board)) {
            printf("\nsolvable"); 
        } else {
            printf("\nunsolvable");
        }
    }

    free_pointers(input_Board);
    free_pointers(goal_Board);
    return EXIT_SUCCESS;
}

void validateAndFree(int validity, Board board, int boardType){

    printf("\nWhile parsing,");
    if ( boardType == INPUT_BOARD) {
        printf(" start board has ");
    } else {
        printf(" goal board has ");
    }
    printValidationMsg(validity);
    free_pointers(board);
    exit(0);   
}

void printValidationMsg(int code) {
    switch (code) {
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
            printf("one or more Tile(s) invalid. Invalid Board\n");
            break;       

        case -5:
            fprintf(stderr,"not been allocated memory\n");
            break;

        default:
            printf("invalid. Please check input\n");
            break;
    }
}