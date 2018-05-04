#include <iostream>
#include <Windows.h>
#include <vector>
#include "GoBang.h"

#define PLAYER 1
#define PLAYE_RFIRST 1

void color(int a)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void showBoard(Board *board)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    color(FOREGROUND_INTENSITY);
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
            {
                color(11);
                printf(" x ");
                color(FOREGROUND_INTENSITY);
            }
            else if (board->checkerboard[i][j] == 1)
            {
                color(14);
                printf(" o ");
                color(FOREGROUND_INTENSITY);
            }
            else
            {
                printf(" . ");
            }
                
        }
        printf("\n");
    }
}
void ShowStep(std::vector<std::pair<int, int>>  computer, std::vector<std::pair<int, int>>  player)
{
    printf("Computer:\n  ");
    for (auto i = computer.begin(); i != computer.end(); i++)
        printf("(%d,%d) ", i->first, i->second);
    printf("\nPlayer:\n  ");
    for (auto i = player.begin(); i != player.end(); i++)
        printf("(%d,%d) ", i->first, i->second);
}
int main()
{
    Board *board = new Board(17, 17);
    int x = -1, y = -1;
    int res;
    std::vector<std::pair<int, int>> computer, player;

#ifndef PLAYE_RFIRST
    Evaluate(board, x, y);
    Go(board, x, y, 1);
#endif

    while (1)
    {
        showBoard(board);
        color(14);
        printf("Computer(o):%d,%d\n", x, y);
        color(11);
#ifdef PLAYER
        printf("User(x):", x, y);
        res = 1;
        while (res == 1)
        {
            scanf("%d%d", &x, &y);
            if (x == -1)
            {
                ShowStep(computer, player);
            }
            res = Go(board, x, y, -1);
            player.push_back(std::pair<int, int>(x, y));
        }
#else
        Evaluate(board, x, y);
        Go(board, x, y, -1);
        printf("Computer(x):%d,%d\n", x, y);
#endif // PLAYER
        color(FOREGROUND_INTENSITY);

        showBoard(board);
        if (JudgeWin(board, x, y, -1))
        {
            color(11);
            printf("Player wins!\n");
            color(FOREGROUND_INTENSITY);
            break;
        }

        Evaluate(board, x, y);
        Go(board, x, y, 1);
        computer.push_back(std::pair<int, int>(x, y));

        if (JudgeWin(board, x, y, 1))
        {
            color(14);
            printf("Computer wins!\n");
            color(FOREGROUND_INTENSITY);
            break;
        }
    }
    system("pause");
    return 0;
}