/**
 * @file puzzle.c
 * @author Yash Umeshkumar Tamakuwala (z5248584)
 * @brief : Client that creates input and goal boards, shows errors if any and
 * prints if they are solvable/unsolvable.
 * @date 2019-06-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    Board inputBoard = createBoard();
    int validity = errorInBoard(inputBoard);  //to check for errors while input-parsing

    if (validity < 0) {
        validateAndFree(validity, inputBoard, INPUT_BOARD);
    }
    
    validity = isBoardValid(inputBoard);

    if (validity < 0) {
        validateAndFree(validity, inputBoard, INPUT_BOARD);
    }

    printf("\nstart: ");
    displayBoard(inputBoard);

    Board goalBoard = createBoard();
    validity = errorInBoard(goalBoard);

    
    if (validity < 0) {
        validateAndFree(validity, goalBoard, GOAL_BOARD);
    }
       
    validity = isBoardValid(goalBoard);

    if (validity < 0) {
        validateAndFree(validity, goalBoard, GOAL_BOARD);
    }

    printf("\ngoal: ");
    displayBoard(goalBoard);
    validity = isBoardValid(goalBoard);

    if (!equalSizesCheck(inputBoard, goalBoard)) {
        printf("\nInvalid boards as their sizes don't match.");
    } else {
        if (solvable(inputBoard, goalBoard)) {
            printf("\nsolvable"); 
        } else {
            printf("\nunsolvable");
        }
    }

    freePointers(inputBoard);
    freePointers(goalBoard);
    return EXIT_SUCCESS;
}

/**
 * @brief Will print error message for the board based on board type, free pointers and exit program 
 * @param validity 
 * @param board 
 * @param boardType 
 */
void validateAndFree(int validity, Board board, int boardType){

    printf("\nWhile parsing,");
    if ( boardType == INPUT_BOARD) {
        printf(" start board has ");
    } else {
        printf(" goal board has ");
    }
    printValidationMsg(validity);
    freePointers(board);
    exit(0);   
}

/**
 * @brief print validation message based on error code
 * 
 * @param code 
 */
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