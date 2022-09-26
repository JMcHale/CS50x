#include <stdio.h>
#include <math.h>

int main(void)
{
    char array[] = "bob";

    char *array2 = "bobby";

    printf("%s", array);

    printf("%s", array2);

    int max;

    int test1 = 27;
    int test2 = 28;
    int test3 = 28;

    max = round(((float)test1 + (float)test2 + (float)test3) / 3);

    printf("%i", max);
}