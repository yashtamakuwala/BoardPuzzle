/**
 * @file boardADT.c
 * @author Yash U Tamakuwala (z5248584)
 * @brief implementation of ADT
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
#include <ctype.h>

/**
 * @brief Structure 'board' that has elements
 * @element *p- pointer to stream of values
 * @element noOfElements - stores number of elements
 * @element size - stores the size/order of board. 
 * @element error - to store the error code generated while parsing or validating
 * a board with size 5 has 5 x 5 = 25 number of elements
 */ 
struct board{
    int *p;
    int noOfElements ;
    int size ; //number of elements = size * size
    int error;
};

#define BLANK 0
#define MIN_BOARD_SIZE 1
#define VALID_BOARD 1
#define TRUE 1
#define FALSE 0
#define ERR_INVALID_SIZE -1
#define ERR_DUPLICATE_TILE -2
#define ERR_MISSING_TILES -3
#define ERR_INVALID_TILE -4
#define ERR_INSUFFICIENT_MEMORY -5

/**
 * @brief Display elements of board
 * 
 * @param board 
 */
void displayBoard(Board board) {

    for (int i = 1; i <= board->noOfElements; i++) {
        if (*(board->p + i) == BLANK) {
            printf("b ");
        } else {
            printf("%d ", *(board->p + i));
        }
    }
}

/**
 * @brief Check that the board is a perfect square
 * 
 * @param board 
 * @return int 
 */
int validSize(Board board) {
    double size = sqrt(board->noOfElements);
    int isize = size;
    
    if (board->noOfElements == 0 || size == 0) {
        return FALSE;
    }

    if (isize == size) {
        board->size = isize;
        printf("\nsize: %d", board->size);
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @brief Calculates disroder of blank in an even sized board
 * 
 * @param blankNumber 
 * @param boardSize 
 * @return int 
 */
int disorderOfBlank(int blankNumber, int boardSize) {
    int disord = 0;
    int quo = blankNumber/boardSize;
    int rem = blankNumber % boardSize;

    if (rem > 0) {
        disord = quo + 1;
    } else {
        disord = quo;
    }

    return disord;
}

/**
 * @brief Calculates disroder of board
 * 
 * @param board 
 * @return int 
 */
int disorderOfBoard(Board board) {
    int disorder = 0;
    int isBoardOdd = board->size % 2;
    // printf("\n Board odd? :%d", isBoardOdd);

    for (int noOfElements = 1; noOfElements <= board->noOfElements; noOfElements++) {
            if (!isBoardOdd && *(board->p+noOfElements) == BLANK) {
                disorder += disorderOfBlank(noOfElements, board->size);
                continue;
            }
        for (int j = noOfElements + 1; j <= board->noOfElements; j++) {
            if (*(board->p+j) == BLANK) {     //skip blank
                continue;
            }
            if (*(board->p+noOfElements) > *(board->p+j)) {
                disorder += 1;
            }
        }
    }

    return disorder;
}

/**
 * @brief Get the Parity of board, 1 if disorder is even, 0 otherwise
 * 
 * @param disorder 
 * @return int 
 */
int getParity(int disorder) {
    return disorder % 2;
}

/**
 * @brief Validation function to check if there is a duplicate file in the board
 * 
 * @param board 
 * @return int 
 */
int duplicateTileExists(Board board) {
    for (int noOfElements = 1; noOfElements <= board->noOfElements; noOfElements++) {
        for (int j = noOfElements + 1; j <= board->noOfElements; j++) {
            if (*(board->p+noOfElements) == *(board->p+j)) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief Validation function to see if all tiles for a board of given size are 
 * present
 * 
 * @param board 
 * @return int 
 */
int areAllTilesPresent(Board board) {
    int totalElements = board->noOfElements;

    for (int noOfElements = 1; noOfElements < totalElements; noOfElements++) {
        for (int j = 1; j < totalElements; j++) {
            if (*(board->p + j) == noOfElements) {
                break;
            } else if (j < totalElements) {
                continue;
            } else {
                return FALSE;
            }
        }
    }

    return TRUE;
}

/**
 * @brief Validation function to see that no tile number is less than 0 or 
 * greater than sqaure of board size. For a board of size 5, maximum tile 
 * number  will be 24.
 * 
 * @param board 
 * @return int 
 */
int allTilesWithinRange(Board board) {
    int rangeMax = (board->size * board->size) - 1;
    int noOfElements = board->noOfElements;

    for (int i = 1; i <= noOfElements; i++) {
        if (*(board->p + i) < 0 || *(board->p + i) >= rangeMax) {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * @brief Function that validates board for various conditions
 * 
 * @param board 
 * @return int 
 */
int isBoardValid(Board board) {

    if (!validSize(board)) {
        return ERR_INVALID_SIZE;
    } else if (duplicateTileExists(board)) {
        return ERR_DUPLICATE_TILE;
    } else if (!allTilesWithinRange(board)) {
        return ERR_INVALID_TILE;
    } else if (!areAllTilesPresent(board)) {
        return ERR_MISSING_TILES;
    }
    return VALID_BOARD;
}

/**
 * @brief function that initialises board, allocates memory and assigns values 
 * to its elements
 * 
 * @return Board 
 */
Board initialiseBoard(void) {
    Board board;
    board = malloc(sizeof(struct board));
    board->noOfElements = 0;
    board->size = 0;
    board->error = 1;

    return board;
}

/**
 * @brief Create a Board object
 * 
 * @return Board 
 */
Board createBoard(void) {
    Board board = initialiseBoard();
    int *numberStream = NULL;
    char c;
    int noOfElements = 0;
    int bFound = FALSE;
    int num = 0;
    int size = MIN_BOARD_SIZE; //1

    if (board != NULL) {
        while (TRUE) {
            c = getchar();

            //When whitespaces, either a number ends or reading of input ends
            if (c == ' ' || c == '\t' || c == '\n' || c == EOF) {
                if (num>0) {
                    noOfElements += 1;
                    
                    if (noOfElements >= size * size) {
                        size += 1;
                        numberStream = realloc(numberStream, (size*size) * sizeof(int));

                        if (numberStream == NULL) {
                            board->error = ERR_INSUFFICIENT_MEMORY;
                            return board;
                        }

                    }
                    
                    *(numberStream + noOfElements) = num;
                    num = 0;

                    if (c == '\n') {
                        break;
                    }
                    continue;
                } else {
                    
                    //Trailing whitespaces and then input parsing finished
                    if (c == '\n') {
                        break;
                    }
                    continue;
                }
            }

            if (c == 'b') {
                if (!bFound && num == 0) {
                    noOfElements += 1;
                    
                    if (noOfElements == size * size) {
                        size += 1;
                        numberStream = realloc(numberStream, (size*size) * sizeof(int));
                    }

                    *(numberStream + noOfElements) = BLANK;
                    // printf("\nNumber_Stream %d", *(numberStream+noOfElements));
                    // printf("\nNo_of_elements: %d", noOfElements);
                    bFound = TRUE;
                    continue;
                } else {    //Have found duplicate 'b'
                    board->error = ERR_INVALID_TILE;
                    break;
                }
            }

            if (!isdigit(c) || c == '0') {
                board->error = ERR_INVALID_TILE;
                break;
            }

            num = num * 10 + (c-'0');
            // printf("\nCalculated num: %d\n\n", num);
        }
    } else {
        board->error = ERR_INSUFFICIENT_MEMORY;
        return board;
    }

    //Return empty board if 'b' is absent from input
    if (!bFound) {
        if (board->error == 0) { //Check if board doesn't have an error in it already.
            board->error = ERR_MISSING_TILES;
        }
        return board;
    }

    board->p = numberStream;
    board->noOfElements = noOfElements;

    return board;
}

/**
 * @brief Checks if goal state can be reached from input state by checking  
 * their parity.
 * 
 * @param inputBoard 
 * @param goalBoard 
 * @return int 
 */
int solvable(Board inputBoard, Board goalBoard) {

    int inputParity = getParity(disorderOfBoard(inputBoard));
    int goalParity = getParity(disorderOfBoard(goalBoard));
    
    return inputParity == goalParity;
}

/**
 * @brief function to free memory and uninitialise the board
 * 
 * @param board 
 */
void freePointers(Board board) {
    free(board->p);
    board->p = NULL;
    free(board);
    board = NULL;
}

/**
 * @brief function to get the error code of the board
 * 
 * @param board 
 * @return int 
 */
int errorInBoard(Board board) {
    return board->error;
}

/**
 * @brief function that checks if inputBoard has same size as of goalBoard. If 
 * not then it is an Invalid scenario.
 * 
 * @param inputBoard 
 * @param goalBoard 
 * @return int 
 */
int equalSizesCheck(Board inputBoard, Board goalBoard) {
    return inputBoard->size == goalBoard->size;
}