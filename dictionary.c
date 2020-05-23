// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

//word count
unsigned int words = 0;

//result of diferent hashes
unsigned int index = 0;

//check if it's loaded
bool loaded = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //create a copy of the word
    char check_word[strlen(word)];
    strcpy(check_word, word);
    for (int i = 0; check_word[i] != '\0'; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }
    //hash the word
    index = hash(check_word);
    //find the word using the given index
    if (table[index] != NULL)
    {
        for (node *nodeptr = table[index]; nodeptr != NULL; nodeptr = nodeptr->next)
        {
            if (strcmp(nodeptr->word, check_word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //create variables
    int hash = 0;
    int w;
    //hash function from https://www.youtube.com/watch?v=ZEPDBlVFpso&t=800s
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            w = word[i] - 'a' + 1;
        }
        else
        {
            w = 27;
        }
        hash = ((hash << 3) + w) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open file
    FILE *dict_ptr = fopen(dictionary, "r");
    //check for a NULL pointer
    if (dict_ptr == NULL)
    {
        fprintf(stderr, "Couldn't open %s\n", dictionary);
        return false;
    }
    //making sure to format each table slot with NULL
    for (int i = 0; i < 26 ; i++)
    {
        table[i] = NULL;
    }
    //creating variables
    char *word = malloc((LENGTH + 1) * sizeof(char));
    node *new_node;
    //adding each new word to the table
    while (fscanf(dict_ptr, "%s", word) == 1)
    {
        //counting words
        words++;
        //creating a new node for the word
        new_node = malloc(sizeof(node));
        //copying the new word to the new node
        strcpy(new_node->word, word);
        //hashing the word
        index = hash(word);
        //adding the note to the first item of the linked list table
        new_node->next = table[index];
        table[index] = new_node;
 
    }
    //freeing and closing
    free(word);
    fclose(dict_ptr);
    //couldn't use the variable you guys created so created this one myself just to use in the las 2 functions
    loaded = true;
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded == false)
    {
        return 0;
    }
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (loaded == false)
    {
        return 1;
    }
    //creating two new pointers
    node *temp;
    node *pre;
    //iterating over the table to free the nodes
    for (int i = 0; i < N; i++)
    {   
        //checking if head is NULL
        while (table[i] != NULL)
        {
            //assigning temp to head
            temp = table[i];
            //moving the pointers to the last spot
            while (temp->next != NULL)
            {
                pre = temp;
                temp = temp->next;
            }
            //checking if temp reached the head
            if (temp == table[i])
            {
                table[i] = NULL;
            }
            //changing pointer
            else
            {
                pre->next = NULL;
            }
            //freeing temp
            free(temp);
        }
    }
    return true;
}
