#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    //define the node data structure that will make up each part of the linked list, using the prototype struct node to enable it first
    typedef struct node
    {
        //first block of a linked list is a number/a value
        int number;

        //the next block is a pointer to the next block of "node" type, hence we
        struct node *next;
    }
    node;

    //create a node pointer called list that points to the address NULL
    node * list = NULL;

    //create a node called n and point it to the memory assigned that is the size of node
    node * n = malloc(sizeof(node));

    //If the node pointer "n" isn't NULL, then...
    if (n == NULL)
    {
        return 1;
    }

    //Dereference the pointer n, to change the value that it points to, too...
    (*n).number = 1;
    (*n).next = NULL;

    //Set the node pointer list to be the same as node pointer n
    list = n;

    printf("%i\n", (*list).number);
    printf("%i\n", (*n).number);
    printf("52\n");
}