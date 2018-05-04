#include "GoBang.h"
#include <regex>  
std::string* GetNeighbor(Board *board, int x, int y, int player, std::string neighbor[4])
{
    int bx = x - 4 > 0 ? -4 : -x, ex = x + 4 > board->width - 1 ? board->width - x - 1 : 4;
    int by = y - 4 > 0 ? -4 : -y, ey = y + 4 > board->height - 1 ? board->height - y - 1 : 4;
    int bt, et;
    int cx, cy;
    for (cx = x + bx; cx <= x + ex; cx++)
    {
        if (board->checkerboard[y][cx] == player)
            neighbor[0].append("o");
        else if (board->checkerboard[y][cx] == -player)
            neighbor[0].append("x");
        else neighbor[0].append("_");
    }
    for (cy = y + by; cy <= y + ey; cy++)
    {
        if (board->checkerboard[cy][x] == player)
            neighbor[1].append("o");
        else if (board->checkerboard[cy][x] == -player)
            neighbor[1].append("x");
        else neighbor[1].append("_");
    }
    bt = -bx > ey ? -ey : bx;
    et = ex > -by ? -by : ex;
    for (cx = x + bt, cy = y - bt; cx <= x + et, cy >= y - et; cx++, cy--)
    {
        if (board->checkerboard[cy][cx] == player)
            neighbor[2].append("o");
        else if (board->checkerboard[cy][cx] == -player)
            neighbor[2].append("x");
        else neighbor[2].append("_");
    }
    bt = bx > by ? bx : by;
    et = ex > ey ? ey : ex;
    for (cx = x + bt, cy = y + bt; cx <= x + et, cy <= y + et; cx++, cy++)
    {
        if (board->checkerboard[cy][cx] == player)
            neighbor[3].append("o");
        else if (board->checkerboard[cy][cx] == -player)
            neighbor[3].append("x");
        else neighbor[3].append("_");
    }
    return neighbor;
}
int SingleEvaluate(Board *board, int x, int y, int player)
{
    std::string neighbor[4];
    board->checkerboard[y][x] = player;
    GetNeighbor(board, x, y, player, neighbor);
    board->checkerboard[y][x] = 0;
    std::string mode[17] =
    {
        ".*oooooo.*",
        ".*ooooo.*", ".*_oooo_.*", ".*_ooo__.*", ".*__ooo_.*",
        ".*_oo_o_.*", ".*_o_oo_.*", ".*oooo_.*", ".*_oooo.*",
        ".*oo_oo.*", ".*o_ooo.*", ".*ooo_o.*", ".*__oo__.*",
        ".*__o_o_.*", ".*_o_o__.*", ".*___o__.*", ".*__o___.*",
    };
    int score[16] = { 50000, 4320, 720, 720, 720, 720, 720, 720, 720, 720, 720, 120, 120, 120, 20, 20 };
    int totalScore = 0;
    for (int i = 0; i < 4; i++)
    {
        std::regex reg(mode[0]);
        if (std::regex_match(neighbor[i].c_str(), reg))
        {
            return -1;
        }
        for (int j = 1; j < 17; j++)
        {
            std::regex reg(mode[j]);
            if (std::regex_match(neighbor[i].c_str(), reg))
            {
                totalScore += score[j - 1];
                break;
            }
        }
    }
    return totalScore;
}
void Evaluate(Board *board, int &targetx, int &targety)
{
    int offenseScore = 0, defenseScore = 0;
    int score = 0;
    for (int y = 0; y < board->height; y++)
    {
        for (int x = 0; x < board->width; x++)
        {
            if (board->checkerboard[y][x] == 0)
            {
                offenseScore = SingleEvaluate(board, x, y, 1);
                if (offenseScore < 0)
                {
                    targetx = -1;
                    targety = -1;
                    return;
                }
                defenseScore = SingleEvaluate(board, x, y, -1);
                if (offenseScore + defenseScore > score)
                {
                    score = offenseScore + defenseScore;
                    targetx = x;
                    targety = y;
                }
            }
        }
    }
    return;
}

int Go(Board *board, int x, int y, int player)
{
    if (y < board->height && x < board->width && board->checkerboard[y][x] == 0)
    {
        board->checkerboard[y][x] = player;
        return 0;
    }
    return 1;
}