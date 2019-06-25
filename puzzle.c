#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "boardADT.h"
#include <math.h>

int main()
{
    Board input_Board = createBoard();
    // printf("\nElements : %d\n", input_Board->no_of_elements);
    display_board(input_Board);
    
    int validity = is_board_valid(input_Board);
    printf("\nInput validity :%d", validity);

    // Board goal_Board = createBoard();
    // display_board(goal_Board);
    // validity = is_board_valid(goal_Board);
    // printf("\nGoal State validity :%d", validity);


    return EXIT_SUCCESS;
}

