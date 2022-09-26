#include <stdio.h>

int collatz(int n);

int main(void)
{
    int n = 0;
    int ans = 0;
    printf("Collatz of: ");
    scanf("%i", &n);
    ans = collatz(n);
    printf("It would take %i steps\n", ans);
}


int collatz(int n)
{

    if (n == 1)
    {
        //function wants to return 0 as the condition is already specified (collatz of 1 is 0)
        return 0;
    }
    
    //if n is even, we want to find the collatz of half of it
    else if(n % 2 == 0)
    {
        return 1 + collatz(n / 2);
    }
    
    //if n is odd, we want to find the collatz of it tripled, plus 1
    else
    {
        return 1 + collatz(3 * n + 1);
    }
}