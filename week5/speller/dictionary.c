// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int wordcount = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Make the table of pointers of array length N
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //initialise bucket
    int bucket = 0;

    // hash to word to a bucket number
    bucket = hash(word);

    //for handling small dicts
    if (table[bucket] == NULL)
    {
        return false;
    }

    //Create a pointer to act as a cursor that will tell us where we are in a linked list
    node * cursor = NULL;

    //search for word in the bucket number that has results in
    //the linked list with the word possibly in, the first value
    cursor = table[bucket];

    //compares strings without looking at case, if = 0 then the word matches, if not this specific node does not have a matching word
    if(strcasecmp(word, cursor->word) == 0)
    {
        //printf("String found!\n");
        return true;
    }
    else
    {
        //printf("String not found!\n");
    }


    //Change the cursor to the next node in the linked list
    while(cursor != NULL)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            //printf("String found!\n");
            return true;
        }
        else
        {
            //printf("String not found! Moving to next\n");
            cursor = cursor -> next;
        }
    }


    /*
    int wordsum1 = 0;
    int wordsum2 = 0;
    while(cursor -> next != NULL)
    {
        wordsum1 = 0;
        wordsum2 = 0;

        for (int i = 0; i <= strlen(word); i++)
        {
            wordsum1 += toupper(word[i]);
        }
        for (int i = 0; i <= strlen(cursor->word); i++)
        {
            wordsum2 += toupper(cursor->word[i]);
        }
        if(wordsum1 == wordsum2)
        {
            printf("It matches!");
            return true;
        }
        else
        {
            //printf("No match...");
            cursor = cursor -> next;
        }
    }
    */

    //printf("Not found!\n");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //initialise wordsum and set it to start at 0!
    int wordsum = 0;

    //Find a way to split all words into buckets, using a function that ignores apostrophes and capitalisation
    //Can do this by adding up all the ascii values, this would give a unique identifier for each word???
    for (int i = 0; i <= strlen(word); i++)
    {
        wordsum += toupper(word[i]);
    }

    //this won't be ordered but will split all the values. It should mean even if a specific letter has more entries it won't be unbalanced??? Unless weighted towards a remainder number somehow
    wordsum = wordsum % N;
    //printf ("hash returns %i\n", wordsum);

    return wordsum;
}

// Loads dictionary into memory, returning true if successful, else false. This needs to record all the data in a hash table format
bool load(const char *dictionary)
{
    // Opens the file itself to be able to transcribe it
    FILE *dict_input = fopen(dictionary, "r");
    if (dict_input == NULL)
    {
        return false;
    }

    //We need to read a word from the dictionary, then run said word through a hash function to find which bucket it belongs in.
    //Then we need to append it to the end of the linked list in the bucket it belongs in

    //To read a word, read each letter until we hit the end of a word, then record this array of characters using a hash function
    char tmpword[LENGTH+1];

    int count = 0;

    //Initialise the bucket variable
    int bucket;

    /*
    //Read a single letter until we reach a new line
    for (int i = 0; i <= LENGTH+1; i++)
        {
            tmpword[i] = 0;
        }
    */

    //reads along and allocates each character that it reads to the array tmpword, until it hits a new line. When it hits a new line it needs to run the hash function...
    //...allocate this word to a bucket, and then add that word to the end of the linked list in that bucket
    while(fscanf(dict_input, "%s", tmpword) != EOF)
    {
        //Create the node for the table pointer to link to, need to allocate memory for this
        node * newnode = malloc(sizeof(node));

        if (newnode == NULL)
        {
            return false;
        }
            /*
            //print the word
            printf("Word is:");
            for (int i = 0; i <= LENGTH+1; i++)
            {
                printf("%c", tmpword[i]);
            }
            printf("\n");
            */

            //Run the hash function, allocate this word to a bucket,  link this to the end of the buckets linked list
            bucket = hash(tmpword);
            //printf("Hash function success, put in bucket %i\n", bucket);

            //Set the node word as the tmpword, and set the next pointer as null for now
            strcpy(newnode->word, tmpword);
            newnode->next = NULL;

            //If there is nothing in the bucket already, create a new linked list for that bucket
            if (table[bucket] == NULL)
            {
                table[bucket] = newnode;
            }
            else
            {
                newnode->next = table[bucket];
                table[bucket] = newnode;
            }

            //Set count to 0 and reset tmpword array to not contain the letters that were added previously
            /*
            count = 0;
            for (int i = 0; i <= LENGTH+1; i++)
            {
                tmpword[i] = 0;
            }
            printf("New word! Count and tmpword reset!\n");
            */
            wordcount++;
            //printf("Word count is now: %i\n", wordcount);



        //printf("%c added to array\n", tmpword[count]);
        //printf("%i\n", count);
    }

    fclose(dict_input);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    node * cursor = NULL;
    node * tmp = NULL;
    int N_cleared = 0;
    // TODO
    for (int i = 0; i < N ; i++)
    {

        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        N_cleared++;

    }

    if (N_cleared == N)
    {
        return true;
    }


    return false;
}