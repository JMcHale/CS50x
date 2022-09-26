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
    node *list = NULL;

    //create a node called n and point it to the memory assigned that is the size of node
    node *n = malloc(sizeof(node));

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

    /*
    list / n.number
           n.next
    */

    //create a node called n and point it to the memory assigned that is the size of node
    n = malloc(sizeof(node));

    //If the node pointer "n" isn't NULL, then...
    if (n == NULL)
    {
        //Since this isn't the first entry, if the program fails we need to unallocate the list malloc memory
        free(list);
        return 1;
    }

    //Dereference the pointer n, to change the value that it points to, too...
    (*n).number = 2;
    (*n).next = NULL;

    //Set the value of the n.next part of what the list pointer points to, to the pointer n
    (*list).next = n;

    /*
    list / n.number
           n.next  ---->   n.number
                                n.next
    */

    //create a node called n and point it to the memory assigned that is the size of node
    n = malloc(sizeof(node));

    //If the node pointer "n" isn't NULL, then...
    if (n == NULL)
    {
        //since it's now the third run in the list, we have to free the node pointer that the node pointer list points to
        free((*list).next);
        free(list);
        return 1;
    }

    //Set the value that node pointer n points to, to 3
    (*n).number = 3;
    (*n).next = NULL;

    //Set the value of what the .next part of what list points to, and what that points to, to the pointer n
    list->next->next = n;

    /*
    list ---->  n.number
                n.next   ---->  n.number
                                n.next    ----> n.number
                                                n.next
    */

    //To print out a linked list, you can use a for loop, but the usual array won't work, as the memory is not adjacent to each other, instead... create a temp pointer to loop through, changing where it points as you loop through each point, can do this by setting the temp variable to the next pointer
    for(node * tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n" , tmp->number);
    }
    
    //when done we need to go through and free all the memory that we had left, allocated by malloc. We can use a for or while loop to do this, in a similar way to printing out
    while (list != NULL)
    {
        node * tmp = (*list).next;
        free(list);
        list = tmp;
    }
    
    //Return 0 if all runs well
    return 0;
}