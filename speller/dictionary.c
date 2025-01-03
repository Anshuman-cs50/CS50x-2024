// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// O(N/676) < O(N/26)
const unsigned int N = 676;

// Hash table
node *table[N];

unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get the index of the word in the hash table
    unsigned int index = hash(word);

    // set a cursor node pointer
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (strlen(word) < 2)
    {
        return (unsigned int) (tolower(word[0]) - 'a');
    }

    unsigned char char1 = tolower(word[0]);
    unsigned char char2 = tolower(word[1]);

    return (unsigned int) ((((char1 - 'a') * 26) + (char2 - 'a')) % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // 1. open a dictionary file
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        printf("Not enough memory to load dictionary.");
        return false;
    }
    // 2. read strings one at a time
    char word[LENGTH + 1];

    //. while (fscanf(_) != EOF):
    while ((fscanf(dict, "%s", word)) != EOF)
    {
        // 3. create a new node for each word
        // use malloc to allocate memory for each node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            // check for null. return false
            fclose(dict);
            return false;
        }

        // use strcpy to copy the word to node

        strcpy(n->word, word);
        word_count++;

        // 4. hash word to obtain a hash value
        //. use hash function to return an index inside a hash function
        int index = hash(word);

        // 5. insert node into hash table at that location
        //. point the new node's pointer to the existing node which the hash array is pointing to
        //and then the hash pointer to the new node
        n->next = table[index];
        table[index] = n;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    node *temp = NULL;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;

            free(temp);
        }

        table[i] = NULL;
    }
    return true;
}
