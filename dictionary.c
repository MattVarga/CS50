// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char wordcheck[LENGTH + 1];

    strcpy(wordcheck, word);

    for (int i = 0; i < strlen(wordcheck); i++)
    {
        wordcheck[i] = tolower(wordcheck[i]);
    }

    int hashkey = hash(wordcheck);

    node *head = hashtable[hashkey];

    cursor = head;

    while (cursor != NULL)
    {
        if (strcasecmp(wordcheck, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    //if word is not in dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
     int hash = (tolower(word[0]) - 'a');
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    c   char word[LENGTH + 1];

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open Dictionary");
        return false;
    }

    /* -MAKE NEW WORD- use "fscanf" to scan through file(dictionary) for a string, put that string in the variable "word". Execute loop
    until end of dictionary file*/
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        new_node->next = NULL;
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        int hashvalue = hash(word);
        if (hashtable[hashvalue] == NULL)
        {
            hashtable[hashvalue] = new_node;
        }
        else
        {
            new_node->next = hashtable[hashvalue];
            hashtable[hashvalue] = new_node;
        }

        wordcount++;
    }
    fclose(dict);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
    }

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
     for (int i = 0, n = 26; i < n; i++)
    {
        cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
