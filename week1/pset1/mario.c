#include <stdio.h>

int valuecheck(int check);

int main(void)
{
    int height;
    int hashes = 2;
    int spaces;
    int n = 0;

    //Collect user input of height
    printf("Height: ");
    scanf("%i", &height);

    height = valuecheck(height);

    spaces = height - 1;

    //debug test if height has been recieved
    /*
    printf("Selected Height of %i\n", height);
    printf("Spaces starts at: %i\n", spaces);
    */

    //every increase in height has an increase of 2 #, 1 SPACE (before hashes),
    /*
    printf("  #  #\n");
    printf(" ##  ##\n");
    printf("###  ###\n");
    */

    //Loops to create ASCII image
    do
    {
        //Loop through each symbol to print it
        for (int x = 0; x < spaces; x++)
        {
            printf(" ");
        }
        for (int x = 0; x < hashes / 2; x++)
        {
            printf("#");
        }
        printf("  ");
        for (int x = 0; x < hashes / 2; x++)
        {
            printf("#");
        }
        /* debugging
        printf("Hashes are: %i\n", hashes);
        printf("Spaces are: %i\n", spaces);
        */
        printf("\n");
        hashes = hashes + 2;
        spaces--;
        n++;
    }
    while (n < height);
}


//checks if value input is valid
int valuecheck(int check)
{
    /*
    if (check <= 0){
        printf("Please input a positive value\n");
        return 0;

    }
    else if (check > 9){
        printf("Please input a value below 9\n");
        return 0;
    }
    return 1;
    */
    if (check > 0 && check < 9)
    {
        return check;
    }

    else
    {
        do
        {
            printf("Please input a positive value, less than 9\n");
            scanf("%i", &check);
        }
        while (check <= 0 || check > 9);
    }
    return check;
}