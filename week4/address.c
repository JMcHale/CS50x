#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int n = 50;

    //stores the address of n in the integer variable p, otherwise known as a pointer
    int *p = &n;

    //print the address of n, which is stored in p
    printf("%p\n", p);

    //print the VALUE of the address of n, so what is stored in where p is referencing
    printf("%i\n", *p);

    //Initilaise the variable s and store it's value in the address of s (this actually creates an "array" with the start address of where s is)
    char s[] = "hello!";

    //print the character that is stored in the address of s, in this case the first letter
    printf("%c\n", *s);
    //print the character that is after the first character of s
    printf("%c\n", *(s + 1));

    //To create a copy of the s string (this actually just copies the address)
    char *t = s;

    //then to change t we do
    t[0] = toupper(t[0]);


    printf("s is: %s\n", s);
    printf("Copy t of s is: %s\n", t);
    printf("address of s is: %p\n", s);
    printf("address of t is: %p\n", t);

    //To create one that doesn't change both values we have to take a copy that doens't have the same address
    char y[] = "goodbye!";

    //Allocate the memory that string z will need
    char *z = malloc(strlen(y) + 1);

    //then can copy in the string at any point, either with a for loop or strcpy
    strcpy(z, y);

    z[0] = toupper(z[0]);

    printf("y is: %s\n", y);
    printf("Copy z of y is: %s\n", z);
    printf("address of y is: %p\n", y);
    printf("address of z is: %p\n", z);

    //We should free up the memory used by malloc when it is no longer in use
    free(z);

    //doing a string as an array
    char name[] = {"Bobbyjohn"};

    //print the VALUE of name (strings are stored as an address, but C seems to convert it automatically
    printf("%s\n", name);

    //print the ADDRESS of name
    printf("%p\n", name);

}