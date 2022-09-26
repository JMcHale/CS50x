#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    char answer[20];
    printf("Enter name: ");
    scanf("%s", answer);
    printf("hello, %s\n", answer);

    char * pntans;
    printf("Enter other name: ");
    pntans = malloc(sizeof(scanf("%s", pntans)));

    free(pntans);
}
