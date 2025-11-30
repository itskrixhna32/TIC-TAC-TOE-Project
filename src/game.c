#include <stdio.h>
#include<stdlib.h>
#include "game.h"
#include "ai.h"
#include "utils.h"

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = rand() % 2 == 0 ? 'X' : 'O';
    print_board(board);

    while (1)
    {
        if (current_player == 'X')
        {
            player_move(board);
            print_board(board);

            if (check_win(board, 'X'))
            {
                score.player++;
                printf("Congratulations! You Win!!\n");
                break;
            }
            current_player = 'O';
        }
        else
        {
            computer_move(board);
            print_board(board);

            if (check_win(board, 'O'))
            {
                score.computer++;
                printf("Computer Wins!!\n");
                break;
            }
            current_player = 'X';
        }

        if (check_draw(board))
        {
            score.draw++;
            printf("It's a Draw!\n");
            break;
        }
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen();
    printf("\nScore - Player: %d  Computer: %d  Draws: %d\n\n",
           score.player, score.computer, score.draw);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < 2)
                printf("|");
        }
        if (i < 2)
            printf("\n---+---+---\n");
    }
    printf("\n\n");
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return 1;

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return !(row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int r, c;

    while (1)
    {
        printf("Enter row and column (1-3): ");
        if (scanf("%d %d", &r, &c) != 2)
        {
            while (getchar() != '\n');
            continue;
        }

        if (is_valid_move(board, r, c))
            break;

        printf("Invalid Move! Try Again.\n");
    }

    board[r - 1][c - 1] = 'X';
}

void input_difficulty()
{
    while (1)
    {
        printf("\n1. Human (Easy)\n2. God (Impossible)\nEnter choice: ");
        scanf("%d", &difficulty);
        if (difficulty == 1 || difficulty == 2)
            break;
        printf("Invalid Choice!\n");
    }
}
