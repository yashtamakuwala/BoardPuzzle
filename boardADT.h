/**
 * @file boardADT.h
 * @author Yash U Tamakuwala (z5248584)
 * @brief header file of ADT through which client(puzzle.c) will communicate and use functions
 * @date 2019-06-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */
typedef struct board *Board;

void displayBoard(Board);
int isBoardValid(Board);
Board createBoard();
int solvable(Board, Board);
void freePointers(Board);
int errorInBoard(Board);
int equalSizesCheck(Board inputBoard, Board goalBoard);