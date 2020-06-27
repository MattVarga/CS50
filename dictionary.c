// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a hash node 
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Number of buckets in hash table
const unsigned int N = 65536;
node *table[N];
// Number of words in dictionary
int wordcount = 0; 
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}
// Loads dictionary into memory
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char c = fgetc(dict);
    char new_word[LENGTH + 1];
    // loops through dictionary
    while (c != EOF)
    {
        for (int i = 0; i < LENGTH + 1; i++) 
        {
            if (c != '\n') 
            {
                new_word[i] = c;
                c = fgetc(dict);
            }
            else
            {
                new_word[i] = '\0';
                wordcount++;
                c = fgetc(dict);
                break;
            }
        }
        //new_word
        unsigned int hashnum = hash(new_word);
        node *newn = malloc(sizeof(node));
        strcpy(newn->word, new_word);
        newn->next = NULL;
        // Adding to hashtable
        if (table[hashnum] == NULL)
        {
            table[hashnum] = newn;
        }
        else
        {
            newn->next = table[hashnum];
            table[hashnum] = newn;
        }
    }
    fclose(dict);
    return true;
}

// Returns true if word is in dictionary
bool check(const char *word)
{
    // Copies "word" to "input", then lowercases "input"
    int length = strlen(word);
    char input[length];
    strcpy(input, word);
    for (int i = 0; i < length; i++)
    {
        input[i] = tolower(input[i]);
    }
    // Hashes input word
    unsigned int hashnum = hash(input);
    // Checks for input word in hash table
    bool found = false;
    for (node *tmp = table[hashnum]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(tmp->word, input) == 0)
        {
            found = true;
            break;
        }
    }
    return found;
}
// Returns num of words in dictionary 
unsigned int size(void)
{
    return wordcount;
}
// Unloads dictionary
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *next = NULL;

        while (tmp != NULL)
        {
            next = tmp->next;
            free(tmp);
            tmp = next;
        }
        table[i] = NULL;
    }
    return true;
}