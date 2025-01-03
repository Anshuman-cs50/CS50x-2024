#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int counter(string word);

int main()
{
    // Input prompt
    string phrase1 = get_string("Player 1: ");
    string phrase2 = get_string("Player 2: ");

    // Comparison
    int player1 = counter(phrase1);
    int player2 = counter(phrase2);

    // Print the winner
    if (player1 > player2)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2 > player1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int counter(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += points[(word[i] - 'A')];
        }
        else if (islower(word[i]))
        {
            score += points[(word[i] - 'a')];
        }
    }

    return score;
}
