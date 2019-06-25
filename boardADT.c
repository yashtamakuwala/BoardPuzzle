#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "boardADT.h"
#include <math.h>
#include <ctype.h>

#define BLANK 0

struct board{
    int *p;
    int size; //number of elements = size * size
    int no_of_elements;
};


bool is_board_valid(int *p, int no_of_elements){

    return true;
}

void display_board(Board board){
    for (int no_of_elements = 0; no_of_elements < board->no_of_elements; no_of_elements ++) {
        if (no_of_elements % board->size == 0){
            printf("\n");
        }
        // printf("%d", *(board + no_of_elements));
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

    for (int no_of_elements = 0; no_of_elements < board->no_of_elements; no_of_elements++){
            if ( !is_board_odd && *(board->p+no_of_elements) == BLANK){
                disorder += no_of_elements/board->size;
                continue;
            }
        for(int j = no_of_elements; j < board->no_of_elements; j++) {
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
    for (int no_of_elements = 0; no_of_elements < board->no_of_elements; no_of_elements++) {
        for(int j = no_of_elements + 1; j < board->no_of_elements; j++) {
            if(*(board->p+no_of_elements) == *(board->p+j)){
                return true;
            }
        }
    }

    return false;
}

bool areAllTilesPresent(Board board){
    for (int no_of_elements = 0; no_of_elements < board->no_of_elements; no_of_elements++) {
        for (int j = 0; j < board->no_of_elements; j++) {
            if (*(board->p + j) == no_of_elements) {
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


Board createBoard(){
    Board board;
    int *number_stream = malloc(sizeof(int));
    char c;
    int no_of_elements = 0;
    char s[20] = "1 2 3 b\n";

    if(number_stream != NULL) {
        int num = 0;
        while(true){
            c = getchar();
            // c = s[no_of_elements];
            printf("\nCharacter: %c", c);

            if(c == ' ' || c == '\t' || c == '\n'){ //TODO: add EOF handling
                if(num>0){
                    printf("\ninside num %d", num);
                    no_of_elements += 1;
                    *(number_stream+no_of_elements) = num;
                    number_stream = realloc(number_stream, (no_of_elements) * sizeof(int));
                    
                    printf("\nnumber_Stream %d", *(number_stream+no_of_elements));
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



            num = num * 10 + (c-'0');
            // printf("\nnum multi %d\n\n", num);
        }
    printf("\nFinished parsing");
        
    board->p = number_stream;
    board->no_of_elements = no_of_elements;
    return board;
    } else{
        fprintf(stderr,"Insufficient Memory");
        return board;
    }
    
    
}