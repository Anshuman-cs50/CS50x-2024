#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int validate(string k);
int encypher(string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Validate
        if (validate(argv[1]))
        {
            // Encipher
            encypher(argv[1]);
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("usage: ./substitution key\n");
        return 1;
    }
}

int encypher(string key)
{
    // Plain text
    string plain_text = get_string("plaintext: ");

    // Conversion
    int len = strlen(plain_text);

    char cipher_text[len];

    for (int i = 0; i < len; i++)
    {
        if (plain_text[i] >= 'A' && plain_text[i] <= 'Z')
        {
            cipher_text[i] = toupper(key[(plain_text[i] - 65)]);
        }
        else if (plain_text[i] >= 'a' && plain_text[i] <= 'z')
        {
            cipher_text[i] = tolower(key[(plain_text[i] - 97)]);
        }
        else
        {
            cipher_text[i] = plain_text[i];
        }
    }
    cipher_text[len] = '\0';

    // Cypher text output
    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

int validate(string k)
{
    int l = strlen(k);

    if (l == 26)
    {
        for (int i = 0; i < l; i++)
        {
            if ((k[i] >= 'A' && k[i] <= 'Z') || (k[i] >= 'a' && k[i] <= 'z'))
            {
                for (int j = i + 1; j < l; j++)
                {
                    if (toupper(k[i]) == toupper(k[j]))
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 0;
                    }
                }
            }
            else
            {
                printf("Key must only contain alphabetic characters.\n");
                return 0;
            }
        }
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }
    return 1;
}
