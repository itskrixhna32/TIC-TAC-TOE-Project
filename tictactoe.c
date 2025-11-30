
/* tictactoe.c
   Single-file Tic-Tac-Toe project (Player vs Computer)
   Difficulty: 1 = Human (heuristic), 2 = God (Minimax)
   Student: Krishna Grover, Roll No: 590023545
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3

typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL));
    int choice;
    input_difficulty();
    do
    {
        play_game();
        printf("Play again? (1 for YES / 0 for NO):");
        scanf("%d", &choice);
    } while (choice == 1);
    printf("BYE BYE, Thanks for playing!!\n");
}

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
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
                print_board(board);
                printf("Congratulations you have won!! \n");
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
                print_board(board);
                printf("Computer has won!! \n");
                break;
            }
            current_player = 'X';
        }

        if (check_draw(board))
        {
            score.draw++;
            print_board(board);
            printf("It's a draw!\n");
            break;
        }
    }
}
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return !(row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE || board[row - 1][col - 1] != ' ');
}
void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row, col;
    do
    {
        printf("Player X turn.\n");
        printf("Enter row and column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &col);
        
    } while (!is_valid_move(board, row, col));
    row--;
    col--;
    board[row][col] = 'X';
}
void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    //1. play for immediate win
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                if(check_win(board,'O'))
                {
                    return;
                }
                board[i][j]=' ';

            }
        }
    }
    //1. play for immediate win
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='X';
                if(check_win(board,'X'))
                {
                    board[i][j]='O';
                    return;
                }
                board[i][j]=' ';

            }
        }
    }
    //3. play center if available
    if(difficulty==2) //GOD Mode
    {
        if(board[1][1] == ' ')
        {
            board[1][1] = 'O';
            return;
        }
    }

    //4. play corner if available
    int corners[4][2] = {{0,0},{0,2},{2,0},{2,2}};
    for(int i=0;i<4;i++)
    {
        if(board[corners[i][0]] [corners[i][1]] == ' ')
        {
            board[corners[i][0]] [corners[i][1]] = 'O';
            return;
        }
    }
    //5. play first available move
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                return;
            }
        }
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return 1;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return 1;
    }
    return 0;
}
int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}
void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen();
    printf("\nScore - Player X: %d | Computer O: %d | Draws: %d", score.player, score.computer, score.draw);
    printf("\nTIC TAC TOE\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1)
            {
                printf("|");
            }
        }
        if (i < BOARD_SIZE - 1)
        {
            printf("\n---+---+---");
        }
    }
    printf("\n\n");
}

void input_difficulty()
{

    while (1)
    {
        printf("\nselect difficulty level:\n");
        printf("\n1. Human (Standard)");
        printf("\n2. God (Immposssible to win)");
        printf("\nEnter Your Choice: ");
        scanf("%d", &difficulty);
        if (difficulty != 1 && difficulty != 2)
        {
            printf("\n\n Incorrect choice Enter 1/2!!");
        }
        else
        {
            break;
        }
    };
}
void clear_screen()
{
#ifdef _WIN32
    {
        system("cls");
    }
#else
    {
        system("clear");
    }
#endif
}
