#include <stdio.h>
#include <stdlib.h>

void halves(int halving);

int iterations = 0;

int main(void)
{
    int *innum;

    innum = malloc(sizeof(int));

    printf("Number is: ");
    scanf("%i", innum);

    halves(*innum);

    printf("Answer is %i can halve %i times before it reaches 1\n", *innum, iterations);

    free(innum);
}

void halves(int halving)
{
    if (halving == 1)
    {
        return;
    }
    else
    {
        iterations++;
        printf("value is: %i\n", halving);
        halves(halving / 2);
    }
}
