#include <stdlib.h>
#include "boardADT.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define BLANK 0

struct board{
    int *p;
    int size; //number of elements = size * size
    int no_of_elements;
};


bool is_board_valid(int *p, int i){

    return true;
}

void display_board(int *board, int size){
    for (int i = 0; i < size; i ++) {
        if (i % size == 0){
            printf("\n");
        }
        printf("%d", *(board + i));
    }
}

bool valid_size(Board board, int no_of_elements){
    double size = sqrt(no_of_elements);
    int isize = size;
    
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

    for (int i = 0; i < board->no_of_elements; i++){
            if ( !is_board_odd && *(board->p+i) == BLANK){
                disorder += i/board->size;
                continue;
            }
        for(int j = i; j < board->no_of_elements; j++) {
            if (*(board->p+j) == BLANK){     //skip blank
                continue;
            }
            if(*(board->p+i) > *(board->p+j)){
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
    for (int i = 0; i < board->no_of_elements; i++) {
        for(int j = i + 1; j < board->no_of_elements; j++) {
            if(*(board->p+i) == *(board->p+j)){
                return true;
            }
        }
    }

    return false;
}

bool areAllTilesPresent(Board board){
    for (int i = 0; i < board->no_of_elements; i++) {
        for (int j = 0; j < board->no_of_elements; j++) {
            if (*(board->p + j) == i) {
                break;
            } else if (j < board->no_of_elements){
                continue;
            } else {
                return false;
            }
        }
    }

    return true;
}
int createBoard(Board ADT,int size1){

    int *number_stream = malloc(sizeof(int));
    char c;

    if(number_stream != NULL) {
        int num = 0;
        while(true){
            c = getchar();
            
            num = num * 10 + (c-'0');
        }
    } else{
        //show insuffieicent meomery error
    }
    ADT->size=size1;
    printf("%d",ADT->size);
    return 0;
}