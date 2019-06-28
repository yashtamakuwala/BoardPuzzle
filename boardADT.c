#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boardADT.h"
#include <math.h>
#include <ctype.h>

struct board{
    int *p;
    int no_of_elements ;
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

void display_board(Board board){

    // printf("\nDisplaying board");
    // printf("\nElements : %d\n", board->no_of_elements);

    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++) {
        if (*(board->p + no_of_elements) == BLANK) {
            printf("b ");
        } else {
            printf("%d ", *(board->p + no_of_elements));
        }
    }
}

// Check that the board is a perfect square
int valid_size(Board board){
    double size = sqrt(board->no_of_elements);
    int isize = size;
    
    if (board->no_of_elements == 0 || size == 0) {
        return FALSE;
    }

    if (isize == size) {
        board->size = isize;
        return TRUE;
    } else {
        return FALSE;
    }
}

int disorderOfBlank(int blank_number, int board_size ){
    int disord = 0;
    int quo = blank_number/board_size;
    int rem = blank_number % board_size;

    if (rem > 0) {
        disord = quo + 1;
    } else {
        disord = quo;
    }

    return disord;
}

int disorderOfBoard(Board board) {
    int disorder = 0;
    int is_board_odd = board->size % 2;
    // printf("\n Board odd? :%d", is_board_odd);

    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++){
            if (!is_board_odd && *(board->p+no_of_elements) == BLANK) {
                disorder += disorderOfBlank(no_of_elements, board->size);
                continue;
            }
        for (int j = no_of_elements + 1; j <= board->no_of_elements; j++) {
            if (*(board->p+j) == BLANK){     //skip blank
                continue;
            }
            if (*(board->p+no_of_elements) > *(board->p+j)) {
                disorder += 1;
            }
        }
    }

    return disorder;
}

int getParity(int disorder) {
    return disorder % 2;
}

int duplicateTileExists(Board board) {
    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++) {
        for (int j = no_of_elements + 1; j <= board->no_of_elements; j++) {
            if (*(board->p+no_of_elements) == *(board->p+j)) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int areAllTilesPresent(Board board) {
    int total_elements = board->no_of_elements;

    for (int no_of_elements = 1; no_of_elements < total_elements; no_of_elements++) {
        for (int j = 1; j < total_elements; j++) {
            if (*(board->p + j) == no_of_elements) {
                break;
            } else if (j < total_elements){
                continue;
            } else {
                return FALSE;
            }
        }
    }

    return TRUE;
}

int allTilesWithinRange(Board board) {
    int range_max = board->size * board->size;
    int no_of_elements = board->no_of_elements;

    for (int i = 1; i <= no_of_elements; i++) {
        if (*(board->p + i) < 0 || *(board->p + i) >= range_max) {
            return FALSE;
        }
    }

    return TRUE;
}

int is_board_valid(Board board) {

    if (!valid_size(board)) {
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

Board initialise_board() {
    Board board;
    board = malloc(sizeof(struct board));
    board->no_of_elements = 0;
    board->size = 0;

    return board;
}

Board createBoard() {
    Board board ; // = initialise_board();
    int *number_stream = NULL;
    char c;
    int no_of_elements = 0;
    int b_found = FALSE;
    int num = 0;
    int size = MIN_BOARD_SIZE; //2

    board = malloc(sizeof(struct board));
    board->no_of_elements = 0;
    board->size = 0;
    board->error = 1;

    if (board != NULL){
        while(TRUE){
            
            c = getchar();
            // printf("\nCharacter: %c %d",c,c);
            if(c == ' ' || c == '\t' || c == '\n' || c == EOF){
                // printf("\nInside whitespace");
                
                if(num>0){
                    // printf("\ninner num :%d", num);
                    no_of_elements += 1;
                    
                    if (no_of_elements >= size * size){
                        size += 1;
                        number_stream = realloc(number_stream, (size*size) * sizeof(int));

                        if (number_stream == NULL) {
                            board->error = ERR_INSUFFICIENT_MEMORY;
                            return board;
                        }

                    }
                    
                    *(number_stream+no_of_elements) = num;
                    // printf("\nNumber_Stream %d", *(number_stream+no_of_elements));
                    // printf("\nNo_of_elements: %d", no_of_elements);
                    num = 0;

                    if(c == '\n'){
                        // printf("\n num>0 Terminal");
                        break;
                    }
                    continue;
                } else {
                    
                    //Trailing whitespaces and then input parsing finished
                    if(c == '\n'){
                        break;
                    }
                    continue;
                }
            }

            if(c == 'b' ){
                if (!b_found && num == 0) {
                    no_of_elements += 1;
                    
                    if (no_of_elements == size * size){
                        size += 1;
                        number_stream = realloc(number_stream, (size*size) * sizeof(int));
                    }

                    *(number_stream+no_of_elements) = BLANK;
                    // printf("\nNumber_Stream %d", *(number_stream+no_of_elements));
                    // printf("\nNo_of_elements: %d", no_of_elements);
                    b_found = TRUE;
                    continue;
                } else {    //Have found duplicate 'b'
                    board->error = ERR_INVALID_TILE;
                    break;
                }
            }

            if(!isdigit(c) || c == '0'){
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
    if(!b_found){
        if(board->error == 0) { //Check if board doesn't have an error in it already.
            board->error = ERR_MISSING_TILES;
        }
        return board;
    }

    board->p = number_stream;
    board->no_of_elements = no_of_elements;

    // free(number_stream);
    return board;
}

int solvable(Board input_board, Board goal_board) {

    int input_parity = getParity(disorderOfBoard(input_board));
    int goal_parity = getParity(disorderOfBoard(goal_board));
    
    return input_parity == goal_parity;
}

void free_pointers(Board board) {
    free(board->p);
    board->p = NULL;
    free(board);
    board = NULL;
}

int errorInBoard(Board board) {
    return board->error;
}

int sizeCheck(Board inputBoard, Board goalBoard) {
    return inputBoard->size == goalBoard->size;
}