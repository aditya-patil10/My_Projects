#include <stdio.h>

int main()
{
    printf("\n<-------Chocolate Chilly Game------->\n");

    int n;

    printf("Enter the no. of chocolates: ");
    scanf("%d", &n);

    int Player = 1;

    while (n > 0)
    {
        printf("\nPlayer %d Turn\n", Player);

        int pick;

        printf("Pick chocolates (0 to 3): ");
        scanf("%d", &pick);

        if (pick < 0 || pick > 3)
        {
            printf("Invalid Input!!\n");
            continue;
        }

        if (pick > n)
        {
            printf("Not enough chocolates available!!\n");
            continue;
        }

        n = n - pick;

        printf("Chocolates Remaining : %d\n", n);

        if (n == 0)
        {
            printf("\nOnly Chilly remains!\n");
            printf("Player %d gets Chilly\n", Player);
            printf("Player %d LOST\n", Player);

            if (Player == 1)
                printf("Player 2 WON\n");
            else
                printf("Player 1 WON\n");

            break;
        }

        if (Player == 1)
            Player = 2;
        else
            Player = 1;
    }

    return 0;
}