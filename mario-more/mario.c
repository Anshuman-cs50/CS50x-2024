#include <cs50.h>
#include <stdio.h>

int main()
{
    int height;
    // prompt the user for a positive integer input
    do
    {
        height = get_int("Enter the height of the pyramids: ");
    }
    while (height < 1);

    for (int i = 1; i <= height; i++)
    {
        // Counting the spaces
        int spaces = height - i;

        // The first pyramid
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Two block gap between the pyramids
        printf("  ");

        // The second pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}
