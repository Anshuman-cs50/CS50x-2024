#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main()
{
    // Prompt the user for input
    string text = get_string("Text: ");

    // Count the number of letters, words, sentences
    int letters = 0, words = 0, sentences = 0;

    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        char j = text[i];
        if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            if (text[i + 1] == ' ')
            {
                sentences++;
            }
            // End of text
            if (i + 1 == len)
            {
                words++;
                sentences++;
            }
        }
        else if (i + 1 == len)
        {
            sentences++;
            words++;
        }
    }

    // Using Coleman-Liau index
    float L = ((float) letters / (float) words) * 100.0;
    float S = ((float) sentences / (float) words) * 100.0;

    float I = 0.0588 * L - 0.296 * S - 15.8;

    // Output of the level of the text
    if (((int) round(I)) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (I > 1 && I < 16)
    {
        printf("Grade %d\n", (int) round(I));
    }
    else
    {
        printf("Grade 16+\n");
    }

    return 0;
}
