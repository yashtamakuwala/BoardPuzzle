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
    
    return EXIT_SUCCESS;
}

