#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add(int x, int y);

int main(int argc, char *argv[])
{
    int sum = 0;
    if (argc == 3)
    {
        sum = add(atoi(argv[1]), atoi(argv[2]));
        printf("Sum total is: %i\n", sum);
        return 0;
    }
    else
    {
        printf("Please use two integars");
        return 1;
    }
}

int add(int x, int y)
{
    return x + y;
}