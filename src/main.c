#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int difficulty;
Score score = {0, 0, 0};

int main()
{
    srand(time(NULL));
    int choice;

    input_difficulty();

    do
    {
        play_game();
        printf("Play again? (1 for YES / 0 for NO): ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("BYE BYE, Thanks for playing!!\n");
    return 0;
}
