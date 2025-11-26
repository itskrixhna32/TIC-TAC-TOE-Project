
/* tictactoe.c
   Single-file Tic-Tac-Toe project (Player vs Computer)
   Difficulty: 1 = Human (heuristic), 2 = God (Minimax)
   Student: Krishna Grover, Roll No: 590023545
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3

typedef struct {
    int player;
    int computer;
    int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void input_difficulty();
void play_game();

/* Minimax prototypes */
int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int isMaximizing);
int evaluate_board(char board[BOARD_SIZE][BOARD_SIZE]);
int moves_left(char board[BOARD_SIZE][BOARD_SIZE]);
void make_move(char board[BOARD_SIZE][BOARD_SIZE], int r, int c, char mark);
void undo_move(char board[BOARD_SIZE][BOARD_SIZE], int r, int c);
int try_immediate_win_or_block(char board[BOARD_SIZE][BOARD_SIZE], char mark);

int main() {
    srand((unsigned)time(NULL));
    int choice;
    input_difficulty();
    do {
        play_game();
        printf("Play again? (1 for YES / 0 for NO): ");
        if (scanf("%d", &choice) != 1) { choice = 0; }
    } while (choice == 1);
    printf("\nBYE BYE, Thanks for playing!\n");
    return 0;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char current_player = (rand() % 2 == 0 ? 'X' : 'O');
    print_board(board);
    while (1) {
        if (current_player == 'X') {
            player_move(board);
            print_board(board);
            if (check_win(board, 'X')) {
                score.player++;
                printf("Congratulations, you win!\n");
                break;
            }
            current_player = 'O';
        } else {
            computer_move(board);
            print_board(board);
            if (check_win(board, 'O')) {
                score.computer++;
                printf("Computer wins!\n");
                break;
            }
            current_player = 'X';
        }
        if (check_draw(board)) {
            score.draw++;
            printf("It's a draw!\n");
            break;
        }
    }
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int row = 0, col = 0;
    do {
        printf("\nPlayer X turn - enter row and column (1-3): ");
        if (scanf("%d %d", &row, &col) != 2) {
            int c; while ((c = getchar()) != '\\n' && c != EOF) {}
            row = col = 0;
        }
    } while (!is_valid_move(board, row, col));
    board[row - 1][col - 1] = 'X';
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    if (difficulty == 2) {
        if (try_immediate_win_or_block(board, 'O')) return;
        int bestScore = -1000, br = -1, bc = -1;
        for (int i=0;i<BOARD_SIZE;i++) for(int j=0;j<BOARD_SIZE;j++) {
            if (board[i][j]==' ') {
                board[i][j] = 'O';
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestScore) { bestScore = score; br = i; bc = j; }
            }
        }
        if (br!=-1) board[br][bc] = 'O';
        return;
    }
    if (try_immediate_win_or_block(board, 'O')) return;
    if (try_immediate_win_or_block(board, 'X')) return;
    if (board[1][1]==' ') { board[1][1]='O'; return; }
    int corners[4][2] = {{0,0},{0,2},{2,0},{2,2}};
    for (int k=0;k<4;k++){
        int r=corners[k][0], c=corners[k][1];
        if (board[r][c]==' ') { board[r][c]='O'; return; }
    }
    for (int i=0;i<BOARD_SIZE;i++) for (int j=0;j<BOARD_SIZE;j++)
        if (board[i][j]==' ') { board[i][j]='O'; return; }
}

int try_immediate_win_or_block(char board[BOARD_SIZE][BOARD_SIZE], char mark){
    for (int i=0;i<BOARD_SIZE;i++) for (int j=0;j<BOARD_SIZE;j++){
        if (board[i][j]==' ') {
            board[i][j] = mark;
            if (check_win(board, mark)) {
                board[i][j] = 'O';
                return 1;
            }
            board[i][j] = ' ';
        }
    }
    return 0;
}

int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int isMaximizing){
    int score = evaluate_board(board);
    if (score==10) return score - depth;
    if (score==-10) return score + depth;
    if (!moves_left(board)) return 0;
    if (isMaximizing){
        int best = -1000;
        for (int i=0;i<BOARD_SIZE;i++) for (int j=0;j<BOARD_SIZE;j++)
            if (board[i][j]==' ') {
                make_move(board,i,j,'O');
                int val = minimax(board, depth+1, 0);
                undo_move(board,i,j);
                if (val>best) best=val;
            }
        return best;
    } else {
        int best = 1000;
        for (int i=0;i<BOARD_SIZE;i++) for (int j=0;j<BOARD_SIZE;j++)
            if (board[i][j]==' ') {
                make_move(board,i,j,'X');
                int val = minimax(board, depth+1, 1);
                undo_move(board,i,j);
                if (val<best) best=val;
            }
        return best;
    }
}

int evaluate_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[i][0]=='O'&&board[i][1]=='O'&&board[i][2]=='O') return 10;
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[0][i]=='O'&&board[1][i]=='O'&&board[2][i]=='O') return 10;
    if ((board[0][0]=='O'&&board[1][1]=='O'&&board[2][2]=='O') ||
        (board[0][2]=='O'&&board[1][1]=='O'&&board[2][0]=='O')) return 10;
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[i][0]=='X'&&board[i][1]=='X'&&board[i][2]=='X') return -10;
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[0][i]=='X'&&board[1][i]=='X'&&board[2][i]=='X') return -10;
    if ((board[0][0]=='X'&&board[1][1]=='X'&&board[2][2]=='X') ||
        (board[0][2]=='X'&&board[1][1]=='X'&&board[2][0]=='X')) return -10;
    return 0;
}

int moves_left(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i=0;i<BOARD_SIZE;i++) for (int j=0;j<BOARD_SIZE;j++) if (board[i][j]==' ') return 1;
    return 0;
}

void make_move(char board[BOARD_SIZE][BOARD_SIZE], int r, int c, char mark){ board[r][c]=mark; }
void undo_move(char board[BOARD_SIZE][BOARD_SIZE], int r, int c){ board[r][c]=' '; }

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[i][0]==player && board[i][1]==player && board[i][2]==player) return 1;
    for (int i=0;i<BOARD_SIZE;i++)
        if (board[0][i]==player && board[1][i]==player && board[2][i]==player) return 1;
    if ((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
        (board[0][2]==player && board[1][1]==player && board[2][0]==player)) return 1;
    return 0;
}
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) { return !moves_left(board); }
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (row<1||row>3||col<1||col>3) return 0;
    return board[row-1][col-1]==' ';
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    printf("\nScore - Player X: %d | Computer O: %d | Draws: %d\n", score.player, score.computer, score.draw);
    printf("========== TIC TAC TOE ==========\n");
    for (int i=0;i<BOARD_SIZE;i++){
        printf("\n");
        for (int j=0;j<BOARD_SIZE;j++){
            printf(" %c ", board[i][j]);
            if (j<BOARD_SIZE-1) printf("|");
        }
        if (i<BOARD_SIZE-1) printf("\n---+---+---");
    }
    printf("\n\n");
}

void input_difficulty() {
    while (1) {
        printf("\nSelect Difficulty Level:\n1. Human (Standard)\n2. God (Impossible to win)\nEnter your choice: ");
        if (scanf("%d", &difficulty)!=1) difficulty=1;
        if (difficulty==1||difficulty==2) break;
        printf("Invalid choice, enter 1 or 2.\n");
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
