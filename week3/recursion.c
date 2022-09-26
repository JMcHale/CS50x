#include <stdio.h>

int fact (int n);

int main(void)
{
    int number = 0;

    printf("Number: ");
    scanf("%i", &number);
    printf("\n");

    printf("Factorial is: %i\n", fact(number));


}


//function to calculate the factorial of a given number
int fact(int n)
{
    int answer = 0;
    //You ALWAYS need a base case
    if (n == 1)
        return 1;
    else
        return n * fact(n-1);
    //start with the actual function, in this case, n * (n-1)! is the factorial calc, where (n-1)! is the factorial of n-1
    //This means using a function in a function, recursion
    
    //input is 5, so function says 5 * 4!, then inputs this to next function. so 5 * 4 * 3!, and so on until the answer is reached.
}