#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "boardADT.h"
#include <math.h>
#include <ctype.h>

#define BLANK 0
#define VALID_BOARD 1
#define ERR_INVALID_SIZE -1
#define ERR_DUPLICATE_TILE -2
#define ERR_MISSING_TILES -3
#define ERR_INVALID_TILE -4

// struct board{
//     int *p;
//     int size; //number of elements = size * size
//     int no_of_elements;
// };

void display_board(Board board){

    printf("\nDisplaying board");
    printf("\nElements : %d\n", board->no_of_elements);

    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++) {
        // if (no_of_elements % board->size == 0){
        //     printf("\n");
        // }
        printf("%d ", *(board->p + no_of_elements));
    }
}

// Check that the board is a perfect square
bool valid_size(Board board){
    double size = sqrt(board->no_of_elements);
    int isize = size;
    
    if (board->no_of_elements == 0 || size == 0) {
        return false;
    }

    if (isize == size){
        board->size = isize;
        return true;
    } else {
        return false;
    }
}



int disorderOfBoard(Board board){
    int disorder = 0;
    bool is_board_odd = board->size % 2;

    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++){
            if ( !is_board_odd && *(board->p+no_of_elements) == BLANK){
                disorder += no_of_elements/board->size;
                continue;
            }
        for(int j = no_of_elements; j <= board->no_of_elements; j++) {
            if (*(board->p+j) == BLANK){     //skip blank
                continue;
            }
            if(*(board->p+no_of_elements) > *(board->p+j)){
                disorder += 1;
            }
        }
    }

    return disorder;
}

int getParity(int disorder){
    return disorder % 2;
}

bool duplicateTileExists(Board board){
    for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++) {
        for(int j = no_of_elements + 1; j <= board->no_of_elements; j++) {
            if(*(board->p+no_of_elements) == *(board->p+j)){
                return true;
            }
        }
    }

    return false;
}

// bool areAllTilesPresent(Board board){
//     for (int no_of_elements = 1; no_of_elements <= board->no_of_elements; no_of_elements++) {
//         for (int j = 1; j <= board->no_of_elements; j++) {
//             if (*(board->p + j) == no_of_elements) {
//                 break;
//             } else if (j < board->no_of_elements){
//                 continue;
//             } else {
//                 return false;
//             }
//         }
//     }

//     return true;
// }

bool allTilesWithinRange(Board board){
    int range_max = board->size * board->size;
    int no_of_elements = board->no_of_elements;

    for (int i = 1; i <= no_of_elements; i++){
        if (*(board->p + i) < 0 || *(board->p + i) >= range_max){
            return false;
        }
    }

    return true;
}

int is_board_valid(Board board){

    if(!valid_size(board)){
        return ERR_INVALID_SIZE;
    }  else if(duplicateTileExists(board)){
        return ERR_DUPLICATE_TILE;
    } else if (!allTilesWithinRange(board)) {
        return ERR_INVALID_TILE;
    }
    return VALID_BOARD;
}

Board initialise_board(){
    Board board;
    board = malloc(sizeof(struct board));
    board->no_of_elements = 0;
    board->size = 0;

    return board;
}

Board createBoard(){
    Board board ; // = initialise_board();
    board = malloc(sizeof(struct board));
    board->no_of_elements = 0;
    board->size = 0;

    int *number_stream = malloc(sizeof(int));
    char c;
    int no_of_elements = 0;
    // char s[20] = "1 2 3 b\n";
    bool b_found = false;

    if(number_stream != NULL) {
        int num = 0;
        while(true){
            
            c = getchar();

            if(c == ' ' || c == '\t' || c == '\n' || c == EOF){ 
                if(num>0){
                    no_of_elements += 1;
                    *(number_stream+no_of_elements) = num;
                    number_stream = realloc(number_stream, (no_of_elements) * sizeof(int));
                    
                    // printf("\nNumber_Stream %d", *(number_stream+no_of_elements));
                    
                    num = 0;

                    if(c == '\n'){
                        break;
                    }
                    continue;
                } else {

                    if(c == '\n'){
                        break;
                    }
                    continue;
                }
            }

            if(c == 'b' ){
                if (!b_found) {
                    no_of_elements += 1;
                    *(number_stream+no_of_elements) = BLANK;
                    number_stream = realloc(number_stream, (no_of_elements) * sizeof(int));
                    printf("\nNumber_Stream %d", *(number_stream+no_of_elements));
                    b_found = true;
                    continue;
                } else {
                    break;
                }
            }

            num = num * 10 + (c-'0');
        }
    
    board->p = number_stream;
    board->no_of_elements = no_of_elements;

    free(number_stream);
    return board;
    } else{
        fprintf(stderr,"Insufficient Memory");
        return board;
    }
}

bool solvable(Board input_board, Board goal_board){

    if(input_board->size != goal_board->size){
        return false;
    }

    int input_parity = getParity(disorderOfBoard(input_board));
    int goal_parity = getParity(disorderOfBoard(goal_board));
    
    return input_parity == goal_parity;
}