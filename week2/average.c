#include <stdio.h>

float sum_calc(int length, int array[]);

//script to calculate average of a number of values, any amount
int main (void)
{
    //First get total number of values
    int value_number;
    do
    {
        printf("Number of values: ");
        scanf("%i", &value_number);
    }
    while (value_number < 0);
    printf("There are %i values\n", value_number);

    //Then get user to input these values into an array the size of number of values
    int values[value_number];

    for (int i = 0; i < value_number; i++)
    {
        printf("Value %i: ", i + 1);
        scanf("%i", &values[i]);
    }

    //Check what is stored in the array
    printf("Array is: ");
    for (int i = 0; i < value_number; i++)
    {
        printf("%i, ", values[i]);
    }
    printf("\n");

    //Then run the average calculation (for an array)
    printf("Average is: %f\n", sum_calc(value_number, values) / value_number);

}


//Defining the SUM function
float sum_calc(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum;
}