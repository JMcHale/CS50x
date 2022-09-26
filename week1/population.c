#include <stdio.h>

int main(void)
{
    int startsize;
    int endsize;
    int currentsize;
    int years = 0;

    //Get start size input
    do
    {
        printf("Start Size: ");
        scanf("%i", &startsize);
    }
    while (startsize < 9);

    //Get end size input
    do
    {
        printf("End Size: ");
        scanf("%i", &endsize);
    }
    while (endsize < startsize);

    //Loop to go through years until the endsize is reached
    currentsize = startsize;
    if (endsize == startsize)
    {
        printf("Years: %i", years);
    }
    else
    {
        do
        {
            //Calculation for population in a given year
            currentsize = currentsize + currentsize / 3 - currentsize / 4;
            years++;
            //For visual debugging to see population in the current year/to see how the population grows
            printf("Pop is: %i\n", currentsize);
            printf("Year is: %i\n", years);


        }
        while (currentsize < endsize);
        printf("Years: %i", years);
    }
}