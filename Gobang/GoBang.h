#pragma once
#include <malloc.h>
#include <memory.h>
#include <string>

struct Board
{
    int height, width;
    //  -1 player 0 space 1 computer
    int **checkerboard;

    Board(int height, int width)
    {
        this->height = height;
        this->width = width;
        checkerboard = (int **)malloc(height * sizeof(int*));
        for (int i = 0; i < height; i++)
        {
            checkerboard[i] = (int *)malloc(width * sizeof(int));
            memset(checkerboard[i], 0, width * sizeof(int));
        }
    }
};
int Go(Board *board, int x, int y, int player);
void Evaluate(Board *board, int &targetx, int &targety);
bool JudgeWin(Board *board, int x, int y, int player);