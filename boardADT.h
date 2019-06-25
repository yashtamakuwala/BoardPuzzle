
typedef struct board *Board;

struct board{
    int *p;
    int no_of_elements;
    int size; //number of elements = size * size
};

void display_board(Board);
Board createBoard();
