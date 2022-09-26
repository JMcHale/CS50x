#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int bob = 5;

    //initialise pointer val to the address of bob
    int * val = &bob;
    printf("%i\n", *val);

    //set the value of the dereference of pointer val, to 10
    *val = 10;
    printf("%i\n", *val);
    printf("%i\n", bob);

    //create another variable for the pointer val to point to, this means we can swap simply by changing what val points to. Nothing else in the code has to change!
    int jen = 7;

    val = &jen;
    printf("%i\n", *val);

    //Create a char pointer variable, pointing at the first letter of memory size 4
    char * text = malloc(4);

    //We can then set "text" to the array of characters, wet
    text = "wet";

    //We can print this as a string
    printf("%s\n", text);

    //Or we can print the characters of the array directly
    printf("%c\n", *text);
    printf("%c\n", *(text+1));

}