#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        printf("Command is : %s\n", argv[1]);
        //to access an array of arrays
        printf("First digit is: %c\n", argv[1][0]);
    }
    else
    {
        printf("Please input a single arguement.\n");
    }
}