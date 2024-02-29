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

// TODO: Choose number of buckets in hash table
const unsigned int N = 17676; // 26 ** 2

// Hash table
node *table[N];

// Size of dictionary
int num = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int key = hash(word);
    node *current = table[key];
    while (current != NULL)
    {
        if (!strcasecmp(word, current->word))
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    if (strlen(word) > 2)
        return 676 * (toupper(word[0]) - 'A') + 26 * (toupper(word[1]) - 'A') + toupper(word[2]) - 'A';

    else if (strlen(word) > 1)
        return 26 * (toupper(word[0]) - 'A') + toupper(word[1]) - 'A';

    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary!");
        return false;
    }

    char current_word[sizeof(table[0]->word)];

    while (fscanf(dict, "%s", current_word) != EOF)
    {
        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            printf("Could not allocate memory for word!");
            return false;
        }

        strcpy(word_node->word, current_word);
        word_node->next = NULL;

        int key = hash(word_node->word);

        word_node->next = table[key];
        table[key] = word_node;

        num++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
