#include <iostream>
#include "GoBang.h"

void showBoard(Board *board)
{
    system("cls");
    printf("   ");
    for (int i = 0; i < board->width; i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < board->height; i++)
    {
        printf("%3d ", i);
        for (int j = 0; j < board->width; j++)
        {
            if (board->checkerboard[i][j] == -1)
                printf(" x ");
            else if (board->checkerboard[i][j] == 1)
                printf(" o ");
            else printf(" . ");
            // printf("%3d", SingleEvaluate(board, j, i, -1));
                
        }
        printf("\n");
    }
}
int main()
{
    Board *board = new Board(17, 17);
    int x, y, score = 0;
    int res = 1;
    Go(board, 8, 8, 1);
    while (1)
    {
        showBoard(board);
        res = 1;
        while (res == 1)
        {
            std::cin >> x >> y;
            res = Go(board, x, y, -1);
        }
        showBoard(board);
        Evaluate(board, x, y);
        Go(board, x, y, 1);
        showBoard(board);
    }
    //Evaluate(board, 1, x, y, score);
    //printf("%d,%d,%d", x, y, score);
}