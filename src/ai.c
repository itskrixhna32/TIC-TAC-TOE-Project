#include "ai.h"
#include "game.h"
#include <stdlib.h>

void computer_move(char board[3][3])
{
    if (difficulty == 1)
    {
        int r, c;
        do
        {
            r = rand() % 3;
            c = rand() % 3;
        } while (board[r][c] != ' ');
        board[r][c] = 'O';
        return;
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                if (check_win(board, 'O'))
                    return;
                board[i][j] = ' ';
            }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                if (check_win(board, 'X'))
                {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }

    if (board[1][1] == ' ')
    {
        board[1][1] = 'O';
        return;
    }

    int corners[4][2] = {{0,0},{0,2},{2,0},{2,2}};
    for (int i = 0; i < 4; i++)
        if (board[corners[i][0]][corners[i][1]] == ' ')
        {
            board[corners[i][0]][corners[i][1]] = 'O';
            return;
        }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                return;
            }
}
