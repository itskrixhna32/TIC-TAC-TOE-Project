#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 3

typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

extern Score score;
extern int difficulty;

void play_game();
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void input_difficulty();

#endif
