// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Variable for load to pass to size (word count)
static unsigned int WORDS_LOADED = 0;

bool compare(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (!(tolower(a[i]) == tolower(b[i])))
        {
            return false;
        }
        i++;
    }
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find where word would belong
    unsigned int place = hash(word) % N;

    // Traverse the linked list
    node *trav = table[place];
    while (trav != NULL)
    {
        if (compare(trav->word, word))
        {
            return true;
        }
        trav = trav->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // Read strings from file one at a time
    char word[LENGTH + 1];

    while (fscanf(source, "%s", word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        unsigned int place = hash(n->word) % N;
        n->next = table[place];
        table[place] = n;

        WORDS_LOADED++;
    }

    // Hash the word

    // insert node into hash table
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Already counted by load so just return updated value
    return WORDS_LOADED;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse the linked list and have a tmp pointer on the next node
    for (unsigned int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav->next;
            free(trav);
            trav = tmp;
        }
    }
    return true;
}

