
typedef struct board *Board;

void display_board(Board);
int is_board_valid(Board);
Board createBoard();
int solvable(Board, Board);
void free_pointers(Board);
int errorInBoard(Board);
int sizeCheck(Board inputBoard, Board goalBoard);