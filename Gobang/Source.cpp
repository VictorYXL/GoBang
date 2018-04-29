#include <vector>
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
void ShowStep(std::vector<std::pair<int, int>>  computer, std::vector<std::pair<int, int>>  player)
{
    printf("Computer:\n  ");
    for (auto i = computer.begin(); i != computer.end(); i++)
        printf("(%d,%d) ", i[0], i[1]);
    printf("\nPlayer:\n  ");
    for (auto i = player.begin(); i != player.end(); i++)
        printf("(%d,%d) ", i[0], i[1]);

}
int main()
{
    Board *board = new Board(17, 17);
    int x = 8, y = 8;
    int res = 1;
    std::vector<std::pair<int, int>> computer, player;
    Go(board, x, y, 1);
    while (1)
    {
        showBoard(board);
        computer.push_back(std::pair<int, int>(x, y));
        printf("Computer: %d, %d\n", x, y);
        printf("Player: ");
        res = 1;
        while (res == 1)
        {
            scanf("%d%d", &x, &y);
            if (x == -1)
            {
                ShowStep(computer, player);
            }
            res = Go(board, x, y, -1);
        }
        player.push_back(std::pair<int, int>(x, y));
        showBoard(board);
        Evaluate(board, x, y);
        Go(board, x, y, 1);
        showBoard(board);
    }
    //Evaluate(board, 1, x, y, score);
    //printf("%d,%d,%d", x, y, score);
}